# CHIP-PUMP CP8000 Arduino SDK

語言：[English](README.md) | [繁體中文](README.zh-TW.md) | [简体中文](README.zh-CN.md) | [日本語](README.ja.md)

這是 CHIP-PUMP CP8000/CP800X 開發板的 Arduino Boards Manager 套件。

## Boards Manager URL

請使用這個固定公開 Boards Manager URL：

```text
https://github.com/v7idea/chip-pump-cp8000/releases/download/boards-manager/package_chip-pump_cp8000_index.json
```

這個 URL 會維持固定。公開安裝文件應該指向這個 `boards-manager`
release asset，而不是指向特定版本的 package index。

## 需求

- Arduino IDE 2.x 或 Arduino CLI。
- 第一次安裝時需要網路，讓 Arduino 下載 CP8000 platform 與 XuanTie toolchain 套件。
- `PATH` 中需要有 Python 3.9 或更新版本。
- 該 Python 安裝需要可使用 `pip`。
- USB-to-UART 轉接器或開發板所需的驅動程式。

CP8000 uploader 使用 Python `pyserial` 存取 serial port。從 `0.1.1-alpha.4`
開始，需要 serial port 的 uploader 指令會檢查 `pyserial`，並嘗試用 Arduino IDE
啟動的同一個 Python 自動安裝：

```bash
python -m pip install --user --disable-pip-version-check --no-input "pyserial>=3.5"
```

如果你使用受管理或離線的 Python 環境，可以關閉自動安裝：

```bash
CP8000_UPLOADER_AUTO_INSTALL=0
```

手動安裝指令：

```powershell
py -3 -m pip install pyserial
```

```bash
python3 -m pip install pyserial
```

## Arduino IDE 安裝

1. 開啟 Arduino IDE。
2. 開啟 **File > Preferences**。
3. 將上方 Boards Manager URL 加入 **Additional Boards Manager URLs**。
4. 開啟 **Tools > Board > Boards Manager**。
5. 搜尋 `CP8000`。
6. 安裝 `CHIP-PUMP CP8000 Boards`。
7. 選擇開發板，例如 **CHIP-PUMP CP8001 SOP16**。
8. 選擇正確的 serial port，然後上傳範例程式。

### Windows Boards Manager 快取

Windows 版 Arduino IDE 有時會保留舊的 Boards Manager package index，
即使公開 URL 已經更新，Boards Manager 仍可能只顯示舊版 CP8000，例如
`0.1.0-alpha.9`。如果沒有看到最新版，請先關閉 Arduino IDE，然後只清除
CP8000 相關快取檔案：

```text
C:\Users\<USER>\AppData\Local\Arduino15
```

可能需要刪除的檔案：

```text
package_chip-pump_cp8000_index.json
package_chip-pump_cp8000_index.json.sig
staging\packages\chippump-cp8000-*.tar.gz
```

PowerShell 範例：

```powershell
$arduino15 = Join-Path $env:LOCALAPPDATA "Arduino15"
Remove-Item "$arduino15\package_chip-pump_cp8000_index.json" -ErrorAction SilentlyContinue
Remove-Item "$arduino15\package_chip-pump_cp8000_index.json.sig" -ErrorAction SilentlyContinue
Remove-Item "$arduino15\staging\packages\chippump-cp8000-*.tar.gz" -ErrorAction SilentlyContinue
```

除非你刻意要移除所有已安裝開發板套件與快取，否則不要刪除整個
`Arduino15` 目錄。清除 CP8000 快取後，重新開啟 Arduino IDE，確認
Additional Boards Manager URL 正確，再檢查 Boards Manager 的版本下拉選單。

## Arduino CLI 安裝

```bash
arduino-cli core update-index \
  --additional-urls https://github.com/v7idea/chip-pump-cp8000/releases/download/boards-manager/package_chip-pump_cp8000_index.json

arduino-cli core install chippump:cp8000@0.1.1-alpha.4 \
  --additional-urls https://github.com/v7idea/chip-pump-cp8000/releases/download/boards-manager/package_chip-pump_cp8000_index.json
```

編譯 Blink：

```bash
arduino-cli compile \
  --fqbn chippump:cp8000:cp8001_sop16 \
  arduino/hardware/chippump/cp8000/libraries/01.GPIO/examples/Blink
```

## 目前套件

`0.1.1-alpha.4` 包含：

- CP8000 Arduino core，以及 CP8001 SOP16、CP8003 SOP16 開發板定義。
- 依開發板範例分類：
  `01.GPIO`、`02.I2C_SPI`、`03.BLE`、`04.Serial`、`05.24GRadio`、
  `06.Watchdog`、`07.OTA`。
- 適用於 Windows、macOS、Linux 的 CP8xxx UART uploader。
- 第一次執行需要 serial access 的 uploader 指令時，自動安裝 `pyserial`。
- 範例所需的 vendor CP8000 runtime libraries 與 linker assets。
- Boards Manager 管理的 `cp8000-xuantie-elf-newlib@0.1.0-alpha.9` toolchain 套件。

## 注意事項

這個套件目前是 alpha release，用於硬體 bring-up 與 Arduino 生態系驗證。
BLE、OTA 與正式量產燒錄流程仍可能調整。
