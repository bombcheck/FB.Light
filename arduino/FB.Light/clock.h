// FB.Light Responsive LED Control
// https://github.com/bombcheck/FB.Light
//
// Forked from doctormord's Responsive Led Control
// https://github.com/doctormord/Responsive_LED_Control
//
// Free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as 
// published by the Free Software Foundation, either version 3 of 
// the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

bool showClock = false;
bool showText = false;
bool TextLoaded = false;
unsigned long clockAppearTimer = 0;
unsigned long textAppearTimer = 0;
String TextDataPrefix = "";
char ClockDataChar[TEXT_DATA_PREFIX_COUNT + 6];
char TextDataChar[266];

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP,TIME_SERVER,0,NTP_UPDATE_INTERVAL);

void setTextParams(uint8_t tcolor, uint8_t tbrightness, uint8_t tspeed, uint8_t tdim) {
    ScrollingMsg.SetFrameRate(tspeed);
    ScrollingMsg.SetBackgroundMode(BACKGND_DIMMING,tdim);
    
    if (tcolor == 0) ScrollingMsg.SetTextColrOptions(COLR_RGB | COLR_SINGLE, tbrightness, tbrightness, tbrightness);  // White
    else if (tcolor == 1) ScrollingMsg.SetTextColrOptions(COLR_RGB | COLR_SINGLE, tbrightness, 0, 0);                 // Red
    else if (tcolor == 2) ScrollingMsg.SetTextColrOptions(COLR_RGB | COLR_SINGLE, tbrightness, tbrightness, 0);       // Yellow
    else if (tcolor == 3) ScrollingMsg.SetTextColrOptions(COLR_RGB | COLR_SINGLE, 0, tbrightness, 0);                 // Green
    else if (tcolor == 4) ScrollingMsg.SetTextColrOptions(COLR_RGB | COLR_SINGLE, 0, tbrightness, tbrightness);       // Aqua
    else if (tcolor == 5) ScrollingMsg.SetTextColrOptions(COLR_RGB | COLR_SINGLE, 0, 0, tbrightness);                 // Blue
    else if (tcolor == 6) ScrollingMsg.SetTextColrOptions(COLR_RGB | COLR_SINGLE, tbrightness, 0, tbrightness);       // Purple
    else ScrollingMsg.SetTextColrOptions(COLR_RGB | COLR_SINGLE, tbrightness, tbrightness, tbrightness);              // White (default)  
}

void initClock() {
    unsigned long rawTime = timeClient.getEpochTime() + (settings.clock_offset * 3600);
    unsigned long hours = (rawTime % 86400L) / 3600;
    String hoursStr = hours < 10 ? "0" + String(hours) : String(hours);
    unsigned long minutes = (rawTime % 3600) / 60;
    String minutesStr = minutes < 10 ? "0" + String(minutes) : String(minutes);
    
    String ClockData = TextDataPrefix + hoursStr + ":" + minutesStr;
    ClockData.toCharArray(ClockDataChar,sizeof(ClockDataChar));

    ScrollingMsg.SetText((unsigned char *)ClockDataChar, sizeof(ClockDataChar) - 1);
    setTextParams(settings.clock_color, settings.clock_brightness, settings.clock_speed, settings.clock_dim);
    showClock = true;
}

void initText() {
    TextDataPrefix.toCharArray(TextDataChar,TextDataPrefix.length() + 1);
    strcat(TextDataChar, settings.text_msg);

    ScrollingMsg.SetText((unsigned char *)TextDataChar, settings.text_length + TextDataPrefix.length());
    setTextParams(settings.text_color, settings.text_brightness, settings.text_speed, settings.text_dim);
    TextLoaded = false;
    showText = true;
}

