// L293D + DC Motor, Pot speed control (A0 -> speed, D5 PWM, D2/D3 direction)

const int EN1 = 5;   // PWM enable for Motor A
const int IN1 = 2;   // Direction 1
const int IN2 = 3;   // Direction 2
const int POT = A0;  // Potentiometer wiper

// Tuning
const int MIN_PWM = 60;   // below this, small motors often buzz/stall
const int MAX_PWM = 255;  // full speed
const int FILTER = 6;     // EMA filter strength (higher = smoother, slower)

int pwmCmd = 0;
int ema = 0;

void setup() {
  pinMode(EN1, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(POT, INPUT);

  // Set a fixed direction (forward). Change as needed.
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // Gentle startup
  analogWrite(EN1, 0);
}

void loop() {
  // Read and smooth potentiometer
  int raw = analogRead(POT);     // 0..1023
  ema = ema + (raw - ema) / FILTER;

  // Map to PWM with a stall-safe floor and true zero zone
  int p = map(ema, 0, 1023, 0, MAX_PWM);

  // Create a “dead zone” for very low speeds to avoid buzzing
  if (p > 0 && p < MIN_PWM) p = MIN_PWM;

  // If pot really near zero, force OFF
  if (ema < 10) p = 0;

  // Apply command
  analogWrite(EN1, p);

  // (Optional) print for debugging
  // Serial.begin(9600);
  // Serial.print("raw="); Serial.print(raw);
  // Serial.print("  ema="); Serial.print(ema);
  // Serial.print("  pwm="); Serial.println(p);

  delay(10);
}
