#define LED_PIN 5     // PWM pin
#define POT_PIN A0    // Analog input

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Read potentiometer (0–1023)
  int potValue = analogRead(POT_PIN);

  // Map to PWM range (0–255)
  int pwmValue = map(potValue, 0, 1023, 0, 255);

  // Output PWM
  analogWrite(LED_PIN, pwmValue);
  delay(10);
}

