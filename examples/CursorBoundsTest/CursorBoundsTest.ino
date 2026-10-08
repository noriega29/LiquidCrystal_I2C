#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    lcd.begin();

    // Posición válida: última columna de la primera fila
    lcd.setCursor(15, 0);
    lcd.write('A');

    // Posición válida: última columna de la segunda fila
    lcd.setCursor(15, 1);
    lcd.write('B');
    
    // Posición inválida: columna 16
    lcd.setCursor(16, 0);
    lcd.write('X');

    // Posición inválida: fila 2
    lcd.setCursor(0, 2);
    lcd.write('Y');
}

void loop() {

}
