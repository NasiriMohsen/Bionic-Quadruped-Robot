#include "Quadruped.h"
#include <Arduino.h>

Servo Hip_BR, Hip_FR, Hip_FL, Hip_BL, Knee_BR, Knee_FR, Knee_FL, Knee_BL;
 
// Setup function
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

// Individual leg control functions
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



// Poses
void Balance_Knee(int hip, int knee, float pitch, float roll) {
    Front_Right(hip, knee - pitch + roll);
    Back_Right(hip, knee + pitch + roll);
    Back_Left(hip, knee + pitch - roll);
    Front_Left(hip, knee - pitch - roll);
}
void Balance_Hip(int hip, int knee, float pitch, float roll) {
    Front_Right(hip + pitch + roll, knee);
    Back_Right(hip + pitch - roll, knee);
    Back_Left(hip - pitch - roll, knee);
    Front_Left(hip - pitch + roll, knee);
}
void Balance_All(int hip, int knee, float knee_pitch, float knee_roll, float hip_pitch, float hip_roll) {
    Front_Right(hip + hip_pitch + hip_roll, knee - knee_pitch + knee_roll);
    Back_Right(hip + hip_pitch - hip_roll, knee + knee_pitch + knee_roll);
    Back_Left(hip - hip_pitch - hip_roll, knee + knee_pitch - knee_roll);
    Front_Left(hip - hip_pitch + hip_roll, knee - knee_pitch - knee_roll);
}




void Flat() {
    Front_Right(Hip_Default_angle, Flat_angle);
    Back_Right(Hip_Default_angle, Flat_angle);
    Back_Left(Hip_Default_angle, Flat_angle);
    Front_Left(Hip_Default_angle, Flat_angle);
}



void Hostile() {
    Front_Right(Hip_Default_angle, Hostile_angle);
    Back_Right(Hip_Default_angle, Hostile_angle);
    Back_Left(Hip_Default_angle, Hostile_angle);
    Front_Left(Hip_Default_angle, Hostile_angle);
}



void Normal() {
    Front_Right(Hip_Default_angle, Normal_angle);
    Back_Right(Hip_Default_angle, Normal_angle);
    Back_Left(Hip_Default_angle, Normal_angle);
    Front_Left(Hip_Default_angle, Normal_angle);
}



void Compressed() {
    Front_Right(Hip_Default_angle, Compressed_angle);
    Back_Right(Hip_Default_angle, Compressed_angle);
    Back_Left(Hip_Default_angle, Compressed_angle);
    Front_Left(Hip_Default_angle, Compressed_angle);
}



void Hostile_Lean_Left() {
    Front_Right(Hip_Default_angle, Hostile_angle);
    Back_Right(Hip_Default_angle, Hostile_angle);
    Back_Left(Hip_Default_angle, Lean_H_angle);
    Front_Left(Hip_Default_angle, Lean_H_angle);
}

void Hostile_Lean_Right() {
    Front_Right(Hip_Default_angle, Lean_N_angle);
    Back_Right(Hip_Default_angle, Lean_N_angle);
    Back_Left(Hip_Default_angle, Hostile_angle);
    Front_Left(Hip_Default_angle, Hostile_angle);
}

void Hostile_Lean_Front() {
    Front_Right(Hip_Default_angle, Lean_H_angle);
    Back_Right(Hip_Default_angle, Hostile_angle);
    Back_Left(Hip_Default_angle, Hostile_angle);
    Front_Left(Hip_Default_angle, Lean_H_angle);
}

void Hostile_Lean_Back() {
    Front_Right(Hip_Default_angle, Hostile_angle);
    Back_Right(Hip_Default_angle, Lean_H_angle);
    Back_Left(Hip_Default_angle, Lean_H_angle);
    Front_Left(Hip_Default_angle, Hostile_angle);
}




void Normal_Lean_Left(){
    Front_Right(Hip_Default_angle, Normal_angle);
    Back_Right(Hip_Default_angle, Normal_angle);
    Back_Left(Hip_Default_angle, Lean_N_angle);
    Front_Left(Hip_Default_angle, Lean_N_angle);
}

void Normal_Lean_Right() {
    Front_Right(Hip_Default_angle, Lean_N_angle);
    Back_Right(Hip_Default_angle, Lean_N_angle);
    Back_Left(Hip_Default_angle, Normal_angle);
    Front_Left(Hip_Default_angle, Normal_angle);
}

