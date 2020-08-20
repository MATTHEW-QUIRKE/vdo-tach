#include <Arduino.h>
#include <U8x8lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

// U8x8 Contructor  
U8X8_SSD1306_128X32_UNIVISION_SW_I2C u8x8(/* clock=*/ 8, /* data=*/ 9, /* reset=*/ U8X8_PIN_NONE);   // Adafruit Feather ESP8266/32u4 Boards + FeatherWing OLED

void setup(void)
{
  u8x8.begin();
  u8x8.setPowerSave(0);
  
}

void loop(void)
{
 
  int engh = 9999;
  int triph = 300;
  int tmpC = 61;
  int oilP = 21;
  
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.setCursor(1, 0);
  u8x8.print("eng/h"); 
  u8x8.setCursor(10, 0);
  u8x8.print(engh);
  
  u8x8.setCursor(1, 2);
  u8x8.print("trip/h     ");
  u8x8.setCursor(11, 2);
  u8x8.print(triph); 
  delay(2000);

}
