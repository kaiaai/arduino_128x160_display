// Based on source code by @lehnertak https://youtu.be/Rw_BSWku54E

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>

//Pin for ESP32
  #define TFT_CS         5  //case select connect to pin 5
  #define TFT_RST        15 //reset connect to pin 15
  #define TFT_DC         32 //AO connect to pin 32  (not sure that this is really used)  try pin 25
  #define TFT_MOSI       23 //Data = SDA connect to pin 23
  #define TFT_SCLK       18 //Clock = SCK connect to pin 18

// For ST7735-based displays, we will use this call
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

//powering the tft display...

//GND is GND  that is the easy one
//LED pin on TFT will control brightness.  Using DAC on the ESP32 can control brightness by connecting
//to this pin.  See code below.  If this pin is high, VCC on the TFT does not need to be connected, but
//things seem to work better when it is connected.  VCC can go to either the 3.3 volt or the 5 volt (Vin)
//of the ESP32.  There does not appear to be any appreciable brightness difference when 5v is used instead of 3.3
//But the screen is brightest when 3.3 volts for VCC and 5volts for LED.


void setup(void) {
  Serial.begin(115200);
  // Use this initializer if using a 1.8" TFT screen:
  tft.initR(INITR_GREENTAB);      // Init ST7735S chip, black tab

  Serial.println("Initialized");

  tft.setRotation(1);

tft.fillScreen(ST77XX_BLACK);
int w = tft.width();
int h = tft.height();
Serial.print("width =");
Serial.println(w);
Serial.print("height =");
Serial.println(h);
//expecting 128 x 160

}//end of void setup

void loop() {

int w = tft.width();
int h = tft.height();

  // a single pixel
  tft.fillScreen(ST77XX_BLACK);   
  tft.drawPixel(w/2, h/2, ST77XX_GREEN);
  delay(1000);
  
  tft.fillScreen(ST77XX_RED);
  delay(500);

// Fade up brightness test

  tft.setTextColor(ST77XX_BLUE);
  tft.setTextSize(2);


for (int i = 200; i < 256; i = i+1) { // i = 255 = approx 3.3 volts, i = 0 = approx 0.0 volts

dacWrite(25, i);
  tft.setCursor(20, 80); 
  tft.print(i);
  delay(100);
  tft.fillRect(20,80,40,15, ST77XX_RED);
}

//screen starts showing up with DAC output of about 200.  
// no difference if Vcc is 5v or 3.3v


  //a line
   tft.fillScreen(ST77XX_BLACK);
   tft.drawLine(0, 0, w,h/2, ST77XX_YELLOW);
 delay(1000);
    tft.fillScreen(ST77XX_BLACK);
    delay(500);
       tft.drawLine(50, 50, 60,60, ST77XX_YELLOW);
 delay(1000);
    tft.fillScreen(ST77XX_BLACK);
    delay(500);

//a rectangle
tft.drawRect(5,10,5, 20, ST77XX_CYAN);
delay(1000);
    tft.fillScreen(ST77XX_BLACK);
delay(500);
    
//a filled rectangle
 tft.fillRect(5,10,15,60, ST77XX_MAGENTA);
delay(1000);
    tft.fillScreen(ST77XX_BLACK);
delay(500); 

  uint16_t color = 0xF800;
  
//a rounded rectangle
 tft.drawRoundRect(10, 20, w-10, h-20, 5, color);
delay(1000);
    tft.fillScreen(ST77XX_BLACK);
delay(500);

 //a circle xcenter, ycenter, radius, color
tft.drawCircle(50, 100, 15, ST77XX_BLUE);
delay(1000);
    tft.fillScreen(ST77XX_BLACK);
delay(500);

//a filled circle
       tft.fillCircle(50, 100, 15, ST77XX_WHITE);
delay(1000);
    tft.fillScreen(ST77XX_BLACK);
delay(500);

//a triangle x1,y1, x2,y2, x3,y3, color
color +=1000;
    tft.drawTriangle(10, 20, 0, 50, w, h, color);
delay(1000);
    tft.fillScreen(ST77XX_BLACK);
delay(500);

  
//text with wrapping
  tft.setTextWrap(true);
  tft.fillScreen(ST77XX_BLACK);
  delay(1000);
  tft.setCursor(0, 30);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(1);
  char hello[]="Hello World, what is out there?";
  for (int i=0; i<32; i++){
    tft.print(hello[i]);
    delay (100);
  }
  tft.invertDisplay(true);
  delay(1500);
  tft.invertDisplay(false);
  delay(1500);
  tft.fillScreen(ST77XX_BLACK);

  //text without wrapping
  
  tft.setTextWrap(false);
  tft.setCursor(0, 0);
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(0);
  tft.println("Size 0");

  tft.setCursor(0, 10);  
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(1);
  tft.println("Size 1");

  tft.setCursor(0, 20); 
  tft.setTextColor(ST77XX_BLUE);
  tft.setTextSize(2);
  tft.print("Size 2");


  tft.setCursor(0, 35); 
  tft.setTextColor(ST77XX_CYAN);
  tft.setTextSize(3);
  tft.print("Size 3");


  tft.setCursor(0, 57); 
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(4);
  tft.print("Size 4");

  
  tft.setCursor(0, 86); 
  tft.setTextColor(ST77XX_ORANGE);
  tft.setTextSize(5);
  tft.print("Size 5");
    
  delay(1000);


}//end of void loop
