#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    lcd.begin();

    long value = 123456789;

    lcd.print(value);
}

void loop() {

}