void Normal_Lean_Front() {
    Front_Right(Hip_Default_angle, Lean_N_angle);
    Back_Right(Hip_Default_angle, Normal_angle);
    Back_Left(Hip_Default_angle, Normal_angle);
    Front_Left(Hip_Default_angle, Lean_N_angle);
}

void Normal_Lean_Back() {
    Front_Right(Hip_Default_angle, Normal_angle);
    Back_Right(Hip_Default_angle, Lean_N_angle);
    Back_Left(Hip_Default_angle, Lean_N_angle);
    Front_Left(Hip_Default_angle, Normal_angle);
}



void Hostile_Point_BR() {
    Front_Right(Hip_Point_Right_angle, Hostile_angle);
    Back_Right(Hip_Default_angle, Point_H_angle);
    Back_Left(Hip_Point_Left_angle, Hostile_angle);
    Front_Left(Hip_Default_angle, Hostile_angle);
}

void Hostile_Point_FR() {
    Front_Right(Hip_Default_angle, Point_H_angle);
    Back_Right(Hip_Point_Left_angle, Hostile_angle);
    Back_Left(Hip_Default_angle, Hostile_angle);
    Front_Left(Hip_Point_Right_angle, Hostile_angle);
}

void Hostile_Point_FL() {
    Front_Right(Hip_Point_Left_angle, Hostile_angle);
    Back_Right(Hip_Default_angle, Hostile_angle);
    Back_Left(Hip_Point_Right_angle, Hostile_angle);
    Front_Left(Hip_Default_angle, Point_H_angle);
}

void Hostile_Point_BL() {
    Front_Right(Hip_Default_angle, Hostile_angle);
    Back_Right(Hip_Point_Right_angle, Hostile_angle);
    Back_Left(Hip_Default_angle, Point_H_angle);
    Front_Left(Hip_Point_Left_angle, Hostile_angle);
}



void Normal_Point_BR() {
    Front_Right(Hip_Point_Right_angle, Normal_angle);
    Back_Right(Hip_Default_angle, Point_N_angle);
    Back_Left(Hip_Point_Left_angle, Normal_angle);
    Front_Left(Hip_Default_angle, Normal_angle);
}

void Normal_Point_FR() {
    Front_Right(Hip_Default_angle, Point_N_angle);
    Back_Right(Hip_Point_Left_angle, Normal_angle);
    Back_Left(Hip_Default_angle, Normal_angle);
    Front_Left(Hip_Point_Right_angle, Normal_angle);
}

void Normal_Point_FL() {
    Front_Right(Hip_Point_Left_angle, Normal_angle);
    Back_Right(Hip_Default_angle, Normal_angle);
    Back_Left(Hip_Point_Right_angle, Normal_angle);
    Front_Left(Hip_Default_angle, Point_N_angle);
}

void Normal_Point_BL() {
    Front_Right(Hip_Default_angle, Normal_angle);
    Back_Right(Hip_Point_Right_angle, Normal_angle);
    Back_Left(Hip_Default_angle, Point_N_angle);
    Front_Left(Hip_Point_Left_angle, Normal_angle);
}



void Turn_Left_Hostile_R(int timeframe) {
  Front_Right(Hip_Left_angle, Lift_H_angle);
  Back_Right(Hip_Default_angle, Hostile_angle);
  Back_Left(Hip_Left_angle, Lift_H_angle);
  Front_Left(Hip_Default_angle, Hostile_angle);
  delay(timeframe);
  Front_Right(Hip_Left_angle, Hostile_angle);
  Back_Right(Hip_Default_angle, Hostile_angle);
  Back_Left(Hip_Left_angle, Hostile_angle);
  Front_Left(Hip_Default_angle, Hostile_angle);
  delay(timeframe);
  Front_Right(Hip_Left_angle, Hostile_angle);
  Back_Right(Hip_Left_angle, Lift_H_angle);
  Back_Left(Hip_Left_angle, Hostile_angle);
  Front_Left(Hip_Left_angle, Lift_H_angle);
  delay(timeframe);
  Front_Right(Hip_Left_angle, Hostile_angle);
  Back_Right(Hip_Left_angle, Hostile_angle);
  Back_Left(Hip_Left_angle, Hostile_angle);
  Front_Left(Hip_Left_angle, Hostile_angle);
  delay(timeframe);
  Front_Right(Hip_Default_angle, Hostile_angle);
  Back_Right(Hip_Default_angle, Hostile_angle);
  Back_Left(Hip_Default_angle, Hostile_angle);
  Front_Left(Hip_Default_angle, Hostile_angle);
}

