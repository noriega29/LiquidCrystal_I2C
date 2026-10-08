#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    lcd.begin();

    lcd.print(123);
    lcd.setCursor(0, 1);
    lcd.print(-456);
}

void loop() {

}
