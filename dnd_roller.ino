#include "arduino_secrets.h"
/*
  Discord DnD Roller for ESP8266
  Code Adapted from:
  https://technoreview85.com/how-to-program-esp-32-cam-using-arduino-uno-board/
*/
#include "discord.h"
#include "rotaryswitch.h"

//const int pinLed = LED_BUILTIN;
const int pinButtonRoll = 12;//D0;//12;
const int pinSwitchSides = 13;//D2;//13;
const int pinSwitchNum = 16;//D3;//16;
const int pinRotary_1 = 4;//D6;//4;
const int pinRotary_2 = 2;//D7;//2;
const int pinRotary_3 = 14;//D5;//14;
const int pinRotary_4 = 15;//D8;//15;

int stateButton = 0;
int num = 1;
int sides = 20;

void setup() {
  pinMode(pinButtonRoll, INPUT);
  pinMode(pinSwitchSides, INPUT);
  pinMode(pinSwitchNum, INPUT);
//  pinMode(pinLed, OUTPUT);
  rotaryModes(pinRotary_1, pinRotary_2, pinRotary_3, pinRotary_4);
  Serial.begin(9600);
  connectWIFI();
//  flash();
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

////activate the flashlight temporarily
//void flash() {
//  digitalWrite(pinLed, LOW);
//  delay(300);
//  digitalWrite(pinLed, HIGH);
//  delay(300);
//}
