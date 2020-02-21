// Adafruit test program modified by Andrew Donatelli for BD1 droid rear panel

// NEOPIXEL BEST PRACTICES for most reliable operation:
// - Add 1000 uF CAPACITOR between NeoPixel strip's + and - connections.
// - MINIMIZE WIRING LENGTH between microcontroller board and first pixel.
// - NeoPixel strip's DATA-IN should pass through a 300-500 OHM RESISTOR.
// - AVOID connecting NeoPixels on a LIVE CIRCUIT. If you must, ALWAYS
//   connect GROUND (-) first, then +, then data.
// - When using a 3.3V microcontroller with a 5V-powered NeoPixel strip,
//   a LOGIC-LEVEL CONVERTER on the data line is STRONGLY RECOMMENDED.
// (Skipping these may work OK on your workbench but can fail in the field)

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    6

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 96

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)f


// setup() function -- runs once at startup --------------------------------

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(30); // Set BRIGHTNESS (max = 255)

  Serial.begin(9600);
  randomSeed(analogRead(0));
  colorStrip(strip.Color(0,   0,   255) ,1); // start with a blue background
}


// loop() function -- runs repeatedly as long as board is on ---------------

void loop() {

   
  //Blue
  twinkle(strip.Color(0,   0,   255), strip.Color(255,   255,   255), 3, 10); 

  //Cyan
  twinkle(strip.Color(0,  255,   255), strip.Color(0,   255,   127), 2, 0);

  //Green
  twinkle(strip.Color(0,   255,   0), strip.Color(255,   255,   0), 3, 0);

  //Yellow
  twinkle(strip.Color(255,   255,   0), strip.Color(255,   114,   0), 1, 10);

  //Orange
  twinkle(strip.Color(255,   114,   0), strip.Color(255,   0,   0), 1, 10);

  //Red
  twinkle(strip.Color(255,   0,   0), strip.Color(210,   0,   255), 2, 10);

  //Purple
  twinkle(strip.Color(180,   0,   255), strip.Color(80,   0,   255), 1, 10);


}



/*
  Twinkle function:
  by Andrew Donatelli 02/21/2020
  main color, secondary color, number of cycles, delay
*/
void twinkle(uint32_t color,uint32_t color2, int cycles, int wait) {
  for(int c=0; c<=cycles; c++) { // Number of times to cycle through
    for(int i=0; i<strip.numPixels()/3; i++) { // For each pixel in strip...

      // Select 4 random pixels
      int r1=random(0,96);
      int r2=random(0,96);
      int r3=random(0,96);
      int r4=random(0,96);
      
      int flashMode=random(0,2); // chance to ramp up or instant on
      
      int multiPixel=random(0,3);  // chance to have more than 1 LED light up
      
      int multiPixelLength=random(4,10);  // length of multiple pixel row

      int rowMode = random(0,6); // chance to light up row sequentially

      if (random(0,10) == 0){ // chance of top row flashing like in the game
        multiPixelLength = 13;
        r1=21;
        rowMode = 1; // always fade mode for top row
      }
      
     
      int x = random(3,6); // random fade speed

      if (rowMode == 0){ // chance to light up row sequentially
        if (multiPixel == 1) { //light up row of LEDS
            for (int r=0; r <= multiPixelLength; r = r + 1){
              strip.setPixelColor(r1 + r*4,color, 255);
              strip.show();
              delay(30);
            }  
          }
      }

        
      for (int b=20; b <= 255; b = b + x) {
        strip.setPixelColor(r1,color, b*255/255);

        if (rowMode > 0){
          if (multiPixel == 1) { // light up row of LEDS
            for (int r=0; r <= multiPixelLength; r = r + 1){
              strip.setPixelColor(r1 + r*4,color, b);
            }  
          }

        // Turn on the 4 random LEDs with varying brightness
        strip.setPixelColor(r1,color, b); 
        strip.setPixelColor(r2,color2, b*100/255); 
        strip.setPixelColor(r3,color, b*85/255); 
        strip.setPixelColor(r4,color, b*20/255); 
        strip.show();
        }
      
      }


      if (multiPixel == 1) { // dim row of LEDS
        for (int b=255; b >= random(15,40); b = b - x) {  // fade out to random dimness
          for (int r=multiPixelLength; r >= 0; r = r - 1){
              strip.setPixelColor(r1 + r*4,color, b); 
          }
          strip.show();
        }

      }
      
      if (flashMode <1){ //chance to fade out
        for (int b=255; b >= random(0,60); b = b - x) {  // fade out to random dimness

          // Fade the 4 pixels
          strip.setPixelColor(r1,color, b);
          strip.setPixelColor(r2,color2, b); 
          strip.setPixelColor(r3,color, b); 
          strip.setPixelColor(r4,color, b); 
          strip.show();
 
      
        }
      }
    
     
    delay(wait);
     
    }
  }
}

// Fill the entire strip with a single color
void colorStrip(uint32_t color, int randB ) {
  int bright = 255;

  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    
    if (randB == 1) {
      bright = random(0,255);
    }
    
    strip.setPixelColor(i, color, bright);   //  Set pixel's color (in RAM)  
  }
  strip.show();  
}
// End of BD1 Specific funtions.  I'm leaving the Adafruit functions below in case you want to use them - Andrew Donatelli


// Some functions of our own for creating animated effects -----------------

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this outer loop:
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}