void Turn_Right_Hostile_R(int timeframe) {
  Front_Right(Hip_Right_angle, Lift_H_angle);
  Back_Right(Hip_Default_angle, Hostile_angle);
  Back_Left(Hip_Right_angle, Lift_H_angle);
  Front_Left(Hip_Default_angle, Hostile_angle);
  delay(timeframe);
  Front_Right(Hip_Right_angle, Hostile_angle);
  Back_Right(Hip_Default_angle, Hostile_angle);
  Back_Left(Hip_Right_angle, Hostile_angle);
  Front_Left(Hip_Default_angle, Hostile_angle);
  delay(timeframe);
  Front_Right(Hip_Right_angle, Hostile_angle);
  Back_Right(Hip_Right_angle, Lift_H_angle);
  Back_Left(Hip_Right_angle, Hostile_angle);
  Front_Left(Hip_Right_angle, Lift_H_angle);
  delay(timeframe);
  Front_Right(Hip_Right_angle, Hostile_angle);
  Back_Right(Hip_Right_angle, Hostile_angle);
  Back_Left(Hip_Right_angle, Hostile_angle);
  Front_Left(Hip_Right_angle, Hostile_angle);
  delay(timeframe);
  Front_Right(Hip_Default_angle, Hostile_angle);
  Back_Right(Hip_Default_angle, Hostile_angle);
  Back_Left(Hip_Default_angle, Hostile_angle);
  Front_Left(Hip_Default_angle, Hostile_angle);
}

void Turn_Left_Hostile_L(int timeframe) {
  Front_Right(Hip_Default_angle, Hostile_angle);
  Back_Right(Hip_Left_angle, Lift_H_angle);
  Back_Left(Hip_Default_angle, Hostile_angle);
  Front_Left(Hip_Left_angle, Lift_H_angle);
  delay(timeframe);
  Front_Right(Hip_Default_angle, Hostile_angle);
  Back_Right(Hip_Left_angle, Hostile_angle);
  Back_Left(Hip_Default_angle, Hostile_angle);
  Front_Left(Hip_Left_angle, Hostile_angle);
  delay(timeframe);
  Front_Right(Hip_Left_angle, Lift_H_angle);
  Back_Right(Hip_Left_angle, Hostile_angle);
  Back_Left(Hip_Left_angle, Lift_H_angle);
  Front_Left(Hip_Left_angle, Hostile_angle);
  delay(timeframe);
  Front_Right(Hip_Left_angle, Hostile_angle);
  Back_Right(Hip_Left_angle, Hostile_angle);
  Back_Left(Hip_Left_angle, Hostile_angle);
  Front_Left(Hip_Left_angle, Hostile_angle);
  delay(timeframe);
  Front_Right(Hip_Default_angle, Hostile_angle);
  Back_Right(Hip_Default_angle, Hostile_angle);
  Back_Left(Hip_Default_angle, Hostile_angle);
  Front_Left(Hip_Default_angle, Hostile_angle);
}

void Turn_Right_Hostile_L(int timeframe) {
  Front_Right(Hip_Default_angle, Hostile_angle);
  Back_Right(Hip_Right_angle, Lift_H_angle);
  Back_Left(Hip_Default_angle, Hostile_angle);
  Front_Left(Hip_Right_angle, Lift_H_angle);
  delay(timeframe);
  Front_Right(Hip_Default_angle, Hostile_angle);
  Back_Right(Hip_Right_angle, Hostile_angle);
  Back_Left(Hip_Default_angle, Hostile_angle);
  Front_Left(Hip_Right_angle, Hostile_angle);
  delay(timeframe);
  Front_Right(Hip_Right_angle, Lift_H_angle);
  Back_Right(Hip_Right_angle, Hostile_angle);
  Back_Left(Hip_Right_angle, Lift_H_angle);
  Front_Left(Hip_Right_angle, Hostile_angle);
  delay(timeframe);
  Front_Right(Hip_Right_angle, Hostile_angle);
  Back_Right(Hip_Right_angle, Hostile_angle);
  Back_Left(Hip_Right_angle, Hostile_angle);
  Front_Left(Hip_Right_angle, Hostile_angle);
  delay(timeframe);
  Front_Right(Hip_Default_angle, Hostile_angle);
  Back_Right(Hip_Default_angle, Hostile_angle);
  Back_Left(Hip_Default_angle, Hostile_angle);
  Front_Left(Hip_Default_angle, Hostile_angle);
}



