import serial
import pyautogui
import time
import ctypes # Damit können wir Windows direkt sagen, dass es sperren soll

COM_PORT = 'COM5' 

try:
    ser = serial.Serial(COM_PORT, 115200, timeout=0.01)
    print("Sicherheits-System aktiv: Knopf an Pin 23 sperrt den PC.")

    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8', errors='ignore').strip()
            
            if line == "LOCK_PC":
                print("Sperre Windows...")
                # Methode 1: Über Windows API (sicherer als Hotkey)
                ctypes.windll.user32.LockWorkStation()
                
                # Methode 2 (Alternative als Hotkey):
                # pyautogui.hotkey('win', 'l') 
        
        time.sleep(0.01)

except Exception as e:
    print(f"Fehler: {e}")
    input("Enter zum Schließen...")
