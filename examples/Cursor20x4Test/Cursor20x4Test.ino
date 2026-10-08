#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
    lcd.begin();

    lcd.setCursor(0, 0);
    lcd.write('A');

    lcd.setCursor(19, 0);
    lcd.write('B');

    lcd.setCursor(0, 1);
    lcd.write('C');

    lcd.setCursor(19, 1);
    lcd.write('D');

    lcd.setCursor(0, 2);
    lcd.write('E');

    lcd.setCursor(19, 2);
    lcd.write('F');

    lcd.setCursor(0, 3);
    lcd.write('G');

    lcd.setCursor(19, 3);
    lcd.write('H');
}

void loop() {
    
}
