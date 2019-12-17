/*     This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <FastLED.h> //http://fastled.io/
#include <Time.h> //https://github.com/PaulStoffregen/Time
#include <stdlib.h> //This is a standard arduino library
#include <StringSplitter.h> //https://github.com/aharshac/StringSplitter The limit needs to be increased


//LED-display controlls
#define NUM_LEDS 121 //Amount of LEDs in the display -- Don't change this, except if you know, what you are doing but then you will also have to change the code marked as "please don't change"
#define DATA_PIN D4 //Pin for controlling the LEDs

//Button-pin controlls --- Do not edit except the hardware changed
#define BTN_NEXT D7 //Pin for Next-button
#define BTN_PREV D6 //Pin for previous-button
#define SEL_MOD1 D1 //This mode is for moving hours
#define SEL_MOD2 D2 //This mode is for moving 5 Minutes
#define SEL_MOD3 D5 //This mode is for changing colors

//Day-/nightmode controlls
#define nightmode true //This is for toggling on and off day/nightmode
#define NIGHT_START 22 //This is the time when the nightmode should be enabled
#define NIGHT_END 8 //This is the time when the nightmode should be disabled
#define brightnessDay 100 //This is the brightness in daymode
#define brightnessNight 25 //This is the brightness in nightmode

//Delay controls
#define BTN_DELAY 250 //This is for setting the time after which the next button press can be registered, this is to stop unexpected behaviour Default: 250
#define LOOP_DELAY 50 //This is for setting the delay in the loop in milliseconds setting this to values higher than 100 will make the clock feel unresponsive Default: 50



//Please don't edit the code here until allowed again
// -%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%- //
int time_it_is[] = {110, 111, 113, 114, 115}; //This array saves the LEDs required for the part of the display that says "Es ist"
  
int time_minutes[][12] = { //This array saves the LEDs that are required for each minute step
  { 13,  12,  11,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1},
  {117, 118, 119, 120,  85,  84,  83,  82,  -1,  -1,  -1,  -1},
  {109, 108, 107, 106,  85,  84,  83,  82,  -1,  -1,  -1,  -1},
  { 92,  93,  94,  95,  96,  97,  98,  85,  84,  83,  82,  -1},
  {105, 104, 103, 102, 101, 100,  99,  85,  84,  83,  82,  -1},
  {117, 118, 119, 120,  81,  80,  79,  66,  67,  68,  69,  -1},
  { 66,  67,  68,  69,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1},
  {117, 118, 119, 120,  85,  84,  83,  82,  66,  67,  68,  69},
  {105, 104, 103, 102, 101, 100,  99,  81,  80,  79,  -1,  -1},
  { 92,  93,  94,  95,  96,  97,  98,  81,  80,  79,  -1,  -1},
  {109, 108, 107, 106,  81,  80,  79,  -1,  -1,  -1,  -1,  -1},
  {117, 118, 119, 120,  81,  80,  79,  -1,  -1,  -1,  -1,  -1}
};

int time_hours[][6] = { //This array saves the LEDs that are required for each hour
  {71, 72, 73, 74, 75, -1},
  {63, 62, 61, 60, -1, -1},
  {65, 64, 63, 62, -1, -1},
  {45, 46, 47, 48, -1, -1},
  {36, 35, 34, 33, -1, -1},
  {51, 52, 53, 54, -1, -1},
  {20, 19, 18, 17, 16, -1},
  {60, 59, 58, 57, 56, 55},
  {23, 24, 25, 26, -1, -1},
  {40, 39, 38, 37, -1, -1},
  {27, 28, 29, 30, -1, -1},
  {43, 42, 41, -1, -1, -1}
};
// -%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%- //
//From here on you may edit the code again

//Here the declaration of variables begins and a first method and a struct are defined

typedef struct { 
  int r;
  int g;
  int b;
} color_t;

// ------------

color_t getColor(int red, int green, int blue) { //This is for converting three values, r, g and b, to a color
  color_t ret;
  ret.r = red;
  ret.g = green;
  ret.b = blue;
  return ret;  
}

// ------------

CRGB leds[NUM_LEDS];
/*int r = 255;
int g = 255; This really seems to do nothing
int b = 255;*/

//HERE ARE THE VARIABLES FOR THE FIRMWAREVERSION AND DISTRIBUTOR INFO
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
const float version = 2.36; //This is the version, it should be counted as follows Major.MinorBugfix
const String vendor = "Superengine"; //This is where the vendor company's name should go
const String name = "clockOS"; //This is the name for the system
const String releaseType = "release"; //Here is room for a release note like: PRE-ALPHA, ALPHA, BETA, CANDIDATE, release and LEGACY
const String releaseDate = "2019/12/17"; //This is for saving the date on that this version was finished
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

