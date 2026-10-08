#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    lcd.begin();

    lcd.printBase(255, DEC);

    lcd.setCursor(0, 1);
    lcd.printBase(255, OCT);
}

void loop() {

}
