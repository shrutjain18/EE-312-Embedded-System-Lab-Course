#define PWM_PIN 5
#define POT_PIN A0

void setup() {
  DDRD |= (1 << PWM_PIN);
}

void loop() {
  int potValue = analogRead(POT_PIN); // 0-1023
  float duty = potValue / 1023.0;     // 0-1
  
  float freq = 100; 
  float period_us = 1000000.0 / freq;
  float on_time = period_us * duty;
  float off_time = period_us - on_time;
  
  PORTD |= (1 << PWM_PIN);
  delayMicroseconds((int)on_time);
  PORTD &= ~(1 << PWM_PIN);
  delayMicroseconds((int)off_time);
}
