#include <LiquidCrystal.h>

// Initialize LCD with the same pin configuration as before
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Fibonacci variables
unsigned long previous1 = 0;  // F(n-2)
unsigned long previous2 = 1;  // F(n-1)
unsigned long current = 0;    // F(n)
int term = 0;                 // Term counter

void setup() {
  lcd.begin(16, 2);
  lcd.print("Fibonacci Counter");
  delay(300);
  lcd.clear();
}

void loop() {
  // Calculate next Fibonacci number
  if (term == 0) {
    current = 0;
  } 
  else if (term == 1) {
    current = 1;
  } 
  else {
    current = previous1 + previous2;
  }

  // Display the current term
  lcd.setCursor(0, 0);
  lcd.print("Term ");
  lcd.print(term);
  lcd.print(": ");
  
  lcd.setCursor(0, 1);
  lcd.print("                "); // Clear line
  lcd.setCursor(0, 1);
  lcd.print(current);

  // Update previous values for next iteration
  previous1 = previous2;
  previous2 = current;
  term++;

  // Check for overflow
  if (current + previous1 < previous1) { // Overflow occurred
    lcd.clear();
    lcd.print("Max reached!");
    lcd.setCursor(0, 1);
    lcd.print("Resetting...");
    delay(300);
    resetCounter();
  }
  
  delay(300); // Delay between terms
}

void resetCounter() {
  previous1 = 0;
  previous2 = 1;
  current = 0;
  term = 0;
  lcd.clear();
}