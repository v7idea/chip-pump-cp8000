import argparse
import importlib
import os
import subprocess
import sys
from pathlib import Path

from . import __version__
from .capture import CaptureRequest, run_capture
from .protocol import (
    BootloaderSyncError,
    CP8000BootloaderProtocol,
    CP8xxxBinaryProtocol,
    PHY62xxTextProtocol,
    ProtocolNotImplementedError,
    UploadRequest,
    binary_command,
    binary_probe,
    dwc_probe,
)


def available_serial_ports() -> list[str]:
    try:
        from serial.tools import list_ports
    except ImportError:
        return []
    return [port.device for port in list_ports.comports()]


def print_pyserial_help(action: str) -> None:
    print(f"cp8000-uploader: pyserial is required for {action}", file=sys.stderr)
    print("Install it for the Python used by the uploader:", file=sys.stderr)
    print("  Windows: py -3 -m pip install pyserial", file=sys.stderr)
    print("  macOS/Linux: python3 -m pip install pyserial", file=sys.stderr)
    print("Then retry the Arduino upload.", file=sys.stderr)


def ensure_pyserial(action: str) -> bool:
    try:
        importlib.import_module("serial")
        return True
    except ImportError:
        pass

    if os.environ.get("CP8000_UPLOADER_AUTO_INSTALL", "1").lower() in ("0", "false", "no"):
        print_pyserial_help(action)
        return False

    print(f"cp8000-uploader: pyserial is missing; installing it for {action}...", file=sys.stderr)
    command = [
        sys.executable,
        "-m",
        "pip",
        "install",
        "--user",
        "--disable-pip-version-check",
        "--no-input",
        "pyserial>=3.5",
    ]
    try:
        subprocess.check_call(command)
    except Exception as exc:
        print(f"cp8000-uploader: automatic pyserial install failed: {exc}", file=sys.stderr)
        print_pyserial_help(action)
        return False

    importlib.invalidate_caches()
    try:
        importlib.import_module("serial")
    except ImportError:
        print("cp8000-uploader: pyserial installed, but Python still cannot import it.", file=sys.stderr)
        print("Restart Arduino IDE and retry the upload.", file=sys.stderr)
        return False

    print("cp8000-uploader: pyserial installed successfully; continuing.", file=sys.stderr)
    return True


