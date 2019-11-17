#include <FastLED.h>
#define NUM_LEDS 121
#define DATA_PIN D4

CRGB leds[NUM_LEDS];
    
void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness( 40 );
  Serial.begin(9600);
  Serial.println("Starting display test! Send a 'n' to commence the next test part!");

  //Full white
  Serial.println("First test: full white display!");
  for(int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::White; 
  }
  FastLED.show();

  //Questioning the (world), i meant the serialport
  while(!Serial.available()) {
    delay(10);
  }
  Serial.readString();
  
  //Full off
  Serial.println("Second test: Display will turn off!");
  for(int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Black; 
  }
  FastLED.show();

  //Questioning the (world), i meant the serialport
  while(!Serial.available()) {
    delay(10);
  }
  Serial.readString();

  //Full red
  Serial.println("Third test: full red display!");
  for(int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Red;
  }
  FastLED.show();

  //Questioning the (world), i meant the serialport
  while(!Serial.available()) {
    delay(10);
  }
  Serial.readString();

  //Full green
  Serial.println("Fourth test: full green display!");
  for(int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Green;
  }
  FastLED.show();

  //Questioning the (world), i meant the serialport
  while(!Serial.available()) {
    delay(10);
  }
  Serial.readString();

  //Full blue
  Serial.println("Fifth test: full blue display!");
  for(int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Blue;
  }
  FastLED.show();

  //Questioning the (world), i meant the serialport
  while(!Serial.available()) {
    delay(10);
  }
  Serial.readString();

  //striped
  Serial.println("Sixth test: striped display!");
  Serial.println("Colors (top to bottom, HTML 4.01 webcolors):");
  Serial.println("Fuchsia");
  Serial.println("Teal");
  Serial.println("White");
  Serial.println("Black");
  Serial.println("Maroon");
  Serial.println("Lime");
  Serial.println("Yellow");
  Serial.println("Purple");
  Serial.println("Green");
  Serial.println("Red");
  Serial.println("Blue");
  Serial.println("");
  for(int i = 0; i < NUM_LEDS; i++) {
      if(i >= 0 && i < 11){
        leds[i] = CRGB::Blue;
      } else if(i >= 11 && i < 22){
        leds[i] = CRGB::Red;
      } else if(i >= 22 && i < 33){
        leds[i] = CRGB::Green;
      } else if(i >= 33 && i < 44){
        leds[i] = CRGB::Purple;
      } else if(i >= 44 && i < 55){
        leds[i] = CRGB::Yellow;
      } else if(i >= 55 && i < 66){
        leds[i] = CRGB::Lime;
      } else if(i >= 66 && i < 77){
        leds[i] = CRGB::Maroon;
      } else if(i >= 77 && i < 88){
        leds[i] = CRGB::Black;
      } else if(i >= 88 && i < 99){
        leds[i] = CRGB::White;
      } else if(i >= 99 && i < 110){
        leds[i] = CRGB::Teal;
      } else if(i >= 110 && i < 121){
        leds[i] = CRGB::Fuchsia;
      }
  }
  FastLED.show();

  //Questioning the (world), i meant the serialport
  while(!Serial.available()) {
    delay(10);
  }
  Serial.readString();

  //counting up
  for(int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Black;
  }
  FastLED.show();
  
  Serial.println("Seventh test: pixel moving up!");
  for(int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::White;
      FastLED.show();
      delay(100);
      leds[i] = CRGB::Black;
  }

  for(int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Black;
  }
  FastLED.show();

  //Questioning the (world), i meant the serialport
  while(!Serial.available()) {
    delay(10);
  }
  Serial.readString();

  //Complete
  Serial.println("The test is over, you can now test the dcf receiver, \n or if this is already done, you are ready for the real software");
  
  
}

void loop() {
  for(int i = 0; i < NUM_LEDS; i++) {
      int led = i;
      leds[led] = CRGB::Red; 
      FastLED.show();
      delay(100);
      
      leds[led] = CRGB::Black;
      FastLED.show();
      delay(100);
    }

    for(int i = 0; i < NUM_LEDS; i++) {
      int led = i;
      leds[led] = CRGB::White; 
      
    }
    FastLED.show();
    delay(5000);

    for(int i = 0; i < NUM_LEDS; i++) {
      int led = i;
      leds[led] = CRGB::Black; 
      
    }

    FastLED.show();
}
