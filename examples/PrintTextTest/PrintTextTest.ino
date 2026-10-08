#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    lcd.begin();

    lcd.setCursor(0, 0);
    lcd.print("Hola mundo");

    lcd.setCursor(0, 1);
    lcd.print("ESP32 + LCD");
}

void loop() {

}
