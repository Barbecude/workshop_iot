#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

DHT dht(DHTPIN, DHTTYPE);
int M,sensor_analog;
const int sensor_pin = 34;

const char* ssid ="POCO M3";
const char* password = "12345678910";
#define CHAT_ID  "5874125506"
#define BOTtoken "6687002855:AAEK0S6VdL0oG6i7pCwfDS45xMtfq6FJN74"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
int botRequestDelay =1000;
unsigned long lastTimeBotRan;

void setup(){
  Serial.begin(115200);
  
    Serial.print("Connecting Wifi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  bot.sendMessage(CHAT_ID, "Tunggu dulu...monitoring akan segera dimulai", "");

    delay(2000);
    Serial.print("Workshop Monitoring Tanaman XI RPL 2");
    dht.begin();
}
void loop() {
  sensor_analog = analogRead(sensor_pin);
   M = ( 100 - ( (sensor_analog/4095.00) * 100 ) );
  float tempe = dht.readTemperature();
  float humid = dht.readHumidity();
  if (isnan(humid) || isnan(tempe) || isnan(M)) {
    Serial.println("Sensor tidak terbaca!");
    bot.sendMessage(CHAT_ID,"Sensor tidak terbaca!", "");
    return;
}
  Serial.print("====================Monitoring tanaman=====================\n");
  Serial.print("Humiditas gas udara;");
  Serial.print(humid); 
  Serial.println("%");
  Serial.print("Temperatur lingkungan: ");
  Serial.print(tempe); 
  Serial.print(" °C");
  Serial.print("Kelembapan tanah");
  Serial.print(M);
  Serial.println("%");
  bot.sendMessage(CHAT_ID,"Monitoring tanamah XI RPL 2");
  //delay(1000);
  kirimPesanTelegram(humid,tempe,M);
}

void kirimPesanTelegram(float humid, float tempe, int moist) {
  String pesan = "Suhu saat ini: " + String(tempe, 2) + "°C\n" +
                 "Humiditas udara saat ini: " + String(humid, 2) + "%\n" +
                 "Tingkat kelembaban tanah saat ini: " + String(moist) + "%\n";

  if (bot.sendMessage(CHAT_ID, pesan, "Markdown")) {
    Serial.println("Pesan berhasil dikirim");
  } else {
    Serial.println("Gagal mengirim pesan");
  }

  delay(1000);  // Menunggu sejenak sebelum mengirim pesan lagi
}
