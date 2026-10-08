#ifndef LIQUIDCRYSTAL_I2C_H
#define LIQUIDCRYSTAL_I2C_H

#include <Arduino.h>
#include <Wire.h>

class LiquidCrystal_I2C {

    private:

        // Configuración del LCD
        uint8_t _address;
        uint8_t _columns;
        uint8_t _rows;

        // Bus I2C
        TwoWire* _wire;

        // Estado del PCF8574
        uint8_t _portState = 0;
        bool _backlight = true;

        // Pines del PCF8574
        static constexpr uint8_t PIN_RS = 0;
        static constexpr uint8_t PIN_RW = 1;
        static constexpr uint8_t PIN_EN = 2;
        static constexpr uint8_t PIN_BL = 3;

        static constexpr uint8_t PIN_D4 = 4;
        static constexpr uint8_t PIN_D5 = 5;
        static constexpr uint8_t PIN_D6 = 6;
        static constexpr uint8_t PIN_D7 = 7;

        // Comunicación con el PCF8574
        void writeByte(uint8_t value);
        void writeNibble(uint8_t nibble, bool rs);
        void sendByte(uint8_t value, bool rs);

        // Comunicación con el HD44780
        void writeData(uint8_t value);
        void writeCommand(uint8_t value);
        void initializeLCD();

        // Funciones auxiliares
        void updateBacklight();
        uint8_t getRowAddress(uint8_t row);

        // Estado del cursor
        bool _cursorBlinking = false;
        bool _cursorVisible = false;

        unsigned long _lastCursorBlink = 0;

        static constexpr unsigned long CURSOR_BLINK_INTERVAL = 650;

    public:

        // Constructor
        LiquidCrystal_I2C(
            uint8_t address,
            uint8_t columns,
            uint8_t rows,
            TwoWire* wire = &Wire
        );

        // Inicialización
        void begin();
        void begin(int sda, int scl);

        // Escritura
        void write(uint8_t value);

        void print(const char* text);

        void print(int value);
        void print(unsigned int value);
        void print(long value);
        void print(unsigned long value);

        void print(float value);
        void print(float value, int decimals);
        void print(double value);
        void print(double value, int decimals);

        void printBase(long value, int base);

        // Posicionamiento
        void setCursor(uint8_t column, uint8_t row);

        // Control del display
        void clear();
        void home();
        void display();
        void noDisplay();

        // Control del cursor
        void showCursor();
        void hideCursor();
        void blinkCursor();
        void noBlinkCursor();

        // Parpadeo de celda
        void blinkCell();
        void noBlinkCell();

        // Backlight
        void backlight();
        void noBacklight();

        // Actualización
        void update();
};

#endif
