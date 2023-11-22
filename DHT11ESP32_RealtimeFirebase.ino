//ESP32DHT11, Firebase Project, Realtime Database

#include <DHT.h>
#include <WiFi.h>
#include <IOXhop_FirebaseESP32.h>
#include <ArduinoJson.h>


#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define WIFI_SSID "BIA_2G"
#define WIFI_PASSWORD "Sapo-666"
#define FIREBASE_AUTH "dht11esp32-f2e38-default-rtdb.firebaseio.com/"
#define FIREBASE_HOST "c1x3IPajydlf678KdbfHQ4ioZmmSJx3qkEi9SwRK"

void setup() {
  Serial.begin(115200);
  Serial.print("DHT TEST");
  dht.begin();

  //Connect to WIFI
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED){
    Serial.println(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Connected:");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_AUTH, FIREBASE_HOST);
}
int n = 0;
  
void loop() {

  delay(2000);
  //DHT = Humidity and Temperature
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if(isnan(h) || isnan(t)) {
     Serial.println("Failed to read from DHT sensor!");
     return;
  }  
  Serial.print("Humidity:");
  Serial.print(h);
  Serial.print(" %\t");

  Serial.print("Temperature:");
  Serial.print(t);
  Serial.print(" *C");

  //set value
  Firebase.setFloat("Humidity", h);
  //Handle error
  if(Firebase.failed()){
    Serial.print("Setting/number failed:");
    Serial.println(Firebase.error());
    return;
  }  
  delay(1000);
  Firebase.setFloat("Temperature", t);
  //Handle error
  if(Firebase.failed()){
    Serial.print("Setting/number failed:");
    Serial.println(Firebase.error());
    return;
  }  
  Serial.println("    Temperature and Humidity Data Sent Successfully!");
  delay(2000);
  
}
