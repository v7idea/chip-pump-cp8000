from dataclasses import dataclass
from pathlib import Path
import struct
import sys
import time


class ProtocolNotImplementedError(RuntimeError):
    pass


class BootloaderSyncError(RuntimeError):
    pass


@dataclass(frozen=True)
class UploadRequest:
    port: str
    target: str
    baud: str
    address: int
    firmware: Path
    protocol: str = "stub"
    dwc_sequence: str = "UXTDWU"
    connect_timeout: float = 20.0
    boot_reset_method: str = "none"
    entry_sync_mode: str = "prelude-sync"
    reset_method: str = "self-start"
    run_address: int | None = None
    flash_write_mode: str = "safe"
    verbose: bool = False


@dataclass(frozen=True)
class DWCProbeResult:
    sequence: str
    matched: bool
    data: bytes


@dataclass(frozen=True)
class BinaryProbeResult:
    matched: bool
    baud: int
    data: bytes


@dataclass(frozen=True)
class BinaryCommandResult:
    command: int
    payload: bytes
    sync_response: bytes
    response: bytes
    sync_packets: list["CP8xxxDecodedPacket"]
    packets: list["CP8xxxDecodedPacket"]


@dataclass(frozen=True)
class CP8xxxDecodedPacket:
    command: int
    payload: bytes
    header_checksum: int
    header_checksum_ok: bool
    raw: bytes


@dataclass(frozen=True)
class CP8xxxPacket:
    command: int
    payload: bytes = b""
    magic: bytes = b"\xD4\xC3\xB2\xA1"

    def encode(self) -> bytes:
        return encode_cp8xxx_packet(self.command, self.payload, magic=self.magic)


def encode_cp8xxx_packet(
    command: int,
    payload: bytes = b"",
    *,
    length_field: int | None = None,
    magic: bytes = b"\xD4\xC3\xB2\xA1",
) -> bytes:
    """Encode a CP8xxx binary packet.

    Most packets use the payload size in the 16-bit length field. The vendor
    flasher's block-header packet uses a field value that names only part of
    the body, so keep the field override explicit.
    """
    if length_field is None:
        length_field = len(payload)
    if not 0 <= length_field <= 0xFFFF:
        raise ValueError(f"invalid CP8xxx length field: {length_field}")
    if not 0 <= command <= 0xFFFFFFFF:
        raise ValueError(f"invalid CP8xxx command: {command}")

    header = bytearray()
    header.extend(magic)
    header.extend(command.to_bytes(4, "little"))
    header.extend(length_field.to_bytes(2, "little"))
    header_sum = sum(header) & 0xFFFF
    header.extend(header_sum.to_bytes(2, "little"))
    return bytes(header) + payload


def byte_sum32(data: bytes) -> int:
    return sum(data) & 0xFFFFFFFF


def encode_cp8xxx_block_header(address: int, length_words: int) -> bytes:
    """Build the vendor flasher's firmware block header packet.

    Recovered from CP8xxx_Debug_Tool v1.2.0:
    command=0x001005ee, field=0x000a,
    body=sum(address||length_words)||address||length_words.

    Hardware probes show the device interprets this value as a 32-bit word
    count. A value of 0x100 requests/transfers 0x400 bytes.
    """
    if not 0 <= address <= 0xFFFFFFFF:
        raise ValueError(f"invalid block address: {address}")
    if not 0 <= length_words <= 0x400:
        raise ValueError(f"invalid block word count: {length_words}")

    address_bytes = address.to_bytes(4, "little")
    length_bytes = length_words.to_bytes(4, "little")
    body_checksum = byte_sum32(address_bytes + length_bytes)
    payload = body_checksum.to_bytes(4, "little") + address_bytes + length_bytes
    return encode_cp8xxx_packet(0x001005EE, payload, length_field=0x000A)


def encode_cp8xxx_data_packet(data: bytes) -> bytes:
    """Build a firmware data packet matching the vendor flasher.

    The 16-bit length field covers a 4-byte byte-sum followed by the data.
    """
    if len(data) > 0x400:
        raise ValueError(f"CP8xxx data packets are limited to 1024 bytes, got {len(data)}")

    payload = byte_sum32(data).to_bytes(4, "little") + data
    return encode_cp8xxx_packet(0x000001EE, payload)


