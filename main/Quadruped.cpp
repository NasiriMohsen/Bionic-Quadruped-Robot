#include "Quadruped.h"
#include <Arduino.h>

Servo Hip_BR, Hip_FR, Hip_FL, Hip_BL, Knee_BR, Knee_FR, Knee_FL, Knee_BL;

void Setup_Legs() {
    Hip_BR.attach(PIN_Hip_BR);
    Hip_FR.attach(PIN_Hip_FR);
    Hip_FL.attach(PIN_Hip_FL);
    Hip_BL.attach(PIN_Hip_BL);
    Knee_BR.attach(PIN_Knee_BR);
    Knee_FR.attach(PIN_Knee_FR);
    Knee_FL.attach(PIN_Knee_FL);
    Knee_BL.attach(PIN_Knee_BL);
}

void Toggle_Motors() {
  if (Hip_BR.attached() || Hip_FR.attached() || Hip_FL.attached() || Hip_BL.attached() || Knee_BR.attached() || Knee_FR.attached() || Knee_FL.attached() || Knee_BL.attached()) {
    Hip_BR.detach();
    Hip_FR.detach();
    Hip_FL.detach();
    Hip_BL.detach();
    Knee_BR.detach();
    Knee_FR.detach();
    Knee_FL.detach();
    Knee_BL.detach();    
  } else {
    Setup_Legs();
  }    
}

void Front_Right(int hip, int knee) {
    Hip_FR.write(constrain((hip + Offset_Hip_FR), Servo_min, Servo_max));
    Knee_FR.write(constrain((knee + Offset_Knee_FR), Servo_min, Servo_max));
}

void Front_Left(int hip, int knee) {
    Hip_FL.write(constrain((hip + Offset_Hip_FL), Servo_min, Servo_max));
    Knee_FL.write(constrain((knee + Offset_Knee_FL), Servo_min, Servo_max));
}

void Back_Right(int hip, int knee) {
    Hip_BR.write(constrain((hip + Offset_Hip_BR), Servo_min, Servo_max));
    Knee_BR.write(constrain((knee + Offset_Knee_BR), Servo_min, Servo_max));
}

void Back_Left(int hip, int knee) {
    Hip_BL.write(constrain((hip + Offset_Hip_BL), Servo_min, Servo_max));
    Knee_BL.write(constrain((knee + Offset_Knee_BL), Servo_min, Servo_max));
}

void Forward_L(int knee, int lift) {
  Front_Right(Hip_Default,   knee);
  Back_Right (Left_Default,  lift);
  Back_Left  (Hip_Default,   knee);
  Front_Left (Right_Default, lift);
  delay(Time_Default);
  Front_Right(Right_Default, knee);
  Back_Right (Left_Default,  knee);
  Back_Left  (Left_Default,  knee);
  Front_Left (Right_Default, knee);
  delay(Time_Default);
  Front_Right(Left_Default,  lift);
  Back_Right (Hip_Default,   knee);
  Back_Left  (Right_Default, lift);
  Front_Left (Hip_Default,   knee);
  delay(Time_Default);
  Front_Right(Left_Default,  knee);
  Back_Right (Right_Default, knee);
  Back_Left  (Right_Default, knee);
  Front_Left (Left_Default,  knee);
  delay(Time_Default);
}

void Forward_R(int knee, int lift) {
  Front_Right(Left_Default,  lift);
  Back_Right (Hip_Default,   knee);
  Back_Left  (Right_Default, lift);
  Front_Left (Hip_Default,   knee);
  delay(Time_Default);
  Front_Right(Left_Default,  knee);
  Back_Right (Right_Default, knee);
  Back_Left  (Right_Default, knee);
  Front_Left (Left_Default,  knee);
  delay(Time_Default);
  Front_Right(Hip_Default,   knee);
  Back_Right (Left_Default,  lift);
  Back_Left  (Hip_Default,   knee);
  Front_Left (Right_Default, lift);
  delay(Time_Default);
  Front_Right(Right_Default, knee);
  Back_Right (Left_Default,  knee);
  Back_Left  (Left_Default,  knee);
  Front_Left (Right_Default, knee);
  delay(Time_Default);
}

