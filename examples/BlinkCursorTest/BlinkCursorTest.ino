#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    lcd.begin();

    lcd.setCursor(0, 0);
    lcd.write('H');
    lcd.write('o');
    lcd.write('l');
    lcd.write('a');

    lcd.setCursor(4, 0);

    lcd.blinkCursor();
}

void loop() {
    lcd.update();
}
