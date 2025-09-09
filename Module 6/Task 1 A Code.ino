#include <Adafruit_LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>

Adafruit_LiquidCrystal lcd(0);


// ---------------- LCD ----------------
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  // RS, E, D4, D5, D6, D7

// ---------------- Servo ----------------
Servo myServo;
int servoPin = 3;

// ---------------- Buzzer ----------------
int buzzerPin = 8;

// ---------------- Keypad ----------------
const byte ROWS = 4; 
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {13, 12, 11, 10};   // R1, R2, R3, R4
byte colPins[COLS] = {7, 6, 5, 4}; // C1, C2, C3, C4

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// ---------------- Password ----------------
String password = "1234";  // change as per need
String input = "";

void setup() {
  // Initialize LCD
  lcd.begin(16, 2);
  lcd.setBacklight(1);   // Turn on backlight
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");
  myServo.attach(servoPin);
  myServo.write(0); // locked position
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key == '#') {
      if (input == password) {
        lcd.clear();
        lcd.print("Access Granted");
        myServo.write(90); // unlock
        digitalWrite(buzzerPin, LOW);
        delay(2000);
        myServo.write(0);  // lock again
        lcd.clear();
        lcd.print("Enter Password:");
      } else {
        lcd.clear();
        lcd.print("Access Denied");
        tone(buzzerPin, 1000, 500); // buzzer sound
        delay(2000);
        lcd.clear();
        lcd.print("Enter Password:");
      }
      input = "";  // reset input
    }
    else if (key == '*') {
      input = "";  // clear input
      lcd.clear();
      lcd.print("Enter Password:");
    }
    else {
      input += key;
      lcd.setCursor(0, 1);
      lcd.print(input); // show typed password
    }
  }
}