void Turn_Left_Normal_R(int timeframe) {
  Front_Right(Hip_Left_angle, Lift_N_angle);
  Back_Right(Hip_Default_angle, Normal_angle);
  Back_Left(Hip_Left_angle, Lift_N_angle);
  Front_Left(Hip_Default_angle, Normal_angle);
  delay(timeframe);
  Front_Right(Hip_Left_angle, Normal_angle);
  Back_Right(Hip_Default_angle, Normal_angle);
  Back_Left(Hip_Left_angle, Normal_angle);
  Front_Left(Hip_Default_angle, Normal_angle);
  delay(timeframe);
  Front_Right(Hip_Left_angle, Normal_angle);
  Back_Right(Hip_Left_angle, Lift_N_angle);
  Back_Left(Hip_Left_angle, Normal_angle);
  Front_Left(Hip_Left_angle, Lift_N_angle);
  delay(timeframe);
  Front_Right(Hip_Left_angle, Normal_angle);
  Back_Right(Hip_Left_angle, Normal_angle);
  Back_Left(Hip_Left_angle, Normal_angle);
  Front_Left(Hip_Left_angle, Normal_angle);
  delay(timeframe);
  Front_Right(Hip_Default_angle, Normal_angle);
  Back_Right(Hip_Default_angle, Normal_angle);
  Back_Left(Hip_Default_angle, Normal_angle);
  Front_Left(Hip_Default_angle, Normal_angle);
}

void Turn_Right_Normal_R(int timeframe) {
  Front_Right(Hip_Right_angle, Lift_N_angle);
  Back_Right(Hip_Default_angle, Normal_angle);
  Back_Left(Hip_Right_angle, Lift_N_angle);
  Front_Left(Hip_Default_angle, Normal_angle);
  delay(timeframe);
  Front_Right(Hip_Right_angle, Normal_angle);
  Back_Right(Hip_Default_angle, Normal_angle);
  Back_Left(Hip_Right_angle, Normal_angle);
  Front_Left(Hip_Default_angle, Normal_angle);
  delay(timeframe);
  Front_Right(Hip_Right_angle, Normal_angle);
  Back_Right(Hip_Right_angle, Lift_N_angle);
  Back_Left(Hip_Right_angle, Normal_angle);
  Front_Left(Hip_Right_angle, Lift_N_angle);
  delay(timeframe);
  Front_Right(Hip_Right_angle, Normal_angle);
  Back_Right(Hip_Right_angle, Normal_angle);
  Back_Left(Hip_Right_angle, Normal_angle);
  Front_Left(Hip_Right_angle, Normal_angle);
  delay(timeframe);
  Front_Right(Hip_Default_angle, Normal_angle);
  Back_Right(Hip_Default_angle, Normal_angle);
  Back_Left(Hip_Default_angle, Normal_angle);
  Front_Left(Hip_Default_angle, Normal_angle);
}

void Turn_Left_Normal_L(int timeframe) {
  Front_Right(Hip_Default_angle, Normal_angle);
  Back_Right(Hip_Left_angle, Lift_N_angle);
  Back_Left(Hip_Default_angle, Normal_angle);
  Front_Left(Hip_Left_angle, Lift_N_angle);
  delay(timeframe);
  Front_Right(Hip_Default_angle, Normal_angle);
  Back_Right(Hip_Left_angle, Normal_angle);
  Back_Left(Hip_Default_angle, Normal_angle);
  Front_Left(Hip_Left_angle, Normal_angle);
  delay(timeframe);
  Front_Right(Hip_Left_angle, Lift_N_angle);
  Back_Right(Hip_Left_angle, Normal_angle);
  Back_Left(Hip_Left_angle, Lift_N_angle);
  Front_Left(Hip_Left_angle, Normal_angle);
  delay(timeframe);
  Front_Right(Hip_Left_angle, Normal_angle);
  Back_Right(Hip_Left_angle, Normal_angle);
  Back_Left(Hip_Left_angle, Normal_angle);
  Front_Left(Hip_Left_angle, Normal_angle);
  delay(timeframe);
  Front_Right(Hip_Default_angle, Normal_angle);
  Back_Right(Hip_Default_angle, Normal_angle);
  Back_Left(Hip_Default_angle, Normal_angle);
  Front_Left(Hip_Default_angle, Normal_angle);
}

