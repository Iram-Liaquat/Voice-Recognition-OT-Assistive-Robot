#include <Servo.h>

Servo servoBase;
Servo servoShoulder;
Servo servoElbow;
Servo servoWrist;

int pinScissor = 2;
int pinKnife = 3;
int pinThread = 4;
int pinNeedle = 5;

void setup() {
  servoBase.attach(6);
  servoShoulder.attach(7);
  servoElbow.attach(8);
  servoWrist.attach(9);

  pinMode(pinScissor, INPUT);
  pinMode(pinKnife, INPUT);
  pinMode(pinThread, INPUT);
  pinMode(pinNeedle, INPUT);

  servoBase.write(0);
  delay(1000);
  servoShoulder.write(0);
  delay(1000);
  servoElbow.write(0);
  delay(1000);
  servoWrist.write(0);
  delay(1000);
}

void loop() {
  int scissor = digitalRead(pinScissor);
  int knife = digitalRead(pinKnife);
  int thread = digitalRead(pinThread);
  int needle = digitalRead(pinNeedle);

  if (scissor == HIGH && knife == LOW && thread == LOW && needle == LOW) {
    executePickAndPlace();
  }
  else if (scissor == LOW && knife == HIGH && thread == LOW && needle == LOW) {
    executePickAndPlace();
  }
  else if (scissor == LOW && knife == LOW && thread == HIGH && needle == LOW) {
    executePickAndPlace();
  }
  else if (scissor == LOW && knife == LOW && thread == LOW && needle == HIGH) {
    executePickAndPlace();
  }
}

void executePickAndPlace() {
  // Move to pickup position
  servoBase.write(100);
  delay(1000);
  servoShoulder.write(50);
  delay(1000);
  servoElbow.write(100);
  delay(1000);
  servoWrist.write(50); // Close gripper
  delay(1000);

  // Wait for handover
  delay(50000); 

  // Move to handover position and release
  servoBase.write(100);
  delay(1000);
  servoShoulder.write(50);
  delay(1000);
  servoElbow.write(100);
  delay(1000);
  servoWrist.write(50); // Open gripper
  delay(1000);
}
