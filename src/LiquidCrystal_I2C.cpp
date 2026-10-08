#include "LiquidCrystal_I2C.h"


// ============================================================
// Constructor
// ============================================================

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


// ============================================================
// Inicialización
// ============================================================

void LiquidCrystal_I2C::begin() {

    // Inicializa el bus I2C utilizando los pines
    // predeterminados de la instancia TwoWire.
    _wire->begin();

    initializeLCD();
}


void LiquidCrystal_I2C::begin(int sda, int scl) {

    // Inicializa el bus I2C utilizando los pines
    // SDA y SCL proporcionados por el usuario.
    _wire->begin(sda, scl);

    initializeLCD();
}


void LiquidCrystal_I2C::initializeLCD() {

    /*
     * Secuencia de inicialización del HD44780 en modo de 4 bits.
     *
     * Al encender, el controlador LCD puede encontrarse en
     * un estado desconocido. Por eso se utiliza una secuencia
     * específica de nibbles antes de establecer formalmente
     * el modo de 4 bits.
     */

    delay(50);

    // Primera señal de inicialización.
    writeNibble(0x03, false);
    delay(5);

    // Segunda señal de inicialización.
    writeNibble(0x03, false);
    delay(1);

    // Tercera señal de inicialización.
    writeNibble(0x03, false);
    delay(1);

    // Cambia finalmente al modo de 4 bits.
    writeNibble(0x02, false);
    delay(1);

    /*
     * Function Set:
     *
     * 4 bits
     * 2 líneas
     * Fuente de 5x8 puntos
     */
    writeCommand(0x28);

    // Display encendido, cursor oculto y sin parpadeo.
    writeCommand(0x0C);

    // Limpia el display.
    writeCommand(0x01);
    delay(2);

    // Incrementa automáticamente la posición del cursor
    // después de escribir un carácter.
    writeCommand(0x06);
}


// ============================================================
// Comunicación con el PCF8574
// ============================================================

void LiquidCrystal_I2C::writeByte(uint8_t value) {

    /*
     * Guardamos una copia del último estado enviado al
     * PCF8574. Esto permite modificar posteriormente
     * determinados bits sin perder el estado de los demás.
     */
    _portState = value;

    _wire->beginTransmission(_address);
    _wire->write(value);
    _wire->endTransmission();
}


void LiquidCrystal_I2C::writeNibble(uint8_t nibble, bool rs) {

    /*
     * Partimos del estado actual del PCF8574.
     *
     * Esto permite conservar bits que no pertenecen
     * directamente al nibble que estamos transmitiendo.
     */
    uint8_t value = _portState;


    // --------------------------------------------------------
    // D4-D7
    // --------------------------------------------------------

    /*
     * Conservamos P0-P3 y limpiamos P4-P7.
     *
     * P4-P7 corresponden a D4-D7 del LCD.
     */
    value &= 0x0F;

    // Coloca el nibble en P4-P7.
    value |= nibble << 4;


    // --------------------------------------------------------
    // RS
    // --------------------------------------------------------

    /*
     * RS = 0 → comando
     * RS = 1 → dato
     */
    if (rs) {
        value |= (1 << PIN_RS);
    } else {
        value &= ~(1 << PIN_RS);
    }


    // --------------------------------------------------------
    // R/W
    // --------------------------------------------------------

    /*
     * Actualmente la librería solamente realiza operaciones
     * de escritura, por lo que R/W permanece siempre en 0.
     */
    value &= ~(1 << PIN_RW);


    // --------------------------------------------------------
    // Backlight
    // --------------------------------------------------------

    /*
     * El estado del backlight se conserva independientemente
     * de la operación que estemos realizando sobre el LCD.
     */
    if (_backlight) {
        value |= (1 << PIN_BL);
    } else {
        value &= ~(1 << PIN_BL);
    }


    // --------------------------------------------------------
    // Pulso Enable
    // --------------------------------------------------------

    /*
     * El HD44780 captura el nibble cuando se produce el
     * pulso de Enable.
     *
     * Secuencia:
     *
     * EN = 1
     * EN = 0
     */
    writeByte(value | (1 << PIN_EN));
    writeByte(value);
}


void LiquidCrystal_I2C::sendByte(uint8_t value, bool rs) {

    /*
     * El HD44780 está configurado en modo de 4 bits,
     * por lo que cada byte debe dividirse en dos nibbles.
     *
     * Primero se transmite el nibble alto y después
     * el nibble bajo.
     */

    writeNibble(value >> 4, rs);
    writeNibble(value & 0x0F, rs);
}


