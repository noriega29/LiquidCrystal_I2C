#include "LiquidCrystal_I2C.h"

LiquidCrystal_I2C::LiquidCrystal_I2C(
    uint8_t address,
    uint8_t columns,
    uint8_t rows,
    TwoWire* wire
) {
    _address = address;
    _columns = columns;
    _rows = rows;
    _wire = wire;
}

void LiquidCrystal_I2C::begin() {
    _wire->begin();

    delay(50);

    writeNibble(0x03, false);
    delay(5);

    writeNibble(0x03, false);
    delay(1);

    writeNibble(0x03, false);
    delay(1);

    writeNibble(0x02, false);
    delay(1);

    writeCommand(0x28);
    writeCommand(0x0C);

    writeCommand(0x01);
    delay(2);

    writeCommand(0x06);
}

void LiquidCrystal_I2C::begin(int sda, int scl) {
    _wire->begin(sda, scl);

    delay(50);

    writeNibble(0x03, false);
    delay(5);

    writeNibble(0x03, false);
    delay(1);

    writeNibble(0x03, false);
    delay(1);

    writeNibble(0x02, false);
    delay(1);

    writeCommand(0x28);
    writeCommand(0x0C);

    writeCommand(0x01);
    delay(2);

    writeCommand(0x06);
}

void LiquidCrystal_I2C::writeByte(uint8_t value) {
    _wire->beginTransmission(_address);
    _wire->write(value);
    _wire->endTransmission();
}

void LiquidCrystal_I2C::writeNibble(uint8_t nibble, bool rs) {
    uint8_t value = nibble << 4;

    if (rs) {
        value |= (1 << PIN_RS);
    }

    value &= ~(1 << PIN_RW);

    value |= (1 << PIN_BL);

    writeByte(value | (1 << PIN_EN));
    writeByte(value);
}

void LiquidCrystal_I2C::sendByte(uint8_t value, bool rs) {
    writeNibble(value >> 4, rs);
    writeNibble(value & 0x0F, rs);
}

void LiquidCrystal_I2C::writeData(uint8_t value) {
    sendByte(value, true);
}

void LiquidCrystal_I2C::writeCommand(uint8_t value) {
    sendByte(value, false);
}

void LiquidCrystal_I2C::write(uint8_t value) {
    writeData(value);
}
