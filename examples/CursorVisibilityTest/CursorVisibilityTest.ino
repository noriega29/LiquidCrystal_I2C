#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    lcd.begin();

    lcd.write('A');

    lcd.showCursor();

    delay(5000);

    lcd.hideCursor();

    delay(5000);

    lcd.showCursor();
}

void loop() {

}
