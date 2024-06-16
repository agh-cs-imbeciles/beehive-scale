<!-- markdownlint-disable MD031 MD033 -->

# Beehive Scale

## Arduino for Visual Studio Code project setup (Linux)

1. Install [Arduino extension for Visual Studio Code](https://marketplace.visualstudio.com/items?itemName=vsciot-vscode.vscode-arduino).
2. Download and install [Arduino CLI](https://arduino.github.io/arduino-cli/0.35/installation/).
3. Add 2 files to _.vscode_ folder.<br>
    - **.vscode/settings.json**
      ```json
      {
          "arduino.useArduinoCli": true,
          "arduino.path": "/path/to/arduino-cli/folder",
          "arduino.commandPath": "arduino-cli",
          "arduino.logLevel": "info",
          "C_Cpp.errorSquiggles": "enabled",
      }
      ```
    - **.vscode/arduino.json**<br>
      `port` is a path to the connected board via USB, e.g. _/dev/ttyUSB0_
      ```json
      {
          "port": "/path/to/USB/port",
          "prebuild": "./prebuild.sh",
          "board": "esp32:esp32:esp32",
          "sketch": "beehive_scale.ino",
          "output": "./build",
          "configuration": "JTAGAdapter=default,PSRAM=disabled,PartitionScheme=default,CPUFreq=240,FlashMode=qio,FlashFreq=80,FlashSize=4M,UploadSpeed=921600,LoopCore=1,EventsCore=1,DebugLevel=info,EraseFlash=none",
          "buildPreferences": [
              [
                  "compiler.cpp.extra_flags",
                  "-fexceptions"
              ]
          ],
          "programmer": "esptool"
      }
      ```
4. In Command Pallette select _"Arduino: Board Manager"_ and then select _"esp32 by Espressif Systems Version 2.0.16"_ board.
5. In **~/Arduino/libraries/** put folder containing a following library [HX711](https://github.com/bogde/HX711/releases/tag/0.7.5).
6. Verify files (press `CTRL + ALT + R` in **beehive_scale.ino**).
7. Upload files (press `CTRL + ALT + U` in **beehive_scale.ino**).
8. You can now open _Serial Monitor_ and watch logs.
9. _**Warning!** This app isn't foolproof yet. There may be a lot of bugs. Sometimes a lot of random things are logged._
