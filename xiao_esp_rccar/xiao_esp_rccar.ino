#include <Arduino.h>
#include <LiquidCrystal.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

// LCD wiring: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

// BLE globals
BLECharacteristic* pCharacteristic = nullptr;
volatile bool g_connected = false;
volatile bool g_connChanged = false;
volatile bool g_cmdUpdated = false;
String g_lastCmd = "";

// BLE callbacks
class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* /*pServer*/) override {
    g_connected = true;
    g_connChanged = true;
  }
  void onDisconnect(BLEServer* pServer) override {
    g_connected = false;
    g_connChanged = true;
    pServer->getAdvertising()->start();
  }
};

class MyWriteCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic* ch) override {
    String v = ch->getValue();
    if (v.length() > 0) {
      g_lastCmd = v;
      g_cmdUpdated = true;
      // Send only the first character (like 'F') to Arduino via UART
      Serial1.write(v[0]);
    }
  }
};

void showDisconnected() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("BLE: Disconnected");
  lcd.setCursor(0, 1);
  lcd.print("Waiting...");
}

void showConnected() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("BLE: Connected");
  lcd.setCursor(0, 1);
  lcd.print("Send cmd...");
}

void showCommand(const String& cmd) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("BLE: Connected");
  lcd.setCursor(0, 1);
  lcd.print("CMD: ");
  lcd.print(cmd.substring(0, 11));
}

void setup() {
  // LCD
  lcd.begin(16, 2);
  showDisconnected();

  // UART to Arduino using GPIO 21 (TX)
  Serial1.begin(9600, SERIAL_8N1, -1, 21);  // TX = GPIO21, no RX

  // BLE setup
  BLEDevice::init("XIAO-Car");
  BLEServer* pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService* pService = pServer->createService("4fafc201-1fb5-459e-8fcc-c5c9c331914b");
  pCharacteristic = pService->createCharacteristic(
      "beb5483e-36e1-4688-b7f5-ea07361b26a8",
      BLECharacteristic::PROPERTY_WRITE
  );
  pCharacteristic->setCallbacks(new MyWriteCallbacks());

  pService->start();
  pServer->getAdvertising()->addServiceUUID("4fafc201-1fb5-459e-8fcc-c5c9c331914b");
  pServer->getAdvertising()->start();
}

void loop() {
  if (g_connChanged) {
    g_connChanged = false;
    if (g_connected) showConnected();
    else showDisconnected();
  }

  if (g_cmdUpdated) {
    g_cmdUpdated = false;
    showCommand(g_lastCmd);
  }
}
