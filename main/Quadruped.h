#ifndef Quadruped_H
#define Quadruped_H

#include <Servo.h>

// Pin definitions
#define PIN_Hip_BR 2
#define PIN_Hip_FR 3 
#define PIN_Hip_FL 4 
#define PIN_Hip_BL 5
#define PIN_Knee_BR 10
#define PIN_Knee_FR 8
#define PIN_Knee_FL 9
#define PIN_Knee_BL 11

// Servo offsets
#define Offset_Hip_BR 0
#define Offset_Hip_FR 0
#define Offset_Hip_FL 0 
#define Offset_Hip_BL 0
#define Offset_Knee_BR 0
#define Offset_Knee_FR 0
#define Offset_Knee_FL -10
#define Offset_Knee_BL 0

// Servo limits
#define Servo_min 0
#define Servo_max 180

// Angle definitions
#define Hip_Default_angle 90
#define Flat_angle 110
#define Hostile_angle 60
#define Normal_angle 35
#define Compressed_angle 0
#define Lean_H_angle 100
#define Lean_N_angle 110
#define Point_H_angle 130
#define Point_N_angle 130
#define Lift_H_angle 90
#define Lift_N_angle 65
#define Hip_Left_angle 135
#define Hip_Right_angle 45

// Function prototypes for individual leg control
void Front_Right(int hip, int knee);
void Front_Left(int hip, int knee);
void Back_Right(int hip, int knee);
void Back_Left(int hip, int knee);

// Function prototypes for poses
void Flat();
void Hostile();
void Normal();
void Compressed();
void Normal_Lean_Left();
void Normal_Lean_Right();
void Normal_Lean_Front();
void Normal_Lean_Back();
void Hostile_Point_BR();
void Hostile_Point_FR();
void Hostile_Point_FL();
void Hostile_Point_BL();
void Normal_Point_BR();
void Normal_Point_FR();
void Normal_Point_FL();
void Normal_Point_BL();
void Turn_Left_Hostile_R(int timeframe);
void Turn_Right_Hostile_R(int timeframe);
void Turn_Left_Hostile_L(int timeframe);
void Turn_Right_Hostile_L(int timeframe);
void Turn_Left_Normal_R(int timeframe);
void Turn_Right_Normal_R(int timeframe);
void Turn_Left_Normal_L(int timeframe);
void Turn_Right_Normal_L(int timeframe);

// Setup function for legs
void Setup_Legs();

#endif
