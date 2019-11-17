
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
