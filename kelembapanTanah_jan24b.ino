#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11
#include <WiFi.h>
#include <WifiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
DHT dht(DHTPIN, DHTTYPE);
int M,sensor_analog;
const int sensor_pin = 34;

const char* ssid ="POCO M3";
const char* password = "12345678910";
#define CHAT_ID = "5874125506";
#define BOTtoken "6687002855:AAEK0S6VdL0oG6i7pCwfDS45xMtfq6FJN74";

WiFiClientSecure client;
UniversalTelegramBot bot(Bottoken, client);
int botRequestDelay =1000;
unsigned long lastTimeBotRan;

void setup(){
  Serial.begin(115200);
  delay(2000);
  Serial.print("Workshop Monitoring Tanaman XI RPL 2\n");
  dht.begin();
  Serial.begin(115200);
  delay(2000);
  Serial.print("Workshop Monitoring Tanaman XI RPL 2");
  
  Serial.begin(115200);
  Serial.print(POCO M3, 12345678910)
  Client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  Serial.println("");
  Serial.println("WiFi connected")
    Serial.println("Ip address:")
    Serial.println(WiFi.localIP());

    bot.sendMessage(CHAT_ID, "Tunggu dulu...monitoring akan segera di mulai", "");

    delay(2000);
    Serial.print("Workshop Monitoring Tanaman XI RPL 2");
    dht.begin();
}
void loop() {
  sensor_analog = analogRead(sensor_pin);
} 

    
    


  while (wifi.status() !=WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
}

void loop(){
  float t = dht.readTemperature();
  float h =dht.readHumidity();
  if (isnan(h) || isnan(t)){
    Serial.println("Sensor tidak terbaca!");
    return;
  }
  Serial.print("====================Monitoring tanaman=====================\n");
  Serial.print("Humiditas gas udara;");
  Serial.print(h); 
  Serial.println("%");
  Serial.print("Temperatur lingkungan: ");
  Serial.print(t);
  Serial.print(" °C");
  delay(2000);

   sensor_analog = analogRead(sensor_pin);
  M = (100 - ( (sensor_analog/4095.00) * 100));
  if(isnan(M)){
    Serial.println("Sensor tidak terbaca!");
    return;
  }
  Serial.print("============================Monitoring tanaman==========================\n");
  Serial.print("Kelembapan air tanah: ");
  Serial.print(M); 
  Serial.println("%");
  delay(1000);
}

