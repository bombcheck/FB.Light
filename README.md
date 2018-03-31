# FB.Light Responsive LED Control

Using this while playing around with WS2812-LEDs. Mixed up doctormord's great work with Aaron Liddiment's Matrix and Text-Libs to implement a nice, NTP-driven clock and build a decent RGB-LED-Lamp (milk glass / 11x8 LEDs) with it:

![Confetti-Mode](https://breakout.bernis-hideout.de/git/FB.Light/confetti_1_small.gif)
![BPM-Mode](https://breakout.bernis-hideout.de/git/FB.Light/bpm_small.gif)
![Juggle-Mode](https://breakout.bernis-hideout.de/git/FB.Light/juggle_small.gif)
![Confetti-Mode with clock](https://breakout.bernis-hideout.de/git/FB.Light/confetti_clock_small.gif)
![BPM-Mode with clock](https://breakout.bernis-hideout.de/git/FB.Light/bpm_clock_small.gif)

## Used libraries / software

Fork of FastLED 3.1.3 library (included in this repo: see libraries-folder!):
https://github.com/coryking/FastLED

We are using this fork because it supports DMA which removes flicker issues. Enabled via `#define FASTLED_ESP8266_DMA`. You must use pin 3 for your LED stripe!

RemoteDebug:
https://github.com/JoaoLopesF/RemoteDebug

LEDMatrix by Aaron Liddiment (included in this repo: see libraries-folder!):
https://github.com/AaronLiddiment/LEDMatrix

LEDText by Aaron Liddiment (included in this repo: see libraries-folder!):
https://github.com/AaronLiddiment/LEDText

NTPClient
https://github.com/arduino-libraries/NTPClient

Original McLighting library:
https://github.com/toblum/McLighting

Russel's implementation of McLighting:
https://github.com/russp81/LEDLAMP_FASTLEDs

Jakes's "Grisworld" LED Controller:
https://github.com/jake-b/Griswold-LED-Controller

## How to start

If you aren't familiar with how to setup your ESP8266, see the readme on McLighting's git.  It's well written and should get you up and running.

In short you will:

1.  Configure the Arduino IDE to communicate with the ESP8266. Or export the bin file from the IDE and use your favourite flashing tool instead.
2.  Upload the sketch (from this repo). The sketch is setup for a 88 pixel WS2812B GRB LED Strip on pin 3 with DMA enabled. Matrix is configured
	as a vertical 11x8 (width x height) layout with the beginning at bottom right (change the applicable options in `definitions.h` to your desire).
3.  Patch FastLED Library (not neccessary when using the library included in this repo!):

```arduino
// Note, you need to patch FastLEDs in order to use this.  You'll get an
// error related to <avr\pgmspace.h>. Saves more than 3k given the palettes
//
// Simply edit <fastled_progmem.h> and update the include (Line ~29):

#if FASTLED_INCLUDE_PGMSPACE == 1
#if (defined(__AVR__))
#include <avr\pgmspace.h>
#else
#include <pgmspace.h>
#endif
#endif
```

4.  On first launch, the ESP8266 will advertise it's own WiFi network for you to connect to. Once you connect to it, launch your browser
    and the web interface is self explanatory. (If the interface doesn't load, type in "192.168.4.1" into your browser and hit go).
5.  Once the ESP is on your wifi network, you can then upload the required files for the web interface by typing the IP address
    of the ESP followed by `/upload` (i.e. `192.168.1.20/upload`). Then upload the files from the folder labeled
    `upload these to ESP8266` from this repo.
6.  Once you have finished uploading, type in the IP of the ESP into your browser and you should be up and running!
7.	You can edit the location string shown in the web ui by editing the file `location.txt` before you upload it.
	Or edit the file afterwards by typing the IP address of the ESP followed by `/edit` (i.e. `192.168.1.20/edit`) using the integrated ESP Editor.

## Updating the firmware

After the first flash, you can update the firmware via OTA by typing the IP address of the ESP followed by `/update` (i.e. `192.168.1.20/update`).
WIFI config and uploaded files will stay untouched.

## License

As per the original [McLighting](https://github.com/toblum/McLighting) and [Jake's "Grisworld"](https://github.com/jake-b/Griswold-LED-Controller) project, this project is released under the GNU LESSER GENERAL PUBLIC LICENSE Version 3, 29 June 2007.

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
