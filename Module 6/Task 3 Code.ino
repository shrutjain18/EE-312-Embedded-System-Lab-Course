
// ------------------ Pins ------------------
const int pir1 = 2;  // PIR sensor 1
const int pir2 = 3;  // PIR sensor 2

// ------------------ Variables ------------------
int peopleCount = 0;
bool pir1State = false;
bool pir2State = false;

void setup() {
  pinMode(pir1, INPUT);
  pinMode(pir2, INPUT);
  Serial.begin(9600);
  Serial.println("People Counter System Started");
}

void loop() {
  int pir1Val = digitalRead(pir1);
  int pir2Val = digitalRead(pir2);

  // Detect entry (PIR1 then PIR2)
  if (pir1Val == HIGH && !pir1State) {
    pir1State = true;
  }
  if (pir1State && pir2Val == HIGH) {
    peopleCount++;
    Serial.print("Person Entered | Count: ");
    Serial.println(peopleCount);
    delay(500); // debounce
    pir1State = false;
  }

  // Detect exit (PIR2 then PIR1)
  if (pir2Val == HIGH && !pir2State) {
    pir2State = true;
  }
  if (pir2State && pir1Val == HIGH) {
    if (peopleCount > 0) peopleCount--;
    Serial.print("Person Exited | Count: ");
    Serial.println(peopleCount);
    delay(500); // debounce
    pir2State = false;
  }
}
