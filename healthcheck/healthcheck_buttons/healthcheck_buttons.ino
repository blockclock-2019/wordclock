/*
    This program is free software: you can redistribute it and/or modify
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


#define BTN_NEXT D7 //Pin for Next-button
#define BTN_PREV D6 //Pin for previous-button
#define SEL_MOD1 D1 //This mode is for moving hours
#define SEL_MOD2 D2 //This mode is for moving 5 Minutes
#define SEL_MOD3 D5 //This mode is for changing colors

const float version = 2.35;

void setup() {
  pinMode(BTN_NEXT, INPUT);
  pinMode(BTN_PREV, INPUT);
  pinMode(SEL_MOD1, INPUT);
  pinMode(SEL_MOD2, INPUT);
  pinMode(SEL_MOD3, INPUT);
  Serial.begin(9600);
  Serial.println("Firmware version: BUTTON-HEALTHCHECK " + (String)version);
  Serial.println("Please follow the instructions from the serialport");
}

void loop() {
  Serial.println("Please press the next-button!");
  while(digitalRead(BTN_NEXT) == LOW) delay(100);
  Serial.println("Success!");
  
  Serial.println("Please press the previous-button!");
  while(digitalRead(BTN_PREV) == LOW) delay(100);
  Serial.println("Success!");

  Serial.println("Please put the mode-switch into hour-mode!");
  while(digitalRead(SEL_MOD1) == LOW) delay(100);
  Serial.println("Success!");

  Serial.println("Please put the mode-switch into minute-mode!");
  while(digitalRead(SEL_MOD2) == LOW) delay(100);
  Serial.println("Success! Assuming, color-mode is wired correctly.");
  
  Serial.println("Test successful!");
  Serial.println("The test will be restarted in 10 seconds. If anything was wrong, you can swap it now if the switches are unpluggable.");
  delay(10000);
}
