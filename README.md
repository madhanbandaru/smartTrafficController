# 🚦 IoT-Based Traffic Monitoring and Control System
good to see window view ->https://madhanbandaru.github.io/smartTrafficController/ 

This project is a smart IoT solution using **ESP8266** that monitors environmental conditions and detects emergency vehicles like ambulances based on sound, along with harmful gas levels. Based on this input, it automatically manages traffic lights and sends real-time data to the **Blynk IoT dashboard**.

---

## 🔧 Technologies Used

- ⚙️ **ESP8266 NodeMCU**
- 💨 **DHT11 Sensor** – for Temperature and Humidity
- 🔊 **Sound Sensor** – to detect ambulance sirens or loud sounds
- ☠️ **MQ2 Gas Sensor** – to detect harmful gases
- 🚦 **Traffic Light LEDs** – red, yellow, green (for signal control)
- 📡 **Blynk IoT Platform** – for real-time monitoring and control
- 💡 **Arduino IDE** – for development and code upload

---

## 📷 System Overview

The system performs the following actions:
- 📈 Continuously monitors **temperature** and **humidity** via the DHT11 sensor.
- 🔊 Detects **ambulance sirens or loud noises** using the sound sensor.
- ☠️ Monitors **air quality** using a gas sensor.
- 🚦 Automatically changes traffic lights based on sound/gas detection:
  - Green light is prioritized when a siren is detected or gas is present.
  - Otherwise, it runs a normal red → yellow → green cycle.
- 📲 Sends sensor values to the **Blynk dashboard** for visualization.

---

## 🛠️ Hardware Setup

| Component        | ESP8266 Pin |
|------------------|-------------|
| DHT11 Sensor     | D5 (GPIO 13)|
| Sound Sensor     | D5 (GPIO 14)|
| Gas Sensor       | D6 (GPIO 12)|
| Red LED          | D0 (GPIO 16)|
| Yellow LED       | D1 (GPIO 5) |
| Green LED        | D2 (GPIO 4) |
| Buzzer (Optional)| D4 (GPIO 2) |

> Note: Make sure to use 220Ω resistors for LEDs.

---

## 📲 Blynk Setup

- Create a project in [https://blynk.cloud](https://blynk.cloud)
- Add virtual widgets:
  - V0 → Temperature (Value Display)
  - V1 → Humidity (Value Display)
  - V2 → Sound Detected (LED or Value)
  - V3 → Harmful Gas Detected (LED or Value)
- Replace these values in code:
  ```cpp
  #define BLYNK_TEMPLATE_ID "YourTemplateID"
  #define BLYNK_TEMPLATE_NAME "YourTemplateName"
  #define BLYNK_AUTH_TOKEN "YourAuthToken"
📌 Features
Real-time temperature and humidity monitoring

Sound-based ambulance detection

Harmful gas alert system

Automated traffic light control

Live cloud monitoring via Blynk

Expandable and easy to modify for smart city needs

🔒 Future Enhancements
Replace sound thresholding with FFT or ML model for more accurate siren detection

Add GPS tracking of ambulances

Implement LoRa communication for longer range

Use Edge Impulse for deploying sound classification models
Madhan Bandaru       
IoT & Java Developer
📧madhan2you@gmail.com
