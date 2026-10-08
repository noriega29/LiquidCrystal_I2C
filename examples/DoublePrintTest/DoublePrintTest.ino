#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    lcd.begin();

    lcd.print(3.14);

    lcd.setCursor(0, 1);
    lcd.print(-25.75);
}

void loop() {

}
