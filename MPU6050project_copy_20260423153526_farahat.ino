#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

int16_t accX, accY, accZ;
int16_t gyroX, gyroY, gyroZ;

long accX_offset = 0, accY_offset = 0, accZ_offset = 0;
long gyroX_offset = 0, gyroY_offset = 0, gyroZ_offset = 0;

float f_accX = 0, f_accY = 0, f_accZ = 0;

float accAngleY;
float gyroAngleY = 0;
float finalAngleY = 0;

unsigned long prevTime;
float dt;

float alpha = 0.5;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();

  Serial.println("Calibrating...");

  for(int i = 0; i < 1000; i++){
    mpu.getMotion6(&accX, &accY, &accZ, &gyroX, &gyroY, &gyroZ);

    accX_offset += accX;
    accY_offset += accY;
    accZ_offset += accZ;

    gyroX_offset += gyroX;
    gyroY_offset += gyroY;
    gyroZ_offset += gyroZ;

    delay(2);
  }

  accX_offset /= 1000;
  accY_offset /= 1000;
  accZ_offset = (accZ_offset / 1000) - 16384;

  gyroX_offset /= 1000;
  gyroY_offset /= 1000;
  gyroZ_offset /= 1000;

  prevTime = millis();

  Serial.println("Done Calibration");
}

void loop() {
  unsigned long currentTime = millis();
  dt = (currentTime - prevTime) / 1000.0;
  prevTime = currentTime;

  mpu.getMotion6(&accX, &accY, &accZ, &gyroX, &gyroY, &gyroZ);

  accX -= accX_offset;
  accY -= accY_offset;
  accZ -= accZ_offset;

  gyroY -= gyroY_offset;

  //  Filtering
  f_accX = alpha * accX + (1 - alpha) * f_accX;
  f_accY = alpha * accY + (1 - alpha) * f_accY;
  f_accZ = alpha * accZ + (1 - alpha) * f_accZ;

  //  زاوية من accelerometer
  accAngleY = atan2(-f_accX, sqrt(f_accY*f_accY + f_accZ*f_accZ)) * 180 / PI;

  //  زاوية من gyro
  gyroAngleY += (gyroY / 131.0) * dt;

  //  دمج
  finalAngleY = 0.96 * gyroAngleY + 0.04 * accAngleY;

  Serial.print("Angle: ");
  Serial.println(finalAngleY);

  delay(20);
}