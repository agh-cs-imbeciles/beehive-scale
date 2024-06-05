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
4. In Command Pallette select `Arduino: Board Manager`
    and then select `esp32 by Espressif Systems Version 2.0.16` board.
5. In folder `~/Arduino/libraries/` put folders containing following libraries:
    - [ArduinoJson](https://github.com/bblanchon/ArduinoJson/releases/tag/v7.0.4),
    - [ESP Mail Client](https://github.com/mobizt/ESP-Mail-Client/releases/tag/v3.4.19),
    - [HX711](https://github.com/bogde/HX711/releases/tag/0.7.5),
    - [Vector](https://github.com/janelia-arduino/Vector/releases/tag/1.2.2).
6. Copy file `config/esp32_template.json` into `config/esp32.json`. Then set proper values in this file.
7. Copy `scripts/.env_template` into `scripts/.env` and set `PORT` to port to which esp32 is connected. (It is rather unlikely that you will have to change other variables, but it is possible.)
8. Verify files (CTRL+ALT+R after you open `beehive_scale.ino`).
9. Upload files (CTRL+ALT+U after you open `beehive_scale.ino`).
10. You can now open Serial Monitor and watch logs.
11. Run `scripts/flash_filesystem.sh`.
12. Click `en` button on `esp32` board.
13. Warning! This app isn't foolproof yet. There may be a lot of bugs. Sometimes a lot of random things are logged.
