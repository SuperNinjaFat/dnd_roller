#include "arduino_secrets.h"
/*
  Discord DnD Roller for ESP8266
  Code Adapted from:
  https://technoreview85.com/how-to-program-esp-32-cam-using-arduino-uno-board/
*/
#include "discord.h"
#include "rotaryswitch.h"

//const int pinLed = LED_BUILTIN;
const int pinButtonRoll = D0; 
const int pinSwitchSides = D2;//3;
const int pinSwitchNum = D1;//1;
const int pinRotary_1 = D6;
const int pinRotary_2 = D7;
const int pinRotary_3 = D5;
const int pinRotary_4 = D8;

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
  switchRead(pinSwitchSides, 0, 0);
  sides = rotaryConvert();//switchRead(pinSwitchSides, 8, 20);
  if (stateButton == LOW) { //check button press state, if high
    sendDiscord("!" + String(num) + "d" + String(sides));//# @Bart"); //send message
//    flash(); //blink led
    delay(400);
  }
  delay(300);
}

int switchRead(int pin, int x, int y) {
  if (digitalRead(pin) == LOW) {
    Serial.println("switchpin" + String(pin) + " = LOW");
    return x;
  }
  Serial.println("switchpin" + String(pin) + " = HIGH");
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
