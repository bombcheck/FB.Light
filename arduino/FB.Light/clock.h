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
uint32_t clockAppearTimer = 0;
String ClockDataPrefix = "";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP,TIME_SERVER,NTP_OFFSET,NTP_UPDATE_INTERVAL);

void initClock() {
    String ClockData = ClockDataPrefix + timeClient.getFormattedTime();
    static char ClockDataChar[CLOCK_DATA_PREFIX_COUNT + 6];
    ClockData.toCharArray(ClockDataChar,sizeof(ClockDataChar));

    ScrollingMsg.SetText((unsigned char *)ClockDataChar, sizeof(ClockDataChar) - 1);
    ScrollingMsg.SetFrameRate(settings.clock_speed);
    ScrollingMsg.SetScrollDirection(SCROLL_LEFT);
    ScrollingMsg.SetBackgroundMode(BACKGND_DIMMING,settings.clock_dim);
    ScrollingMsg.SetTextColrOptions(COLR_RGB | COLR_SINGLE, settings.clock_brightness, settings.clock_brightness, settings.clock_brightness);
    showClock = true;
}

