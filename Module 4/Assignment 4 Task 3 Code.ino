// Pin definitions
const int forwardPin = 8;   // Forward input
const int rightPin   = 9;   // Right input
const int leftPin    = 10;  // Left input

const int motorA = 5;  // PWM output for one motor
const int motorB = 6;  // PWM output for other motor

const int potPin = A0; // Potentiometer input

void setup() {
  // Configure pins
  pinMode(forwardPin, INPUT);
  pinMode(rightPin, INPUT);
  pinMode(leftPin, INPUT);

  pinMode(motorA, OUTPUT);
  pinMode(motorB, OUTPUT);
}

void loop() {
  // Read inputs
  bool forward = digitalRead(forwardPin);
  bool right   = digitalRead(rightPin);
  bool left    = digitalRead(leftPin);

  // Read potentiometer (0–1023) and map to PWM (0–255)
  int speed = analogRead(potPin);
  speed = map(speed, 0, 1023, 0, 255);

  // Default: stop motors
  int pwmA = 0;
  int pwmB = 0;

  // Control logic
  if (forward) {
    pwmA = speed;
    pwmB = speed;
  }
  else if (right) {
    pwmA = speed;
    pwmB = 0;
  }
  else if (left) {
    pwmA = 0;
    pwmB = speed;
  }

  // Output PWM signals
  analogWrite(motorA, pwmA);
  analogWrite(motorB, pwmB);
}
