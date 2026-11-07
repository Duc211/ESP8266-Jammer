#include <Arduino.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <RF24.h>

#define SCK_PIN   14
#define MISO_PIN  12
#define MOSI_PIN  13

// Module 1
#define CE_PIN1   5
#define CSN_PIN1  4

#define LED 2 

bool NRF1Connected = false;

SPIClass spi;

// Khởi tạo module RF24
RF24 radio(CE_PIN1, CSN_PIN1);

void setupModule(RF24 &radio);

void setup() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect(true);  
  WiFi.mode(WIFI_OFF); 

  Serial.begin(115200);
  delay(10);

  // Cấu hình LED built-in
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
 
  // Khởi tạo SPI theo pin mặc định của ESP8266
  spi.begin();

  Serial.println("NRF JAMMER by @Duc_12_34");   
  Serial.println("Waiting NRF24...");           

/*  // Blink LED nhanh khi đang khởi tạo
  for (int i = 0; i < 1; i++) { 
    digitalWrite(LED, LOW);
    delay(75);
    digitalWrite(LED, HIGH);
    delay(75);
  }
*/
  // Kiểm tra module 1
  if (!radio.begin(&spi)) {
    Serial.println("NRF 1: Not found!");
    NRF1Connected = false;
  } else {
    Serial.println("NRF 1: Connected!");
    NRF1Connected = true;
    setupModule(radio);
  }
}

// ==================== CẤU HÌNH MODULE ====================
void setupModule(RF24 &radio) {
  // Thiết lập các thông số cho module NRF24
  //radio.setAutoAck(false);
  //radio.setRetries(0, 0);
  radio.setPALevel(RF24_PA_MIN, true);
  radio.setDataRate(RF24_250KBPS);
  //radio.setCRCLength(RF24_CRC_DISABLED);
  //radio.stopListening();
  radio.startConstCarrier(RF24_PA_MAX, 45);
}

// ==================== LOOP ====================
void loop() {
  // ----- NHẢY KÊNH NRF -----
  if (!NRF1Connected) {
    digitalWrite(LED, LOW);
    delay(500);
    digitalWrite(LED, HIGH);
    delay(500);
  } else {
    digitalWrite(LED, LOW);
    radio.setChannel(random(1, 126));
    //delayMicroseconds(50);
  }
}
