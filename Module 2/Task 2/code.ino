// Rename BCD pins for Hundreds, Tens, Ones
int AH = 10, BH = 11, CH = 12, DH = 13;     // Hundreds
int AT = 6,  BT = 7,  CT = 8,  DT = 9;      // Tens
int AO = 2,  BO = 3,  CO = 4,  DO = 5;      // Ones

int resetButton = A0;   // Reset button pin
int count = 0;

void setup() {
  // Set all BCD pins as output
  pinMode(AH, OUTPUT); pinMode(BH, OUTPUT); pinMode(CH, OUTPUT); pinMode(DH, OUTPUT);
  pinMode(AT, OUTPUT); pinMode(BT, OUTPUT); pinMode(CT, OUTPUT); pinMode(DT, OUTPUT);
  pinMode(AO, OUTPUT); pinMode(BO, OUTPUT); pinMode(CO, OUTPUT); pinMode(DO, OUTPUT);

  pinMode(resetButton, INPUT_PULLUP);  // Reset button with internal pull-up
}

void loop() {
  // Check reset button (active LOW)
  if (digitalRead(resetButton) == LOW) {
     // Debounce
   
      count = 0; // Reset count
    }
  

  // Display current count
  displayNumber(count);

  // Increment counter every second
  delay(1000);
  count++;
  if (count > 999) count = 0; // Reset after 999
}

// Function to split number into digits and display
void displayNumber(int num) {
  int hundreds = num / 100;
  int tens = (num / 10) % 10;
  int ones = num % 10;

  displayBCD(hundreds, AH, BH, CH, DH);
  displayBCD(tens, AT, BT, CT, DT);
  displayBCD(ones, AO, BO, CO, DO);
}

// Function to output BCD for a digit
void displayBCD(int digit, int A, int B, int C, int D) {
  digitalWrite(A, digit & 0x01);        
  digitalWrite(B, (digit >> 1) & 0x01);
  digitalWrite(C, (digit >> 2) & 0x01);
  digitalWrite(D, (digit >> 3) & 0x01); 
}
