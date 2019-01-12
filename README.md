# FB.Light WS2812B WiFi-LED-Strip-Controller

Based upon [doctormord's](https://github.com/doctormord/Responsive_LED_Control) great mixture, this software is intended to act as a full-featured WiFi-LED-Strip-Controller for WS2812B-LEDs. I added some new effects to doctormord's work and integrated Aaron Liddiment's Matrix and Text-Libs to implement a nice, NTP-driven clock. As a prove of concept I finally build a decent RGB-LED-Lamp (milk glass / 11x8 LEDs) with it:

![Confetti-Mode](https://breakout.bernis-hideout.de/git/FB.Light/confetti_1_small.gif)
![Juggle-Mode](https://breakout.bernis-hideout.de/git/FB.Light/juggle_small.gif)
![Confetti-Mode with clock](https://breakout.bernis-hideout.de/git/FB.Light/confetti_clock_small_2.gif)
![BPM-Mode with clock](https://breakout.bernis-hideout.de/git/FB.Light/bpm_clock_small.gif)

## Features

* Runs on an ESP8266 (I used a NodeMCU-board with an ESP-12E).
* Easy integration into your existing WiFi network.
* Max. power consumption can be defined (`#define MAX_CURRENT`): Protects your power supply by cutting brightness if current draw exceeds configured value.
* Responsive user interface which can be used with any desktop or mobile web browser.
* Static color can be selected with a decent, delay-free colorwheel.
* Many different effect-modes which can be tweaked and customized. They look great on both strips and matrices.
* Customizable scrolling NTP-driven clock (only useful on a matrix with a minimum height of 7 pixel). Can be combined with the other effects.
* Customizable scrolling text (only useful on a matrix with a minimum height of 7 pixel). Can be combined with the other effects.
* API to integrate the controller in existing home automation environments.
* Firmware upgradeable via web interface.
* Debug-Output can be viewed via telnet session.

## Used libraries / software

* [Fork of FastLED 3.1.3 library](https://github.com/coryking/FastLED) (included in this repo: see libraries-folder!).
We are using this fork because it supports DMA which removes flicker issues. Enabled via `#define FASTLED_ESP8266_DMA`. You must use pin 3 for your LED stripe!
* [RemoteDebug](https://github.com/JoaoLopesF/RemoteDebug): Debug output is visible via a telnet session rather than printing to serial):
* [LEDMatrix by Aaron Liddiment](https://github.com/AaronLiddiment/LEDMatrix) (included in this repo: see libraries-folder!).
* [LEDText by Aaron Liddiment](https://github.com/AaronLiddiment/LEDText) (included in this repo: see libraries-folder!).
* [NTPClient](https://github.com/arduino-libraries/NTPClient)

## How to start

1.	Wire your LEDs to your controller: In order to use the highly prefered DMA-Mode, you must use GPIO3 (RX on a NodeMCU) as the DATA_PIN!
2.	Copy libraries from the `libraries`-folder in this repo to your arduino libraries-folder and make sure your have the other needed libraries added via your Arduino IDE as well.
3.  Configure the Arduino IDE to communicate with the ESP8266. Or export the bin file from the IDE and use your favourite flashing tool instead.
4.  Compile and upload the sketch (from this repo). The sketch is setup for a 88 pixel WS2812B GRB LED Strip on pin 3 with DMA enabled. Matrix is configured
	as a vertical 11x8 (width x height) layout with the beginning at bottom right (change the applicable options in `hardware.h` to your desire).
5.  On first launch, the ESP8266 will advertise it's own WiFi network for you to connect to. Once you connect to it, launch your browser
    and the web interface is self explanatory. (If the interface doesn't load, type in "192.168.4.1" into your browser and hit go).
6.  Once the ESP is on your wifi network, you can then upload the required files for the web interface by typing the IP address
    of the ESP followed by `/upload` (i.e. `192.168.1.20/upload`). Then upload the files from the folder labeled `upload these to ESP8266` from this repo.
7.  Once you have finished uploading, type in the IP of the ESP into your browser and you should be up and running!
8.	You can edit the location string shown in the web ui by editing the file `location.txt` before you upload it. Or edit the file afterwards by typing the IP address of the ESP
    followed by `/edit` (i.e. `192.168.1.20/edit`) using the integrated ESP Editor (should be used with Google Chrome).

## Updating the firmware

After the first flash, you can update the firmware via OTA by typing the IP address of the ESP followed by `/update` (i.e. `192.168.1.20/update`).
WiFi config, settings and uploaded files will stay untouched.

## API

### Useful URLs:

1. `/upload`: Upload files to SPIFFS-filesystem (used to upload/update web ui)
1. `/update`: Upload new firmware here (web ui and settings will be kept). 
1. `/edit`: Edit/upload files on the SPIFFS filesystem.
1. `/graphs.htm`: Some statistic graphs of system ressources.
1. `/restart`: Reboot the system (make sure to save changed settings before!).
1. `/reset_wlan`: Delete the wifi settings (system will come up with the default WiFi configuration ap to connect to).

### API-Endpoints:

1. `/set_brightness`: Set overall brightness. Possible parameters: Brightness in percent `c=(0-100)` or absolute brightness `p=(0-255)`.
1. `/set_clock_brightness`: Set brightness of the clock. Possible parameters: Brightness in percent `c=(0-100)` or absolute brightness `p=(0-255)`.
1. `/set_clock`: Show clock. Possible parameters: Turn on `s=1` (clock runs immediately) or turn off `s=0`.
1. `/set_text`: Show text. Possible parameters: Turn on `s=1` (text runs immediately) or turn off `s=0`.
1. `/set_text_brightness`: Set brightness of the scrolling text. Possible parameters: Brightness in percent `c=(0-100)` or absolute brightness `p=(0-255)`.
1. `/update_text`: Updates custom scrolling text and display it once. Parameters: `text=(Max. 255 chars of text)` and (optional) `color=(0-6)`.
1. `/get_brightness`: Returns the current overall brightness in percent.
1. `/get_clock_brightness`: Returns the current brightness of the clock in percent.
1. `/get_text_brightness`: Returns the current brightness of the scrolling text in percent.
1. `/get_switch`: Returns `0` if current mode is `OFF`, otherwise `1`.
1. `/get_color`: Returns the current main color in HEX.
1. `/status`: Returns JSON of current settings.
1. `/restore_defaults`: Restores default effect settings.
1. `/load_settings`: Load effect settings from memory.
1. `/save_settings`: Save current effect settings to memory.

### Set Mode via API:

1. `/off`: OFF (even glitter, clock and text are disabled)
1. `/all`: SOLID COLOR (set color via additional parameter: `rgb=#COLORHEXVALUE` or `r=0-255`, `g=0-255`, `b=0-255`)
1. `/rainbow`: RAINBOW
1. `/confetti`: CONFETTI
1. `/sinelon`: SINELON
1. `/juggle`: JUGGLE
1. `/bpm`: BPM
1. `/ripple`: RIPPLE
1. `/comet`: COMET
1. `/wipe`: WIPE
1. `/tv`: TV
1. `/fire`: FIRE
1. `/frainbow`: FIRE RAINBOW
1. `/fworks`: FIREWORKS
1. `/fwsingle`: FIREWORKS SINGLE
1. `/fwrainbow`: FIREWORKS RAINBOW
1. `/colorflow`: COLORFLOW
1. `/caleidoscope1`: CALEIDOSCOPE 1
1. `/caleidoscope2`: CALEIDOSCOPE 2
1. `/caleidoscope3`: CALEIDOSCOPE 3
1. `/caleidoscope4`: CALEIDOSCOPE 4
1. `/blank`: BLANK (same as OFF but with glitter, clock and text enabled)

## License

This project is released under the GNU LESSER GENERAL PUBLIC LICENSE Version 3, 29 June 2007.

	Griswold is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as 
	published by the Free Software Foundation, either version 3 of 
	the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
