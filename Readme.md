# Custom Communication protocol
---
This project demonstrates how an **Arduino** (acting as the transmitter) sends data packets to an **ESP32** (acting as the receiver) over serial communication. The baud rate is set higher to allow the transmission of large blobs of data in a single transfer. The ESP32 verifies the packet integrity using a checksum and then outputs the received data.

## Features
- **High-Speed Serial Communication**: The data is transmitted at a higher baud rate (`2,000,000` baud) to handle large data packets in one transfer.
- **Data Integrity Check**: The ESP32 performs a checksum validation to ensure the received data is accurate.
- **Custom Data Packet Format**: Data packets include a start byte, length, payload, and checksum.
- **Arduino as Transmitter**: The Arduino sends the data, and the ESP32 receives and processes it.

## Hardware Requirements
- **Arduino Board** (e.g., Arduino Uno, Mega, etc.)
- **ESP32 Board**
- **Wires for connection**:
  - Arduino TX → ESP32 RX (GPIO 16)
  - Arduino RX → ESP32 TX (GPIO 17)

## Pin Configuration
- **Arduino TX Pin** → **ESP32 RX Pin**: GPIO 16
- **Arduino RX Pin** → **ESP32 TX Pin**: GPIO 17

### Serial Communication Setup on ESP32:
The serial communication on the ESP32 is set to `2000000` baud, enabling the high-speed transfer of large data packets.

### Data Packet Format
| Start Byte (1 byte)  | Length (2 bytes) | Payload (n bytes) | Checksum (2 bytes) |
|----------------------|------------------|-------------------|---------------------|



## Example Packet

Consider a packet with a payload containing the string `"Hello"` and a checksum that is the sum of the ASCII values of the string characters.

### Data Breakdown:

| **Field**        | **Value**            | **Description**                          |
|------------------|----------------------|------------------------------------------|
| **Start Byte**   | `0x7E`               | Marks the beginning of the packet        |
| **Length**       | `0x00 0x05`          | 5 bytes of payload (length in two bytes) |
| **Payload**      | `0x48 0x65 0x6C 0x6C 0x6F` | ASCII values of `"Hello"`                 |
| **Checksum**     | `0x02 0xE5`          | Checksum calculated from payload (0x02E5)The sum of the ASCII values: `72 + 101 + 108 + 108 + 111 = 500(0x02E5)|

### Complete Packet in Hex:
| **Byte Position** | **Value (Hex)** |
|-------------------|-----------------|
| 1                 | `0x7E`          |
| 2                 | `0x00`          |
| 3                 | `0x05`          |
| 4                 | `0x48`          |
| 5                 | `0x65`          |
| 6                 | `0x6C`          |
| 7                 | `0x6C`          |
| 8                 | `0x6F`          |
| 9                 | `0x02`          |
| 10                | `0xE5`          |



