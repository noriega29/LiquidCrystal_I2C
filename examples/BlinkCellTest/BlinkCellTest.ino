#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    lcd.begin();

    lcd.write('A');

    delay(5000);

    lcd.blinkCell();

    delay(5000);

    lcd.noBlinkCell();

    delay(5000);

    lcd.blinkCell();
}

void loop() {

}