def encode_cp8xxx_address_command(command: int, address: int = 0) -> bytes:
    """Build a state/address command used by the vendor flasher.

    The executable builds packets such as 0x040001ee, 0x050001ee, and
    0x060001ee with an 8-byte body: byte-sum(address)||address.
    """
    address_bytes = address.to_bytes(4, "little")
    payload = byte_sum32(address_bytes).to_bytes(4, "little") + address_bytes
    return encode_cp8xxx_packet(command, payload)


def encode_cp8xxx_address_data_command(command: int, address: int, data: bytes) -> bytes:
    """Build the vendor flasher's address+data packet variant.

    Recovered from CP8xxx_Debug_Tool v1.2.0 RAM/loader path:
    body is byte_sum32(address_le32 || data), address_le32, data. The GUI
    uses this with command values such as 0x040001ee when downloading code to
    RAM before self-start.
    """
    if not 0 <= address <= 0xFFFFFFFF:
        raise ValueError(f"invalid command address: {address}")
    if len(data) > 0x400:
        raise ValueError(f"CP8xxx address+data packets are limited to 1024 bytes, got {len(data)}")

    address_bytes = address.to_bytes(4, "little")
    payload = byte_sum32(address_bytes + data).to_bytes(4, "little") + address_bytes + data
    return encode_cp8xxx_packet(command, payload)


def encode_cp8xxx_value_address_command(command: int, address: int, value: int) -> bytes:
    """Build the vendor flasher's checksum/address command variant.

    The GUI has a 24-byte packet form for commands such as 0x050001ee:
    body is byte_sum32(address_le32 || value_le32), address_le32, value_le32.
    This is used in the observed CRC/finalization path.
    """
    address_bytes = address.to_bytes(4, "little")
    value_bytes = value.to_bytes(4, "little")
    payload = byte_sum32(address_bytes + value_bytes).to_bytes(4, "little") + address_bytes + value_bytes
    return encode_cp8xxx_packet(command, payload)