// ============================================================
// Comunicación con el HD44780
// ============================================================

void LiquidCrystal_I2C::writeData(uint8_t value) {

    // RS = 1 indica que el byte corresponde a un dato.
    sendByte(value, true);
}


void LiquidCrystal_I2C::writeCommand(uint8_t value) {

    // RS = 0 indica que el byte corresponde a un comando.
    sendByte(value, false);
}


// ============================================================
// Escritura de datos
// ============================================================

void LiquidCrystal_I2C::write(uint8_t value) {

    // Envía directamente un byte como dato al LCD.
    writeData(value);
}

// Imprime una cadena de caracteres terminada en '\0'.
void LiquidCrystal_I2C::print(const char* text) {

    /*
     * Recorre la cadena carácter por carácter hasta encontrar
     * el terminador nulo '\0'.
     */
    while (*text != '\0') {

        write(*text);
        text++;
    }
}


// Imprime un número entero con signo.
void LiquidCrystal_I2C::print(int value) {

    String text = String(value);

    print(text.c_str());
}


// Imprime un número entero sin signo.
void LiquidCrystal_I2C::print(unsigned int value) {

    String text = String(value);

    print(text.c_str());
}


// Imprime un número entero largo con signo.
void LiquidCrystal_I2C::print(long value) {

    String text = String(value);

    print(text.c_str());
}


// Imprime un número entero largo sin signo.
void LiquidCrystal_I2C::print(unsigned long value) {

    String text = String(value);

    print(text.c_str());
}


// Imprime un número decimal de tipo float.
void LiquidCrystal_I2C::print(float value) {

    String text = String(value);

    print(text.c_str());
}


// Imprime un número decimal de tipo float con una cantidad
// específica de posiciones decimales.
void LiquidCrystal_I2C::print(float value, int decimals) {

    String text = String(value, decimals);

    print(text.c_str());
}


// Imprime un número decimal de tipo double.
void LiquidCrystal_I2C::print(double value) {

    String text = String(value);

    print(text.c_str());
}


// Imprime un número decimal de tipo double con una cantidad
// específica de posiciones decimales.
void LiquidCrystal_I2C::print(double value, int decimals) {

    String text = String(value, decimals);

    print(text.c_str());
}


// Imprime un número entero utilizando la base numérica especificada.
void LiquidCrystal_I2C::printBase(long value, int base) {

    /*
     * Permite representar un número utilizando una base
     * determinada.
     *
     * Ejemplos:
     *
     * printBase(255, DEC) → 255
     * printBase(255, HEX) → ff
     * printBase(255, OCT) → 377
     * printBase(255, BIN) → 11111111
     */
    String text = String(value, base);

    print(text.c_str());
}


// ============================================================
// Posicionamiento del cursor
// ============================================================

void LiquidCrystal_I2C::setCursor(uint8_t column, uint8_t row) {

    /*
     * Evita acceder a una posición que se encuentre fuera
     * de las dimensiones declaradas del LCD.
     */
    if (column >= _columns || row >= _rows) {
        return;
    }

    /*
     * Cada fila comienza en una dirección diferente de la
     * DDRAM del HD44780.
     */
    uint8_t address = getRowAddress(row) + column;

    /*
     * El bit 7 indica que se está estableciendo una dirección
     * de DDRAM.
     */
    writeCommand(0x80 | address);
}


uint8_t LiquidCrystal_I2C::getRowAddress(uint8_t row) {

    // --------------------------------------------------------
    // LCD de 1 o 2 filas
    // --------------------------------------------------------

    if (_rows <= 2) {

        switch (row) {

            case 0:
                return 0x00;

            case 1:
                return 0x40;
        }
    }


    // --------------------------------------------------------
    // LCD de 4 filas
    // --------------------------------------------------------

    if (_rows == 4) {


        // ----------------------------------------------------
        // LCD 16x4
        // ----------------------------------------------------

        if (_columns == 16) {

            switch (row) {

                case 0:
                    return 0x00;

                case 1:
                    return 0x40;

                case 2:
                    return 0x10;

                case 3:
                    return 0x50;
            }
        }


        // ----------------------------------------------------
        // LCD 20x4
        // ----------------------------------------------------

        if (_columns == 20) {

            switch (row) {

                case 0:
                    return 0x00;

                case 1:
                    return 0x40;

                case 2:
                    return 0x14;

                case 3:
                    return 0x54;
            }
        }
    }


    // Configuración no soportada.
    return 0x00;
}


