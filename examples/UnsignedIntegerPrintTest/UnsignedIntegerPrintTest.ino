#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    lcd.begin();

    unsigned int value = 50000;

    lcd.print(value);
}

void loop() {

}
