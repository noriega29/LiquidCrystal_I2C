#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    lcd.begin();

    lcd.setCursor(0, 0);
    lcd.write('A');

    lcd.setCursor(15, 0);
    lcd.write('B');

    lcd.setCursor(0, 1);
    lcd.write('C');

    lcd.setCursor(15, 1);
    lcd.write('D');
}

void loop() {

}
