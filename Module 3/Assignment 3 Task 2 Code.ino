// Manual PWM to control LED brightness without analogWrite()

const int pwmPin = 5;      // Output pin
const int period = 1000;   // Period in microseconds (1 kHz frequency)

void setup() {
  pinMode(pwmPin, OUTPUT);
}

void loop() {
  // Ramp duty cycle from 0% to 100%
  for (int dutyCycle = 0; dutyCycle <= 100; dutyCycle++) {
    for (int i = 0; i < 50; i++) {
      int highTime = (period * dutyCycle) / 100;
      int lowTime  = period - highTime;

      if (highTime > 0) digitalWrite(pwmPin, HIGH);
      if (highTime > 0) delayMicroseconds(highTime);

      if (lowTime > 0) digitalWrite(pwmPin, LOW);
      if (lowTime > 0) delayMicroseconds(lowTime);
    }
  }

  // Ramp duty cycle from 100% back to 0%
  for (int dutyCycle = 100; dutyCycle >= 0; dutyCycle--) {
    for (int i = 0; i < 50; i++) {
      int highTime = (period * dutyCycle) / 100;
      int lowTime  = period - highTime;

      if (highTime > 0) digitalWrite(pwmPin, HIGH);
      if (highTime > 0) delayMicroseconds(highTime);

      if (lowTime > 0) digitalWrite(pwmPin, LOW);
      if (lowTime > 0) delayMicroseconds(lowTime);
    }
  }
}
