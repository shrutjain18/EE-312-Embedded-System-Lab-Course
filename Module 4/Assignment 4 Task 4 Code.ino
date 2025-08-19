#include <Adafruit_LiquidCrystal.h>

// Create LCD object (address 0 for I2C backpack)
// Change "0" if your module uses a different address
Adafruit_LiquidCrystal lcd(0);

// Pin definitions
const int forwardPin = 8;   // Forward DIP input
const int rightPin   = 9;   // Right DIP input
const int leftPin    = 10;  // Left DIP input

const int motorA = 5;  // PWM output (EN1)
const int motorB = 6;  // PWM output (EN2)

const int potPin = A0; // Potentiometer input

void setup() {
  // DIP switch inputs with pull-ups
  pinMode(forwardPin, INPUT_PULLUP);
  pinMode(rightPin, INPUT_PULLUP);
  pinMode(leftPin, INPUT_PULLUP);

  pinMode(motorA, OUTPUT);
  pinMode(motorB, OUTPUT);

  // Initialize LCD
  lcd.begin(16, 2);
  lcd.setBacklight(1);   // Turn on backlight
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Motor Control");
}

void loop() {
  // Read DIP switch states (LOW = switch ON)
  bool forward = (digitalRead(forwardPin) == LOW);
  bool right   = (digitalRead(rightPin)   == LOW);
  bool left    = (digitalRead(leftPin)    == LOW);

  // Read potentiometer → map to PWM
  int speed = analogRead(potPin);
  speed = map(speed, 0, 1023, 0, 255);

  // Default: stop
  int pwmA = 0;
  int pwmB = 0;
  String direction = "Stop";

  // Control logic
  if (forward) {
    pwmA = speed;
    pwmB = speed;
    direction = "Forward";
  }
  else if (right) {
    pwmA = speed;
    pwmB = 0;
    direction = "Right";
  }
  else if (left) {
    pwmA = 0;
    pwmB = speed;
    direction = "Left";
  }

  // Apply motor speed
  analogWrite(motorA, pwmA);
  analogWrite(motorB, pwmB);

  // --- LCD Display ---
  lcd.setCursor(0, 0);
  lcd.print("Speed: ");
  lcd.print(speed);
  lcd.print("   "); // clear trailing chars

  lcd.setCursor(0, 1);
  lcd.print("Dir: ");
  lcd.print(direction);
  lcd.print("     "); // clear trailing chars

  delay(200); // update rate
}
