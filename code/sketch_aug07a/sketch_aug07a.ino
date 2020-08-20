#include <Wire.h>
#include <Adafruit_GFX.h>       
#include <Adafruit_SSD1306.h> 
#include <U8x8lib.h>

const double myFloat = 123.4567;

U8X8_SSD1306_128X32_UNIVISION_SW_I2C u8x8(/* clock=*/ 8, /* data=*/ 9, /* reset=*/ U8X8_PIN_NONE);   // Adafruit Feather ESP8266/32u4 Boards + FeatherWing OLED

void setup() {
  
  Wire.begin(0x38);    // **** 0x38 is VDO dst address - OLED u8x8 also uses 0x38 ****         
  Serial.begin(9600);          
  
  u8x8.begin();
  u8x8.setPowerSave(0);  
  u8x8.setFont(u8x8_font_chroma48medium8_r);
}


void loop() {

  delay(100);
  u8x8.setCursor(9, 0);
  u8x8.print(myFloat,1);;
}
