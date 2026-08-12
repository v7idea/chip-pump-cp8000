import unittest
from pathlib import Path

from cp8000_uploader.protocol import CP8xxxBinaryProtocol, UploadRequest


class FakeSerial:
    def __init__(self, response=b""):
        self.response = bytearray(response)
        self.writes = []

    def reset_input_buffer(self):
        pass

    def write(self, data):
        self.writes.append(bytes(data))
        return len(data)

    def flush(self):
        pass

    def read(self, size):
        if not self.response:
            return b""
        chunk = bytes(self.response[:size])
        del self.response[:size]
        return chunk


class ConnectProtocol(CP8xxxBinaryProtocol):
    def __init__(self, request, serial):
        super().__init__(request)
        self.fake_serial = serial
        self.entered_bootloader = False

    def _open(self, baud):
        self.opened_baud = baud
        return self.fake_serial

    def _enter_bootloader(self, timeout):
        self.entered_bootloader = True

    def _status(self, message):
        pass


def make_protocol():
    request = UploadRequest(
        port="TEST",
        target="flash",
        baud="115200",
        address=0x10000000,
        firmware=Path("firmware.bin"),
        protocol="cp8xxx-binary",
    )
    return CP8xxxBinaryProtocol(request)


class ApplicationResetTests(unittest.TestCase):
    def test_acknowledgement_is_detected(self):
        protocol = make_protocol()
        protocol.serial = FakeSerial(b"noise" + protocol.APP_RESET_ACK)

        self.assertTrue(protocol._request_application_reset(0.05))
        self.assertEqual(protocol.serial.writes, [protocol.APP_RESET_REQUEST])

    def test_timeout_returns_false(self):
        protocol = make_protocol()
        protocol.serial = FakeSerial()

        self.assertFalse(protocol._request_application_reset(0.01))
        self.assertEqual(protocol.serial.writes, [protocol.APP_RESET_REQUEST])

    def test_auto_mode_continues_to_manual_bootloader_fallback(self):
        request = make_protocol().request
        protocol = ConnectProtocol(request, FakeSerial())

        protocol.connect()

        self.assertTrue(protocol.entered_bootloader)
        self.assertEqual(protocol.fake_serial.writes, [protocol.APP_RESET_REQUEST])

    def test_required_mode_rejects_missing_ack(self):
        request = UploadRequest(
            port="TEST",
            target="flash",
            baud="115200",
            address=0x10000000,
            firmware=Path("firmware.bin"),
            protocol="cp8xxx-binary",
            app_reset_mode="required",
            app_reset_timeout=0.01,
        )
        protocol = ConnectProtocol(request, FakeSerial())

        with self.assertRaisesRegex(Exception, "application reset ACK"):
            protocol.connect()


if __name__ == "__main__":
    unittest.main()