void Turn_Right_Normal_L(int timeframe) {
  Front_Right(Hip_Default_angle, Normal_angle);
  Back_Right(Hip_Right_angle, Lift_N_angle);
  Back_Left(Hip_Default_angle, Normal_angle);
  Front_Left(Hip_Right_angle, Lift_N_angle);
  delay(timeframe);
  Front_Right(Hip_Default_angle, Normal_angle);
  Back_Right(Hip_Right_angle, Normal_angle);
  Back_Left(Hip_Default_angle, Normal_angle);
  Front_Left(Hip_Right_angle, Normal_angle);
  delay(timeframe);
  Front_Right(Hip_Right_angle, Lift_N_angle);
  Back_Right(Hip_Right_angle, Normal_angle);
  Back_Left(Hip_Right_angle, Lift_N_angle);
  Front_Left(Hip_Right_angle, Normal_angle);
  delay(timeframe);
  Front_Right(Hip_Right_angle, Normal_angle);
  Back_Right(Hip_Right_angle, Normal_angle);
  Back_Left(Hip_Right_angle, Normal_angle);
  Front_Left(Hip_Right_angle, Normal_angle);
  delay(timeframe);
  Front_Right(Hip_Default_angle, Normal_angle);
  Back_Right(Hip_Default_angle, Normal_angle);
  Back_Left(Hip_Default_angle, Normal_angle);
  Front_Left(Hip_Default_angle, Normal_angle);
}



void Hostile_Forward() {
  Front_Right(Hip_Movement_Left_angle, Lift_H_angle);
  Back_Right(Hip_Default_angle, Hostile_angle);
  Back_Left(Hip_Movement_Right_angle, Lift_H_angle);
  Front_Left(Hip_Default_angle, Hostile_angle);
  delay(125);
  Front_Right(Hip_Movement_Left_angle, Hostile_angle);
  Back_Right(Hip_Default_angle, Hostile_angle);
  Back_Left(Hip_Movement_Right_angle, Hostile_angle);
  Front_Left(Hip_Default_angle, Hostile_angle);
  delay(125);
  Front_Right(Hip_Default_angle, Hostile_angle);
  Back_Right(Hip_Default_angle, Hostile_angle);
  Back_Left(Hip_Default_angle, Hostile_angle);
  Front_Left(Hip_Default_angle, Hostile_angle);
  delay(125);
  Front_Right(Hip_Default_angle, Hostile_angle);
  Back_Right(Hip_Movement_Left_angle, Lift_H_angle);
  Back_Left(Hip_Default_angle, Hostile_angle);
  Front_Left(Hip_Movement_Right_angle, Lift_H_angle);
  delay(125);
  Front_Right(Hip_Default_angle, Hostile_angle);
  Back_Right(Hip_Movement_Left_angle, Hostile_angle);
  Back_Left(Hip_Default_angle, Hostile_angle);
  Front_Left(Hip_Movement_Right_angle, Hostile_angle);
  delay(125);
  Front_Right(Hip_Default_angle, Hostile_angle);
  Back_Right(Hip_Default_angle, Hostile_angle);
  Back_Left(Hip_Default_angle, Hostile_angle);
  Front_Left(Hip_Default_angle, Hostile_angle);
  delay(125);
}



