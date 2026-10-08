#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    lcd.begin();

    lcd.setCursor(0, 0);
    lcd.write('A');

    lcd.setCursor(5, 1);
    lcd.write('B');

    delay(2000);

    lcd.clear();
}

void loop() {

}