def build_cp8xxx_flash_packets(address: int, data: bytes, block_size: int = 0x400) -> list[bytes]:
    packets: list[bytes] = []
    offset = 0
    while offset < len(data):
        chunk = data[offset : offset + block_size]
        if len(chunk) % 4:
            chunk = chunk.ljust((len(chunk) + 3) & ~3, b"\xFF")
        packets.append(encode_cp8xxx_block_header(address + offset, len(chunk) // 4))
        packets.append(encode_cp8xxx_data_packet(chunk))
        offset += len(chunk)
    return packets


def decode_cp8xxx_packets(data: bytes) -> list[CP8xxxDecodedPacket]:
    packets: list[CP8xxxDecodedPacket] = []
    offset = 0
    magic = CP8xxxPacket.magic
    while offset + 12 <= len(data):
        start = data.find(magic, offset)
        if start < 0 or start + 12 > len(data):
            break
        header = data[start : start + 12]
        command = int.from_bytes(header[4:8], "little")
        length = int.from_bytes(header[8:10], "little")
        header_checksum = int.from_bytes(header[10:12], "little")
        end = start + 12 + length
        if end > len(data):
            break
        raw = data[start:end]
        payload = data[start + 12 : end]
        packets.append(
            CP8xxxDecodedPacket(
                command=command,
                payload=payload,
                header_checksum=header_checksum,
                header_checksum_ok=(sum(header[:10]) & 0xFFFF) == header_checksum,
                raw=raw,
            )
        )
        offset = end
    return packets


class CP8000BootloaderProtocol:
    """Protocol boundary for the CP8000 UART bootloader.

    The vendor documents say the chip enters programming mode when it receives
    a special UART command immediately after reset. The exact bytes are not in
    the current SDK bundle, so this class intentionally exposes the stages while
    leaving the wire format unimplemented.
    """

    def __init__(self, request: UploadRequest):
        self.request = request

    def connect(self) -> None:
        raise ProtocolNotImplementedError("bootloader connect handshake is not implemented")

    def erase(self) -> None:
        raise ProtocolNotImplementedError("flash erase command is not implemented")

    def write(self) -> None:
        raise ProtocolNotImplementedError("firmware write command is not implemented")

    def verify(self) -> None:
        raise ProtocolNotImplementedError("firmware verify command is not implemented")

    def reset(self) -> None:
        raise ProtocolNotImplementedError("reset/run command is not implemented")

    def upload(self) -> None:
        self.connect()
        if self.request.target in ("flash", "otp"):
            self.erase()
        self.write()
        self.verify()
        self.reset()


class PHY62xxTextProtocol:
    """Experimental text-command UART flash protocol.

    This implements the protocol described by the PHY62XX UART-to-FLASH Write
    Protocol PDF found in the local SDK folder. CP800X compatibility is not
    confirmed yet; keep this selectable until hardware proves it.
    """

    PROMPT = b"cmd>>:"
    OK = b"#OK>>:"

    def __init__(self, request: UploadRequest):
        self.request = request
        self.serial = None

    def _log(self, message: str) -> None:
        if self.request.verbose:
            print(f"phy62xx-text: {message}")

    def _open(self, baud: int):
        try:
            import serial
        except ImportError as exc:
            raise RuntimeError("pyserial is required for upload") from exc

        serial_port = open_serial_port(serial, self.request.port, baud, timeout=0.05)
        serial_port.reset_input_buffer()
        serial_port.reset_output_buffer()
        return serial_port

    def _read_until(self, marker: bytes, timeout: float = 5.0) -> bytes:
        deadline = time.monotonic() + timeout
        data = bytearray()
        while time.monotonic() < deadline:
            chunk = self.serial.read(128)
            if chunk:
                data.extend(chunk)
                if marker in data:
                    return bytes(data)
        raise TimeoutError(f"timed out waiting for {marker!r}; received {bytes(data)!r}")

    def _enter_dwc(self, sequence: bytes, timeout: float = 20.0) -> bytes:
        deadline = time.monotonic() + timeout
        data = bytearray()
        while time.monotonic() < deadline:
            self.serial.write(sequence)
            self.serial.flush()
            chunk = self.serial.read(128)
            if chunk:
                data.extend(chunk)
                if self.PROMPT in data:
                    return bytes(data)
            time.sleep(0.03)
        raise TimeoutError(f"timed out waiting for {self.PROMPT!r}; received {bytes(data)!r}")

    def _command(self, command: str, marker: bytes = OK, timeout: float = 5.0) -> bytes:
        self._log(f"> {command}")
        self.serial.write(command.encode("ascii") + b"\r\n")
        self.serial.flush()
        data = self._read_until(marker, timeout)
        self._log(f"< {data!r}")
        return data

    def connect(self) -> None:
        baud = parse_baud(self.request.baud)
        if baud is not None:
            self.serial = self._open(baud)
            self._read_until(self.PROMPT, 2.0)
            return

        self._log(f"sending DWC sequence {self.request.dwc_sequence!r} at 9600 baud")
        self.serial = self._open(9600)
        seq = self.request.dwc_sequence.encode("ascii")
        data = self._enter_dwc(seq)
        self._log(f"< {data!r}")
        self._command("uarts 115200")
        self.serial.close()
        time.sleep(0.2)
        self.serial = self._open(115200)

    def erase(self) -> None:
        if self.request.target != "flash":
            raise ProtocolNotImplementedError("phy62xx-text currently supports flash target only")
        self._command("er512", timeout=20.0)

    def write(self) -> None:
        data = self.request.firmware.read_bytes()
        checksum = sum(data) & 0xFFFFFFFF
        address = self.request.address
        size = len(data)
        run_address = address

        self._command("cpnum 1")
        self._command(
            f"cpbin 0 {address:08X} {size:X} {run_address:08X}",
            marker=b"by hex mode:",
            timeout=5.0,
        )
        self.serial.write(data)
        self.serial.flush()
        self._read_until(b"checksum is:", timeout=30.0)
        self._command(f"0x{checksum:08X}", timeout=10.0)

    def verify(self) -> None:
        return

    def reset(self) -> None:
        self._command("reset", marker=self.PROMPT, timeout=5.0)

    def upload(self) -> None:
        try:
            self.connect()
            if self.request.target in ("flash", "otp"):
                self.erase()
            self.write()
            self.verify()
            self.reset()
        finally:
            if self.serial:
                self.serial.close()


class CP8xxxBinaryProtocol:
    """Experimental CP8xxx binary UART protocol.

    The packet header was recovered from the vendor CP8xxx Debug Tool v1.2.0
    and confirmed on hardware: command 0xEE with an empty payload receives an
    empty 0xEF response.
    """

    SYNC = CP8xxxPacket(0xEE)
    VENDOR_CONNECT_PREAMBLE = bytes.fromhex(
        "D4C3B2A1EE0600000E00EC039F00000024010840130000001F00"
    )
    ACK_MAGIC = b"\xD4\xC3\xB2\xA1\xEF"
    FLASH_CRC_ADDRESS = 0x1003E000
    FLASH_FINALIZE_ADDRESS = 0x1003F000
    FLASH_ERASE_BLOCKS = 0x40
    OTP_CRC_ADDRESS = 0x1F803EF0
    VENDOR_SELF_START_ADDRESS = 0x20002000
    FLASH_ALGORITHM_ADDRESS = 0x20000000
    FLASH_ERASE_STUB_ADDRESS = 0x20002000
    FLASH_PROGRAM_STUB_ADDRESS = 0x20002000
    FLASH_PROGRAM_BUFFER_ADDRESS = 0x20001000
    FLASH_PROGRAM_CONTROL_ADDRESS = 0x20003700
    FLASH_ERASE_STUB = bytes.fromhex(
        "611106c222c0a147370400405cc0b7070020938767248297b70700209387"
        "6732b705040037050010829785471cc473005010f5bf"
    )
    FLASH_PROGRAM_STUB = bytes.fromhex(
        "611106c222c0a147370400405cc0b7070020938767248297b73700209387"
        "07708843d043b715002093874580829785471cc473005010f5bf"
    )

    def __init__(self, request: UploadRequest):
        self.request = request
        self.serial = None
        self._firmware_data: bytes | None = None
        self._upload_started_at: float | None = None

    def _log(self, message: str) -> None:
        if self.request.verbose:
            print(f"cp8xxx-binary: {message}")

    def _timed(self, label: str, func, *args, **kwargs):
        started_at = time.monotonic()
        try:
            return func(*args, **kwargs)
        finally:
            self._log(f"timing {label} {time.monotonic() - started_at:.2f}s")

    def _open(self, baud: int):
        try:
            import serial
        except ImportError as exc:
            raise RuntimeError("pyserial is required for upload") from exc

        return open_serial_port(serial, self.request.port, baud, timeout=0.05)

    def _read_packet(self, timeout: float) -> bytes:
        deadline = time.monotonic() + timeout
        data = bytearray()
        while time.monotonic() < deadline:
            chunk = self.serial.read(256)
            if chunk:
                data.extend(chunk)
                if self.ACK_MAGIC in data and len(data) >= 12:
                    return bytes(data)
            time.sleep(0.01)
        raise TimeoutError(f"timed out waiting for CP8xxx binary response; received {bytes(data).hex()}")

    def _read_response(self, timeout: float = 0.5) -> bytes:
        deadline = time.monotonic() + timeout
        data = bytearray()
        while time.monotonic() < deadline:
            chunk = self.serial.read(1024)
            if chunk:
                data.extend(chunk)
                if self.ACK_MAGIC in data and len(data) >= 12:
                    return bytes(data)
            time.sleep(0.005)
        if not data:
            raise TimeoutError("timed out waiting for CP8xxx binary response")
        return bytes(data)

    def _send(self, label: str, packet: bytes, timeout: float = 0.5) -> bytes:
        self._log(f"> {label}: {packet.hex()}")
        self.serial.reset_input_buffer()
        self.serial.write(packet)
        self.serial.flush()
        data = self._read_response(timeout)
        self._log(f"< {label}: {data[:128].hex()} ({len(data)} bytes)")
        return data

    def _sync(self, timeout: float) -> None:
        sync = self.SYNC.encode()
        deadline = time.monotonic() + timeout
        attempts = 0
        while time.monotonic() < deadline:
            attempts += 1
            self.serial.reset_input_buffer()
            self.serial.write(sync)
            self.serial.flush()
            try:
                data = self._read_packet(0.35)
            except TimeoutError:
                time.sleep(0.08)
                continue
            self._log(f"< sync attempt {attempts}: {data.hex()}")
            return

        raise BootloaderSyncError("no CP8xxx binary bootloader ACK after RAM flash helper")

    def _enter_bootloader(self, timeout: float) -> None:
        """Enter the ROM bootloader using the configured entry sequence.

        The default `prelude-sync` restores the hardware-validated flow from
        commit db48270: vendor long prelude, short delay, empty binary sync.
        `prelude-only` and `sync-only` are kept for A/B probing.
        """
        mode = (self.request.entry_sync_mode or "prelude-sync").lower()
        sync = self.SYNC.encode()
        deadline = time.monotonic() + timeout
        attempts = 0
        while time.monotonic() < deadline:
            attempts += 1
            self.serial.reset_input_buffer()
            if mode in ("prelude-sync", "prelude-only"):
                self.serial.write(self.VENDOR_CONNECT_PREAMBLE)
                self.serial.flush()
            if mode == "prelude-sync":
                time.sleep(0.02)
            if mode in ("prelude-sync", "sync-only"):
                self.serial.write(sync)
                self.serial.flush()
            if mode not in ("prelude-sync", "prelude-only", "sync-only"):
                raise ValueError(f"unknown entry sync mode: {mode}")
            try:
                data = self._read_packet(0.35)
            except TimeoutError:
                time.sleep(0.08)
                continue
            self._log(f"< entry {mode} attempt {attempts}: {data.hex()}")
            return

        raise BootloaderSyncError(f"no CP8xxx binary bootloader ACK after {mode} entry sequence")

    def _send_ram_data(self, address: int, data: bytes, label: str) -> None:
        offset = 0
        block_index = 0
        while offset < len(data):
            chunk = data[offset : offset + 0x400]
            block_address = address + offset
            packet = encode_cp8xxx_address_data_command(0x040001EE, block_address, chunk)
            for attempt in range(1, 4):
                try:
                    self._send(f"{label}[{block_index}]@0x{block_address:08x}", packet, timeout=2.5)
                    break
                except TimeoutError:
                    if attempt == 3:
                        raise
                    self._log(f"retrying {label}[{block_index}] after timeout")
                    time.sleep(0.1)
            offset += len(chunk)
            block_index += 1
        self._log(f"sent {block_index} {label} blocks, {offset} bytes")

    def _self_start(self, address: int, timeout: float = 1.0) -> None:
        self._send(
            f"self-start@0x{address:08x}",
            encode_cp8xxx_address_command(0x000004EE, address),
            timeout=timeout,
        )

    def _load_flash_algorithm(self) -> None:
        self._send_ram_data(self.FLASH_ALGORITHM_ADDRESS, load_cp8xxx_flash_algorithm(), "flash-algorithm")

    def connect(self) -> None:
        baud = parse_baud(self.request.baud) or 115200
        self.serial = self._open(baud)
        apply_serial_boot_reset(self.serial, self.request.boot_reset_method, self._log)
        timeout = max(0.5, self.request.connect_timeout)
        self._log(
            f"sending {self.request.entry_sync_mode} boot entry at {baud} baud "
            f"for up to {timeout:.1f}s"
        )
        try:
            self._enter_bootloader(timeout)
            print(
                "cp8000-uploader: bootloader ACK received; CP8000 is in bootloader mode.",
                file=sys.stderr,
            )
            time.sleep(0.25)
            return
        except BootloaderSyncError as exc:
            raise BootloaderSyncError(
                "no CP8xxx binary bootloader ACK; reset or power-cycle the target "
                "while upload is waiting"
            ) from exc

    def erase(self) -> None:
        if self.request.target != "flash":
            self._log(f"erase skipped for target {self.request.target}")
            return

        self._timed("erase-load-flash-algorithm", self._load_flash_algorithm)
        self._timed(
            "erase-load-stub",
            self._send_ram_data,
            self.FLASH_ERASE_STUB_ADDRESS,
            self.FLASH_ERASE_STUB,
            "flash-erase-stub",
        )
        self._timed("erase-self-start", self._self_start, self.FLASH_ERASE_STUB_ADDRESS)
        self._timed("erase-sync", self._sync, 20.0)

    def write(self) -> None:
        data = self.request.firmware.read_bytes()
        self._firmware_data = data
        if self.request.target not in ("flash", "ram"):
            raise ProtocolNotImplementedError("cp8xxx-binary currently supports flash/ram experimental writes only")

        if self.request.target == "ram":
            self._send_ram_data(self.request.address, data, "ram-data")
            return

        if self.request.flash_write_mode == "cached":
            self._write_flash_with_cached_ram_helper(data)
        else:
            self._write_flash_with_ram_helper(data)
        return

        self._send("enter-transfer", encode_cp8xxx_address_command(0x040001EE, 0), timeout=0.5)
        offset = 0
        block_index = 0
        while offset < len(data):
            chunk = data[offset : offset + 0x400]
            if len(chunk) % 4:
                chunk = chunk.ljust((len(chunk) + 3) & ~3, b"\xFF")
            address = self.request.address + offset
            self._send(
                f"block-header[{block_index}]@0x{address:08x}",
                encode_cp8xxx_block_header(address, len(chunk) // 4),
                timeout=1.2,
            )
            self._send(
                f"block-data[{block_index}]@0x{address:08x}",
                encode_cp8xxx_data_packet(chunk),
                timeout=1.2,
            )
            offset += len(chunk)
            block_index += 1
        self._log(f"sent {block_index} blocks, {offset} bytes")

    def _write_flash_with_ram_helper(self, data: bytes) -> None:
        offset = 0
        block_index = 0
        while offset < len(data):
            self._timed(f"load-flash-algorithm[{block_index}]", self._load_flash_algorithm)
            chunk = data[offset : offset + 0x400]
            self._program_flash_chunk(block_index, self.request.address + offset, chunk, reload_stub=True)
            offset += len(chunk)
            block_index += 1
        self._log(f"programmed {block_index} flash chunks, {offset} bytes")

    def _write_flash_with_cached_ram_helper(self, data: bytes) -> None:
        self._timed("cached-load-flash-algorithm", self._load_flash_algorithm)
        offset = 0
        block_index = 0
        while offset < len(data):
            chunk = data[offset : offset + 0x400]
            try:
                self._program_flash_chunk(block_index, self.request.address + offset, chunk, reload_stub=True)
            except TimeoutError:
                self._log(
                    f"cached write timed out at chunk {block_index}; "
                    "reloading flash algorithm and retrying chunk"
                )
                self._timed(f"cached-reload-flash-algorithm[{block_index}]", self._load_flash_algorithm)
                self._program_flash_chunk(block_index, self.request.address + offset, chunk, reload_stub=True)
            offset += len(chunk)
            block_index += 1
        self._log(f"programmed {block_index} flash chunks, {offset} bytes in cached mode")

    def _program_flash_chunk(self, block_index: int, flash_address: int, chunk: bytes, *, reload_stub: bool) -> None:
        control = flash_address.to_bytes(4, "little") + len(chunk).to_bytes(4, "little")
        self._timed(
            f"program-data[{block_index}]",
            self._send_ram_data,
            self.FLASH_PROGRAM_BUFFER_ADDRESS,
            chunk,
            f"program-data[{block_index}]",
        )
        self._timed(
            f"program-control[{block_index}]",
            self._send_ram_data,
            self.FLASH_PROGRAM_CONTROL_ADDRESS,
            control,
            f"program-control[{block_index}]",
        )
        if reload_stub:
            self._timed(
                f"program-stub[{block_index}]",
                self._send_ram_data,
                self.FLASH_PROGRAM_STUB_ADDRESS,
                self.FLASH_PROGRAM_STUB,
                f"program-stub[{block_index}]",
            )
        self._timed(f"program-self-start[{block_index}]", self._self_start, self.FLASH_PROGRAM_STUB_ADDRESS)
        self._timed(f"program-sync[{block_index}]", self._sync, 60.0)

    def verify(self) -> None:
        if self.request.target == "ram":
            self._log("RAM target does not use flash CRC finalization")
            return

        data = self._firmware_data if self._firmware_data is not None else self.request.firmware.read_bytes()
        checksum = byte_sum32(data)
        if self.request.target == "flash":
            command = 0x050001EE
            crc_address = self.FLASH_CRC_ADDRESS
        elif self.request.target == "otp":
            command = 0x060001EE
            crc_address = self.OTP_CRC_ADDRESS
        else:
            raise ProtocolNotImplementedError(f"cp8xxx-binary CRC is not implemented for target {self.request.target}")

        self._send(
            f"write-crc checksum=0x{checksum:08x}",
            encode_cp8xxx_value_address_command(command, crc_address, checksum),
            timeout=2.0,
        )
        if self.request.target == "flash":
            self._send(
                f"finalize-flash@0x{self.FLASH_FINALIZE_ADDRESS:08x}",
                encode_cp8xxx_address_command(command, self.FLASH_FINALIZE_ADDRESS),
                timeout=2.0,
            )

    def reset(self) -> None:
        if self.request.reset_method == "none":
            self._log("reset skipped by --reset-method none")
            return

        run_address = self.request.run_address
        if run_address is None:
            run_address = self.VENDOR_SELF_START_ADDRESS
        self._send(
            f"self-start@0x{run_address:08x}",
            encode_cp8xxx_address_command(0x000004EE, run_address),
            timeout=1.0,
        )

    def upload(self) -> None:
        self._upload_started_at = time.monotonic()
        try:
            self.connect()
            if self.request.target in ("flash", "otp"):
                self.erase()
            self.write()
            self.verify()
            self.reset()
        finally:
            if self._upload_started_at is not None:
                self._log(f"timing total-upload {time.monotonic() - self._upload_started_at:.2f}s")
            if self.serial:
                self.serial.close()


def parse_baud(value: str) -> int | None:
    if value == "default":
        return None
    return int(value, 0)


def load_cp8xxx_flash_algorithm() -> bytes:
    elf_path = find_cp8xxx_flash_algorithm()
    return extract_first_riscv_load_segment(elf_path)


def find_cp8xxx_flash_algorithm() -> Path:
    relative_paths = (
        Path("system/sdk/components/flash_algorithm/dl2flash_no_flash_pin_init.elf"),
        Path("arduino/hardware/chippump/cp8000/system/sdk/components/flash_algorithm/dl2flash_no_flash_pin_init.elf"),
    )
    start = Path(__file__).resolve()
    for parent in (start.parent, *start.parents):
        for relative_path in relative_paths:
            candidate = parent / relative_path
            if candidate.is_file():
                return candidate
    raise FileNotFoundError("dl2flash_no_flash_pin_init.elf not found in packaged CP8000 SDK")


def extract_first_riscv_load_segment(path: Path) -> bytes:
    data = path.read_bytes()
    if len(data) < 52 or data[:4] != b"\x7fELF":
        raise ValueError(f"not an ELF file: {path}")
    if data[4] != 1 or data[5] != 1:
        raise ValueError(f"expected 32-bit little-endian ELF: {path}")

    e_phoff = struct.unpack_from("<I", data, 28)[0]
    e_phentsize = struct.unpack_from("<H", data, 42)[0]
    e_phnum = struct.unpack_from("<H", data, 44)[0]
    for index in range(e_phnum):
        offset = e_phoff + index * e_phentsize
        if offset + 32 > len(data):
            break
        p_type, p_offset, _p_vaddr, _p_paddr, p_filesz, _p_memsz, _p_flags, _p_align = struct.unpack_from(
            "<IIIIIIII", data, offset
        )
        if p_type == 1 and p_filesz:
            return data[p_offset : p_offset + p_filesz]
    raise ValueError(f"no PT_LOAD segment found in {path}")


def open_serial_port(serial_module, port: str, baud: int, timeout: float):
    serial_port = serial_module.Serial(
        port,
        baud,
        timeout=timeout,
        write_timeout=2,
        rtscts=False,
        dsrdtr=False,
    )
    serial_port.dtr = False
    serial_port.rts = False
    time.sleep(0.05)
    return serial_port


def apply_serial_boot_reset(serial_port, method: str, log=None) -> None:
    """Try a USB-UART control-line sequence before bootloader sync.

    Many vendor flashers toggle DTR/RTS implicitly when connecting. Keep this
    opt-in because CP8000 boards do not all wire those control lines the same
    way.
    """
    method = (method or "none").lower()

    def set_lines(dtr: bool, rts: bool, delay: float) -> None:
        serial_port.dtr = dtr
        serial_port.rts = rts
        time.sleep(delay)

    if method == "none":
        return

    if log:
        log(f"applying boot reset method: {method}")

    if method == "pulse-dtr":
        set_lines(True, False, 0.12)
        set_lines(False, False, 0.25)
    elif method == "pulse-rts":
        set_lines(False, True, 0.12)
        set_lines(False, False, 0.25)
    elif method == "dtr-rts":
        set_lines(True, False, 0.08)
        set_lines(True, True, 0.12)
        set_lines(False, True, 0.08)
        set_lines(False, False, 0.25)
    elif method == "rts-dtr":
        set_lines(False, True, 0.08)
        set_lines(True, True, 0.12)
        set_lines(True, False, 0.08)
        set_lines(False, False, 0.25)
    else:
        raise ValueError(f"unknown boot reset method: {method}")

    try:
        serial_port.reset_input_buffer()
        serial_port.reset_output_buffer()
    except Exception:
        pass


def dwc_probe(port: str, sequences: list[str], timeout: float, verbose: bool = False) -> DWCProbeResult:
    try:
        import serial
    except ImportError as exc:
        raise RuntimeError("pyserial is required for probe") from exc

    deadline = time.monotonic() + timeout
    encoded = [(sequence, sequence.encode("ascii")) for sequence in sequences]
    data = bytearray()
    sent = 0

    with open_serial_port(serial, port, 9600, timeout=0.05) as ser:
        while time.monotonic() < deadline:
            for sequence, payload in encoded:
                ser.write(payload)
                ser.flush()
                sent += 1
                if verbose and sent % 50 == 0:
                    print(f"dwc-probe: sent {sent} sequences; last={sequence}; received={len(data)} bytes")

                chunk = ser.read(256)
                if chunk:
                    data.extend(chunk)
                    if PHY62xxTextProtocol.PROMPT in data:
                        return DWCProbeResult(sequence=sequence, matched=True, data=bytes(data))

                time.sleep(0.03)

    return DWCProbeResult(sequence=",".join(sequences), matched=False, data=bytes(data))


def binary_probe(
    port: str,
    bauds: list[int],
    timeout_per_baud: float,
    verbose: bool = False,
    boot_reset_method: str = "none",
    entry_sync_mode: str = "prelude-sync",
) -> BinaryProbeResult:
    try:
        import serial
    except ImportError as exc:
        raise RuntimeError("pyserial is required for probe") from exc

    preamble = CP8xxxBinaryProtocol.VENDOR_CONNECT_PREAMBLE
    sync = CP8xxxBinaryProtocol.SYNC.encode()
    mode = (entry_sync_mode or "prelude-sync").lower()
    all_data = bytearray()

    for baud in bauds:
        with open_serial_port(serial, port, baud, timeout=0.05) as ser:
            apply_serial_boot_reset(
                ser,
                boot_reset_method,
                (lambda message: print(f"binary-probe: {message}")) if verbose else None,
            )
            deadline = time.monotonic() + timeout_per_baud
            sent = 0
            data = bytearray()
            while time.monotonic() < deadline:
                ser.reset_input_buffer()
                if mode in ("prelude-sync", "prelude-only"):
                    ser.write(preamble)
                    ser.flush()
                if mode == "prelude-sync":
                    time.sleep(0.02)
                if mode in ("prelude-sync", "sync-only"):
                    ser.write(sync)
                    ser.flush()
                if mode not in ("prelude-sync", "prelude-only", "sync-only"):
                    raise ValueError(f"unknown entry sync mode: {mode}")
                sent += 1
                chunk = ser.read(256)
                if chunk:
                    data.extend(chunk)
                    all_data.extend(chunk)
                    if CP8xxxBinaryProtocol.ACK_MAGIC in data:
                        return BinaryProbeResult(matched=True, baud=baud, data=bytes(data))
                if verbose and sent % 25 == 0:
                    print(f"binary-probe: baud={baud}; sent={sent}; received={len(data)} bytes")
                time.sleep(0.05)

    return BinaryProbeResult(matched=False, baud=0, data=bytes(all_data))


def binary_command(
    port: str,
    baud: int,
    command: int,
    payload: bytes,
    read_timeout: float,
    pre_sync: bool = False,
    verbose: bool = False,
) -> BinaryCommandResult:
    try:
        import serial
    except ImportError as exc:
        raise RuntimeError("pyserial is required for binary command probing") from exc

    request = CP8xxxPacket(command, payload).encode()
    sync_response = bytearray()
    response = bytearray()

    with open_serial_port(serial, port, baud, timeout=0.05) as ser:
        ser.reset_input_buffer()
        if pre_sync:
            sync = CP8xxxBinaryProtocol.SYNC.encode()
            if verbose:
                print(f"binary-command: TX sync {sync.hex()}")
            ser.write(sync)
            ser.flush()
            deadline = time.monotonic() + read_timeout
            while time.monotonic() < deadline:
                try:
                    chunk = ser.read(256)
                except serial.SerialException as exc:
                    raise RuntimeError(f"serial read failed during sync: {exc}") from exc
                if chunk:
                    sync_response.extend(chunk)
                    if CP8xxxBinaryProtocol.ACK_MAGIC in sync_response and len(sync_response) >= 12:
                        break
            ser.reset_input_buffer()

        if verbose:
            print(f"binary-command: TX command {request.hex()}")
        ser.write(request)
        ser.flush()

        deadline = time.monotonic() + read_timeout
        while time.monotonic() < deadline:
            try:
                chunk = ser.read(512)
            except serial.SerialException as exc:
                raise RuntimeError(f"serial read failed during command: {exc}") from exc
            if chunk:
                response.extend(chunk)
            time.sleep(0.01)

    return BinaryCommandResult(
        command=command,
        payload=payload,
        sync_response=bytes(sync_response),
        response=bytes(response),
        sync_packets=decode_cp8xxx_packets(bytes(sync_response)),
        packets=decode_cp8xxx_packets(bytes(response)),
    )
