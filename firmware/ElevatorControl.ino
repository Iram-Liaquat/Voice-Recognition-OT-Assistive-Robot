#include <Encoder.h>

int motorLA = 9;
int motorLB = 10;
int motorLpwm = 11;

Encoder myEnc(5, 6);

int limitSensor = 8;
int triggerPin1 = 2; // eleven
int triggerPin2 = 3; // towelve

long a;
int i;

void setup() {
  Serial.begin(9600);
  pinMode(limitSensor, INPUT);
  pinMode(motorLA, OUTPUT);
  pinMode(motorLB, OUTPUT);
  pinMode(motorLpwm, OUTPUT);
  pinMode(triggerPin1, INPUT);
  pinMode(triggerPin2, INPUT);

  int sensor = digitalRead(limitSensor);
  if (sensor == LOW) {
    Serial.println("Limit Sensor Bad");
    digitalWrite(motorLA, LOW);
    digitalWrite(motorLB, LOW);
    analogWrite(motorLpwm, 0);
    return; 
  }
}

void loop() {
  long newPosition = myEnc.read();
  if (newPosition != a) {
    a = newPosition;
    Serial.println(a);
  }

  int state1 = digitalRead(triggerPin1);
  int state2 = digitalRead(triggerPin2);

  if (state1 == HIGH && state2 == HIGH) {
    goToPosition(-7);
  } 
  else if (state1 == LOW && state2 == HIGH) {
    goToPosition(-48);
  } 
  else if (state1 == HIGH && state2 == LOW) {
    goToPosition(-28);
  } 
  else if (state1 == LOW && state2 == LOW) {
    goToPosition(-20);
  }
}

void goToPosition(long targetPos) {
  if (a == targetPos) {
    digitalWrite(motorLA, LOW);
    digitalWrite(motorLB, LOW);
    analogWrite(motorLpwm, 0);
  } 
  else if (a > targetPos) {
    digitalWrite(motorLA, HIGH);
    digitalWrite(motorLB, LOW);
    analogWrite(motorLpwm, 255);
  } 
  else {
    digitalWrite(motorLA, LOW);
    digitalWrite(motorLB, HIGH);
    analogWrite(motorLpwm, 255);
  }
}
