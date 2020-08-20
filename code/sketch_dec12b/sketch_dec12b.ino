#include <Arduino.h>
#include <U8g2lib.h>

U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C u8g2(/* clock=*/ 9, /* data=*/8, /* reset=*/5 );   // Adafruit Feather ESP8266/32u4 Boards + FeatherWing OLED
void setup(void) {
  u8g2.begin();
}

void loop(void) {
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB14_tr);
    u8g2.drawStr(0,15,"Hello World!");
  } while ( u8g2.nextPage() );
  delay(1000);
}
