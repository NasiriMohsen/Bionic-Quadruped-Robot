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
#define Offset_Knee_FL -9
#define Offset_Knee_BL 0

// Servo limits
#define Servo_min 0
#define Servo_max 180

// Angle definitions
#define Hip_Default 90
#define Left_Default 135
#define Right_Default 45
#define Point_Left_Default 110
#define Point_Right_Default 70

#define Knee_Default 60
#define Lean_Default 100
#define Lift_Default 100
#define Point_Default 130
#define Time_Default 125

#define Flat_angle 110
#define Hostile_angle 60
#define Straight_angle 35
#define Compressed_angle 0

void Front_Right(int hip, int knee);
void Front_Left(int hip, int knee);
void Back_Right(int hip, int knee);
void Back_Left(int hip, int knee);

// Function prototypes for poses
void Forward_L(int knee = Knee_Default, int lift = Lift_Default);
void Forward_R(int knee = Knee_Default, int lift = Lift_Default);
void Backward_L(int knee = Knee_Default, int lift = Lift_Default);
void Backward_R(int knee = Knee_Default, int lift = Lift_Default);
void Left_L(int knee = Knee_Default, int lift = Lift_Default);
void Left_R(int knee = Knee_Default, int lift = Lift_Default);
void Right_L(int knee = Knee_Default, int lift = Lift_Default);
void Right_R(int knee = Knee_Default, int lift = Lift_Default);

void Turn_Left_L(int knee = Knee_Default, int lift = Lift_Default);
void Turn_Left_R(int knee = Knee_Default, int lift = Lift_Default);
void Turn_Right_L(int knee = Knee_Default, int lift = Lift_Default);
void Turn_Right_R(int knee = Knee_Default, int lift = Lift_Default);

void Point_FR(int knee = Knee_Default, int point = Point_Default);
void Point_BR(int knee = Knee_Default, int point = Point_Default);
void Point_BL(int knee = Knee_Default, int point = Point_Default);
void Point_FL(int knee = Knee_Default, int point = Point_Default);

void Knee_Hip(int knee = Knee_Default, int hip = Hip_Default);

void Front_Knees(int knee = Knee_Default, int lean = Lean_Default);
void Back_Knees(int knee = Knee_Default, int lean = Lean_Default);
void Left_Knees(int knee = Knee_Default, int lean = Lean_Default);
void Right_Knees(int knee = Knee_Default, int lean = Lean_Default);

void Balance_Knee(float pitch, float roll, int knee = Knee_Default, int hip = Hip_Default);
void Balance_Hip(float pitch, float roll, int knee = Knee_Default, int hip = Hip_Default);
void Balance_All(float knee_pitch, float knee_roll, float hip_pitch, float hip_roll, int knee = Knee_Default, int hip = Hip_Default);

void Setup_Legs();
void Toggle_Motors();

#endif
