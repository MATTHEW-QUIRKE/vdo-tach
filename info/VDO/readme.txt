How to use:

1. These instructions are for Windows
2. If you want to create your own splash-screen, then follow the next steps, otherwise skip to step 3
 a. Create an image of size 128x64 (or fewer lines). You can use Paint. I prefer paint.net (free)
 b. Draw or paste/resize your desired output on the canvas
 c. Better save for later reuse, but this is not necessary
 d. Select the entire 128x64 canvas, and copy
 e. Open the supplied SplashScreenConverter tool
 f. Click the "Paste image from clipboard" button
 e. "Image copied from clipboard" shows the image in full color
 f. "Image as it will look on the display" shows the monochrome image that will be shown on the display
 g. Unless you used a monochrome image (this gives you most control) you can change the treshold to 
    adjust which pixels should light up
 h. Copy the output in the lower text box
 i. Paste this content into the empty SplashScreen.h file, and save it
3. Install the Arduino IDE (Get it here: http://arduino.cc/en/main/software )
4. Install the driver for your Arduino USB chip. You should get this from your supplier
5. Open the VDO.ino Arduino project file
6. Connect the Arduino to the OLED display and VDO instrument, see instructions on 
   http://mtech.dk/thomsen/Husky/repairs/index.php
7. Connect the Arduino to the PC
8. Select ONE of the "#define USE_SEGMENTS" lines and ONE of the "#define USECOMMA" lines
9. Press the "compile and download" button
10. Done

"#define USE_SEGMENTS 0" results in an Arial style font (unknown characters will be written with a 7-segment font)
"#define USE_SEGMENTS 1" results in a 7-segment style font

"#define USE_SEGMENTS 2" results in the Arduino selecting the font based on a jumper setting:

Jumper on D2+D3 selects the Arial style font
Jumper on D3+D4 selects the 7-segment font

You can use this if you want to be able to select the font without recompiling and redownloading the code.
Note that if USE_SEGMENTS 2 is selected and no jumper is present the Arduino will arbitrarily select one or the other depending on the voltage level when the pin is sampled during startup.