def print_upload_reset_notice(args: argparse.Namespace) -> None:
    timeout = getattr(args, "connect_timeout", 20.0)
    port = getattr(args, "port", "")
    print("cp8000-uploader: upload is starting.", file=sys.stderr)
    if getattr(args, "app_reset_mode", "auto") == "disabled":
        print("cp8000-uploader: automatic reset is disabled; prepare to press Reset.", file=sys.stderr)
    else:
        print("cp8000-uploader: trying the running Core's software-reset handshake first.", file=sys.stderr)
    print(
        f"cp8000-uploader: waiting up to {timeout:.1f}s for bootloader on {port}.",
        file=sys.stderr,
    )


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        prog="cp8000-uploader",
        description="Command-line uploader for CHIP-PUMP CP8000 UART bootloader.",
    )
    parser.add_argument("--version", action="version", version=f"%(prog)s {__version__}")
    subparsers = parser.add_subparsers(dest="command", required=True)

    upload = subparsers.add_parser("upload", help="Upload a firmware image")
    upload.add_argument("--port", required=True, help="Serial port, for example COM3 or /dev/ttyUSB0")
    upload.add_argument("--target", choices=["flash", "otp", "ram"], required=True)
    upload.add_argument("--baud", default="default", help="Bootloader baud option; default follows vendor tool behavior")
    upload.add_argument("--address", default=None, help="Target base address, for example 0x10000000")
    upload.add_argument("--file", required=True, help="Firmware .bin file")
    upload.add_argument("--protocol", choices=["stub", "phy62xx-text", "cp8xxx-binary"], default="stub")
    upload.add_argument("--dwc-sequence", default="UXTDWU", help="Experimental DWC sequence for phy62xx-text default baud")
    upload.add_argument(
        "--connect-timeout",
        type=float,
        default=20.0,
        help="Seconds to keep probing for the bootloader before upload starts",
    )
    upload.add_argument(
        "--app-reset-mode",
        choices=["auto", "disabled", "required"],
        default="auto",
        help="Ask the running Arduino Core to reset before ROM bootloader sync; auto falls back to manual Reset",
    )
    upload.add_argument(
        "--app-reset-timeout",
        type=float,
        default=1.0,
        help="Seconds to wait for the running Arduino Core reset acknowledgement",
    )
    upload.add_argument(
        "--boot-reset-method",
        choices=["none", "pulse-dtr", "pulse-rts", "dtr-rts", "rts-dtr"],
        default="none",
        help="Optional pre-sync USB-UART DTR/RTS sequence for boards wired for auto boot entry",
    )
    upload.add_argument(
        "--entry-sync-mode",
        choices=["prelude-sync", "prelude-only", "sync-only"],
        default="prelude-sync",
        help="Initial ROM bootloader entry sequence; prelude-sync matches the validated vendor GUI flow",
    )
    upload.add_argument(
        "--reset-method",
        choices=["self-start", "none"],
        default="self-start",
        help="Post-upload reset/run strategy; self-start is experimental for CP8xxx flash",
    )
    upload.add_argument(
        "--run-address",
        default=None,
        help="Address passed to the experimental self-start command; defaults to vendor 0x20002000",
    )
    upload.add_argument(
        "--flash-write-mode",
        choices=["safe", "cached"],
        default="cached",
        help="Flash write strategy: safe reloads the RAM flash algorithm for every chunk; cached loads it once",
    )
    upload.add_argument("--dry-run", action="store_true", help="Validate arguments without opening the serial port")
    upload.add_argument("--verbose", action="store_true")
    upload.set_defaults(func=cmd_upload)

    ports = subparsers.add_parser("ports", help="List serial ports")
    ports.set_defaults(func=cmd_ports)

    probe = subparsers.add_parser("probe", help="Probe for a CP8000 bootloader")
    probe.add_argument("--port", required=True)
    probe.add_argument("--baud", default="default")
    probe.add_argument(
        "--dwc-sequence",
        default="both",
        help="DWC sequence to send at 9600 baud: UXTDWU, UXTL16, both, or comma-separated values",
    )
    probe.add_argument("--timeout", type=float, default=60.0, help="Probe duration in seconds")
    probe.add_argument("--verbose", action="store_true")
    probe.set_defaults(func=cmd_probe)

    binary = subparsers.add_parser("binary-probe", help="Probe for the CP8xxx binary UART bootloader")
    binary.add_argument("--port", required=True)
    binary.add_argument("--baud", default="115200", help="Baud or comma-separated baud list")
    binary.add_argument("--timeout-per-baud", type=float, default=10.0)
    binary.add_argument(
        "--boot-reset-method",
        choices=["none", "pulse-dtr", "pulse-rts", "dtr-rts", "rts-dtr"],
        default="none",
        help="Optional pre-sync USB-UART DTR/RTS sequence",
    )
    binary.add_argument(
        "--entry-sync-mode",
        choices=["prelude-sync", "prelude-only", "sync-only"],
        default="prelude-sync",
        help="Initial ROM bootloader entry sequence",
    )
    binary.add_argument("--verbose", action="store_true")
    binary.set_defaults(func=cmd_binary_probe)

    binary_command_parser = subparsers.add_parser(
        "binary-command",
        help="Send one CP8xxx binary packet and decode the response",
    )
    binary_command_parser.add_argument("--port", required=True)
    binary_command_parser.add_argument("--baud", type=int, default=115200)
    binary_command_parser.add_argument("--command", required=True, help="Command value, for example 0x00ee")
    binary_command_parser.add_argument("--payload-hex", default="", help="Payload bytes as hex")
    binary_command_parser.add_argument("--read-timeout", type=float, default=1.0)
    binary_command_parser.add_argument("--pre-sync", action="store_true", help="Send CP8xxx sync before the command")
    binary_command_parser.add_argument("--verbose", action="store_true")
    binary_command_parser.set_defaults(func=cmd_binary_command)

    capture = subparsers.add_parser("capture", help="Capture raw serial traffic for protocol analysis")
    capture.add_argument("--port", required=True)
    capture.add_argument("--baud", type=int, default=115200)
    capture.add_argument("--output", help="Raw binary output path; stdout prints timestamped hex when omitted")
    capture.add_argument("--duration", type=float, help="Capture duration in seconds; omit to run until Ctrl-C")
    capture.add_argument("--verbose", action="store_true")
    capture.set_defaults(func=cmd_capture)

    return parser


