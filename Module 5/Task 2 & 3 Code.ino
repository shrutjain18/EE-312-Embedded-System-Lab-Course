// 2nd Arduino pins for ultrasonic sensors
#define trigF 4
#define echoF 5
#define trigR A1
#define echoR A2
#define trigL 6
#define echoL 7
#define trigB 8
#define echoB 9

float dur = 0;
// Output pins to 1st Arduino for direction control (digital)
const int pathPinA = 10; // Right
const int pathPinB = 11; // Forward
const int pathPinC = 12; // Left
const int pathPinD = 13; // Backward

// Analog output pin for speed (PWM)
const int speedPin = A3; // Use PWM pin on Arduino (D3, D5, D6, D9, D10, D11)

void setup() {
  pinMode(trigF, OUTPUT); pinMode(echoF, INPUT);
  pinMode(trigR, OUTPUT); pinMode(echoR, INPUT_PULLUP);
  pinMode(trigL, OUTPUT); pinMode(echoL, INPUT);
  pinMode(trigB, OUTPUT); pinMode(echoB, INPUT);

  pinMode(pathPinA, OUTPUT);
  pinMode(pathPinB, OUTPUT);
  pinMode(pathPinC, OUTPUT);
  pinMode(pathPinD, OUTPUT);

  pinMode(speedPin, OUTPUT);

  Serial.begin(9600);
}

long measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 30000); // 30ms timeout
  long distance = duration * 0.034 / 2;
  dur = duration/(float)1000;
  if(distance == 0) distance = 999; // no reading fallback
  return distance;
}

void resetOutputs() {
  digitalWrite(pathPinA, LOW);
  digitalWrite(pathPinB, LOW);
  digitalWrite(pathPinC, LOW);
  digitalWrite(pathPinD, LOW);
  analogWrite(speedPin, 0);
}

void loop() {
  long distF = measureDistance(trigF, echoF);
  long distR = measureDistance(trigR, echoR);
  long distL = measureDistance(trigL, echoL);
  long distB = measureDistance(trigB, echoB);

  Serial.print(" F:"); Serial.print(distF);
  Serial.print(" R:"); Serial.print(distR);
  Serial.print(" L:"); Serial.print(distL);
  Serial.print(" B:"); Serial.println(distB);
  Serial.print(" Delay :"); Serial.print(dur);Serial.println(" ms");

  resetOutputs();

  // Maze-solving decision logic (right hand wall follower)
  // Priority order: turn right if clear, else forward, else left, else backward

  int speed = 200; // PWM speed 0-255

  if(distL > 30) {
    digitalWrite(pathPinA, LOW);
    digitalWrite(pathPinB, LOW);
    digitalWrite(pathPinC, HIGH);
    digitalWrite(pathPinD, LOW); // turn left
  }
  else if(distF > 30) {
    digitalWrite(pathPinA, LOW);
    digitalWrite(pathPinB, HIGH);
    digitalWrite(pathPinC, LOW);
    digitalWrite(pathPinD, LOW); // forward
  }
  
  else if(distR > 30) {
    digitalWrite(pathPinA, HIGH);
    digitalWrite(pathPinB, LOW);
    digitalWrite(pathPinC, LOW);
    digitalWrite(pathPinD, LOW);// turn right
  }
  else {
    digitalWrite(pathPinA, LOW);
    digitalWrite(pathPinB, LOW);
    digitalWrite(pathPinC, LOW);
    digitalWrite(pathPinD, HIGH); // backward/turn around
    //speed = 150; // reduce speed reversing
  }

  analogWrite(speedPin, speed);

  delay(150);
}
