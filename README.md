# 🏎️ Bluetooth-Controlled Car

A summer engineering project featuring an **Arduino Uno** and a **Seeed Studio XIAO ESP32**. This project demonstrates how to bridge two microcontrollers to achieve smartphone-controlled mobility via Bluetooth.

---

## 📌 Project Overview

The car uses a dual-controller architecture to handle communication and physical movement:

* **XIAO ESP32:** Acts as the "brain's ears." it receives wireless commands via Bluetooth from a smartphone and translates them into logic signals.
* **Arduino Uno:** Acts as the "motor specialist." It receives the processed signals from the XIAO and uses **PWM (Pulse Width Modulation)** to control the speed and direction of the DC motors.
* **Breadboard Interface:** Serves as the communication bridge between the XIAO and the Arduino.



---

## 🛠️ Hardware Stack
`Please note:` you can choose any model for the motors and the battery

| Component | Purpose |
| :--- | :--- |
| **Arduino Uno** | Main motor controller and PWM generator |
| **XIAO ESP32** | Bluetooth Low Energy (BLE) receiver |
| **DC Motors** | Drive system for the wheels |
| **Breadboard** | Prototyping and signal routing |
| **Smartphone** | Remote control interface |
| **6V Battery** | Powers up the whole car system |
| **LCD Screen** | Displays the commands received by the system |

---

## 📂 Repository Contents

* **`/arduino_rccar`**: Contains the `.ino` sketch for the Arduino Uno to handle DC motor logic.
* **`/xiao_esp_rccar`**: Contains the code for the XIAO module to enable Bluetooth discoverability.
* **`/diagrams`**: Wiring schematics and pinout map for the breadboard connections.

---

## 🚀 How to Use

### 1. Hardware Setup
Connect the XIAO ESP32 to the Arduino Uno. Ensure that both boards share a **Common Ground (GND)** on the breadboard as only one battery would power up the whole car.

### 2. Software Installation
1.  Upload the `xiao_esp_rccar` code to your XIAO module using the Arduino IDE.
2.  Upload the `arduino_rccar` code to your Uno.

### 3. Remote Control Interface
For this example, we use the **LightBlue** app (available on iOS and Android) to send commands:
1.  Power on the car.
2.  Open **LightBlue** and look for the XIAO device in the scanning list.
3.  Connect to the device and select the appropriate command characteristic.
4.  Send your movement values—**and the car is ready to roll!**

---

## 🔧 Future Roadmap
* Integrate an Ultrasonic sensor for "Auto-Avoidance" mode.
* Develop a custom Flutter/React Native app for a more intuitive UI and joystick controls.
* Migrate from a breadboard to a custom soldered PCB for more polished appearance.
