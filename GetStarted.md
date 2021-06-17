# Getting Started

### Hardware
You'll need a ESP8266 or ESP32 microcontroller developer board or module.

### USB Drivers

Don't forget to install proper drivers for the USB-to-serial converter. If needed!

If you're using a board along with a standalone FTDI adapter on Linux or
Mac OS X, it should be shipped with the OS, for Windows drivers see
[FTDI website](http://www.ftdichip.com/Drivers/VCP.htm).

Silabs CP210x USB-to-serial chip (NodeMCU v2) for which you can
get driver from [here](https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers).

CH34x chip, Win driver (NodeMCU 0.9) can be found [here](http://www.wch-ic.com/downloads/category/30.html).

### Install the Arduino Desktop IDE
To get step-by-step instructions select one of the following link accordingly to your operating system.

[Windows](https://www.arduino.cc/en/Guide/Windows)

[Mac OS X](https://www.arduino.cc/en/Guide/MacOSX)

[Linux](https://www.arduino.cc/en/Guide/Linux)

### Install ESP Arduino Core 
To get step-by-step instructions select one of the following links accordingly to your microcontroller board.

[ESP8266](https://arduino-esp8266.readthedocs.io/en/2.6.3/installing.html#instructions)

[ESP32](https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md)

### Install Arduino spiffs filesystem uploader
You'll also need to download and install the spiffs upload tool. 

See [here](https://github.com/esp8266/arduino-esp8266fs-plugin/blob/master/README.md) for the ESP8266. 

Or [here](https://github.com/me-no-dev/arduino-esp32fs-plugin) fpr the ESP32.
### Installing Additional Arduino Libraries

> ### Import using the Library Manager

Using the Library Manager 'search' and 'install' the following libraries. See [here](https://www.arduino.cc/en/Guide/Libraries#toc2) for more information.

**ArduinoJson (v5.x)** important to use version 5.x

**Adafruit_NeoPixel**

**Wasm3**


> ### Importing a .zip Library

The next libraries can't be installed using the Library Manager and you'll have to download and install them from zip files. See [here](https://www.arduino.cc/en/Guide/Libraries#toc4) for more information.

[ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer/archive/master.zip)

select one of the following links accordingly to your microcontroller board.

ESP32   - [AsyncTCP](https://github.com/me-no-dev/AsyncTCP/archive/master.zip)

ESP8266 - [ESPAsyncTCP](https://github.com/me-no-dev/ESPAsyncTCP/archive/master.zip)

### Installing NeoWasm Files
Download and install the NeoWasm project files. NeoWasm is a Sketch and not a Library.
The latest release can be download from [here](https://github.com/MelodyToys/NeoWasm/releases). 

Extract the archive into you Arduino home folder or somewhere within your local filesystem. 

Open the NeoWasm.ino file within the Arduino IDE. For more information on using the Arduino IDE can be found [here](https://www.arduino.cc/en/Tutorial/Foundations) and [here](https://www.arduino.cc/en/Guide/Environment) 

You'll need to change the board and board options within the IDE before uploading the firware *(make sure you selected an appropriate spiffs size)* 

Upload the Sketch using the menu (Sketch->Upload) or keyboard shortcut (Ctrl+U). 

After uploading the firmware you next need to upload the filesystem. Select Tools > ESP8266 Sketch Data Upload menu item. See [here](https://github.com/esp8266/arduino-esp8266fs-plugin/blob/master/README.md#usage) for more information. 

If eveything was successful continue reading ["Using NeoWasm"](https://github.com/MelodyToys/NeoWasm/blob/master/UsingNeoWasm.md)