void Backward_L(int knee, int lift) {
  Front_Right(Hip_Default,   knee);
  Back_Right (Right_Default, lift);
  Back_Left  (Hip_Default,   knee);
  Front_Left (Left_Default,  lift);
  delay(Time_Default);
  Front_Right(Left_Default,  knee);
  Back_Right (Right_Default, knee);
  Back_Left  (Right_Default, knee);
  Front_Left (Left_Default,  knee);
  delay(Time_Default);
  Front_Right(Right_Default, lift);
  Back_Right (Hip_Default,   knee);
  Back_Left  (Left_Default,  lift);
  Front_Left (Hip_Default,   knee);
  delay(Time_Default);
  Front_Right(Right_Default, knee);
  Back_Right (Left_Default,  knee);
  Back_Left  (Left_Default,  knee);
  Front_Left (Right_Default, knee);
  delay(Time_Default);
}

void Backward_R(int knee, int lift) {
  Front_Right(Right_Default, lift);
  Back_Right (Hip_Default,   knee);
  Back_Left  (Left_Default,  lift);
  Front_Left (Hip_Default,   knee);
  delay(Time_Default);
  Front_Right(Right_Default, knee);
  Back_Right (Left_Default,  knee);
  Back_Left  (Left_Default,  knee);
  Front_Left (Right_Default, knee);
  delay(Time_Default);
  Front_Right(Hip_Default,   knee);
  Back_Right (Right_Default, lift);
  Back_Left  (Hip_Default,   knee);
  Front_Left (Left_Default,  lift);
  delay(Time_Default);
  Front_Right(Left_Default,  knee);
  Back_Right (Right_Default, knee);
  Back_Left  (Right_Default, knee);
  Front_Left (Left_Default,  knee);
  delay(Time_Default);
}

void Left_L(int knee, int lift) {
  Front_Right(Left_Default,  lift);
  Back_Right (Hip_Default,   knee);
  Back_Left  (Right_Default, lift);
  Front_Left (Hip_Default,   knee);
  delay(Time_Default);
  Front_Right(Left_Default,  knee);
  Back_Right (Left_Default,  knee);
  Back_Left  (Right_Default, knee);
  Front_Left (Right_Default, knee);
  delay(Time_Default);
  Front_Right(Hip_Default,   knee);
  Back_Right (Right_Default, lift);
  Back_Left  (Hip_Default,   knee);
  Front_Left (Left_Default,  lift);
  delay(Time_Default);
  Front_Right(Right_Default, knee);
  Back_Right (Right_Default, knee);
  Back_Left  (Left_Default,  knee);
  Front_Left (Left_Default,  knee);
  delay(Time_Default);
}

void Left_R(int knee, int lift) {
  Front_Right(Hip_Default,   knee);
  Back_Right (Right_Default, lift);
  Back_Left  (Hip_Default,   knee);
  Front_Left (Left_Default,  lift);
  delay(Time_Default);
  Front_Right(Right_Default, knee);
  Back_Right (Right_Default, knee);
  Back_Left  (Left_Default,  knee);
  Front_Left (Left_Default,  knee);
  delay(Time_Default);
  Front_Right(Left_Default,  lift);
  Back_Right (Hip_Default,   knee);
  Back_Left  (Right_Default, lift);
  Front_Left (Hip_Default,   knee);
  delay(Time_Default);
  Front_Right(Left_Default,  knee);
  Back_Right (Left_Default,  knee);
  Back_Left  (Right_Default, knee);
  Front_Left (Right_Default, knee);
  delay(Time_Default);
}

