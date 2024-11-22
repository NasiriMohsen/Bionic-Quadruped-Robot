#include "Quadruped.h"

String input = "down";

void setup() {
    Setup_Legs();
    Flat();
    delay(1000);
    Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    input = Serial.readString();
    input.trim();
  }
  if (input == "run") {
//------------------------------------------------- 
  Turn_Left_Hostile_R(100);
  delay(1000);
  Turn_Left_Hostile_R(100);
  delay(1000);
  Turn_Left_Hostile_R(100);
  delay(1000);
  Turn_Left_Hostile_L(100);
  delay(1000);
  Turn_Left_Hostile_L(100);
  delay(1000);
  Turn_Left_Hostile_L(100);
  delay(1000);
//-------------------------------------------------
  }else if (input == "down"){
    Flat();
  } else {
    Hostile();
  }
}
