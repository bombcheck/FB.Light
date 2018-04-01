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
unsigned long clockAppearTimer = 0;
String ClockDataPrefix = "";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP,TIME_SERVER,0,NTP_UPDATE_INTERVAL);

void initClock() {
    unsigned long rawTime = timeClient.getEpochTime() + (settings.clock_offset * 3600);
    unsigned long hours = (rawTime % 86400L) / 3600;
    String hoursStr = hours < 10 ? "0" + String(hours) : String(hours);
    unsigned long minutes = (rawTime % 3600) / 60;
    String minutesStr = minutes < 10 ? "0" + String(minutes) : String(minutes);
    
    String ClockData = ClockDataPrefix + hoursStr + ":" + minutesStr;
    static char ClockDataChar[CLOCK_DATA_PREFIX_COUNT + 10];
    ClockData.toCharArray(ClockDataChar,sizeof(ClockDataChar));

    ScrollingMsg.SetText((unsigned char *)ClockDataChar, sizeof(ClockDataChar) - 1);
    ScrollingMsg.SetFrameRate(settings.clock_speed);
    ScrollingMsg.SetBackgroundMode(BACKGND_DIMMING,settings.clock_dim);
    ScrollingMsg.SetTextColrOptions(COLR_RGB | COLR_SINGLE, settings.clock_brightness, settings.clock_brightness, settings.clock_brightness);
    showClock = true;
}

