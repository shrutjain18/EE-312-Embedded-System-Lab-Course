#include <Adafruit_LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>
#include <EEPROM.h>
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

// ------------------ PASSWORD / EEPROM ------------------
const int passLength = 4;
const int eepromAddr = 0; // starting address to store password (4 bytes)
String input = "";
unsigned long lastHashTime = 0;
int consecutiveHashCount = 0;
const unsigned long hashTimeout = 1500UL; // ms to count #### presses

// ------------------ HELPERS ------------------
void showPrompt() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter Password:");
  lcd.setCursor(0,1);
  lcd.print("                "); // clear second line
  lcd.setCursor(0,1);
}

String readStoredPassword() {
  String p = "";
  for (int i = 0; i < passLength; ++i) {
    byte b = EEPROM.read(eepromAddr + i);
    if (b == 255 || b == 0) b = '0'; // fallback if empty
    p += char(b);
  }
  return p;
}

void writeStoredPassword(const String &p) {
  for (int i = 0; i < passLength; ++i) {
    EEPROM.update(eepromAddr + i, p[i]);
  }
}

// Blocking read of a single key (waits for press then release)
char getKeyBlocking() {
  char k;
  do { k = keypad.getKey(); } while (k == NO_KEY);
  // wait for key release
  while (keypad.getKey() != NO_KEY) delay(10);
  return k;
}

// Read exactly passLength digits (shows '*' as typed)
String readDigitsExactly(const char *prompt) {
  lcd.clear();
  lcd.print(prompt);
  lcd.setCursor(0,1);
  String s = "";
  while (s.length() < passLength) {
    char k = getKeyBlocking();
    if (k == '*') { // clear entered digits
      s = "";
      lcd.setCursor(0,1);
      lcd.print("                ");
      lcd.setCursor(0,1);
      continue;
    }
    if (k >= '0' && k <= '9') {
      s += k;
      // print masked char
      for (int i = 0; i < s.length(); ++i) lcd.print('*');
    }
    // ignore other keys (A/B/C/D/#)
  }
  delay(150); // small debounce
  return s;
}

// Enter reset flow: Verify old pass then get new pass and store
void enterResetMode() {
  String stored = readStoredPassword();
  String oldP = readDigitsExactly("Enter current:");
  if (oldP == stored) {
    String newP = readDigitsExactly("Enter new pass:");
    writeStoredPassword(newP);
    lcd.clear();
    lcd.print("Password Saved");
    delay(1200);
  } else {
    lcd.clear();
    lcd.print("Wrong Current!");
    tone(buzzerPin, 1000, 700);
    delay(900);
    noTone(buzzerPin);
  }
  showPrompt();
}

// Check submitted password
void checkPasswordSubmit() {
  String stored = readStoredPassword();
  if (input == stored) {
    lcd.clear();
    lcd.print("Access Granted");
    // no buzzer on correct entry
    myServo.write(90);   // unlock
    delay(1600);
    myServo.write(0);    // lock back
    delay(200);
    showPrompt();
  } else {
    lcd.clear();
    lcd.print("Access Denied");
    tone(buzzerPin, 900, 700); // beep for wrong
    delay(900);
    noTone(buzzerPin);
    showPrompt();
  }
  input = "";
}

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
  if (EEPROM.read(eepromAddr) == 255 || EEPROM.read(eepromAddr) == 0) {
    writeStoredPassword("1234");
  }

  showPrompt();
}

void loop() {
  char key = keypad.getKey();
  if (!key) return;

  // Clear star '*' clears current input
  if (key == '*') {
    input = "";
    lcd.setCursor(0,1);
    lcd.print("                ");
    consecutiveHashCount = 0;
    return;
  }

  // Submit / Hash logic
  if (key == '#') {
    if (input.length() > 0) {
      // user submitted a password attempt
      checkPasswordSubmit();
      consecutiveHashCount = 0;
    } else {
      // input empty: count consecutive '#' presses for reset trigger
      unsigned long now = millis();
      if (now - lastHashTime <= hashTimeout) consecutiveHashCount++;
      else consecutiveHashCount = 1;
      lastHashTime = now;
      if (consecutiveHashCount >= 4) {
        consecutiveHashCount = 0;
        // go to reset mode
        enterResetMode();
      }
    }
    return;
  }

  // If numeric key and not yet full, append and show masked
  if (key >= '0' && key <= '9') {
    if (input.length() < passLength) {
      input += key;
      lcd.setCursor(0,1);
      for (int i = 0; i < input.length(); ++i) lcd.print('*');
    }
  } else {
    // ignore A/B/C/D or other keys in normal input
  }

  // any normal key press breaks consecutive '#' chain
  consecutiveHashCount = 0;
}

