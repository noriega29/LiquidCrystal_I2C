#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    lcd.begin();

    unsigned long value = 4000000000UL;

    lcd.print(value);
}

void loop() {

}
