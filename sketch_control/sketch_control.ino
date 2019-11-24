/*
   The pump control is connected to the PIN 7
   The Tiny RTC I2C is connected to the A4 for the SDA intput and A5 for the SCL input PIN
   The LCD 1602A is connected following those instructions :
   LCD RS pin to digital pin 12
   LCD Enable pin to digital pin 11
   LCD D4 pin to digital pin 5
   LCD D5 pin to digital pin 4
   LCD D6 pin to digital pin 3
   LCD D7 pin to digital pin 2
   LCD R/W pin to ground
   LCD VSS pin to ground
   LCD VCC pin to 5V
   10K resistor:
   ends to +5V and ground
   wiper to LCD VO pin (pin 3)

   It's driven by the library : http://www.arduino.cc/en/Tutorial/LiquidCrystal
*/

// include the library code:
#include <LiquidCrystal.h>
#include <Wire.h>
#include "RTClib.h"

void printTime() ;

int pumpControlPin = 7;
int lightControlPin = 8;
int menuButtonPin = 9;
int selectButtonPin = 10;
RTC_DS1307 RTC;
char rtcStatus;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  pinMode(pumpControlPin, OUTPUT);
  pinMode(lightControlPin, OUTPUT);
  pinMode(menuButtonPin, INPUT_PULLUP);
  pinMode(selectButtonPin, INPUT_PULLUP);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  //Setup the RTC module communication
  rtcStatus = 0;
  Wire.begin();
  RTC.begin();
  // Check to see if the RTC is keeping time.  If it is, load the time from your computer.
  if (! RTC.isrunning()) {
    // This will reflect the time that your sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  } else {
    rtcStatus = 1;
  }
}

void loop() {
  lcd.clear();
  lcd.setCursor(0, 0);

  if (rtcStatus == 0) {
    lcd.print("RTC battery HS");
  } else {
    printTime();
  }
  delay(1000);
}

void printTime() {
  DateTime now = RTC.now();
  char buf[ 16 ];
  sprintf( buf, "%02d/%02d/%02d", now.day(), now.month(), now.year());
  lcd.setCursor(0, 0); //On se place sur la permiere ligne
  lcd.print(buf);

  sprintf( buf, "%02d:%02d:%02d", now.hour(), now.minute(), now.second() );
  lcd.setCursor(0, 1); //On se place sur la deuxième ligne
  lcd.print(buf);
}