def cmd_upload(args: argparse.Namespace) -> int:
    firmware = Path(args.file)
    if not firmware.is_file():
        print(f"error: firmware file not found: {firmware}", file=sys.stderr)
        return 2

    if args.dry_run:
        print("cp8000-uploader: dry run ok")
        print(f"port={args.port}")
        print(f"target={args.target}")
        print(f"baud={args.baud}")
        print(f"protocol={args.protocol}")
        print(f"dwc_sequence={args.dwc_sequence}")
        print(f"connect_timeout={args.connect_timeout}")
        print(f"app_reset_mode={args.app_reset_mode}")
        print(f"app_reset_timeout={args.app_reset_timeout}")
        print(f"boot_reset_method={args.boot_reset_method}")
        print(f"entry_sync_mode={args.entry_sync_mode}")
        print(f"reset_method={args.reset_method}")
        print(f"run_address={args.run_address or '0x20002000'}")
        print(f"flash_write_mode={args.flash_write_mode}")
        print(f"address={args.address or target_default_address(args.target)}")
        print(f"file={firmware}")
        print(f"size={firmware.stat().st_size}")
        return 0

    print_upload_reset_notice(args)

    if not ensure_pyserial("upload"):
        return 2

    request = UploadRequest(
        port=args.port,
        target=args.target,
        baud=args.baud,
        address=parse_address(args.address or target_default_address(args.target)),
        firmware=firmware,
        protocol=args.protocol,
        dwc_sequence=args.dwc_sequence,
        connect_timeout=args.connect_timeout,
        app_reset_mode=args.app_reset_mode,
        app_reset_timeout=args.app_reset_timeout,
        boot_reset_method=args.boot_reset_method,
        entry_sync_mode=args.entry_sync_mode,
        reset_method=args.reset_method,
        run_address=parse_address(args.run_address) if args.run_address else None,
        flash_write_mode=args.flash_write_mode,
        verbose=args.verbose,
    )

    try:
        make_protocol(request).upload()
    except ProtocolNotImplementedError as exc:
        print(f"cp8000-uploader: {exc}", file=sys.stderr)
        print("next step: implement UART bootloader wire format from vendor docs or capture", file=sys.stderr)
        return 78
    except BootloaderSyncError as exc:
        print(f"cp8000-uploader: {exc}", file=sys.stderr)
        return 1
    except TimeoutError as exc:
        print(f"cp8000-uploader: {exc}", file=sys.stderr)
        return 1
    except RuntimeError as exc:
        if "pyserial is required" in str(exc):
            print_pyserial_help("upload")
            return 2
        raise
    except Exception as exc:
        if exc.__class__.__name__ == "SerialException":
            print(f"cp8000-uploader: cannot open serial port {request.port}: {exc}", file=sys.stderr)
            ports = available_serial_ports()
            if ports:
                print("available serial ports:", file=sys.stderr)
                for port in ports:
                    print(f"  {port}", file=sys.stderr)
            else:
                print("available serial ports: none", file=sys.stderr)
            print("next step: reconnect the USB-to-TTL adapter and select the active /dev/cu.* port in Arduino IDE.", file=sys.stderr)
            return 1
        raise

    return 0


def make_protocol(request: UploadRequest):
    if request.protocol == "phy62xx-text":
        return PHY62xxTextProtocol(request)
    if request.protocol == "cp8xxx-binary":
        return CP8xxxBinaryProtocol(request)
    return CP8000BootloaderProtocol(request)


def cmd_ports(args: argparse.Namespace) -> int:
    del args
    if not ensure_pyserial("port listing"):
        return 2

    try:
        from serial.tools import list_ports
    except ImportError:
        print_pyserial_help("port listing")
        return 2

    found = False
    for port in list_ports.comports():
        found = True
        description = port.description or ""
        hwid = port.hwid or ""
        print(f"{port.device}\t{description}\t{hwid}")

    if not found:
        print("no serial ports found", file=sys.stderr)
    return 0


def cmd_probe(args: argparse.Namespace) -> int:
    if not ensure_pyserial("probe"):
        return 2

    if args.baud != "default":
        print("error: DWC probe currently supports --baud default only", file=sys.stderr)
        return 2

    sequences = parse_dwc_sequences(args.dwc_sequence)
    print(f"cp8000-uploader: probing {args.port} at 9600 baud for {args.timeout:.1f}s")
    print(f"cp8000-uploader: sequences={','.join(sequences)}; reset or power-cycle the target now")

    result = dwc_probe(args.port, sequences=sequences, timeout=args.timeout, verbose=args.verbose)
    if result.matched:
        print(f"cp8000-uploader: matched {result.sequence}; bootloader prompt found")
        print(f"cp8000-uploader: received {len(result.data)} bytes")
        return 0

    print("cp8000-uploader: no bootloader prompt found", file=sys.stderr)
    print(f"cp8000-uploader: received {len(result.data)} bytes", file=sys.stderr)
    if args.verbose and result.data:
        print(f"cp8000-uploader: tail={result.data[-256:]!r}", file=sys.stderr)
    return 1


