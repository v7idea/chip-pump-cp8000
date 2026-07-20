#!/usr/bin/env python3
"""Send a CP8000 OTA image over the vendor BLE OTA service.

Install dependency:
  python3 -m pip install bleak

Example:
  python3 send_ota.py build/BLEOTADevice.ino.bin --name CP8000-OTA
"""

from __future__ import annotations

import argparse
import asyncio
import hashlib
import math
import struct
from pathlib import Path

from bleak import BleakClient, BleakScanner


OTA_SERVICE_UUID = "00002600-0000-1000-8000-00805f9b34fb"
OTA_CTRL_UUID = "00007000-0000-1000-8000-00805f9b34fb"
OTA_DATA_UUID = "00007001-0000-1000-8000-00805f9b34fb"

OTA_SIGNATURE_CMD = 0
OTA_DIGEST_CMD = 1
OTA_START_REQ = 2
OTA_START_RSP = 3
OTA_NEW_SECTOR_CMD = 4
OTA_INTEGRITY_CHECK_REQ = 5
OTA_INTEGRITY_CHECK_RSP = 6
OTA_FINISH_CMD = 7

OTA_STATUS_OK = 0x01
OTA_REBOOT = 0x02

FLASH_SECTOR_SIZE = 4096
DEFAULT_SEGMENT_SIZE = 16


def chunks(data: bytes, size: int):
    for offset in range(0, len(data), size):
        yield offset // size, data[offset : offset + size]


async def find_device(name: str, timeout: float):
    device = await BleakScanner.find_device_by_filter(
        lambda dev, adv: dev.name == name
        or adv.local_name == name
        or OTA_SERVICE_UUID in [uuid.lower() for uuid in adv.service_uuids],
        timeout=timeout,
    )
    if device is None:
        raise RuntimeError(f"CP8000 OTA device not found: {name}")
    return device


async def send_ota(path: Path, name: str, segment_size: int, reboot: bool, timeout: float) -> None:
    image = path.read_bytes()
    digest = hashlib.sha256(image).digest()
    padded_size = int(math.ceil(len(image) / segment_size) * segment_size)
    padded_image = image + bytes(padded_size - len(image))

    device = await find_device(name, timeout)
    print(f"connecting to {device.address} ({device.name})")

    indications: asyncio.Queue[bytes] = asyncio.Queue()

    def on_ctrl(_: int, data: bytearray) -> None:
        indications.put_nowait(bytes(data))

    async with BleakClient(device) as client:
        await client.start_notify(OTA_CTRL_UUID, on_ctrl)

        for idx, block in chunks(bytes(64), 16):
            await client.write_gatt_char(OTA_CTRL_UUID, bytes([OTA_SIGNATURE_CMD, idx]) + block, response=True)

        for idx, block in chunks(digest, 16):
            await client.write_gatt_char(OTA_CTRL_UUID, bytes([OTA_DIGEST_CMD, idx]) + block, response=True)

        start_req = bytes([OTA_START_REQ]) + struct.pack("<IIH", 0, len(image), segment_size)
        await client.write_gatt_char(OTA_CTRL_UUID, start_req, response=True)

        rsp = await asyncio.wait_for(indications.get(), timeout=timeout)
        if not rsp or rsp[0] != OTA_START_RSP or rsp[1] != 0:
            raise RuntimeError(f"OTA start rejected: {rsp.hex()}")
        print(f"OTA start accepted, image={len(image)} bytes")

        segments_per_sector = FLASH_SECTOR_SIZE // segment_size
        for sector_idx in range(math.ceil(len(padded_image) / FLASH_SECTOR_SIZE)):
            await client.write_gatt_char(OTA_CTRL_UUID, bytes([OTA_NEW_SECTOR_CMD]) + struct.pack("<H", sector_idx), response=True)

            sector_start = sector_idx * FLASH_SECTOR_SIZE
            sector = padded_image[sector_start : sector_start + FLASH_SECTOR_SIZE]
            for segment_id in range(segments_per_sector):
                start = segment_id * segment_size
                payload = sector[start : start + segment_size]
                if not payload:
                    break
                if len(payload) < segment_size:
                    payload += bytes(segment_size - len(payload))
                await client.write_gatt_char(OTA_DATA_UUID, bytes([segment_id]) + payload, response=False)

            ack = await client.read_gatt_char(OTA_DATA_UUID)
            print(f"sector {sector_idx}: ack={bytes(ack).hex()}")

        await client.write_gatt_char(OTA_CTRL_UUID, bytes([OTA_INTEGRITY_CHECK_REQ, 0]), response=True)
        integrity = await asyncio.wait_for(indications.get(), timeout=timeout)
        if not integrity or integrity[0] != OTA_INTEGRITY_CHECK_RSP or integrity[1] != 0:
            raise RuntimeError(f"OTA integrity check failed: {integrity.hex()}")

        status = OTA_STATUS_OK | (OTA_REBOOT if reboot else 0)
        first_word = (len(image) << 8) | status
        finish = bytes([OTA_FINISH_CMD]) + struct.pack("<IIII", first_word, 0, 0, 0)
        await client.write_gatt_char(OTA_CTRL_UUID, finish, response=True)
        print("OTA finish sent")


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("firmware", type=Path)
    parser.add_argument("--name", default="CP8000-OTA")
    parser.add_argument("--segment-size", type=int, default=DEFAULT_SEGMENT_SIZE)
    parser.add_argument("--no-reboot", action="store_true")
    parser.add_argument("--timeout", type=float, default=15.0)
    args = parser.parse_args()

    if args.segment_size <= 0 or FLASH_SECTOR_SIZE % args.segment_size != 0:
        raise SystemExit("segment size must divide 4096")

    asyncio.run(send_ota(args.firmware, args.name, args.segment_size, not args.no_reboot, args.timeout))


if __name__ == "__main__":
    main()
