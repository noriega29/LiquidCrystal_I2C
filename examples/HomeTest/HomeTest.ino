#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    lcd.begin();

    lcd.setCursor(5, 1);
    lcd.write('A');

    delay(2000);

    lcd.home();
    lcd.write('B');
}

void loop() {

}
