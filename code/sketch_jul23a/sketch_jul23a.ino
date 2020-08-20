#include <Wire.h>                // For TWI/I2C
#include <Adafruit_GFX.h>        // Some graphics functions
#include <Adafruit_SSD1306.h> // OLED driver
#include <U8x8lib.h>

char rawLine1[10];
char rawLine2[10];
int line1;
char line2[10];
char oldline1[10];
int engh = 1000;
int triph = 300;
int tmpC = 61;
int oilP = 21;

// U8x8 Contructor  
U8X8_SSD1306_128X32_UNIVISION_SW_I2C u8x8(/* clock=*/ 8, /* data=*/ 9, /* reset=*/ U8X8_PIN_NONE);   // Adafruit Feather ESP8266/32u4 Boards + FeatherWing OLED
  
void setup(void)
{
  u8x8.begin();
  u8x8.setPowerSave(0);
  // Initialize I2C bus:
  Wire.begin(0x38);             // join i2c bus with address 38h
  Wire.onReceive(receiveEvent); // register event
}

void receiveEvent()
{   
 engh++;
 triph++;
}   

void loop() {
  
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.setCursor(1, 0);  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.setCursor(1, 0);
  u8x8.print("eng/h"); 
  u8x8.setCursor(10, 0);
  u8x8.print(engh);

  u8x8.print("eng/h"); 
  u8x8.setCursor(10, 0);
  u8x8.print(engh);

  u8x8.setCursor(1, 2);
  u8x8.print("trip/h     ");
  u8x8.setCursor(10, 2);
  u8x8.print(triph); 
  delay(300);
}