color_t bgColor; //This is the variable that saves the background color
color_t fgColor; //This is the variable that saves the foreground color

int lastHour; //This is used to determine whether the hour changed since the last run of the loop

volatile boolean nextp = false; //This is used to determine if the next-button was pressed since the last check
volatile boolean prevp = false; //This is used to determine if the previous-button was pressed since the last check

volatile long lastp = millis(); //This is used to determine if the previous-button-press is valid
volatile long lastn = millis(); //This is used to determine if the next-button-press is valid

int colorPos = 0; //This is used to determine what color should be used if it changes from a button-press

color_t colors[] = {getColor(255, 255, 255), getColor(255, 0, 0), getColor(0, 255, 0), getColor(0, 0, 255), getColor(255, 255, 0), getColor(0, 255, 255), getColor(255, 0, 255), getColor(255, 0, 102), getColor(51, 153, 255), getColor(0, 204, 153)}; //Here are the built-in colors
const int colAm = 10; //This saves the amount of built in colors


//Here all the methods used for the wordclock are declared
void setDisplayTime(int h, int m) { //This sets the display to the time
  if(m%5 <= 2) { //Checking what direction to round
    m = (m - (m % 5));
  } else {
    m = m + (5-(m%5));
  }

  
  if(m >= 23) { //If 30 minutes have passed it's time for the next hour to show
    h += 1;
  }
  if(m >= 58) { //If this case happens it should not only count up the hour, but also reset the minutes to 0
    m = 0;  
  }

  m = m / 5; //Calculating what minute amount should be chosen from the array of minutes
  h = h % 12; //Calculating the amount of hours to be chosen from the array

  for(int i = 0; i < NUM_LEDS; i++) { //setting all LEDs to the background color
    leds[i].setRGB(bgColor.r * 0.2, bgColor.g * 0.2, bgColor.b * 0.2);
  }
  
  for(int i = 0; i < 5; i++) { //Turning on the LEDs showing "Es ist"
    leds[time_it_is[i]].setRGB(fgColor.r, fgColor.g, fgColor.b);
  } 
  if(h == 1 && m == 0) { //If it is 1 o'clock, those LEDs must be turned on
    leds[11].setRGB(fgColor.r, fgColor.g, fgColor.b);
    leds[12].setRGB(fgColor.r, fgColor.g, fgColor.b);
    leds[13].setRGB(fgColor.r, fgColor.g, fgColor.b);
    leds[61].setRGB(fgColor.r, fgColor.g, fgColor.b);
    leds[62].setRGB(fgColor.r, fgColor.g, fgColor.b);
    leds[63].setRGB(fgColor.r, fgColor.g, fgColor.b);
  } else {
    for(int mm = 0; mm < 12; mm++) { //Here the minute LEDs according to the minute count turn on
      if(time_minutes[m][mm] >= 0) {
        leds[time_minutes[m][mm]].setRGB(fgColor.r, fgColor.g, fgColor.b);
      }
    }

    for(int hh = 0; hh < 6; hh++) { //Here the hour LEDs according to the hour count turn on
      if(time_hours[h][hh] >= 0) {
          leds[time_hours[h][hh]].setRGB(fgColor.r, fgColor.g, fgColor.b);
      }
    }
  }

  FastLED.show(); //Show the set pattern on the display
}

// ------------

void ICACHE_RAM_ATTR nextPress() { //This is the interrupt function triggered, when the next-button is pressed, the ICACHE_RAM_ATTR flag is required, so the function is loaded into ram for the interrupt to work
  if(millis()-lastn > BTN_DELAY) { //Checking whether the button-press is valid
    nextp = true;
    lastn = millis();
  } 
}

// ------------

void ICACHE_RAM_ATTR prevPress() { //This is the interrupt function triggered, when the previous-button is pressed
  if(millis()-lastp > BTN_DELAY) { //Checking whether the button-press is valid
    prevp = true;
    lastp = millis();
  }
}

// ------------

void addHour() {
  time_t t = now();
  if((signed int)hour(t)+1 < 24) { //checking for hour counts higher than 24, nothing should happen if this isn't done
    setTime(hour(t)+1, minute(t), second(t), day(t), month(t), year(t));
  } else {
    setTime(0, minute(t), second(t), day(t), month(t), year(t));
  }
}

