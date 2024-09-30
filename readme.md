# ESP32 Project: REST API Data Transmission with DHT11 Sensor

## Introduction

This project demonstrates how to use an ESP32 to collect sensor data from a DHT11 sensor and transmit it to a local server using HTTP REST API (POST Method). The project consists of:

1. An `.ino` file to collect temperature and humidity data from the DHT11 sensor and send it to a local server.
2. A `.py` file to receive data via REST API and return an appropriate response.
3. A physical setup of an ESP32 module with the DHT11 sensor.

## Project Overview

The main objective of this project is to establish a simple IoT system where temperature and humidity data from the DHT11 sensor connected to an ESP32 is transmitted to a local server using REST API. The system includes:

- **ESP32 Setup:** Collects data from the DHT11 sensor and sends it to a local server via HTTP POST.
- **REST API:** A Python server that receives the sensor data and processes it.

### Key Components:
- ESP32 Kit
- DHT11 Sensor
- Local server running Python Flask to handle REST API requests

## Project Files

1. `sic_ta1.ino`: Arduino code that collects temperature and humidity data from the DHT11 sensor and sends it to the local server.
2. `app.py`: Python code that runs the local server to receive sensor data from the ESP32.
3. **Photos:** Physical setup of the ESP32 with the DHT11 sensor.

## Setup Instructions

### Prerequisites

- ESP32 Kit
- DHT11 Sensor
- Arduino IDE
- Python 3.x
- VSCode or any other code editor
- Required Python libraries (Flask, etc.)

### Steps to Run

1. **Run the Python server:**
   - Open `app.py` in VSCode.
   - Run the file using the terminal:
     ```bash
     python app.py
     ```
   - Note the server URL that appears in the terminal (e.g., `http://localhost:5000`).

2. **Configure the Arduino code:**
   - Open `sic_ta1.ino` in Arduino IDE.
   - Set the `server_url` in the code to the server URL shown in VSCode (e.g., `http://localhost:5000`).
   - Compile and upload the code to your ESP32.

3. **Verify the setup:**
   - Open the Serial Monitor in Arduino IDE to ensure the DHT11 sensor data is being sent and there are no errors.
   - Ensure that the ESP32 is successfully connected to the server.

4. **Check the results:**
   - Open your browser and navigate to the endpoint:
     ```
     http://your-server-url:port/sensor/data
     ```
   - You should see the temperature and humidity data sent from the ESP32 displayed on the server.

## Conclusion

This project demonstrates how to set up an IoT system that sends temperature and humidity data from a DHT11 sensor to a local server using a REST API. It showcases how to integrate an embedded system with a server using HTTP communication for data transmission and processing.



---
