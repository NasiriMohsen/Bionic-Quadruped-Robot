gyro.calculate_PID(knee_pitch, knee_roll, hip_pitch, hip_roll, gyro.calculateDeltaTime(), 0, 0, 180);
Front_Right(frhip + hip_pitch + hip_roll, frknee - knee_pitch + knee_roll);
Back_Right (brhip + hip_pitch - hip_roll, brknee + knee_pitch + knee_roll);
Back_Left  (blhip - hip_pitch - hip_roll, blknee + knee_pitch - knee_roll);
Front_Left (flhip - hip_pitch + hip_roll, flknee - knee_pitch - knee_roll);


frhip = Hip_Default   > Right_Default > Left_Default  > Left_Default
brhip = Left_Default  > Left_Default  > Hip_Default   > Right_Default
blhip = Hip_Default   > Left_Default  > Right_Default > Right_Default
flhip = Right_Default > Right_Default > Hip_Default   > Left_Default

frknee = Knee_Default > Knee_Default > Lift_Default > Knee_Default
brknee = Lift_Default > Knee_Default > Knee_Default > Knee_Default
blknee = Knee_Default > Knee_Default > Lift_Default > Knee_Default
flknee = Lift_Default > Knee_Default > Knee_Default > Knee_Default


  Front_Right(, - knee_pitch + knee_roll);
  Back_Right (,);
  Back_Left  (, + knee_pitch - knee_roll);
  Front_Left (,);

  delay(Time_Default);
  
  Front_Right(, - knee_pitch + knee_roll);
  Back_Right (, + knee_pitch + knee_roll);
  Back_Left  (, + knee_pitch - knee_roll);
  Front_Left (, - knee_pitch - knee_roll);
  delay(Time_Default);
  
  Front_Right(,);
  Back_Right (, + knee_pitch + knee_roll);
  Back_Left  (, + knee_pitch - knee_roll);
  Front_Left (,);
  delay(Time_Default);
  
  Front_Right(, - knee_pitch + knee_roll);
  Back_Right (, + knee_pitch + knee_roll);
  Back_Left  (, + knee_pitch - knee_roll);
  Front_Left (, - knee_pitch - knee_roll);
  delay(Time_Default);