// ------------

void add5Minutes() {
  time_t t = now();
  if((signed int)minute(t)+5 < 60) { //Checking for minute counts higher than 60, this is for good measure, nothing should happen, if we don't do it
    setTime(hour(t), minute(t)+5, second(t), day(t), month(t), year(t));
  } else {
    setTime(hour(t), minute(t)+5-60, second(t), day(t), month(t), year(t));  
    addHour();
  }
}

// ------------

void removeHour() {
  time_t t = now();
  if((signed int)hour(t)-1 >= 0) { //Make sure not to have a negativ amount of hours, weird stuff will happen
    setTime(hour(t)-1, minute(t), second(t), day(t), month(t), year(t));
  } else {
    setTime(23, minute(t), second(t), day(t), month(t), year(t));  
  }
}

// ------------

void remove5Minutes() {
  time_t t = now();
  if((signed int)minute(t)-5 >= 0) { //Make sure the hour doesn't have to change, if it goes to a negative amount of minutes, strange things happen
    setTime(hour(t), minute(t)-5, second(t), day(t), month(t), year(t));
  } else {
    setTime(hour(t), minute(t)-5+60, second(t), day(t), month(t), year(t));
    removeHour();
  }
}

// ------------

void cycleColors(char c) { //Here is the method for cycling through the colors
  if(c == 'n') { //If the char is n we will change to the next color
    colorPos++;
    if(colorPos >= colAm) { //if the selected color index is larger than the array set it to 0 again
      colorPos = 0;  
    }
    fgColor = colors[colorPos];
  } else { //If the char is something else, but should only be 'c' we change to the previous color
    colorPos--;
    if(colorPos < 0) { //If the selected index is smaller than 0 now, we set it to the highest allowed index
      colorPos = colAm-1;  
    }
    fgColor = colors[colorPos];
  }
}

// ------------

color_t hexToRGB(String colorString) { //Here is the method for converting the Hexcolors to RGB
  char colorCh[7];
  colorString.toCharArray(colorCh, 7); //the colorstring is split into a char array
  char re[3] = {colorCh[0], colorCh[1], NULL}; //Extracting the colors in these lines and attaching a Null, so the array is null-terminated
  char gr[3] = {colorCh[2], colorCh[3], NULL};
  char bl[3] = {colorCh[4], colorCh[5], NULL};
  
  long r = strtol(re, NULL, 16); //Converting the Hexvalues to decimal in these lines
  long g = strtol(gr, NULL, 16);
  long b = strtol(bl, NULL, 16);

  color_t c; //Creating and returning the resulting rgb-color-struct
  c.r = r;
  c.g = g;
  c.b = b;
  return c;
}

// ------------

void softwareReset( uint8_t prescaller) { //This will reset the board if called
  wdt_enable( prescaller); // start watchdog with the provided prescaller
  while(1) {} // wait for the prescaller time to expire without sending the reset signal by using the wdt_reset() method
}


//Here are the main methods: setup is run once while starting and loop will run in a loop until the controller turns off
void setup() {
  Serial.begin(9600); //Opening the serialport
  for(int i = 0; i <= 50; i++) { //Creating 50 newline calls to clear the connected host's serial console from debris
    Serial.println();  
  }
  Serial.println("Booting up...");

  pinMode(BTN_NEXT, INPUT); //assigning the buttonpins as inputs
  pinMode(BTN_PREV, INPUT);

  attachInterrupt(digitalPinToInterrupt(BTN_NEXT), nextPress, RISING); //attaching the interrupts to the button-pins
  attachInterrupt(digitalPinToInterrupt(BTN_PREV), prevPress, RISING);

  pinMode(SEL_MOD1, INPUT); //assigning the pins for the selector as inputs
  pinMode(SEL_MOD2, INPUT);
  pinMode(SEL_MOD3, INPUT); //This does not need to be used, if you don't have a three-pin selector, or don't want to solder all three pins

  bgColor.r = 0; //Setting the backgroundcolor to black
  bgColor.g = 0;
  bgColor.b = 0;

  fgColor = colors[0]; //Setting the foregroundcolor to the first color

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS); //Initializing the controls for the LEDs
  FastLED.setBrightness(brightnessDay); //Setting the brightness to default day brightness

  setTime(12, 0, 0, 17, 12, 2019); //This is required for the nightmode to work logically

  lastHour = hour(); //initializing the lastHour variable to prevent unexpected behaviour

  for(int i = 0; i < NUM_LEDS; i++) { //Turning all LEDs off
    leds[i].setRGB(0, 0, 0);
  }

  FastLED.show(); //Showing the configured stuff on the display

  Serial.println("Booting finished! Ready."); //Sending the boot finished signal to the serialport
  Serial.println("Firmware version: \"" + vendor + "\" " + name + " " + releaseType + " " + (String)version + " \nRelese Date: " + releaseDate);
}

