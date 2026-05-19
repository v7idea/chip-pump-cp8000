from __future__ import annotations

import datetime as _dt
import sys
import time
from dataclasses import dataclass
from pathlib import Path


@dataclass(frozen=True)
class CaptureRequest:
    port: str
    baud: int
    output: Path | None
    duration: float | None
    chunk_size: int = 256
    verbose: bool = False


def run_capture(request: CaptureRequest) -> int:
    try:
        import serial
    except ImportError:
        print("error: pyserial is required for serial capture", file=sys.stderr)
        return 2

    started = time.monotonic()
    deadline = None if request.duration is None else started + request.duration
    total = 0

    sink = request.output.open("ab") if request.output else None
    try:
        with serial.Serial(request.port, request.baud, timeout=0.1) as ser:
            print(
                f"capture: port={request.port} baud={request.baud} "
                f"output={request.output or '<stdout-hex>'}",
                file=sys.stderr,
            )
            while deadline is None or time.monotonic() < deadline:
                data = ser.read(request.chunk_size)
                if not data:
                    continue
                total += len(data)
                if sink:
                    sink.write(data)
                    sink.flush()
                else:
                    sys.stdout.write(format_hex_line(data))
                    sys.stdout.flush()
                if request.verbose:
                    timestamp = _dt.datetime.now().isoformat(timespec="milliseconds")
                    print(f"{timestamp} +{len(data)} bytes total={total}", file=sys.stderr)
    except serial.SerialException as exc:
        print(f"error: serial capture failed: {exc}", file=sys.stderr)
        return 1
    except KeyboardInterrupt:
        print("capture: stopped by user", file=sys.stderr)
    finally:
        if sink:
            sink.close()

    print(f"capture: captured {total} bytes", file=sys.stderr)
    return 0


def format_hex_line(data: bytes) -> str:
    timestamp = _dt.datetime.now().isoformat(timespec="milliseconds")
    hex_bytes = " ".join(f"{byte:02X}" for byte in data)
    ascii_text = "".join(chr(byte) if 32 <= byte <= 126 else "." for byte in data)
    return f"{timestamp}  {hex_bytes}  |{ascii_text}|\n"
