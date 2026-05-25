# CHIP-PUMP CP8000 Arduino SDK

言語：[English](README.md) | [繁體中文](README.zh-TW.md) | [简体中文](README.zh-CN.md) | [日本語](README.ja.md)

CHIP-PUMP CP8000/CP800X ボード向けの Arduino Boards Manager パッケージです。

画像付き Arduino IDE インストールガイド：[日本語](install-board-sdk.ja.html) |
[繁體中文](install-board-sdk.html) |
[简体中文](install-board-sdk.zh-CN.html) |
[English](install-board-sdk.en.html)

## Boards Manager URL

次の固定公開 Boards Manager URL を使用してください。

```text
https://github.com/v7idea/chip-pump-cp8000/releases/download/boards-manager/package_chip-pump_cp8000_index.json
```

この URL は固定の公開エントリーポイントです。公開インストール手順では、
バージョン付き package index ではなく、この `boards-manager` release asset を参照してください。

## 必要環境

- Arduino IDE 2.x または Arduino CLI。
- 初回インストール時に、CP8000 platform と XuanTie toolchain パッケージをダウンロードするためのインターネット接続。
- `PATH` から利用できる Python 3.9 以降。
- その Python 環境で利用できる `pip`。
- 使用する USB-to-UART アダプターまたはボード用のドライバー。

CP8000 uploader は serial port アクセスに Python `pyserial` を使用します。
`0.1.1` 以降、serial port が必要な uploader コマンドは `pyserial` を確認し、
Arduino IDE から起動されたものと同じ Python で自動インストールを試みます。

```bash
python -m pip install --user --disable-pip-version-check --no-input "pyserial>=3.5"
```

管理された Python 環境やオフライン環境では、自動インストールを無効にできます。

```bash
CP8000_UPLOADER_AUTO_INSTALL=0
```

手動インストールコマンド：

```powershell
py -3 -m pip install pyserial
```

```bash
python3 -m pip install pyserial
```

## Arduino IDE でのインストール

1. Arduino IDE を開きます。
2. **File > Preferences** を開きます。
3. 上記の Boards Manager URL を **Additional Boards Manager URLs** に追加します。
4. **Tools > Board > Boards Manager** を開きます。
5. `CP8000` を検索します。
6. `CHIP-PUMP CP8000 Boards` をインストールします。
7. **CHIP-PUMP CP8001 SOP16** などのボードを選択します。
8. 正しい serial port を選択し、サンプルをアップロードします。

### Windows Boards Manager キャッシュ

Windows 版 Arduino IDE は、公開 URL が更新された後でも古い Boards Manager
package index を保持することがあります。Boards Manager に古い CP8000
バージョン、たとえば `0.1.0-alpha.9` だけが表示される場合や、最新リリースが
表示されない場合は、Arduino IDE を閉じて、CP8000 関連のキャッシュファイルだけを
削除してください。

```text
C:\Users\<USER>\AppData\Local\Arduino15
```

削除対象になる可能性があるファイル：

```text
package_chip-pump_cp8000_index.json
package_chip-pump_cp8000_index.json.sig
staging\packages\chippump-cp8000-*.tar.gz
```

PowerShell の例：

```powershell
$arduino15 = Join-Path $env:LOCALAPPDATA "Arduino15"
Remove-Item "$arduino15\package_chip-pump_cp8000_index.json" -ErrorAction SilentlyContinue
Remove-Item "$arduino15\package_chip-pump_cp8000_index.json.sig" -ErrorAction SilentlyContinue
Remove-Item "$arduino15\staging\packages\chippump-cp8000-*.tar.gz" -ErrorAction SilentlyContinue
```

すべてのボードパッケージとキャッシュを意図的に削除したい場合を除き、
`Arduino15` ディレクトリ全体は削除しないでください。CP8000 キャッシュを削除した後、
Arduino IDE を再起動し、Additional Boards Manager URL が正しいことを確認してから、
Boards Manager のバージョンドロップダウンを再確認してください。

## Arduino CLI でのインストール

```bash
arduino-cli core update-index \
  --additional-urls https://github.com/v7idea/chip-pump-cp8000/releases/download/boards-manager/package_chip-pump_cp8000_index.json

arduino-cli core install chippump:cp8000@0.1.1 \
  --additional-urls https://github.com/v7idea/chip-pump-cp8000/releases/download/boards-manager/package_chip-pump_cp8000_index.json
```

Blink をコンパイルします。

```bash
arduino-cli compile \
  --fqbn chippump:cp8000:cp8001_sop16 \
  arduino/hardware/chippump/cp8000/libraries/01.GPIO/examples/Blink
```

## 現在のパッケージ

`0.1.1` には次の内容が含まれます。

- CP8000 Arduino core、および CP8001 SOP16 / CP8003 SOP16 のボード定義。
- ボードスコープのサンプルカテゴリ：
  `01.GPIO`、`02.I2C_SPI`、`03.BLE`、`04.Serial`、`05.24GRadio`、
  `06.Watchdog`、`07.OTA`。
- Windows、macOS、Linux 向けの CP8xxx UART uploader。
- serial access が必要な uploader コマンドの初回実行時に `pyserial` を自動インストール。
- サンプルに必要な vendor CP8000 runtime libraries と linker assets。
- Boards Manager 管理の `cp8000-xuantie-elf-newlib@0.1.0-alpha.9` toolchain パッケージ。

## 注意

このパッケージは、ハードウェア bring-up と Arduino エコシステム検証のための早期公開 release です。
BLE、OTA、本番向け書き込みワークフローは今後変更される可能性があります。
