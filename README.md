# Laboratory Activity 8: Wired Communication (UART, I²C, and SPI)

Verification of the three wired serial communication interfaces on the **DOIT ESP32 DEVKIT V1 (WROOM-32)**: **UART (`Serial2`)**, **I²C (`Wire`)**, and **SPI (`HSPI`)**.

---

## 1. Pin Assignment Table

Safe, non-strapping GPIOs selected on the WROOM-32 module (avoiding flash pins GPIO 6–11, strapping pins GPIO 0, 2, 5, 12, 15, and input-only pins GPIO 34–39):

| Signal | GPIO used |
| :--- | :--- |
| **UART TX** | GPIO 17 |
| **UART RX** | GPIO 16 |
| **I²C SDA** | GPIO 21 |
| **I²C SCL** | GPIO 22 |
| **SPI SCK** | GPIO 14 |
| **SPI MOSI** | GPIO 13 |
| **SPI MISO** | GPIO 26 |
| **SPI CS** | GPIO 4 |

---

## 2. Wiring Diagram

```text
               +-----------------------------------+
               |     DOIT ESP32 DEVKIT V1          |
               |           (WROOM-32)              |
               |                                   |
  +----------->| GPIO 17 (UART2 TX)                |
  | (Jumper)   |                                   |
  +----------->| GPIO 16 (UART2 RX)                |
               |                                   |
               | GPIO 21 (I2C SDA)  <--------------+------+
               | GPIO 22 (I2C SCL)  <--------------+----+ |
               | 3V3                ---------------+--+ | |
               | GND                ---------------+--+ | |
               |                                   |  | | |
  +----------->| GPIO 13 (SPI MOSI)                |  | | |
  | (Jumper)   |                                   |  | | |
  +----------->| GPIO 26 (SPI MISO)                |  | | |
               | GPIO 14 (SPI SCK)                 |  | | |
               | GPIO 4  (SPI CS)                  |  | | |
               +-----------------------------------+  | | |
                                                      | | |
                                   +------------------+ | |
                                   |    +---------------+ |
                                   |    |    +------------+
                                   v    v    v
                                 +-------------+
                                 | VCC GND SCL SDA
                                 | I2C Module  |
                                 | (OLED/BMP280)|
                                 +-------------+
