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


#define MODE1 D1
#define MODE2 D2
#define MODE3 D5
#define PREV D7
#define NEXT D6


void setup() {
  pinMode(MODE1, INPUT);
  pinMode(MODE2, INPUT);
  pinMode(MODE3, INPUT);
  pinMode(PREV, INPUT);
  pinMode(NEXT, INPUT);
  Serial.begin(9600);
  Serial.println("Press any button you like");
}

void loop() {
  if(digitalRead(PREV) == HIGH) {
    if(digitalRead(MODE1) == HIGH) {
      Serial.println("Button previous was pressed! Current mode is MODE1"); 
    }
    if(digitalRead(MODE2) == HIGH) {
      Serial.println("Button previous was pressed! Current mode is MODE2");
    }
    if(digitalRead(MODE3) == HIGH) {
      Serial.println("Button previous was pressed! Current mode is MODE3");
    }
  }

  if(digitalRead(NEXT) == HIGH) {
    if(digitalRead(MODE1) == HIGH) {
      Serial.println("Button next was pressed! Current mode is MODE1"); 
    }
    if(digitalRead(MODE2) == HIGH) {
      Serial.println("Button next was pressed! Current mode is MODE2");
    }
    if(digitalRead(MODE3) == HIGH) {
      Serial.println("Button next was pressed! Current mode is MODE3");
    }
  }
  delay(100);
}
