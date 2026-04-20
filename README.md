# 🚨 ESP32 OLED Panic Button

This project uses an **ESP32** and a physical button to instantly lock your Windows PC.

## 🛠 Hardware
* ESP32 DevKit V1
* OLED Display (SSD1306, 128x64)
* 1x Push Button

## 🔌 Connections
* **Button:** Pin 23 & GND
* **Display SDA:** Pin 21
* **Display SCL:** Pin 22
* **Display VCC:** 3.3V
* **Display GND:** GND

## 🚀 How to use
1. Upload the `.ino` file to your ESP32.
2. Install the requirements on your PC: `pip install pyautogui pyserial pydirectinput`.
3. Run the `pc_control.py` script.
4. Press the button to lock your PC!
