#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

String roll = "230108051";
String name = "Shibarpita";

void setup() {
    lcd.begin(16, 2);
}

void loop() {
    lcd.setCursor(0, 0);
    lcd.print(name);

    lcd.setCursor(16, 1);
    lcd.autoscroll();

    for (int i = 0; i < 9; i++) {
        delay(100);
        lcd.print(roll[i]);
    }
}