# CHIP-PUMP CP8000 Arduino SDK

语言：[English](README.md) | [繁體中文](README.zh-TW.md) | [简体中文](README.zh-CN.md) | [日本語](README.ja.md)

这是 CHIP-PUMP CP8000/CP800X 开发板的 Arduino Boards Manager 套件。

图形化 Arduino IDE 安装指南：[简体中文](install-board-sdk.zh-CN.html) |
[繁體中文](install-board-sdk.html) |
[日本語](install-board-sdk.ja.html) |
[English](install-board-sdk.en.html)

## Boards Manager URL

请使用这个固定公开 Boards Manager URL：

```text
https://github.com/v7idea/chip-pump-cp8000/releases/download/boards-manager/package_chip-pump_cp8000_index.json
```

这个 URL 会保持固定。公开安装文档应指向这个 `boards-manager`
release asset，而不是指向某个特定版本的 package index。

## 要求

- Arduino IDE 2.x 或 Arduino CLI。
- 首次安装时需要网络，让 Arduino 下载 CP8000 platform 和 XuanTie toolchain 套件。
- `PATH` 中需要有 Python 3.9 或更新版本。
- 该 Python 安装需要可使用 `pip`。
- USB-to-UART 转接器或开发板所需的驱动程序。

CP8000 uploader 使用 Python `pyserial` 访问 serial port。从 `0.1.4`
开始，需要 serial port 的 uploader 命令会检查 `pyserial`，并尝试用 Arduino IDE
启动的同一个 Python 自动安装：

```bash
python -m pip install --user --disable-pip-version-check --no-input "pyserial>=3.5"
```

如果你使用受管理或离线的 Python 环境，可以关闭自动安装：

```bash
CP8000_UPLOADER_AUTO_INSTALL=0
```

手动安装命令：

```powershell
py -3 -m pip install pyserial
```

```bash
python3 -m pip install pyserial
```

## Arduino IDE 安装

1. 打开 Arduino IDE。
2. 打开 **File > Preferences**。
3. 将上方 Boards Manager URL 加入 **Additional Boards Manager URLs**。
4. 打开 **Tools > Board > Boards Manager**。
5. 搜索 `CP8000`。
6. 安装 `CHIP-PUMP CP8000 Boards`。
7. 选择开发板，例如 **CP81-Mini**。
8. 选择正确的 serial port，然后上传示例程序。

### Windows Boards Manager 缓存

Windows 版 Arduino IDE 有时会保留旧的 Boards Manager package index，
即使公开 URL 已经更新，Boards Manager 仍可能只显示旧版 CP8000，例如
`0.1.0-alpha.9`。如果没有看到最新版，请先关闭 Arduino IDE，然后只清除
CP8000 相关缓存文件：

```text
C:\Users\<USER>\AppData\Local\Arduino15
```

可能需要删除的文件：

```text
package_chip-pump_cp8000_index.json
package_chip-pump_cp8000_index.json.sig
staging\packages\chippump-cp8000-*.tar.gz
```

PowerShell 示例：

```powershell
$arduino15 = Join-Path $env:LOCALAPPDATA "Arduino15"
Remove-Item "$arduino15\package_chip-pump_cp8000_index.json" -ErrorAction SilentlyContinue
Remove-Item "$arduino15\package_chip-pump_cp8000_index.json.sig" -ErrorAction SilentlyContinue
Remove-Item "$arduino15\staging\packages\chippump-cp8000-*.tar.gz" -ErrorAction SilentlyContinue
```

除非你有意移除所有已安装开发板套件和缓存，否则不要删除整个
`Arduino15` 目录。清除 CP8000 缓存后，重新打开 Arduino IDE，确认
Additional Boards Manager URL 正确，再检查 Boards Manager 的版本下拉菜单。

## Arduino CLI 安装

```bash
arduino-cli core update-index \
  --additional-urls https://github.com/v7idea/chip-pump-cp8000/releases/download/boards-manager/package_chip-pump_cp8000_index.json

arduino-cli core install chippump:cp8000@0.1.4 \
  --additional-urls https://github.com/v7idea/chip-pump-cp8000/releases/download/boards-manager/package_chip-pump_cp8000_index.json
```

编译 Blink：

```bash
arduino-cli compile \
  --fqbn chippump:cp8000:cp8001_sop16 \
  arduino/hardware/chippump/cp8000/libraries/01.GPIO/examples/Blink
```

## 当前套件

`0.1.4` 包含：

- CP8000 Arduino core，以及 CP81-Mini 开发板定义。
- 按开发板分类的示例：
  `01.GPIO`、`02.I2C_SPI`、`03.BLE`、`04.Serial`、`05.24GRadio`、
  `06.Watchdog`、`07.OTA`。
- 适用于 Windows、macOS、Linux 的 CP8xxx UART uploader。
- 第一次执行需要 serial access 的 uploader 命令时，自动安装 `pyserial`。
- 示例所需的 vendor CP8000 runtime libraries 和 linker assets。
- Boards Manager 管理的 `cp8000-xuantie-elf-newlib@0.1.0-alpha.9` toolchain 套件。

## 注意事项

这个套件目前是早期公开 release，用于硬件 bring-up 和 Arduino 生态验证。
BLE、OTA 和正式量产烧录流程仍可能调整。
