#include "Gyro.h"
#include "Quadruped.h"

MPU6050Handler gyro;

String input = "flat";

void setup() {
    Serial.begin(115200);

    Setup_Legs();
    Knee_Hip(Flat_angle);
    delay(1000);

    if (!gyro.begin()) {
        Serial.println("Failed to initialize MPU6050.");
        while (1);
    }

    Serial.println("Calibrating MPU6050...");
    gyro.calibrate();
    Serial.println("Calibration complete!");
}

void loop() {
  float pitch, roll, knee_pitch, knee_roll, hip_pitch, hip_roll;
  gyro.getAngles(pitch, roll);

  Serial.print("Pitch: ");
  Serial.print(pitch);
  Serial.print(" Roll: ");
  Serial.println(roll);

  if (Serial.available() > 0) {
    input = Serial.readString();
    input.trim();
    gyro.reset_PID();
  }
//------------------------------------------------- 
  if (input == "run") {
  gyro.calculate_PID(knee_pitch, knee_roll, hip_pitch, hip_roll, gyro.calculateDeltaTime(), 0, 0, 0);
  Front_Right(Hip_Default,   Knee_Default - knee_pitch + knee_roll);
  Back_Right (Left_Default,  Lift_Default);
  Back_Left  (Hip_Default,   Knee_Default + knee_pitch - knee_roll);
  Front_Left (Right_Default, Lift_Default);
  delay(Time_Default);
  gyro.calculate_PID(knee_pitch, knee_roll, hip_pitch, hip_roll, gyro.calculateDeltaTime(), 0, 0, 0);
  Front_Right(Right_Default, Knee_Default - knee_pitch + knee_roll);
  Back_Right (Left_Default,  Knee_Default + knee_pitch + knee_roll);
  Back_Left  (Left_Default,  Knee_Default + knee_pitch - knee_roll);
  Front_Left (Right_Default, Knee_Default - knee_pitch - knee_roll);
  delay(Time_Default);
  gyro.calculate_PID(knee_pitch, knee_roll, hip_pitch, hip_roll, gyro.calculateDeltaTime(), 0, 0, 0);
  Front_Right(Left_Default,  Lift_Default);
  Back_Right (Hip_Default,   Knee_Default + knee_pitch + knee_roll);
  Back_Left  (Right_Default, Lift_Default + knee_pitch - knee_roll);
  Front_Left (Hip_Default,   Knee_Default);
  delay(Time_Default);
  gyro.calculate_PID(knee_pitch, knee_roll, hip_pitch, hip_roll, gyro.calculateDeltaTime(), 0, 0, 0);
  Front_Right(Left_Default,  Knee_Default - knee_pitch + knee_roll);
  Back_Right (Right_Default, Knee_Default + knee_pitch + knee_roll);
  Back_Left  (Right_Default, Knee_Default + knee_pitch - knee_roll);
  Front_Left (Left_Default,  Knee_Default - knee_pitch - knee_roll);
  delay(Time_Default);
//-------------------------------------------------
  } else if (input == "balkneeh1"){
    gyro.calculate_PID(knee_pitch, knee_roll, hip_pitch, hip_roll, gyro.calculateDeltaTime(), 0, 0, 180);
    Balance_Knee(knee_pitch, knee_roll);
  } else if (input == "balhiph1"){
    gyro.calculate_PID(knee_pitch, knee_roll, hip_pitch, hip_roll, gyro.calculateDeltaTime(), 0, 0, 180);
    Balance_Hip(hip_pitch, hip_roll);
  } else if (input == "balallh1"){
    gyro.calculate_PID(knee_pitch, knee_roll, hip_pitch, hip_roll, gyro.calculateDeltaTime(), 0, 0, 180);
    Balance_All(knee_pitch, knee_roll, hip_pitch, hip_roll);
  
  } else if (input == "leenlh"){
    Left_Knees();
  } else if (input == "leenrh"){
    Right_Knees();
  } else if (input == "leenfh"){
    Front_Knees();
  } else if (input == "leenbh"){
    Back_Knees();

  } else if (input == "leenln"){
    Left_Knees(Straight_angle);
  } else if (input == "leenrn"){
    Right_Knees(Straight_angle);
  } else if (input == "leenfn"){
    Front_Knees(Straight_angle);
  } else if (input == "leenbn"){
    Back_Knees(Straight_angle);
  
  } else if (input == "leenlc"){
    Left_Knees(Compressed_angle);
  } else if (input == "leenrc"){
    Right_Knees(Compressed_angle);
  } else if (input == "leenfc"){
    Front_Knees(Compressed_angle);
  } else if (input == "leenbc"){
    Back_Knees(Compressed_angle);

  } else if (input == "pointbrh"){
    Point_BR();
  } else if (input == "pointfrh"){
    Point_FR();
  } else if (input == "pointflh"){
    Point_FL();
  } else if (input == "pointblh"){
    Point_BL();

  } else if (input == "pointbrn"){
    Point_BR(Straight_angle);
  } else if (input == "pointfrn"){
    Point_FR(Straight_angle);
  } else if (input == "pointfln"){
    Point_FL(Straight_angle);
  } else if (input == "pointbln"){
    Point_BL(Straight_angle);

  } else if (input == "forwardlh"){
    Forward_L();
  } else if (input == "backwardlh"){
    Backward_L();
  } else if (input == "leftlh"){
    Left_L();
  } else if (input == "rightlh"){
    Right_L();
  } else if (input == "tleftlh"){
    Turn_Left_L();
  } else if (input == "trightlh"){
    Turn_Right_L();  
  } else if (input == "forwardrh"){
    Forward_R();
  } else if (input == "backwardrh"){
    Backward_R();
  } else if (input == "leftrh"){
    Left_R();
  } else if (input == "rightrh"){
    Right_R();
  } else if (input == "tleftrh"){
    Turn_Left_R();
  } else if (input == "trightrh"){
    Turn_Right_R();  

  } else if (input == "forwardln"){
    Forward_L(Straight_angle);
  } else if (input == "backwardln"){
    Backward_L(Straight_angle);
  } else if (input == "leftln"){
    Left_L(Straight_angle);
  } else if (input == "rightln"){
    Right_L(Straight_angle);
  } else if (input == "tleftln"){
    Turn_Left_L(Straight_angle);
  } else if (input == "trightln"){
    Turn_Right_L(Straight_angle);  
  } else if (input == "forwardrn"){
    Forward_R(Straight_angle);
  } else if (input == "backwardrn"){
    Backward_R(Straight_angle);
  } else if (input == "leftrn"){
    Left_R(Straight_angle);
  } else if (input == "rightrn"){
    Right_R(Straight_angle);
  } else if (input == "tleftrn"){
    Turn_Left_R(Straight_angle);
  } else if (input == "trightrn"){
    Turn_Right_R(Straight_angle);  
 
  } else if (input == "chill"){
    Toggle_Motors();
    input = "";
  } else {
    Knee_Hip();
  }
  delay(15);
}
