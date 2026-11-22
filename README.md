# Laboratory Activity 8: Wired Communication (UART, I²C, and SPI)

Verification of the three wired serial communication interfaces on the **DOIT ESP32 DEVKIT V1 (WROOM-32)**: **UART (`Serial2`)**, **I²C (`Wire`)**, and **SPI (`HSPI`)**.

---

## 1. Pin Assignment Table

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
```

* **UART Loopback:** Jumper wire connecting **GPIO 17 (TX)** to **GPIO 16 (RX)**.
* **I²C Bus:** I²C module connected to **GPIO 21 (SDA)**, **GPIO 22 (SCL)**, **3V3**, and **GND**.
* **SPI Loopback:** Jumper wire connecting **GPIO 13 (MOSI)** to **GPIO 26 (MISO)**; **GPIO 14 (SCK)** and **GPIO 4 (CS)** are configured on the SPI bus.

---

## 3. Serial Monitor Output

### UART Loopback (`uart_loopback.ino`)
* **With jumper (115200 baud):**
  ```text
  UART Loopback Test Started
  PING
  PING
  PING
  PING
  ```
* **Without jumper (115200 baud):**
  ```text
  UART Loopback Test Started
  ```
* **Sketch at 9600 baud, Serial Monitor at 115200 baud:**
  ```text
  ⸮⸮x⸮⸮~⸮⸮⸮`⸮⸮x⸮⸮⸮~⸮
  ```
* **Sketch at 9600 baud, Serial Monitor at 9600 baud:**
  ```text
  UART Loopback Test Started
  PING
  PING
  PING
  ```

### I²C Scanner (`i2c_scanner.ino`)
* **With I²C module connected (115200 baud):**
  ```text
  I2C Scanner Started
  Found device at 0x3C
  ```
* **Without I²C module connected (115200 baud):**
  ```text
  I2C Scanner Started
  No I2C devices found
  ```

### SPI Loopback (`spi_loopback.ino`)
* **With jumper (`GPIO 13 -> GPIO 26`, 115200 baud):**
  ```text
  SPI Loopback Test Started
  Sent 0xA5, received 0xA5
  Sent 0xA5, received 0xA5
  Sent 0xA5, received 0xA5
  ```
* **Without jumper (115200 baud):**
  ```text
  SPI Loopback Test Started
  Sent 0xA5, received 0x00
  Sent 0xA5, received 0x00
  Sent 0xA5, received 0x00
  ```

---

## 4. Expected vs. Observed Table

| Test | Expected | Observed |
| :--- | :--- | :--- |
| **UART with jumper** | Prints `PING` every 1 second | Prints `PING` every 1 second |
| **UART without jumper** | Nothing prints after startup | Nothing prints after startup |
| **I²C with module** | `Found device at 0x3C` | `Found device at 0x3C` |
| **I²C without module** | `No I2C devices found` | `No I2C devices found` |
| **SPI with jumper** | `Sent 0xA5, received 0xA5` | `Sent 0xA5, received 0xA5` |
| **SPI without jumper** | `Sent 0xA5, received 0x00` (or `0xFF`) | `Sent 0xA5, received 0x00` |
| **Sketch at 9600, monitor at 115200** | Garbled characters | Garbled characters (`⸮⸮x⸮⸮~⸮`) |
| **Sketch at 9600, monitor at 9600** | Clear `PING` | Clear `PING` |

---

## 5. Questions

1. **Why does UART need both sides to use the same baud rate, while SPI uses a clock line?**  
   UART has no shared clock line, so both sides must use the exact same bit timing (baud rate) to stay synchronized when sampling incoming bits. SPI uses a controller-driven clock line (`SCK`) that tells the peripheral the exact instant to sample each bit.

2. **Why can two devices with the same address not share one I²C bus?**  
   If two peripherals share the same address, both will acknowledge and attempt to drive the shared `SDA` line at the same time during a transfer, causing bus contention and corrupted data.

3. **Why is CS set HIGH between SPI transfers?**  
   Setting Chip Select (`CS`) HIGH deselects the peripheral so it releases `MISO` into a high-impedance state (preventing bus conflicts with other peripherals) and frames the end of the transaction so its internal shift register resets for the next transfer.
