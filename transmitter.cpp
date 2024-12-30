#define START_BYTE 0x7E

void setup() {
    Serial.begin(115200); // For debugging
    Serial.begin(2000000); // Higher baud rate for communication with ESP32
}

uint16_t calculateChecksum(const uint8_t *data, size_t length) { // Accepting const pointer
    uint16_t checksum = 0;
    for (size_t i = 0; i < length; i++) {
        checksum += data[i];
    }
    return checksum;
}

void sendPacket(const uint8_t *payload, size_t length) {
    // Header
    Serial.write(START_BYTE);          // Start byte
    Serial.write((uint8_t)(length >> 8)); // Length high byte
    Serial.write((uint8_t)(length & 0xFF)); // Length low byte

    // Payload
    Serial.write(payload, length);

    // Checksum
    uint16_t checksum = calculateChecksum(payload, length);
    Serial.write((uint8_t)(checksum >> 8)); // Checksum high byte
    Serial.write((uint8_t)(checksum & 0xFF)); // Checksum low byte
}

void loop() {
    uint8_t data[] = "Hello from Arduino with a larger packet!";
    sendPacket(data, sizeof(data) - 1);
    delay(1000); // Send every second
}