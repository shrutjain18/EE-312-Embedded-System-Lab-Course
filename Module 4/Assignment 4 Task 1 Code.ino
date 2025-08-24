// L293D + DC Motor @ approx constant speed (open-loop)
// EN1 -> D5 (PWM), IN1 -> D2, IN2 -> D3

const int EN1 = 5;   // PWM enable for Motor A
const int IN1 = 2;   // Direction 1
const int IN2 = 3;   // Direction 2

// Choose your target PWM (0..255). 170~200 is a good start on 9V.
int targetPWM = 190;     

// Soft-start parameters
const int rampStep = 5;     // PWM increment per step
const int rampDelay = 20;   // ms between steps during ramp

void setup() {
  pinMode(EN1, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // Set direction (IN1=HIGH, IN2=LOW)
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // Soft-start ramp up to targetPWM
  for (int p = 0; p <= targetPWM; p += rampStep) {
    analogWrite(EN1, p);
    delay(rampDelay);
  }

  // Hold target speed
  analogWrite(EN1, targetPWM);
}

void loop() {
  // Keep running at the target speed.
  // If you want to test different speeds, uncomment and edit below.

  // static unsigned long t0 = millis();
  // if (millis() - t0 > 3000) { // every 3s, change speed for demo
  //   t0 = millis();
  //   targetPWM = (targetPWM == 190) ? 150 : 190;
  //   analogWrite(EN1, targetPWM);
  // }
}
