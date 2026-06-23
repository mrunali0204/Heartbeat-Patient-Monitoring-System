# ❤️ Smart Health & Environment Monitoring System using STM32 Blue Pill

An embedded real-time monitoring system built using the **STM32 Blue Pill** microcontroller that continuously monitors both **health** and **environmental** parameters. The system processes sensor data, displays live readings on an OLED screen, and triggers alerts using a buzzer whenever abnormal conditions are detected.

---

## 📌 Overview

The project integrates multiple sensors with the STM32 Blue Pill to provide a compact and low-cost monitoring solution. It is designed for healthcare, smart home, and industrial applications where continuous monitoring and instant alerts are required.

---

# 📸 Project Poster

<p align="center">
  <img src="docs/mspa4_EDA_photo_canvas.png" width="900">
</p>

---

## 🚀 Features

- ❤️ Heartbeat Monitoring
- 🌡 Temperature & Humidity Monitoring
- 💡 Light Intensity Detection
- 🔊 Sound Detection
- 📐 Tilt Detection
- 📺 Real-time OLED Display
- 🔔 Instant Buzzer Alerts
- ⚡ Low-cost Embedded Solution

---

## 🛠 Tech Stack

| Category | Technology |
|----------|------------|
| Language | C |
| IDE | STM32CubeIDE |
| Microcontroller | STM32 Blue Pill |
| Communication | GPIO, ADC, I2C |
| Display | OLED SSD1306 |
| Sensors | DHT11, Pulse Sensor, LDR, Sound Sensor, Tilt Sensor |

---

## 🔧 Hardware Components

- STM32 Blue Pill
- OLED Display (SSD1306)
- Heartbeat Sensor
- DHT11 Sensor
- LDR Sensor
- Sound Sensor
- Tilt Sensor
- Buzzer
- Breadboard
- Jumper Wires
- Power Supply

---

## 🏗️ System Architecture

<p align="center">
  <img src="docs/block_diagram.png" width="750">
</p>

---

## 🔄 Data Flow

```text
Sensors
   │
   ▼
STM32 Blue Pill
   │
   ▼
Data Processing
   │
   ▼
Threshold Comparison
   │
   ├── Normal Condition
   │      │
   │      ▼
   │  OLED Display
   │
   └── Abnormal Condition
          │
          ▼
OLED Display + Buzzer Alert
```

---

## ⚙️ Working

1. Sensors continuously collect environmental and health-related data.
2. STM32 Blue Pill reads sensor values through GPIO and ADC.
3. The controller processes incoming data.
4. Sensor readings are compared with predefined threshold values.
5. If abnormal conditions are detected:
   - OLED displays an alert message.
   - Buzzer is activated.
6. Otherwise, live sensor readings continue to be displayed.

---

## 🎯 Objectives

- Real-time monitoring
- Detect abnormal conditions
- Alert users through buzzer
- Display sensor values on OLED
- Develop an affordable embedded monitoring solution

---

## 💼 Applications

- Healthcare Monitoring
- Patient Safety Systems
- Smart Home Automation
- Environmental Monitoring
- Industrial Monitoring
- Embedded Systems Learning

---

## 📷 Hardware Setup

<p align="center">
  <img src="docs/hardware_img.jpeg" width="650">
</p>

---

## 📂 Project Structure

```text
Heartbeat-Patient-Monitoring-System
│
├── Core/
├── Drivers/
├── Inc/
├── Src/
├── docs/
│   ├── block_diagram.png
│   ├── hardware_img.jpeg
│   └── mspa4_EDA_photo_canvas.png
├── README.md
├── LICENSE
└── .gitignore
```

---

## 🔮 Future Improvements

- Wi-Fi / IoT Integration
- Mobile Application
- Cloud Data Logging
- SMS & Email Notifications
- AI-based Anomaly Detection
- Remote Monitoring Dashboard

---

## 👨‍💻 Author

**Mrunali Jibhakate**

🎓 B.Tech Electronics Engineering  
💻 Software Engineer | Embedded Systems | C/C++ | System Programming

