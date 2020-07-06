#include "arduino_secrets.h"
/*
  Discord DnD Roller for ESP32
  Code Adapted from:
  https://technoreview85.com/how-to-program-esp-32-cam-using-arduino-uno-board/
*/
#include "discord.h"
#include "rotaryswitch.h"
//#include "SD_MMC.h"

const int pinLed = BUILTIN_LED;
const int pinButtonRoll = 12;
const int pinSwitchSides = 13;
const int pinSwitchNum = 16;
const int pinRotary_1 = 4;
const int pinRotary_2 = 2;
const int pinRotary_3 = 14;
const int pinRotary_4 = 15;

int stateButton = 0;
int num = 1;
int sides = 20;

void setup() {
  pinMode(pinButtonRoll, INPUT); // initialize pin 12 as input
  pinMode(pinSwitchSides, INPUT); // initialize pin 14 as input
  pinMode(pinSwitchNum, INPUT); // initialize pin 15 as input
  pinMode(pinLed, OUTPUT); // initialize pin 4 as output
  rotaryModes(pinRotary_1, pinRotary_2, pinRotary_3, pinRotary_4);
  Serial.begin(9600);
//  SD_MMC.begin("/sdcard", true);
  connectWIFI();
  flash();
}

void loop() {
  stateButton = digitalRead(pinButtonRoll);
  num = switchRead(pinSwitchNum, 2, 1);
  sides = rotaryConvert();//switchRead(pinSwitchSides, 8, 20);
  if (stateButton == HIGH) { //check button press state, if high
    sendDiscord("!" + String(num) + "d" + String(sides));//# @Bart"); //send message
//    flash(); //blink led
  }
}

int switchRead(int pin, int x, int y) {
  if (digitalRead(pin) == HIGH) {
    return x;
  }
  return y;
}

int rotaryConvert() {
  sides = int(char(rotaryRead()) + 0);//TEST JUST "sides = rotaryRead();"
  if (sides == 0) {
    return 4;
  }
  else if (sides == 1) {
    return 6;
  }
  else if (sides == 2) {
    return 8;
  }
  else if (sides == 3) {
    return 10;
  }
  else if (sides == 4) {
    return 12;
  }
  else if (sides == 5) {
    return 20;
  }
  else {
    return 0;
  }
}

//activate the flashlight temporarily
void flash() {
  digitalWrite(pinLed, 1);
  delay(100);
  digitalWrite(pinLed, 0);
}
