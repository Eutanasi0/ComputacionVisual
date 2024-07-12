# Proyecto de Escáner 3D Casero con ESP32

Este proyecto consiste en un escáner 3D casero utilizando un ESP32, un sensor óptico y motores paso a paso. Los datos de escaneo se guardan en un archivo TXT.

## Tabla de Contenidos
1. [Descripción del Proyecto](#descripción-del-proyecto)
2. [Componentes](#componentes)
3. [Circuito](#circuito)
4. [Instalación y Configuración](#instalación-y-configuración)
5. [Uso](#uso)
6. [Código Fuente](#código-fuente)
7. [Script de Python](#script-de-python)
8. [Licencia](#licencia)

## Descripción del Proyecto

El escáner 3D casero se basa en un ESP32 que controla un sensor óptico y motores paso a paso para capturar las coordenadas XYZ de un objeto. Las coordenadas se guardan en un archivo TXT para su posterior procesamiento y visualización.

## Componentes

- ESP32
- Sensor óptico SHARP GP2Y0A51SK0F
- Motores paso a paso nema 17
- Driver de motores paso a paso
- Botón
- Resistencias (por ejemplo, 10kΩ)
- Fuente de alimentación
- Protoboard y cables
- Plataforma 

## Circuito

El circuito se conecta de la siguiente manera:

- Sensor óptico al pin GPIO 27 del ESP32
- Botón al pin GPIO 14 del ESP32
- Motores paso a paso y drivers conectados a los pines del ESP32 especificados en el código

## Instalación y Configuración

1. **Configurar el entorno de desarrollo**:
    - Instala el [Arduino IDE](https://www.arduino.cc/en/software).
    - Añade la placa ESP32 al Arduino IDE siguiendo [estas instrucciones](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html).

2. **Instalar las bibliotecas necesarias**:
    - Asegúrate de tener instaladas las bibliotecas `SPI.h`.

3. **Cargar el código al ESP32**:
    - Abre el archivo `.ino` en el Arduino IDE.
    - Configura el puerto y la placa ESP32 en el menú de herramientas.
    - Sube el código al ESP32.

## Uso

1. **Preparar el escáner**:
    - Coloca el objeto a escanear en el centro de la plataforma giratoria.
    - Asegúrate de que todos los componentes estén conectados correctamente.
    - Iniciar el scriptDatos.py

2. **Iniciar el escaneo**:
    - Presiona el botón conectado al ESP32 para comenzar el escaneo.
    - El ESP32 controlará los motores paso a paso y el sensor óptico para capturar las coordenadas XYZ del objeto.

3. **Guardar los datos**:
    - Las coordenadas XYZ se guardarán en un archivo TXT en la ruta especificada que especifiques (`colocar_ruta`).

4. **Visualización de la nube de puntos**:
    - Descargar e instalar meshlab para poder importar la nube de puntos
    - Elgir Point format "x y z" y separator ",".