void Right_L(int knee, int lift) {
  Front_Right(Right_Default, lift);
  Back_Right (Hip_Default,   knee);
  Back_Left  (Left_Default,  lift);
  Front_Left (Hip_Default,   knee);
  delay(Time_Default);
  Front_Right(Right_Default, knee);
  Back_Right (Right_Default, knee);
  Back_Left  (Left_Default,  knee);
  Front_Left (Left_Default,  knee);
  delay(Time_Default);
  Front_Right(Hip_Default,   knee);
  Back_Right (Left_Default,  lift);
  Back_Left  (Hip_Default,   knee);
  Front_Left (Right_Default, lift);
  delay(Time_Default);
  Front_Right(Left_Default,  knee);
  Back_Right (Left_Default,  knee);
  Back_Left  (Right_Default, knee);
  Front_Left (Right_Default, knee);
  delay(Time_Default);
}

void Right_R(int knee, int lift) {
  Front_Right(Hip_Default,   knee);
  Back_Right (Left_Default,  lift);
  Back_Left  (Hip_Default,   knee);
  Front_Left (Right_Default, lift);
  delay(Time_Default);
  Front_Right(Left_Default,  knee);
  Back_Right (Left_Default,  knee);
  Back_Left  (Right_Default, knee);
  Front_Left (Right_Default, knee);
  delay(Time_Default);
  Front_Right(Right_Default, lift);
  Back_Right (Hip_Default,   knee);
  Back_Left  (Left_Default,  lift);
  Front_Left (Hip_Default,   knee);
  delay(Time_Default);
  Front_Right(Right_Default, knee);
  Back_Right (Right_Default, knee);
  Back_Left  (Left_Default,  knee);
  Front_Left (Left_Default,  knee);
  delay(Time_Default);
}

void Turn_Left_L(int knee, int lift) {
  Front_Right(Hip_Default,   knee);
  Back_Right (Left_Default,  lift);
  Back_Left  (Right_Default, knee);
  Front_Left (Hip_Default,   lift);
  delay(Time_Default);
  Front_Right(Right_Default, knee);
  Back_Right (Left_Default,  knee);
  Back_Left  (Right_Default, knee);
  Front_Left (Left_Default,  knee);
  delay(Time_Default);
  Front_Right(Left_Default,  lift);
  Back_Right (Hip_Default,   knee);
  Back_Left  (Hip_Default,   lift);
  Front_Left (Right_Default, knee);
  delay(Time_Default);
  Front_Right(Left_Default,  knee);
  Back_Right (Right_Default, knee);
  Back_Left  (Left_Default,  knee);
  Front_Left (Right_Default, knee);
  delay(Time_Default);
}

void Turn_Left_R(int knee, int lift) {
  Front_Right(Left_Default,  lift);
  Back_Right (Hip_Default,   knee);
  Back_Left  (Hip_Default,   lift);
  Front_Left (Right_Default, knee);
  delay(Time_Default);
  Front_Right(Left_Default,  knee);
  Back_Right (Right_Default, knee);
  Back_Left  (Left_Default,  knee);
  Front_Left (Right_Default, knee);
  delay(Time_Default);
  Front_Right(Hip_Default,   knee);
  Back_Right (Left_Default,  lift);
  Back_Left  (Right_Default, knee);
  Front_Left (Hip_Default,   lift);
  delay(Time_Default);
  Front_Right(Right_Default, knee);
  Back_Right (Left_Default,  knee);
  Back_Left  (Right_Default, knee);
  Front_Left (Left_Default,  knee);
  delay(Time_Default);
}

void Turn_Right_L(int knee, int lift) {
  Front_Right(Hip_Default,   knee);
  Back_Right (Right_Default, lift);
  Back_Left  (Left_Default,  knee);
  Front_Left (Hip_Default,   lift);
  delay(Time_Default);
  Front_Right(Left_Default,  knee);
  Back_Right (Right_Default, knee);
  Back_Left  (Left_Default,  knee);
  Front_Left (Right_Default, knee);
  delay(Time_Default);
  Front_Right(Right_Default, lift);
  Back_Right (Hip_Default,   knee);
  Back_Left  (Hip_Default,   lift);
  Front_Left (Left_Default,  knee);
  delay(Time_Default);
  Front_Right(Right_Default, knee);
  Back_Right (Left_Default,  knee);
  Back_Left  (Right_Default, knee);
  Front_Left (Left_Default,  knee);
  delay(Time_Default);
}

