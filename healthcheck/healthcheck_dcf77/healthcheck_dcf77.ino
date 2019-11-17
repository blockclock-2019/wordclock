/*
 * healthcheck_dcf77.ino
 * Healthcheck code for the wordclocks dcf module
 * Superengine, 2019
 * 
 * This healthcheck checks, wether the dcf77 receiver module of the wordclock is
 * working correctly. This should work on the WeMos D1 Mini
 * 
 * Required libraries:
 * DCF77 by Thijs Elenbaas  | https://github.com/thijse/Arduino-Libraries/downloads for ESP8266 boards, don't forget to add the ICACHE_RAM_ATTR to the int0handler function
 * Time                     | http://www.arduino.cc/playground/Code/Time
 * 
 * 
 */

#include <DCF77.h>
#include <Time.h>

#define DCF_PIN D2 //This is pin D2

DCF77 DCF = DCF77(DCF_PIN, digitalPinToInterrupt(DCF_PIN));

void setup() {
  Serial.begin(9600);
  Serial.println("Serialport is now open at 9600 Bauds");
  
  DCF.Start();

  Serial.println("Waiting for the DCF77 module to sync ...");
  Serial.println("A sync will take at least 2 minutes, even under perfect conditions");
}

void loop() {
  delay(1000);
  time_t DCFtime = DCF.getTime();
  if (DCFtime!=0) {
      tmElements_t tm;   
      breakTime(DCFtime, tm);
      setTime(DCFtime);
      Serial.println("Es ist laut soeben erfolgter synchronisierung: " + (String)tm.Hour + ":" + (String)tm.Minute + ":" + (String)tm.Second);
  }
  Serial.println("Es ist " + (String)hour() + ":" + (String)minute() + ":" + (String)second());
}
