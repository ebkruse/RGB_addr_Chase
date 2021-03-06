#include <Adafruit_NeoPixel.h>

#define PIN 6
#define REDPIN 9
#define GREENPIN 10
#define BLUEPIN 11

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(280, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
}

void loop() {
 
  
  // Some example procedures showing how to display to the pixels:
  colorWipeForward(strip.Color(0, 0, 0), 1); // Red
  theaterChase(strip.Color(4, 4, 4), 50); // White

  colorWipeReverse(strip.Color(0, 0, 0), 1); // Red
  theaterChase(strip.Color(4, 4, 4), 50); // White

  //colorWipe(strip.Color(0, 255, 0), 1000); // Green
  //colorWipe(strip.Color(0, 0, 255), 1000); // Blue
  //colorWipe(strip.Color(127,127,127), 1000); // White
  // Send a theater pixel chase in...
 // theaterChase(strip.Color(127,   0,   0), 50); // Red
 // theaterChase(strip.Color(  0,   0, 127), 50); // Blue

 // rainbow(20);
 // rainbowCycle(20);
 // theaterChaseRainbow(50);
}

// Fill the dots one after the other with a color
void colorWipeForward(long c, int wait) {
  int j = 0;
  for(int i=0; i<strip.numPixels(); i++) {
    
      strip.setPixelColor(i, strip.Color(8,0,0));
      strip.setPixelColor(i-1, strip.Color(0,0,0));

      strip.setPixelColor(i-10, strip.Color(0,8,0));
      strip.setPixelColor(i-11, strip.Color(0,0,0));

      strip.setPixelColor(i-20, strip.Color(0,0,8));
      strip.setPixelColor(i-21, strip.Color(0,0,0));

      strip.setPixelColor(i-30, strip.Color(4,4,4));
      strip.setPixelColor(i-31, strip.Color(0,0,0));
      strip.show();
      
      if (i <= 280)
     {
       j = i/35; 
     }
     else
     {
       j = i/35;
     }
      analogWrite(REDPIN, j);
      analogWrite(GREENPIN, j);
      analogWrite(BLUEPIN, j);
      
    delay(wait);
  }
}
void colorWipeReverse(long c, int wait) {
  int j = 0;
  for(int i=strip.numPixels(); i>=0; i--) {
    
      strip.setPixelColor(i-31, strip.Color(8,0,0));
      strip.setPixelColor(i-30, strip.Color(0,0,0));

      strip.setPixelColor(i-21, strip.Color(0,8,0));
      strip.setPixelColor(i-20, strip.Color(0,0,0));

      strip.setPixelColor(i-11, strip.Color(0,0,8));
      strip.setPixelColor(i-10, strip.Color(0,0,0));

      strip.setPixelColor(i-1, strip.Color(4,4,4));
      strip.setPixelColor(i-0, strip.Color(0,0,0));
      strip.show();
      
      if (i <= 280)
     {
       j = i/35; 
     }
     else
     {
       j = i/35;
     }
      analogWrite(REDPIN, j);
      analogWrite(GREENPIN, j);
      analogWrite(BLUEPIN, j);

    delay(wait);
  }
}

/*void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
*/

// Slightly different, this makes the rainbow equally distributed throughout
/*void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
*/

//Theatre-style crawling lights.
void theaterChase(long c, int wait) {
  for (int j=0; j<5; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      int x=0;
      for (int i=0; i < strip.numPixels(); i=i+3) {
        if( x == 0)
        {
        strip.setPixelColor(i+q, strip.Color(8,0,0));    //turn every third pixel on
        x+=1;
       
        }
        else if (x == 1)
        {
        strip.setPixelColor(i+q, strip.Color(0,8,0));    //turn every third pixel on
        x+=1;
        
        }
        else
        {
        strip.setPixelColor(i+q, strip.Color(0,0,8));    //turn every third pixel on
        x = 0;
        }

      }
      strip.show();
     
      delay(wait);
     
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}


//Theatre-style crawling lights with rainbow effect
/*void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip.show();
       
        delay(wait);
       
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}
*/

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
/*uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
*/

