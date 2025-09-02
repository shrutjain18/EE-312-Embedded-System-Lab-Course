#include <LiquidCrystal.h>

const int trigPin = 11;
const int echoPin = 10;

long duration;
int distance;
bool measured = false;
int maxReferenceHeight = 500;
int referenceHeight;
int maxHeight = 220;
int minHeight = 30;

const int rsPin = 2;
const int enablePin = 3;
const int data_4 = 4;
const int data_5 = 5;
const int data_6 = 6;
const int data_7 = 7;

LiquidCrystal lcd(rsPin, enablePin, data_4, data_5, data_6, data_7); 
// 16*2 LCD Display | RS - 42, Enable - 44, Data - 46, 48, 50, 52 (R/W - GND)

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.clear();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  if (measured == false){
    lcdInitialAlert();
    clearTrigger();
    triggerON(10);
    distance = distanceMeasured();
    printDistanceToLCD(distance); 
    measured = true;
  }
}

void clearTrigger(){
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
}

void triggerON(int MicroSeconds){
  // Sets the trigPin on HIGH state for X micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(MicroSeconds);
  digitalWrite(trigPin, LOW);
}

int distanceMeasured(){
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance = duration*0.034/2;
    Serial.print("Distance: ");
    Serial.println(distance);
    return distance;
}

void printDistanceToLCD(int distance){
  lcd.setCursor(0, 1);
  lcd.print("Height : ");
  lcd.print(distance);
  lcd.print(" cm");
}

void lcdInitialAlert(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ready To Measure");
  delay(2000);
}
