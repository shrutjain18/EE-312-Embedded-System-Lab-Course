// Define the segment pins (same physical connections)
const int segmentPins[] = {2, 3, 4, 5, 6, 7, 8}; // a, b, c, d, e, f, g

// REVISED segment patterns for COMMON ANODE (inverted logic)
const byte digitPatterns[10] = {
  B11000000, // 0 (was B00111111 for cathode)
  B11111001, // 1 (was B00000110)
  B10100100, // 2 (was B01011011)
  B10110000, // 3 (was B01001111)
  B10011001, // 4 (was B01100110)
  B10010010, // 5 (was B01101101)
  B10000010, // 6 (was B01111101)
  B11111000, // 7 (was B00000111)
  B10000000, // 8 (was B01111111)
  B10010000  // 9 (was B01101111)
};

void setup() {
  // Set all segment pins as outputs
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
    digitalWrite(segmentPins[i], HIGH); // Start with all segments OFF
  }
}

void loop() {
  for (int digit = 0; digit < 10; digit++) {
    displayDigit(digit);
    delay(400); // 1 second delay between digits
  }
}

void displayDigit(int digit) {
  byte pattern = digitPatterns[digit];
  
  // Set each segment according to the pattern
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], bitRead(pattern, i));
  }
}
