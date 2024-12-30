#include <Arduino.h>

// put function declarations here:
#define START_BYTE 0x7E
#define MAX_PACKET_SIZE 128 // Define a maximum buffer size for the payload

void setup() {
    Serial.begin(115200); // Debugging
    Serial2.begin(2000000, SERIAL_8N1, 16, 17); // RX=16, TX=17
}

uint16_t calculateChecksum(const uint8_t *data, size_t length) {
    uint16_t checksum = 0;
    for (size_t i = 0; i < length; i++) {
        checksum += data[i];
    }
    return checksum;
}

void loop() {
    if (Serial2.available() >= 4) { // Minimum packet size (header + checksum)
        // Wait for start byte
        if (Serial2.read() != START_BYTE) return;

        // Read length (high byte + low byte)
        uint16_t length = (Serial2.read() << 8) | Serial2.read();

        // Ensure the packet doesn't exceed the maximum allowed size
        if (length > MAX_PACKET_SIZE) {
            Serial.println("Packet too large!");
            return;
        }

        // Read payload
        uint8_t payload[MAX_PACKET_SIZE]; // Fixed-size buffer
        for (uint16_t i = 0; i < length; i++) {
            if (Serial2.available()) {
                payload[i] = Serial2.read();
            }
        }

        // Read checksum (high byte + low byte)
        uint16_t receivedChecksum = (Serial2.read() << 8) | Serial2.read();
        uint16_t calculatedChecksum = calculateChecksum(payload, length);

        if (receivedChecksum == calculatedChecksum) {
            Serial.println("Packet received successfully:");
            Serial.write(payload, length);
            Serial.println();
        } else {
            Serial.println("Checksum error!");
        }
    }
}
