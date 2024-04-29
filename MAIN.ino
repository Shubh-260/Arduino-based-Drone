#include <Wire.h>
#include <MPU6050.h> // Library for MPU-6050

#define RECEIVER_PIN_THROTTLE 8
#define RECEIVER_PIN_ROLL 9
#define RECEIVER_PIN_PITCH 10
#define RECEIVER_PIN_YAW 11

#define FRONT_RIGHT_PIN 4
#define REAR_RIGHT_PIN 5
#define REAR_LEFT_PIN 6
#define FRONT_LEFT_PIN 7

MPU6050 mpu;

void setup() {
  Wire.begin();
  Serial.begin(9600);

  // Initialize ESC pins
  pinMode(FRONT_RIGHT_PIN, OUTPUT);
  pinMode(REAR_RIGHT_PIN, OUTPUT);
  pinMode(REAR_LEFT_PIN, OUTPUT);
  pinMode(FRONT_LEFT_PIN, OUTPUT);

  // Calibrate MPU-6050
  mpu.initialize();
  mpu.calibrateGyro();
}

void loop() {
  // Read receiver inputs
  int throttle = pulseIn(RECEIVER_PIN_THROTTLE, HIGH, 20000);
  int roll = pulseIn(RECEIVER_PIN_ROLL, HIGH, 20000);
  int pitch = pulseIn(RECEIVER_PIN_PITCH, HIGH, 20000);
  int yaw = pulseIn(RECEIVER_PIN_YAW, HIGH, 20000);

  // Map receiver inputs to ESC outputs
  int frontRightSpeed = map(throttle, 1000, 2000, 1000, 2000);
  int rearRightSpeed = map(throttle, 1000, 2000, 1000, 2000);
  int rearLeftSpeed = map(throttle, 1000, 2000, 1000, 2000);
  int frontLeftSpeed = map(throttle, 1000, 2000, 1000, 2000);

  // Control ESCs
  analogWrite(FRONT_RIGHT_PIN, frontRightSpeed);
  analogWrite(REAR_RIGHT_PIN, rearRightSpeed);
  analogWrite(REAR_LEFT_PIN, rearLeftSpeed);
  analogWrite(FRONT_LEFT_PIN, frontLeftSpeed);

  // Print sensor data for calibration
  printData();
}

void printData() {
  // Read and print accelerometer and gyroscope data
  int16_t ax, ay, az;
  int16_t gx, gy, gz;

  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  Serial.print("a/g:\t");
  Serial.print(ax); Serial.print("\t");
  Serial.print(ay); Serial.print("\t");
  Serial.print(az); Serial.print("\t");
  Serial.print(gx); Serial.print("\t");
  Serial.print(gy); Serial.print("\t");
  Serial.println(gz);
}

