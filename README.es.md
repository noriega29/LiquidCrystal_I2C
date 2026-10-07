# LiquidCrystal_I2C

Una librería independiente para Arduino/ESP32 destinada a controlar pantallas LCD compatibles con HD44780 mediante un adaptador I²C basado en PCF8574.

> **Estado:** En desarrollo

## Acerca del proyecto

`LiquidCrystal_I2C` es una implementación independiente diseñada para proporcionar una interfaz sencilla y reutilizable para pantallas LCD de caracteres compatibles con HD44780 conectadas mediante un expansor de E/S I²C PCF8574.

El proyecto se desarrolla haciendo énfasis en:

* Comprender la comunicación entre el microcontrolador, el bus I²C, el PCF8574 y el HD44780.
* Mantener la implementación sencilla y fácil de comprender.
* Proporcionar una API familiar inspirada en las librerías de estilo `LiquidCrystal`.
* Admitir proyectos basados en Arduino y ESP32.
* Gestionar explícitamente la codificación de caracteres.
* Admitir caracteres personalizados mediante la CGRAM del HD44780.
* Mantener la librería independiente de cualquier aplicación o proyecto específico.

Esta librería se desarrolla desde el nivel del protocolo, en lugar de modificar o copiar una implementación existente de `LiquidCrystal_I2C`.

## Hardware

La librería está destinada a la siguiente arquitectura general:

```text
Microcontrolador
     │
     │ I²C
     ▼
  PCF8574
     │
     │ Interfaz paralela
     ▼
   HD44780
     │
     ▼
 Pantalla LCD
```

Los módulos típicos están compuestos por:

* Microcontrolador compatible con Arduino o ESP32
* Expansor de E/S I²C PCF8574
* Pantalla LCD de caracteres compatible con HD44780
* Conexión I²C entre el microcontrolador y el PCF8574

## Funcionalidades

La librería incorporará progresivamente:

* Inicialización de la pantalla LCD
* Limpieza de la pantalla
* Posicionamiento del cursor
* Escritura de texto
* Escritura de valores numéricos
* Control de la visibilidad del cursor
* Parpadeo del cursor
* Encendido y apagado de la pantalla
* Control de la retroiluminación
* Caracteres personalizados mediante CGRAM
* Gestión de caracteres adecuada para controladores compatibles con HD44780

La implementación se desarrolla deliberadamente de forma progresiva.

## Gestión de caracteres

Los controladores compatibles con HD44780 no utilizan UTF-8 como sistema de codificación de caracteres nativo.

Por ejemplo, el carácter:

```text
á
```

está representado por varios bytes en UTF-8, mientras que el HD44780 espera un código de carácter correspondiente al conjunto de caracteres almacenado en su ROM interna.

Un aspecto importante es que **las pantallas compatibles con HD44780 no necesariamente utilizan ROM de caracteres idénticas**. Diferentes controladores, fabricantes o variantes de ROM pueden proporcionar diferentes conjuntos de caracteres.

Por lo tanto, la librería no asumirá inicialmente que un determinado valor de byte representa universalmente caracteres como:

```text
á é í ó ú
Á É Í Ó Ú
ñ Ñ
ü Ü
¿ ¡
°
```

En su lugar, la gestión de caracteres será investigada y documentada de acuerdo con las capacidades del controlador utilizado.

La implementación inicial se centrará en proporcionar un acceso fiable a los caracteres disponibles en la ROM del controlador, evitando al mismo tiempo introducir una complejidad de Unicode innecesaria.

## Caracteres personalizados

Los controladores compatibles con HD44780 proporcionan CGRAM para almacenar patrones de caracteres personalizados.

CGRAM permite que la aplicación defina caracteres utilizando patrones de 5×8 píxeles.

La librería proporcionará una API para crear y mostrar estos caracteres personalizados.

Por ejemplo:

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

El carácter personalizado podrá mostrarse utilizando la posición de CGRAM que le haya sido asignada.

Los caracteres personalizados proporcionan una forma de representar símbolos que no están disponibles en la ROM de caracteres integrada del controlador LCD.

Debido a que CGRAM dispone de un número limitado de posiciones para caracteres personalizados, estos serán gestionados explícitamente por la aplicación.

## Ejemplo básico

Una vez implementada la API inicial, el uso de la librería está pensado para ser similar a:

```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    lcd.begin();

    lcd.backlight();

    lcd.setCursor(0, 0);
    lcd.print("Hola mundo");
}

void loop() {
}
```

La API y el procedimiento de inicialización pueden cambiar durante el desarrollo a medida que la implementación evolucione.

## Estructura del proyecto

La librería sigue la estructura estándar de una librería de Arduino:

```text
LiquidCrystal_I2C/
├── LICENSE
├── README.md
├── README.es.md
├── library.properties
└── src/
    ├── LiquidCrystal_I2C.h
    └── LiquidCrystal_I2C.cpp
```

Los ejemplos se añadirán a medida que avance el desarrollo de la librería.

## Filosofía de desarrollo

Este proyecto prioriza la comprensión sobre la abstracción.

Antes de implementar una funcionalidad, primero debe comprenderse la parte correspondiente del protocolo de comunicación.

La cadena de comunicación prevista es:

```text
Arduino / ESP32
       │
       │ I²C
       ▼
    PCF8574
       │
       │ Estados GPIO
       ▼
    HD44780
       │
       ├── Comandos
       ├── DDRAM
       └── CGRAM
```

Por lo tanto, la implementación se desarrollará progresivamente, comenzando por la comunicación de bajo nivel y construyendo la API de más alto nivel sobre ella.

Durante el desarrollo podrán utilizarse pequeños programas experimentales para verificar individualmente las diferentes partes del proceso de comunicación antes de incorporarlas a la librería.

## Compatibilidad

El objetivo inicial de desarrollo es el ESP32 utilizando el framework de Arduino.

La librería está diseñada para mantener la compatibilidad con otras plataformas compatibles con Arduino que proporcionen la funcionalidad I²C necesaria mediante `Wire`.

La compatibilidad con controladores LCD específicos y diferentes configuraciones de adaptadores basados en PCF8574 será probada y documentada a medida que avance el desarrollo.

## Licencia

Este proyecto está bajo la licencia MIT.

Consulta el archivo [LICENSE](LICENSE) para ver el texto completo de la licencia.

## Autor

**Mateo Noriega Güete**

Copyright © 2026 Mateo Noriega Güete
