<!-- markdownlint-disable MD031 -->

# Beehive Scale

## Arduino Visual Studio Code installation

1. Install [Arduino extension for Visual Studio Code](https://marketplace.visualstudio.com/items?itemName=vsciot-vscode.vscode-arduino).
2. Download and install [Arduino CLI](https://arduino.github.io/arduino-cli/0.35/installation/).
3. In `.vscode/settings.json` put
    ```json
    {
        "arduino.useArduinoCli": true,
        "arduino.path": "/path/to/arduino-cli/folder",
        "arduino.commandPath": "arduino-cli",
        "arduino.logLevel": "info",
        "C_Cpp.errorSquiggles": "enabled",
    }
    ```
3. In `.vscode/arduino.json` put
    ```json
    {
        "port": "/dev/ttyUSB0",
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
4. In Command Pallette select `Arduino: Board Manager`
    and then select `esp32 by Espressif Systems Version 2.0.16` board.
5. In folder `~/Arduino/libraries/` put folders containing following libraries:
    - [HX711](https://github.com/bogde/HX711/releases/tag/0.7.5),
6. Verify files (CTRL+ALT+R after you open `beehive_scale.ino`).
7. Upload files (CTRL+ALT+U after you open `beehive_scale.ino`).
8. You can now open Serial Monitor and watch logs.