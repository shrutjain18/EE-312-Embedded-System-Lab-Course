// C++ code
//
#define PWM_PIN 5 // PD5

void setup() {
  DDRD |= (1 << PWM_PIN); // Set pin as output
}

void loop() {
  float freq = 100;         // 500 Hz PWM
  float duty = 0.5;         // 50% duty cycle
  
  float period_us = 1000000.0 / freq;
  float on_time = period_us * duty;
  float off_time = period_us - on_time;
  
  PORTD |= (1 << PWM_PIN);   // HIGH
  delayMicroseconds((int)on_time);
  
  PORTD &= ~(1 << PWM_PIN);  // LOW
  delayMicroseconds((int)off_time);
}
