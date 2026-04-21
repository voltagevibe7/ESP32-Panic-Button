#include <esp_now.h>
#include <WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Display Einstellungen
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

bool verbunden = false;

// --- FUNKTION ZUM ANZEIGEN ---
void showStatus(int rssi) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.println("SYSTEM STATUS:");
    display.println("---------------------");
    display.setTextSize(2);
    display.setCursor(0, 30);

    if (rssi > -50) {
        display.println("STARK");
    } else if (rssi <= -50 && rssi > -80) {
        display.println("MITTEL");
    } else {
        display.println("SCHWACH");
    }
    display.display();
}

// --- CALLBACK WENN DATEN KOMMEN ---
void OnDataRecv(const esp_now_recv_info *info, const uint8_t *incomingData, int len) {
    verbunden = true;
    
    // RSSI aus den Empfangs-Infos ziehen
    int rssi = info->rx_ctrl->rssi; 
    
    // Status auf dem Display aktualisieren
    showStatus(rssi);

    // Shutdown-Check
    if (incomingData[0] == 'X') { 
        Serial.println("EXECUTE:shutdown /s /f /t 0");
    }
}

void setup() {
    Serial.begin(115200);
    
    // Display starten
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
        for(;;); 
    }
    
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(20, 25);
    display.println("Connecting...");
    display.display();

    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK) return;

    // Den Empfänger registrieren
    esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
    // Hier bleibt alles leer, da der ESP auf Funk-Events wartet
}
