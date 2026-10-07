#ifndef LIQUIDCRYSTAL_I2C_H
#define LIQUIDCRYSTAL_I2C_H

#include <Arduino.h>
#include <Wire.h>

class LiquidCrystal_I2C {

    private:
        uint8_t _address;
        uint8_t _columns;
        uint8_t _rows;

        TwoWire* _wire;

        static constexpr uint8_t PIN_RS = 0;
        static constexpr uint8_t PIN_RW = 1;
        static constexpr uint8_t PIN_EN = 2;
        static constexpr uint8_t PIN_BL = 3;

        static constexpr uint8_t PIN_D4 = 4;
        static constexpr uint8_t PIN_D5 = 5;
        static constexpr uint8_t PIN_D6 = 6;
        static constexpr uint8_t PIN_D7 = 7;

        void writeByte(uint8_t value);
        void writeNibble(uint8_t nibble, bool rs);
        void sendByte(uint8_t value, bool rs);
        void writeData(uint8_t value);
        void writeCommand(uint8_t value);

    public:
        LiquidCrystal_I2C(
            uint8_t address,
            uint8_t columns,
            uint8_t rows,
            TwoWire* wire = &Wire
        );

        void begin();
        void begin(int sda, int scl);

        void write(uint8_t value);
};

#endif
