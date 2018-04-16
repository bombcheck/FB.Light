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


#define DATA_PIN 3          // Fixed to 3 when using FASTLED_ESP8266_DMA!!
//#define BUILTIN_LED 2     // Defaults to pin 2
//#define CLK_PIN   4       
#define MAX_CURRENT 3000    // Max allowed current (set to match your power supply)

#define LED_TYPE WS2812B    // Used LED-Type in your matrix
#define COLOR_ORDER GRB     // Color-Order of your matrix
#define NUM_LEDS 88         // Number of LEDs in your matrix

#define MATRIX_WIDTH   11                                     // Physical width of your matrix
#define MATRIX_HEIGHT  8                                      // Physical height of your matrix  
#define MATRIX_TYPE    VERTICAL_MATRIX                        // Type of your Matrix: VERTICAL_ZIGZAG_MATRIX, VERTICAL_MATRIX, HORIZONTAL_ZIGZAG_MATRIX, HORIZONTAL_MATRIX
cLEDMatrix<-MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE> leds;   // Default starting point: Bottom-Left. Invert (-) MATRIX_WIDTH and/or MATRIX_HEIGHT to match your physical matrix layout
cLEDMatrix<-MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE> buffer; // Default starting point: Bottom-Left. Invert (-) MATRIX_WIDTH and/or MATRIX_HEIGHT to match your physical matrix layout

