#include "Gyro.h"
#include "Quadruped.h"

MPU6050Handler gyro;

String input = "flat";

void setup() {
    Serial.begin(115200);

    Setup_Legs();
    Flat();
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
    Front_Right(Hip_Default_angle, 40);
    Back_Right(Hip_Default_angle, 40);
    Back_Left(Hip_Default_angle, 40);
    Front_Left(Hip_Default_angle, 40);
//-------------------------------------------------
  } else if (input == "balkneeh1"){
    gyro.calculate_PID(knee_pitch, knee_roll, hip_pitch, hip_roll, gyro.calculateDeltaTime(), 0, 0, 180);
    Balance_Knee(Hip_Default_angle, Hostile_angle, knee_pitch, knee_roll);
  } else if (input == "balhiph1"){
    gyro.calculate_PID(knee_pitch, knee_roll, hip_pitch, hip_roll, gyro.calculateDeltaTime(), 0, 0, 180);
    Balance_Hip(Hip_Default_angle, Hostile_angle, hip_pitch, hip_roll);
  } else if (input == "balallh1"){
    gyro.calculate_PID(knee_pitch, knee_roll, hip_pitch, hip_roll, gyro.calculateDeltaTime(), 0, 0, 180);
    Balance_All(Hip_Default_angle, Hostile_angle, knee_pitch, knee_roll, hip_pitch, hip_roll);
  } else if (input == "balkneeh2"){
    gyro.calculate_PID(knee_pitch, knee_roll, hip_pitch, hip_roll, gyro.calculateDeltaTime(), 0, 0, 0);
    Balance_Knee(Hip_Default_angle, Hostile_angle, knee_pitch, knee_roll);
  } else if (input == "balhiph2"){
    gyro.calculate_PID(knee_pitch, knee_roll, hip_pitch, hip_roll, gyro.calculateDeltaTime(), 0, 0, 0);
    Balance_Hip(Hip_Default_angle, Hostile_angle, hip_pitch, hip_roll);
  } else if (input == "balallh2"){
    gyro.calculate_PID(knee_pitch, knee_roll, hip_pitch, hip_roll, gyro.calculateDeltaTime(), 0, 0, 0);
    Balance_All(Hip_Default_angle, Hostile_angle, knee_pitch, knee_roll, hip_pitch, hip_roll);
  } else if (input == "balkneen1"){
    gyro.calculate_PID(knee_pitch, knee_roll, hip_pitch, hip_roll, gyro.calculateDeltaTime(), 0, 0, 180);
    Balance_Knee(Hip_Default_angle, Normal_angle, knee_pitch, knee_roll);
  } else if (input == "balhipn1"){
    gyro.calculate_PID(knee_pitch, knee_roll, hip_pitch, hip_roll, gyro.calculateDeltaTime(), 0, 0, 180);
    Balance_Hip(Hip_Default_angle, Normal_angle, hip_pitch, hip_roll);
  } else if (input == "balalln1"){
    gyro.calculate_PID(knee_pitch, knee_roll, hip_pitch, hip_roll, gyro.calculateDeltaTime(), 0, 0, 180);
    Balance_All(Hip_Default_angle, Normal_angle, knee_pitch, knee_roll, hip_pitch, hip_roll);
  } else if (input == "balkneen2"){
    gyro.calculate_PID(knee_pitch, knee_roll, hip_pitch, hip_roll, gyro.calculateDeltaTime(), 0, 0, 0);
    Balance_Knee(Hip_Default_angle, Normal_angle, knee_pitch, knee_roll);
  } else if (input == "balhipn2"){
    gyro.calculate_PID(knee_pitch, knee_roll, hip_pitch, hip_roll, gyro.calculateDeltaTime(), 0, 0, 0);
    Balance_Hip(Hip_Default_angle, Normal_angle, hip_pitch, hip_roll);
  } else if (input == "balalln2"){
    gyro.calculate_PID(knee_pitch, knee_roll, hip_pitch, hip_roll, gyro.calculateDeltaTime(), 0, 0, 0);
    Balance_All(Hip_Default_angle, Normal_angle, knee_pitch, knee_roll, hip_pitch, hip_roll);
  } else if (input == "balkneec1"){
    gyro.calculate_PID(knee_pitch, knee_roll, hip_pitch, hip_roll, gyro.calculateDeltaTime(), 0, 0, 180);
    Balance_Knee(Hip_Default_angle, Compressed_angle, knee_pitch, knee_roll);
  } else if (input == "balhipc1"){
    gyro.calculate_PID(knee_pitch, knee_roll, hip_pitch, hip_roll, gyro.calculateDeltaTime(), 0, 0, 180);
    Balance_Hip(Hip_Default_angle, Compressed_angle, hip_pitch, hip_roll);
  } else if (input == "balallc1"){
    gyro.calculate_PID(knee_pitch, knee_roll, hip_pitch, hip_roll, gyro.calculateDeltaTime(), 0, 0, 180);
    Balance_All(Hip_Default_angle, Compressed_angle, knee_pitch, knee_roll, hip_pitch, hip_roll);
  } else if (input == "balkneec2"){
    gyro.calculate_PID(knee_pitch, knee_roll, hip_pitch, hip_roll, gyro.calculateDeltaTime(), 0, 0, 0);
    Balance_Knee(Hip_Default_angle, Compressed_angle, knee_pitch, knee_roll);
  } else if (input == "balhipc2"){
    gyro.calculate_PID(knee_pitch, knee_roll, hip_pitch, hip_roll, gyro.calculateDeltaTime(), 0, 0, 0);
    Balance_Hip(Hip_Default_angle, Compressed_angle, hip_pitch, hip_roll);
  } else if (input == "balallc2"){
    gyro.calculate_PID(knee_pitch, knee_roll, hip_pitch, hip_roll, gyro.calculateDeltaTime(), 0, 0, 0);
    Balance_All(Hip_Default_angle, Compressed_angle, knee_pitch, knee_roll, hip_pitch, hip_roll);
  } else if (input == "balkneef1"){
    gyro.calculate_PID(knee_pitch, knee_roll, hip_pitch, hip_roll, gyro.calculateDeltaTime(), 0, 0, 180);
    Balance_Knee(Hip_Default_angle, Flat_angle, knee_pitch, knee_roll);
  } else if (input == "balhipf1"){
    gyro.calculate_PID(knee_pitch, knee_roll, hip_pitch, hip_roll, gyro.calculateDeltaTime(), 0, 0, 180);
    Balance_Hip(Hip_Default_angle, Flat_angle, hip_pitch, hip_roll);
  } else if (input == "balallf1"){
    gyro.calculate_PID(knee_pitch, knee_roll, hip_pitch, hip_roll, gyro.calculateDeltaTime(), 0, 0, 180);
    Balance_All(Hip_Default_angle, Flat_angle, knee_pitch, knee_roll, hip_pitch, hip_roll);
  } else if (input == "balkneef2"){
    gyro.calculate_PID(knee_pitch, knee_roll, hip_pitch, hip_roll, gyro.calculateDeltaTime(), 0, 0, 0);
    Balance_Knee(Hip_Default_angle, Flat_angle, knee_pitch, knee_roll);
  } else if (input == "balhipf2"){
    gyro.calculate_PID(knee_pitch, knee_roll, hip_pitch, hip_roll, gyro.calculateDeltaTime(), 0, 0, 0);
    Balance_Hip(Hip_Default_angle, Flat_angle, hip_pitch, hip_roll);
  } else if (input == "balallf2"){
    gyro.calculate_PID(knee_pitch, knee_roll, hip_pitch, hip_roll, gyro.calculateDeltaTime(), 0, 0, 0);
    Balance_All(Hip_Default_angle, Flat_angle, knee_pitch, knee_roll, hip_pitch, hip_roll);
  } else if (input == "flat"){
    Flat();
  } else if (input == "normal"){
    Normal();
  } else if (input == "compressed"){
    Compressed();
  } else if (input == "hostile"){
    Hostile();
  } else if (input == "nll"){
    Normal_Lean_Left();
  } else if (input == "nlr"){
    Normal_Lean_Right();
  } else if (input == "nlf"){
    Normal_Lean_Front();
  } else if (input == "nlb"){
    Normal_Lean_Back();
  } else if (input == "hpbr"){
    Hostile_Point_BR();
  } else if (input == "hpfr"){
    Hostile_Point_FR();
  } else if (input == "hpfl"){
    Hostile_Point_FL();
  } else if (input == "hpbl"){
    Hostile_Point_BL();
  } else if (input == "npbr"){
    Normal_Point_BR();
  } else if (input == "npfr"){
    Normal_Point_FR();
  } else if (input == "npfl"){
    Normal_Point_FL();
  } else if (input == "npbl"){
    Normal_Point_BL();
  } else if (input == "tlhr"){
    Turn_Left_Hostile_R(100);
  } else if (input == "trhr"){
    Turn_Right_Hostile_R(100);
  } else if (input == "tlhl"){
    Turn_Left_Hostile_L(100);
  } else if (input == "trhl"){
    Turn_Right_Hostile_L(100);
  } else if (input == "tlnr"){
    Turn_Left_Normal_R(100);
  } else if (input == "trnr"){
    Turn_Right_Normal_R(100);
  } else if (input == "tlnl"){
    Turn_Left_Normal_L(100);
  } else if (input == "trnl"){
    Turn_Right_Normal_L(100);
  } else if (input == "chill"){
    Toggle_Motors();
    input = "";
  } else {
    Hostile();
  }
  delay(15);
}
