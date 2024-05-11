## Instructions how to configure
1. Install Arduino extension for VisualStudioCode
2. Download [arduino-cli]https://arduino.github.io/arduino-cli/0.35/installation/
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
4. In Visual Studio Code Command Pallette select `Arduino: Board Manager`, and then select `esp32 by Espressif Systems Version 2.0.16` board.
5. In folder `~/Arduino/libraries/` put folders containing following libraries.
    - [ArduinoJson]https://github.com/bblanchon/ArduinoJson/releases/tag/v7.0.4
    - [ESP_Mail_Client]https://github.com/mobizt/ESP-Mail-Client/releases/tag/v3.4.19
    - [HX711]https://github.com/bogde/HX711/releases/tag/0.7.5
    - [Vector]https://github.com/janelia-arduino/Vector/releases/tag/1.2.2
6. Copy file `esp32_config_files/config_template.json` into `esp32_config_files/config.json`. Then set proper values in this file. 
7. Run `. scripts/activate.sh` (It is rather unlikely that you will have to change paths in this file, but it is possible).
8. Verify files (Ctrl+alt+R after you open `beehive-scale.ino`).
9. Upload files (Ctrl+alt+U after you open `beehive-scale.ino`).
10. You can now open Serial Monitor and watch logs.
11. Run `scripts_filesystem.sh`.
12. Click `en` button on `esp32` board.
12. Warning! This app isn't foolproof yet. There may be a lot of bugs. Sometimes a lot of random things are logged.
