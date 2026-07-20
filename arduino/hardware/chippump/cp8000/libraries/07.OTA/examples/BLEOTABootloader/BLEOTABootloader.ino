#if defined(OTA_BOOT_EN) && OTA_BOOT_EN
extern "C" void ota_reboot_chk(void);
#endif

void setup() {
#if defined(OTA_BOOT_EN) && OTA_BOOT_EN
  ota_reboot_chk();
#else
  Serial.begin(115200);
  delay(100);
  Serial.println("CP8000 BLE OTA bootloader reference");
  Serial.println("Build with Tools > OTA Mode > BLE OTA Bootloader to enable ota_reboot_chk().");
  Serial.println("A production release should ship this as a prebuilt minimal bootloader binary.");
#endif
}

void loop() {
}