def cmd_binary_probe(args: argparse.Namespace) -> int:
    if not ensure_pyserial("binary probe"):
        return 2

    bauds = parse_baud_list(args.baud)
    print(f"cp8000-uploader: probing {args.port} with CP8xxx binary sync")
    print(f"cp8000-uploader: bauds={','.join(str(baud) for baud in bauds)}; reset or power-cycle the target now")

    result = binary_probe(
        args.port,
        bauds=bauds,
        timeout_per_baud=args.timeout_per_baud,
        verbose=args.verbose,
        boot_reset_method=args.boot_reset_method,
        entry_sync_mode=args.entry_sync_mode,
    )
    if result.matched:
        print(f"cp8000-uploader: CP8xxx binary bootloader ACK found at {result.baud} baud")
        print(f"cp8000-uploader: received {len(result.data)} bytes: {result.data.hex()}")
        return 0

    print("cp8000-uploader: no CP8xxx binary bootloader ACK found", file=sys.stderr)
    print(f"cp8000-uploader: received {len(result.data)} bytes", file=sys.stderr)
    if args.verbose and result.data:
        print(f"cp8000-uploader: tail={result.data[-256:].hex()}", file=sys.stderr)
    return 1


def cmd_binary_command(args: argparse.Namespace) -> int:
    if not ensure_pyserial("binary command probing"):
        return 2

    command = parse_address(args.command)
    payload = parse_hex(args.payload_hex)
    result = binary_command(
        args.port,
        baud=args.baud,
        command=command,
        payload=payload,
        read_timeout=args.read_timeout,
        pre_sync=args.pre_sync,
        verbose=args.verbose,
    )

    encoded_size = 12 + len(payload)
    print(f"cp8000-uploader: TX command=0x{command:08x} payload={len(payload)} bytes packet={encoded_size} bytes")
    if args.pre_sync:
        print(f"cp8000-uploader: pre-sync RX {len(result.sync_response)} bytes: {result.sync_response.hex()}")
        print_packets(result.sync_packets, prefix="pre-sync")
    print(f"cp8000-uploader: RX {len(result.response)} bytes: {result.response.hex()}")
    if not result.packets:
        print("cp8000-uploader: no complete CP8xxx response packet decoded")
        return 1 if not result.response else 0

    print_packets(result.packets)
    return 0


def print_packets(packets, prefix: str = "packet") -> None:
    for index, packet in enumerate(packets):
        checksum = "ok" if packet.header_checksum_ok else "bad"
        print(
            "cp8000-uploader: "
            f"{prefix}[{index}] command=0x{packet.command:08x} "
            f"payload={len(packet.payload)} checksum={checksum} "
            f"raw={packet.raw.hex()}"
        )


def cmd_capture(args: argparse.Namespace) -> int:
    if not ensure_pyserial("serial capture"):
        return 2

    output = Path(args.output) if args.output else None
    request = CaptureRequest(
        port=args.port,
        baud=args.baud,
        output=output,
        duration=args.duration,
        verbose=args.verbose,
    )
    return run_capture(request)


def target_default_address(target: str) -> str:
    if target == "flash":
        return "0x10000000"
    if target == "otp":
        return "0x1F800000"
    if target == "ram":
        return "0x20000000"
    return "(unknown)"


def parse_address(value: str) -> int:
    try:
        return int(value, 0)
    except ValueError as exc:
        raise SystemExit(f"invalid address: {value}") from exc


def parse_dwc_sequences(value: str) -> list[str]:
    if value == "both":
        return ["UXTDWU", "UXTL16"]
    sequences = [item.strip() for item in value.split(",") if item.strip()]
    if not sequences:
        raise SystemExit("invalid DWC sequence list")
    return sequences


def parse_baud_list(value: str) -> list[int]:
    if value == "default":
        return [115200]
    bauds = [int(item.strip(), 0) for item in value.split(",") if item.strip()]
    if not bauds:
        raise SystemExit("invalid baud list")
    return bauds


def parse_hex(value: str) -> bytes:
    normalized = "".join(value.split())
    if normalized.startswith("0x"):
        normalized = normalized[2:]
    if not normalized:
        return b""
    try:
        return bytes.fromhex(normalized)
    except ValueError as exc:
        raise SystemExit(f"invalid hex payload: {value}") from exc


def main(argv=None) -> int:
    parser = build_parser()
    args = parser.parse_args(argv)
    return args.func(args)
