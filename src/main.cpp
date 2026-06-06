#include <Arduino.h>
#include <Wire.h>
#include <chrono>


// I2C Settings
const uint8_t I2C_SDA = 8;
const uint8_t I2C_SCL = 9;
const uint32_t I2C_FREQUENCY = 100000;

const uint8_t I2C_ADDRESS_START = 0x00;
const uint8_t I2C_ADDRESS_END = 0x7F;

// Scan-Interval [ms]
const auto SCAN_INTERVAL = std::chrono::seconds(5);

// Timestamp of last scan
auto timeLastScan = std::chrono::steady_clock::now();

void setup()
{
	Serial.begin(115200);
	delay(1000);

	log_i("Starting I2C Scanner...");

	// Initialize I2C
	Wire.begin(I2C_SDA, I2C_SCL, I2C_FREQUENCY);

	log_i("I2C initialized on SDA=%d, SCL=%d", I2C_SDA, I2C_SCL);
}

void scanI2C()
{
	log_i("=== Starting I2C Address Scan ===");

	int deviceCount = 0;

	// Search for connected devices in specified range
	for (uint8_t address = I2C_ADDRESS_START; address <= I2C_ADDRESS_END; ++address)
	{
		Wire.beginTransmission(address);
		const uint8_t error = Wire.endTransmission();

		switch (error)
		{
		case 0:
			// Device found
			log_i("I2C Address: 0x%02X -> Found Device! HEX: 0x%02X | DEC: %d", address, address, address);
			++deviceCount;
			break;
		case 1:
			// Transmit buffer too small
			log_w("I2C Address: 0x%02X -> Transmit Buffer too small!", address);
			break;
		case 2:
			// Received NACK on Address transmission
			log_d("I2C Address: 0x%02X -> Received NACK on Address Transmission", address);
			break;
		case 3:
			// Received NACK on data transmission
			log_w("I2C Address: 0x%02X -> Received NACK on Data Transmission!", address);
			break;
		case 4:
			// Other error
			log_w("I2C Address: 0x%02X -> Other Error!", address);
			break;
		case 5:
			// Timeout
			log_d("I2C Address: 0x%02X -> Timeout!", address);
			break;

		default:
			// Unknown error
			log_e("I2C Address: 0x%02X -> Unknown Error!", address);
			break;
		}
	}

	log_i("=== Scan Complete: %d device(s) found ===", deviceCount);
}

void loop()
{
	const auto timeNow = std::chrono::steady_clock::now();
	const auto timeDiff = (timeNow - timeLastScan);

	// Perform scan in set interval
	if (timeDiff >= SCAN_INTERVAL)
	{
		scanI2C();
		timeLastScan = timeNow;
	}

	delay(100);
}