// ============================================================
// Control básico del display
// ============================================================

void LiquidCrystal_I2C::clear() {

    /*
     * Borra todos los caracteres del display y devuelve
     * el cursor a la posición inicial.
     */
    writeCommand(0x01);

    // Clear Display necesita más tiempo que un comando normal.
    delay(2);
}


void LiquidCrystal_I2C::home() {

    /*
     * Devuelve el cursor a la posición inicial sin borrar
     * el contenido del display.
     */
    writeCommand(0x02);

    // Return Home también requiere un tiempo adicional.
    delay(2);
}


void LiquidCrystal_I2C::display() {

    // Enciende la representación de los caracteres.
    writeCommand(0x0C);
}


void LiquidCrystal_I2C::noDisplay() {

    // Apaga la representación de los caracteres.
    // El contenido de la DDRAM permanece intacto.
    writeCommand(0x08);
}


// ============================================================
// Control del cursor
// ============================================================

void LiquidCrystal_I2C::showCursor() {

    _cursorBlinking = false;
    _cursorVisible = true;

    /*
     * Display ON
     * Cursor ON
     * Blink OFF
     */
    writeCommand(0x0E);
}


void LiquidCrystal_I2C::hideCursor() {

    _cursorBlinking = false;
    _cursorVisible = false;

    /*
     * Display ON
     * Cursor OFF
     * Blink OFF
     */
    writeCommand(0x0C);
}


void LiquidCrystal_I2C::blinkCursor() {

    _cursorBlinking = true;
    _cursorVisible = true;

    /*
     * Comenzamos mostrando el cursor.
     */
    writeCommand(0x0E);

    /*
     * Guarda el instante en el que comenzó el ciclo
     * de parpadeo.
     */
    _lastCursorBlink = millis();
}


void LiquidCrystal_I2C::noBlinkCursor() {

    _cursorBlinking = false;
    _cursorVisible = true;

    /*
     * Dejamos el cursor visible y detenemos el parpadeo.
     */
    writeCommand(0x0E);
}


// ============================================================
// Parpadeo nativo de celda
// ============================================================

void LiquidCrystal_I2C::blinkCell() {

    /*
     * Activa el parpadeo nativo del HD44780.
     *
     * A diferencia de blinkCursor(), este comportamiento
     * pertenece directamente al controlador LCD.
     */
    writeCommand(0x0D);
}


void LiquidCrystal_I2C::noBlinkCell() {

    /*
     * Desactiva el parpadeo nativo de la celda.
     */
    writeCommand(0x0C);
}


// ============================================================
// Actualización del cursor
// ============================================================

void LiquidCrystal_I2C::update() {

    /*
     * El parpadeo personalizado del cursor no utiliza delay().
     *
     * Esto permite que el programa principal continúe ejecutando
     * otras tareas mientras el cursor cambia de estado.
     */
    if (!_cursorBlinking) {
        return;
    }

    unsigned long currentMillis = millis();

    /*
     * Utilizamos una resta entre unsigned long para que el
     * cálculo siga funcionando correctamente cuando millis()
     * se desborde.
     */
    if (currentMillis - _lastCursorBlink >= CURSOR_BLINK_INTERVAL) {

        _lastCursorBlink = currentMillis;

        _cursorVisible = !_cursorVisible;


        if (_cursorVisible) {

            // Cursor visible.
            writeCommand(0x0E);

        } else {

            // Cursor oculto.
            writeCommand(0x0C);
        }
    }
}


// ============================================================
// Control del backlight
// ============================================================

void LiquidCrystal_I2C::backlight() {

    _backlight = true;

    updateBacklight();
}


void LiquidCrystal_I2C::noBacklight() {

    _backlight = false;

    updateBacklight();
}


void LiquidCrystal_I2C::updateBacklight() {

    /*
     * El backlight está conectado al pin P3 del PCF8574.
     *
     * Modificamos únicamente ese bit para no alterar el
     * estado de los demás pines.
     */

    if (_backlight) {

        // P3 = 1 → backlight encendido.
        _portState |= (1 << PIN_BL);

    } else {

        // P3 = 0 → backlight apagado.
        _portState &= ~(1 << PIN_BL);
    }

    /*
     * Enviamos inmediatamente el nuevo estado al PCF8574.
     */
    writeByte(_portState);
}
