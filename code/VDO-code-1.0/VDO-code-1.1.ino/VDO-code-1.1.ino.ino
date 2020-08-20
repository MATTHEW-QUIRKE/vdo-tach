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

void lcd2ascii(unsigned char * input, char * output, char * rawOutput)
// Converts the LCD display memory data received on the I2C bus into ASCII
{
  // First put segments in right order:
  rawOutput[0] = (input[6] & 0xF0) | (input[14] & 0x0F);
  rawOutput[1] = (input[6] << 4)   | (input[14] >> 4);
  rawOutput[2] = (input[7] & 0xF0) | (input[12] & 0x0F);
  rawOutput[3] = (input[7] << 4)   | (input[12] >> 4);
  rawOutput[4] = (input[8] & 0xF0) | (input[11] & 0x0F);
  rawOutput[5] = (input[8] << 4)   | (input[11] >> 4);
  rawOutput[6] = input[10];
  
  // Now rawOutput contains segments with this order: gdbca.fe
  
  char i = 0;
  for (char a = 0; a < 7; a++)
  {
    switch (rawOutput[a] & 0xFB) // ignore dot for now
    {
      case 0x00 : output[i] = ' '; break;
      case 0x7B : output[i] = '0'; break;
      case 0x30 : output[i] = '1'; break;
      case 0xE9 : output[i] = '2'; break;
      case 0xF8 : output[i] = '3'; break;
      case 0xB2 : output[i] = '4'; break;
      case 0xDA : output[i] = '5'; break;
      case 0xDB : output[i] = '6'; break;
      case 0x38 : output[i] = '7'; break;
      case 0xFB : output[i] = '8'; break;
      case 0xFA : output[i] = '9'; break;
      case 0xBB : output[i] = 'A'; break;
      case 0xD3 : output[i] = 'B'; break;
      case 0x4B : output[i] = 'C'; break;
      case 0xF1 : output[i] = 'D'; break;
      case 0xCB : output[i] = 'E'; break;
      case 0x8B : output[i] = 'F'; break;
      default   : output[i] = 'X';
    }
    i++;

  }
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
  u8x8.setCursor(10, 2);
  u8x8.print(triph); 
  delay(3000);
  
  void u8x8_ClearDisplay(u8x8_t *u8x8);
  
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.setCursor(1, 0);
  u8x8.print("temp/C"); 
  u8x8.setCursor(10, 0);
  u8x8.print(tmpC);
  
  u8x8.setCursor(1, 2);
  u8x8.print("oil/P     ");
  u8x8.setCursor(11, 2);
  u8x8.print(oilP); 
  delay(3000);
}
