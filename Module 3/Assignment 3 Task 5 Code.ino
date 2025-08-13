#include <Servo.h>

Servo myServo;

void setup() {
  myServo.attach(5);
}

void loop() {
  for (int angle = 0; angle <= 180; angle += 10) {
    myServo.write(angle);
    delay(500);
  }
}