void Turn_Right_R(int knee, int lift) {
  Front_Right(Right_Default, lift);
  Back_Right (Hip_Default,   knee);
  Back_Left  (Hip_Default,   lift);
  Front_Left (Left_Default,  knee);
  delay(Time_Default);
  Front_Right(Right_Default, knee);
  Back_Right (Left_Default,  knee);
  Back_Left  (Right_Default, knee);
  Front_Left (Left_Default,  knee);
  delay(Time_Default);
  Front_Right(Hip_Default,   knee);
  Back_Right (Right_Default, lift);
  Back_Left  (Left_Default,  knee);
  Front_Left (Hip_Default,   lift);
  delay(Time_Default);
  Front_Right(Left_Default,  knee);
  Back_Right (Right_Default, knee);
  Back_Left  (Left_Default,  knee);
  Front_Left (Right_Default, knee);
  delay(Time_Default);
}

void Point_FR(int knee, int point) {
  Front_Right(Hip_Default, point);
  Back_Right (Point_Left_Default, knee);
  Back_Left  (Hip_Default, knee);
  Front_Left (Point_Right_Default, knee);
}

void Point_BR(int knee, int point) {
  Front_Right(Point_Right_Default, knee);
  Back_Right (Hip_Default, point);
  Back_Left  (Point_Left_Default, knee);
  Front_Left (Hip_Default, knee);
}

void Point_BL(int knee, int point) {
  Front_Right(Hip_Default, knee);
  Back_Right (Point_Right_Default, knee);
  Back_Left  (Hip_Default, point);
  Front_Left (Point_Left_Default, knee);
}

void Point_FL(int knee, int point) {
  Front_Right(Point_Left_Default, knee);
  Back_Right (Hip_Default, knee);
  Back_Left  (Point_Right_Default, knee);
  Front_Left (Hip_Default, point);
}

void Knee_Hip(int knee, int hip) {
  Front_Right(hip, knee);
  Back_Right (hip, knee);
  Back_Left  (hip, knee);
  Front_Left (hip, knee);
}

void Front_Knees(int knee, int lean) {
  Front_Right(Hip_Default, lean);
  Back_Right (Hip_Default, knee);
  Back_Left  (Hip_Default, knee);
  Front_Left (Hip_Default, lean);
}

void Back_Knees(int knee, int lean) {
  Front_Right(Hip_Default, knee);
  Back_Right (Hip_Default, lean);
  Back_Left  (Hip_Default, lean);
  Front_Left (Hip_Default, knee);
}

void Left_Knees(int knee, int lean) {
  Front_Right(Hip_Default, knee);
  Back_Right (Hip_Default, knee);
  Back_Left  (Hip_Default, lean);
  Front_Left (Hip_Default, lean);
}

void Right_Knees(int knee, int lean) {
  Front_Right(Hip_Default, lean);
  Back_Right (Hip_Default, lean);
  Back_Left  (Hip_Default, knee);
  Front_Left (Hip_Default, knee);
}

void Balance_Knee(float pitch, float roll, int knee, int hip) {
  Front_Right(hip, knee - pitch + roll);
  Back_Right (hip, knee + pitch + roll);
  Back_Left  (hip, knee + pitch - roll);
  Front_Left (hip, knee - pitch - roll);
}

void Balance_Hip(float pitch, float roll, int knee, int hip) {
  Front_Right(hip + pitch + roll, knee);
  Back_Right (hip + pitch - roll, knee);
  Back_Left  (hip - pitch - roll, knee);
  Front_Left (hip - pitch + roll, knee);
}

void Balance_All(float knee_pitch, float knee_roll, float hip_pitch, float hip_roll, int knee, int hip) {
  Front_Right(hip + hip_pitch + hip_roll, knee - knee_pitch + knee_roll);
  Back_Right (hip + hip_pitch - hip_roll, knee + knee_pitch + knee_roll);
  Back_Left  (hip - hip_pitch - hip_roll, knee + knee_pitch - knee_roll);
  Front_Left (hip - hip_pitch + hip_roll, knee - knee_pitch - knee_roll);
}



