// code adapted from https://museumexp.wordpress.com/2013/12/03/idiots-guide-to-rotary-dip-switch-16-position-rotary-encoder/
// created 6/16/2020
// by Paul Lindberg

//set constants
int P_1 = 4;//2
int P_2 = 2;//3
int P_3 = 14;//4
int P_4 = 15;//5

//set variables
int switchState1 = 0;
int switchState2 = 0;
int switchState3 = 0;
int switchState4 = 0;
byte test = B0000; //byte for printing the value

void rotaryModes(int pin1, int pin2, int pin3, int pin4) {
  P_1 = pin1;
  P_2 = pin2;
  P_3 = pin3;
  P_4 = pin4;
  pinMode(P_1, INPUT);
  pinMode(P_2, INPUT);
  pinMode(P_3, INPUT);
  pinMode(P_4, INPUT);
}

byte rotaryRead() {
  switchState1 = digitalRead(P_1);
  switchState2 = digitalRead(P_2);
  switchState3 = digitalRead(P_3);
  switchState4 = digitalRead(P_4);

  if (switchState1 == HIGH) {
    Serial.println("pin1 = HIGH");
    bitSet(test, 0);
  }
  else {
    Serial.println("Pin1 = LOW");//“Pin1 = LOW”
    bitClear(test, 0); //sets bit 0 (rightmost bit -000(0)) to 0
  }
  if (switchState2 == HIGH) {
    Serial.println("pin2 = HIGH");
    bitSet(test, 1); //sets bit 1 (second rightmost bit -00(1)0) to 1
  }
  else {
    Serial.println("pin2 = LOW");
    bitClear(test, 1); //sets bit 1 (second rightmost bit -00(0)0) to 0
  }
  if (switchState3 == HIGH) {
    Serial.println("pin3 = HIGH");
    bitSet(test, 2); //sets bit 2 (second leftmost bit -0(1)00) to 1
  }
  else {
    Serial.println("pin3 = LOW");
    bitClear(test, 2); //sets bit 2 (second leftmost bit -0(0)00) to 0
  }
  if (switchState4 == HIGH) {
    Serial.println("pin4 = HIGH");
    bitSet(test, 3); //sets bit 3 (leftmost bit -(1)000) to 1
  }
  else {
    Serial.println("pin4 = LOW");
    bitClear(test, 3); //sets bit 3 (leftmost bit -(0)000) to 1
  }
  Serial.println("\n");

  //Remove comment on these lines to see binary output:
  //Serial.print(switchState1);
  //Serial.print(switchState2);
  //Serial.print(switchState3);
  //Serial.println(switchState4);

  Serial.println(char(test) + 0); //converts to char, and prints ASCII value of 0-15
  //Serial.println(char(test) +1);//uncomment for 1-16…
  Serial.println("\n");
  return test;
}
