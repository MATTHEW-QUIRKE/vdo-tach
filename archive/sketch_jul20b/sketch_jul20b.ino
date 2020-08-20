
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define SDA_PIN 8
#define SCL_PIN 9

void setup()
{
  delay(1000);
//  display.display();
}
void loop()
{
  display.drawLine(0, 0, 127, 63,WHITE);
  delay(1000);
  display(SDA_PIN,SCL_PIN);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("HelTec Automation");
  display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.println(3.141592);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print("0x"); display.println(0xDEADBEEF, HEX);
  delay(2000);
  display.clearDisplay();
}
