#include "Gyro.h"
#include <math.h>

MPU6050Handler::MPU6050Handler() {
    for (int i = 0; i < 3; i++) {
        accelOffsets[i] = 0;
        gyroOffsets[i] = 0;
    }

    last_pitch_error = 0.0;
    last_roll_error = 0.0;

    integral_value_pitch_knee = 0.0;
    integral_value_roll_knee = 0.0;
    integral_value_pitch_hip = 0.0;
    integral_value_roll_hip = 0.0;

    filtered_PID_pitch_knee = 0.0;
    filtered_PID_roll_knee = 0.0;
    filtered_PID_pitch_hip = 0.0;
    filtered_PID_roll_hip = 0.0;
}

void MPU6050Handler::reset_PID() {
    last_pitch_error = 0.0;
    last_roll_error = 0.0;

    integral_value_pitch_knee = 0.0;
    integral_value_roll_knee = 0.0;
    
    filtered_PID_pitch_knee = 0.0;
    filtered_PID_roll_knee = 0.0;
    
    integral_value_pitch_hip = 0.0;
    integral_value_roll_hip = 0.0;
    
    filtered_PID_pitch_hip = 0.0;
    filtered_PID_roll_hip = 0.0;
}

bool MPU6050Handler::begin() {
    if (!mpu.begin()) {
        return false;
    }

    mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);

    return true;
}

void MPU6050Handler::calibrate() {
    sensors_event_t accel, gyro, temp;
    const int samples = 250;

    for (int i = 0; i < samples; i++) {
        mpu.getEvent(&accel, &gyro, &temp);

        accelOffsets[0] += accel.acceleration.x;
        accelOffsets[1] += accel.acceleration.y;
        accelOffsets[2] += accel.acceleration.z;
        gyroOffsets[0] += gyro.gyro.x;
        gyroOffsets[1] += gyro.gyro.y;
        gyroOffsets[2] += gyro.gyro.z;

        delay(10);
    }

    accelOffsets[0] /= samples;
    accelOffsets[1] /= samples;
    accelOffsets[2] = (accelOffsets[2] / samples) - 9.8;
    gyroOffsets[0] /= samples;
    gyroOffsets[1] /= samples;
    gyroOffsets[2] /= samples;
}

void MPU6050Handler::getAngles(float &pitch, float &roll) {
    sensors_event_t accel, gyro, temp;
    mpu.getEvent(&accel, &gyro, &temp);

    float ax = accel.acceleration.x - accelOffsets[0];
    float ay = accel.acceleration.y - accelOffsets[1];
    float az = accel.acceleration.z - accelOffsets[2];

    pitch = (int((atan2(ay, az) * 180 / PI) * 10)) / 10;
    roll = (int((atan2(-ax, sqrt(ay * ay + az * az)) * 180 / PI) * 10)) / 10;
}

void MPU6050Handler::calculate_PID(float &knee_pitch, float &knee_roll,float &hip_pitch, float &hip_roll, float dt ,int desired_pitch, int desired_roll, int integral_limit) {
    float pitch, roll;
    getAngles(pitch, roll);

    float pitch_error = desired_pitch - pitch;
    float roll_error = desired_roll - roll;

    proportional_pitch_knee = constrain((Kp_knee * pitch_error), -180, 180);
    proportional_roll_knee = constrain((Kp_knee * roll_error), -180, 180);
    proportional_pitch_hip = constrain((Kp_hip * pitch_error), -180, 180);
    proportional_roll_hip = constrain((Kp_hip * roll_error), -180, 180);

    float derivative_value_pitch_knee = (pitch_error - last_pitch_error) / dt;
    float derivative_value_roll_knee = (roll_error - last_roll_error) / dt;
    derivative_pitch_knee = constrain((Kd_knee * derivative_value_pitch_knee), -180, 180);
    derivative_roll_knee = constrain((Kd_knee * derivative_value_roll_knee), -180, 180);
    float derivative_value_pitch_hip = (pitch_error - last_pitch_error) / dt;
    float derivative_value_roll_hip = (roll_error - last_roll_error) / dt;
    derivative_pitch_hip = constrain((Kd_hip * derivative_value_pitch_hip), -180, 180);
    derivative_roll_hip = constrain((Kd_hip * derivative_value_roll_hip), -180, 180);

    integral_value_pitch_knee = constrain((integral_value_pitch_knee + pitch_error * dt), (-integral_limit * (1 / Ki_knee)), (integral_limit * (1 / Ki_knee)));
    integral_value_roll_knee = constrain((integral_value_roll_knee + roll_error * dt), (-integral_limit * (1 / Ki_knee)), (integral_limit * (1 / Ki_knee)));
    integral_pitch_knee = Ki_knee * integral_value_pitch_knee;
    integral_roll_knee = Ki_knee * integral_value_roll_knee;
    integral_value_pitch_hip = constrain((integral_value_pitch_hip + pitch_error * dt), (-integral_limit * (1 / Ki_hip)), (integral_limit * (1 / Ki_hip)));
    integral_value_roll_hip = constrain((integral_value_roll_hip + roll_error * dt), (-integral_limit * (1 / Ki_hip)), (integral_limit * (1 / Ki_hip)));
    integral_pitch_hip = Ki_hip * integral_value_pitch_hip;
    integral_roll_hip = Ki_hip * integral_value_roll_hip;

    float PID_pitch_knee = proportional_pitch_knee + integral_pitch_knee + derivative_pitch_knee;
    filtered_PID_pitch_knee = constrain(((1 - filter_coefficient) * filtered_PID_pitch_knee + filter_coefficient * PID_pitch_knee), -180, 180);
    float PID_roll_knee = proportional_roll_knee + integral_roll_knee + derivative_roll_knee;
    filtered_PID_roll_knee = constrain(((1 - filter_coefficient) * filtered_PID_roll_knee + filter_coefficient * PID_roll_knee), -180, 180);
    float PID_pitch_hip = proportional_pitch_hip + integral_pitch_hip + derivative_pitch_hip;
    filtered_PID_pitch_hip = constrain(((1 - filter_coefficient) * filtered_PID_pitch_hip + filter_coefficient * PID_pitch_hip), -180, 180);
    float PID_roll_hip = proportional_roll_hip + integral_roll_hip + derivative_roll_hip;
    filtered_PID_roll_hip = constrain(((1 - filter_coefficient) * filtered_PID_roll_hip + filter_coefficient * PID_roll_hip), -180, 180);

    last_pitch_error = pitch_error;
    last_roll_error = roll_error;

    knee_pitch = filtered_PID_pitch_knee;
    knee_roll = filtered_PID_roll_knee;
    hip_pitch = filtered_PID_pitch_hip;
    hip_roll = filtered_PID_roll_hip;
}

float MPU6050Handler::calculateDeltaTime() {
    unsigned long currentTime = millis();
    float dt = (currentTime - last_time) / 1000.0;
    last_time = currentTime;
    return dt;
}
