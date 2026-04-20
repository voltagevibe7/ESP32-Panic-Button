#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET    -1 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int panicButton = 23;
bool lastState = HIGH;

void setup() {
  Serial.begin(115200);
  pinMode(panicButton, INPUT_PULLUP);

  // Display initialisieren
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    for(;;);
  }

  // Startbildschirm
  display.clearDisplay();
  display.setTextSize(2);      
  display.setTextColor(WHITE); 
  display.setCursor(15, 10);   
  display.println("PANIC");
  display.setTextSize(1);
  display.setCursor(15, 40);
  display.println("BUTTON READY");
  display.display();
}

void loop() {
  bool currentState = digitalRead(panicButton);

  if (currentState == LOW && lastState == HIGH) {
    // Wenn Knopf gedrückt wird
    Serial.println("LOCK_PC");
    
    display.clearDisplay();
    display.invertDisplay(true); // Display blinkt kurz invertiert
    display.setTextSize(2);
    display.setCursor(10, 25);
    display.println("LOCKING!");
    display.display();
    
    delay(1000); // Zeige "Locking" kurz an
    display.invertDisplay(false);
  }
  
  if (currentState == HIGH && lastState == LOW) {
    // Wenn Knopf losgelassen wird -> Zurück zum Standard
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(15, 10);
    display.println("PANIC");
    display.setTextSize(1);
    display.setCursor(15, 40);
    display.println("BUTTON READY");
    display.display();
  }

  lastState = currentState;
  delay(10);
}
