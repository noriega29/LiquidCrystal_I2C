# LiquidCrystal_I2C

An independent Arduino/ESP32 library for controlling HD44780-compatible LCD displays through a PCF8574-based I²C adapter.

> **Status:** Work in progress

## About

`LiquidCrystal_I2C` is an independent implementation designed to provide a simple and reusable interface for HD44780-compatible character LCD displays connected through a PCF8574 I²C I/O expander.

The project is being developed with an emphasis on:

* Understanding the communication between the microcontroller, I²C bus, PCF8574, and HD44780.
* Keeping the implementation simple and easy to understand.
* Providing a familiar API inspired by common `LiquidCrystal`-style libraries.
* Supporting Arduino and ESP32 projects.
* Handling character encoding explicitly.
* Supporting custom characters through the HD44780 CGRAM.
* Keeping the library independent from any specific application or project.

This library is being developed from the protocol level rather than by modifying or copying an existing `LiquidCrystal_I2C` implementation.

## Hardware

The library is intended for the following general architecture:

```text
Microcontroller
     │
     │ I²C
     ▼
  PCF8574
     │
     │ Parallel interface
     ▼
   HD44780
     │
     ▼
 LCD Display
```

Typical modules consist of:

* Arduino-compatible microcontroller or ESP32
* PCF8574 I²C I/O expander
* HD44780-compatible character LCD
* I²C connections between the microcontroller and PCF8574

## Features

The library will progressively support:

* LCD initialization
* Display clearing
* Cursor positioning
* Text output
* Numeric output
* Cursor visibility control
* Cursor blinking
* Display on/off control
* Backlight control
* Custom characters using CGRAM
* Character handling appropriate for HD44780-compatible controllers

The implementation is intentionally being developed incrementally.

## Character Handling

HD44780-compatible controllers do not use UTF-8 as their native character encoding.

For example, the character:

```text
á
```

is represented by multiple bytes in UTF-8, while the HD44780 expects a character code corresponding to the character set stored in its internal character ROM.

An important consideration is that **HD44780-compatible displays do not necessarily use identical character ROMs**. Different controllers, manufacturers, or ROM variants may provide different character sets.

Therefore, the library will not initially assume that a particular byte value universally represents characters such as:

```text
á é í ó ú
Á É Í Ó Ú
ñ Ñ
ü Ü
¿ ¡
°
```

Instead, character handling will be investigated and documented based on the capabilities of the target controller.

The initial implementation will focus on providing reliable access to the characters available in the controller's character ROM, while avoiding unnecessary Unicode complexity.

## Custom Characters

HD44780-compatible controllers provide CGRAM for storing custom character patterns.

CGRAM allows the application to define characters using 5×8 pixel patterns.

The library will expose an API for creating and displaying these custom characters.

For example:

```cpp
uint8_t customChar[8] = {
    0b00100,
    0b01010,
    0b00100,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000
};

lcd.createChar(0, customChar);
```

The custom character can then be displayed using its assigned CGRAM slot.

Custom characters provide a way to represent symbols that are not available in the LCD controller's built-in character ROM.

Because CGRAM has a limited number of available character slots, custom characters will be managed explicitly by the application.

## Basic Example

Once the initial API is implemented, usage is intended to be similar to:

```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    lcd.begin();

    lcd.backlight();

    lcd.setCursor(0, 0);
    lcd.print("Hello world");
}

void loop() {
}
```

The API and initialization procedure may change during development as the implementation evolves.

## Project Structure

The library follows the standard Arduino library structure:

```text
LiquidCrystal_I2C/
├── LICENSE
├── README.md
├── library.properties
└── src/
    ├── LiquidCrystal_I2C.h
    └── LiquidCrystal_I2C.cpp
```

Examples will be added as the library develops.

## Development Philosophy

This project prioritizes understanding over abstraction.

Before implementing a feature, the relevant part of the communication protocol should be understood first.

The intended communication chain is:

```text
Arduino / ESP32
       │
       │ I²C
       ▼
    PCF8574
       │
       │ GPIO states
       ▼
    HD44780
       │
       ├── Commands
       ├── DDRAM
       └── CGRAM
```

The implementation will therefore be developed progressively, beginning with low-level communication and building the higher-level API on top of it.

Small experimental programs may be used during development to verify individual parts of the communication process before incorporating them into the library.

## Compatibility

The initial development target is the ESP32 using the Arduino framework.

The library is intended to remain compatible with other Arduino-compatible platforms where the required I²C functionality is provided by `Wire`.

Compatibility with specific LCD controllers and PCF8574-based adapter configurations will be tested and documented as development progresses.

## License

This project is licensed under the MIT License.

See the [LICENSE](LICENSE) file for the complete license text.

## Author

**Mateo Noriega Güete**

Copyright © 2026 Mateo Noriega Güete