// ------------

void loop() {
  delay(LOOP_DELAY); //Waiting for the time configured up top

  if(nightmode && hour() != lastHour) { //checking whether the hour changed since the last loop pass
    lastHour = hour(); //setting the lastHour to the current hour to prevent this code from executing in the next pass
    if(hour() >= NIGHT_START || hour() < NIGHT_END) { //if it is nighttime the brightness is lowered
        FastLED.setBrightness(brightnessNight);
    } else {
        FastLED.setBrightness(brightnessDay);  
    }
  }

  // ------------

  if(nextp) { //if a press of button next has occured since the last pass
    if(digitalRead(SEL_MOD1) == HIGH) { //we may add an hour,
      addHour();
    }
    else if(digitalRead(SEL_MOD2) == HIGH) { //add five minutes
      add5Minutes();
    }
    else { //or cycle colors according to the selected mode
      cycleColors('n');
    }
    
    nextp = false; //set this to false, so the next press can be registered
  }

  // ------------

  if(prevp) { //if the previous button was pressed since the last pass
    if(digitalRead(SEL_MOD1) == HIGH) { //we may remove one hour
      removeHour();
    }
    else if(digitalRead(SEL_MOD2) == HIGH) { //remove five minutes
      remove5Minutes();
    }
    else { //or cycle colors backwards
      cycleColors('p');
    }
    
    prevp = false; //set this to false, so the next press can be registered
  }
  
  // ------------
  
  setDisplayTime(hour(), minute()); //setting the displayed time
  
  if(Serial.available()) { //This is the command interpreter
    String command = Serial.readString(); //If something was sent to the serialport, we read the command to the String

    if(command.startsWith("setTime")) {
      Serial.println("Bitte Zeit im Format 'hh:mm:ss:dd:mo:yyyy' eingeben"); //We want to make sure, the user can correctly format their input
      int x = 0;
      boolean suc = true;
      while(!Serial.available()) {
        x++;
        if(x >= 600) { //This will give the user 1 Minute to enter the time before going back to making the clock work
          Serial.println("Die Zeit für die Eingabe ist abgelaufen!");
          break;  
        }
        delay(100);
      }
      if(suc) { //If something was recieved in that minute we read it and set the time accordingly in the following
        command = Serial.readString();
        StringSplitter *splitter = new StringSplitter(command, ':', 6);
        setTime(splitter->getItemAtIndex(0).toInt(), splitter->getItemAtIndex(1).toInt(), splitter->getItemAtIndex(2).toInt(), splitter->getItemAtIndex(3).toInt(), splitter->getItemAtIndex(4).toInt(), splitter->getItemAtIndex(5).toInt()); 
      }
      Serial.println("Es ist " + (String)hour() + ":" + (String)minute() + ":" + (String)second() + " Uhr");
    }

    if(command.startsWith("setfColor")) { //setfColor #ff00ff
      String colorString = command.substring(11, 17); //here we change the foreground color to an input hexcolor
      Serial.println("Setting foregroundcolor to #" + colorString);
      fgColor = hexToRGB(colorString);

      colorPos = 0;
    }

    if(command.startsWith("setbColor")) { //setbColor #ff00ff
      String colorString = command.substring(11, 17); //here we change the foreground color to an input hexcolor
      Serial.println("Setting backgroundcolor to #" + colorString);
      bgColor = hexToRGB(colorString);
    }
    
    if(command.startsWith("reset")) { //This command resets the software of the wordclock
      Serial.println("Restarting...");
      softwareReset(WDTO_15MS);
    }

    if(command.startsWith("getTime")) { //This will print the current time to the serialport
      Serial.println("Es ist " + (String)hour() + ":" + (String)minute() + ":" + (String)second() + " Uhr");
    }

    if(command.startsWith("getTimeDate") && !command.endsWith("getTime")) { //This will print the current time and date to the serialport
      Serial.println("Es ist " + (String)hour() + ":" + (String)minute() + ":" + (String)second() + " Uhr am " + (String)day() + "." + (String)month() + "." + (String)year());
    }
  }
}
