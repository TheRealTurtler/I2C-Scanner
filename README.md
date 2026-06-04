# I2C Scanner

A simple I2C bus scanner for Arduino-compatible microcontrollers that automatically detects and logs all connected I2C devices.

## Features

- Automatic I2C device detection on configurable SDA/SCL pins
- Periodic scanning at 5-second intervals
- Serial logging of all detected devices with their addresses (hex and decimal)
- Error handling and reporting
- Real-time serial monitor output

## Hardware

- Any Arduino-compatible microcontroller (Arduino, ESP32, ESP8266, STM32, etc.)
- I2C devices to scan
- USB connection for serial monitoring

## Setup & Build

1. Ensure [PlatformIO](https://platformio.org/) is installed
2. Update `platformio.ini` with your board type (e.g., `board = arduino_uno`, `board = esp32`, etc.)
3. Adjust I2C pins in `src/main.cpp` if needed for your board
4. Build and upload:
   ```bash
   platformio run --target upload
   ```
5. Open the serial monitor to view scan results:
   ```bash
   platformio device monitor
   ```

## Configuration

Edit `src/main.cpp` to customize:

| Setting         | Default   | Purpose            |
| --------------- | --------- | ------------------ |
| `I2C_SDA`       | 8         | SDA pin number     |
| `I2C_SCL`       | 9         | SCL pin number     |
| `I2C_FREQUENCY` | 100000 Hz | I2C bus speed      |
| `SCAN_INTERVAL` | 5 seconds | Time between scans |

## How It Works

The scanner continuously monitors the I2C bus:
1. Sends transmission requests to addresses `0x00` to `0x7F`
2. Logs any device that responds (error code = 0)
3. Reports scan results every 5 seconds
4. All output goes to the serial console at 115200 baud
