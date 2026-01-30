
#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

// Motor Driver Pins
#define IN1 4
#define IN2 5
#define IN3 18
#define IN4 19

void setup() {
  Serial.begin(115200);
  Wire.begin();
  mpu.initialize();

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.println("Head Gesture Wheelchair Ready");
}

void moveForward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void moveBackward() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}

void turnLeft() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void turnRight() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}

void stopWheelchair() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}

void loop() {
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);

  Serial.print("AX: "); Serial.print(ax);
  Serial.print(" AY: "); Serial.println(ay);

  if (ay > 12000) {
    moveForward();
  } 
  else if (ay < -12000) {
    moveBackward();
  } 
  else if (ax > 12000) {
    turnRight();
  } 
  else if (ax < -12000) {
    turnLeft();
  } 
  else {
    stopWheelchair();
  }

  delay(200);
}