void My_Forward() {
  Front_Right(Hip_Default_angle, Hostile_angle);
  Back_Right(Hip_Default_angle, Lift_H_angle);
  Back_Left(Hip_Default_angle, Hostile_angle);
  Front_Left(Hip_Default_angle, Hostile_angle);
  delay(100);
  Front_Right(Hip_Default_angle, Hostile_angle);
  Back_Right(Hip_Movement_Left_angle, Lift_H_angle);
  Back_Left(Hip_Default_angle, Hostile_angle);
  Front_Left(Hip_Default_angle, Hostile_angle);
  delay(125);
  Front_Right(Hip_Default_angle, Hostile_angle);
  Back_Right(Hip_Movement_Left_angle, Hostile_angle);
  Back_Left(Hip_Default_angle, Lift_H_angle);
  Front_Left(Hip_Default_angle, Hostile_angle);
  delay(125);
  Front_Right(Hip_Movement_Left_angle, 75);
  Back_Right(Hip_Movement_Left_angle, Hostile_angle);
  Back_Left(Hip_Movement_Right_angle, Hostile_angle);
  Front_Left(Hip_Movement_Right_angle, 75);
  delay(125);
  Front_Right(Hip_Movement_Left_angle, Hostile_angle);
  Back_Right(Hip_Default_angle, Hostile_angle);
  Back_Left(Hip_Default_angle, Hostile_angle);
  Front_Left(Hip_Movement_Right_angle, Hostile_angle);
  delay(125);
  Front_Right(Hip_Default_angle, Hostile_angle);
  Back_Right(Hip_Default_angle, Hostile_angle);
  Back_Left(Hip_Default_angle, Hostile_angle);
  Front_Left(Hip_Default_angle, Hostile_angle);
  delay(125);
}

void Improved_Hostile_Forward() {
  Front_Right(Hip_Default_angle, Hostile_angle);
  Back_Right(Hip_Movement_Left_angle, Lift_H_angle);
  Back_Left(Hip_Default_angle, Hostile_angle);
  Front_Left(Hip_Default_angle, Hostile_angle);
  delay(125);
  Front_Right(Hip_Default_angle, Hostile_angle);
  Back_Right(Hip_Movement_Left_angle, Hostile_angle);
  Back_Left(Hip_Default_angle, Hostile_angle);
  Front_Left(Hip_Default_angle, Hostile_angle);
  delay(125);
  Front_Right(Hip_Movement_Left_angle, Lift_H_angle);
  Back_Right(Hip_Movement_Left_angle, Hostile_angle);
  Back_Left(Hip_Default_angle, Hostile_angle);
  Front_Left(Hip_Default_angle, Hostile_angle);
  delay(125);
  Front_Right(Hip_Movement_Left_angle, Hostile_angle);
  Back_Right(Hip_Movement_Left_angle, Hostile_angle);
  Back_Left(Hip_Default_angle, Hostile_angle);
  Front_Left(Hip_Default_angle, Hostile_angle);
  delay(125);
  Front_Right(Hip_Default_angle, Hostile_angle);
  Back_Right(Hip_Default_angle, Hostile_angle);
  Back_Left(Hip_Default_angle, Hostile_angle);
  Front_Left(Hip_Default_angle, Hostile_angle);
  delay(125);

  Front_Right(Hip_Default_angle, Hostile_angle);
  Back_Right(Hip_Default_angle, Hostile_angle);
  Back_Left(Hip_Movement_Right_angle, Lift_H_angle);
  Front_Left(Hip_Default_angle, Hostile_angle);
  delay(125);
  Front_Right(Hip_Default_angle, Hostile_angle);
  Back_Right(Hip_Default_angle, Hostile_angle);
  Back_Left(Hip_Movement_Right_angle, Hostile_angle);
  Front_Left(Hip_Default_angle, Hostile_angle);
  delay(125);
  Front_Right(Hip_Default_angle, Hostile_angle);
  Back_Right(Hip_Default_angle, Hostile_angle);
  Back_Left(Hip_Movement_Right_angle, Hostile_angle);
  Front_Left(Hip_Movement_Right_angle, Lift_H_angle);
  delay(125);
  Front_Right(Hip_Default_angle, Hostile_angle);
  Back_Right(Hip_Default_angle, Hostile_angle);
  Back_Left(Hip_Movement_Right_angle, Hostile_angle);
  Front_Left(Hip_Movement_Right_angle, Hostile_angle);
  delay(125);
  Front_Right(Hip_Default_angle, Hostile_angle);
  Back_Right(Hip_Default_angle, Hostile_angle);
  Back_Left(Hip_Default_angle, Hostile_angle);
  Front_Left(Hip_Default_angle, Hostile_angle);
  delay(125);

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