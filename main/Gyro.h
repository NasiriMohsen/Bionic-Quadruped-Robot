#ifndef Gyro_H
#define Gyro_H

#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

class MPU6050Handler {
public:

    MPU6050Handler();

    bool begin();

    void reset_PID();

    void calibrate();

    void getAngles(float &pitch, float &roll);

    void calculate_PID(float &knee_pitch, float &knee_roll,float &hip_pitch, float &hip_roll, float dt ,int desired_pitch, int desired_roll, int integral_limit);

    float calculateDeltaTime();

private:
    Adafruit_MPU6050 mpu;
    float accelOffsets[3];
    float gyroOffsets[3];

    float Kp_knee = 1.8;
    float Ki_knee = 11.8;
    float Kd_knee = 0.025;

    float Kp_hip = 0.75;
    float Ki_hip = 12;
    float Kd_hip = 0.025;

    float last_pitch_error = 0.0;
    float last_roll_error = 0.0;
    float integral_value_pitch_knee = 0.0;
    float integral_value_roll_knee = 0.0;
    float integral_value_pitch_hip = 0.0;
    float integral_value_roll_hip = 0.0;

    float proportional_pitch_knee = 0;
    float proportional_roll_knee = 0;
    float proportional_pitch_hip = 0;
    float proportional_roll_hip = 0;

    float integral_pitch_knee = 0;
    float integral_roll_knee = 0;
    float integral_pitch_hip = 0;
    float integral_roll_hip = 0;

    float derivative_pitch_knee = 0;
    float derivative_roll_knee = 0;
    float derivative_pitch_hip = 0;
    float derivative_roll_hip = 0;

    float filtered_PID_pitch_knee = 0.0;
    float filtered_PID_roll_knee = 0.0;
    float filtered_PID_pitch_hip = 0.0;
    float filtered_PID_roll_hip = 0.0;

    float filter_coefficient = 0.1;
    
    unsigned long last_time = 0;
};

#endif
