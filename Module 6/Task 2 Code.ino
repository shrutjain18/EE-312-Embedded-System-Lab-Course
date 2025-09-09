#include "Adafruit_LEDBackpack.h"
#include <IRremote.h>
int button = 0;
int LED_p = 13, LED_s = 0;
int Motor_p = 12, Motor_s = 0;
int bulb_p =11, bulb_s = 0;
int mapCodeToButton(unsigned long code) {
  if ((code & 0x0000FFFF) == 0x0000BF00) {
    code >>= 16;
    if (((code >> 8) ^ (code & 0x00FF)) == 0x00FF) {
      return code & 0xFF;}}
  return -1;
}
int readInfrared() {
  int result = -1;
  if (IrReceiver.decode()) {
    unsigned long code = IrReceiver.decodedIRData.decodedRawData;
    result = mapCodeToButton(code);
    IrReceiver.resume();}
  return result;
}
void setup()
{
  IrReceiver.begin(2);
  Serial.begin(9600);
  pinMode(LED_p,OUTPUT);
  pinMode(Motor_p,OUTPUT);
  pinMode(bulb_p,OUTPUT);
}
void loop()
{
  button = readInfrared();
  if (button == 16) {
    if (LED_s==0) {
    	digitalWrite(LED_p, HIGH);
      	LED_s = 1;}
    else {
      digitalWrite(LED_p, LOW);
      LED_s = 0;}
  }
  if (button == 17) {
    if (Motor_s==0) {
    	digitalWrite(Motor_p, HIGH);
      	Motor_s = 1;}
    else {
      digitalWrite(Motor_p, LOW);
      Motor_s = 0;}
  }
  if (button == 18) {
    if (bulb_s==0) {
    	digitalWrite(bulb_p, HIGH);
      	bulb_s = 1;}
    else {
      digitalWrite(bulb_p, LOW);
      bulb_s = 0;}
  }
  delay(10);
}
