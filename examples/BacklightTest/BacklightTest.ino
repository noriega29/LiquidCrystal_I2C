#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {

    lcd.begin();

    lcd.print("Hola mundo!");

    delay(2000);

    lcd.noBacklight();

    lcd.setCursor(0, 1);
    lcd.print("Backlight OFF");

    delay(2000);

    lcd.backlight();

    lcd.setCursor(0, 1);
    lcd.print("Backlight ON ");

    delay(2000);

    lcd.noBacklight();

    lcd.setCursor(0, 1);
    lcd.print("Backlight OFF");

    delay(2000);

    lcd.backlight();

    lcd.setCursor(0, 1);
    lcd.print("Backlight ON ");
}

void loop() {

}
