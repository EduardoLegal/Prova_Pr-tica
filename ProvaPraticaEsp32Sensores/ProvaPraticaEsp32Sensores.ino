#include <WiFi.h> 
#include <PubSubClient.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 20
#define DHTTYPE    DHT11

DHT_Unified dht(DHTPIN,DHTTYPE);

const String topic = "ProvaPratica/IoT/Sensor";

const byte pin_echo = 22 ;
const byte pin_trigg = 23;

const byte pin_echo1 = 7;
const byte pin_trigg1 = 0;

const String SSID = "Dudunet";
const String PSWD = "dudu1234";

const String brokerUrl = "test.mosquitto.org";
const int port = 1883;

WiFiClient espClient;
PubSubClient mqttClient(espClient);

void conexaoBroker(){
  Serial.println("Conectando ao broker");
  mqttClient.setServer(brokerUrl.c_str(),port);
  String userId = "ESP-BANANINHA";
  while(!mqttClient.connected()){
    mqttClient.connect(userId.c_str());
    Serial.println(".");
    delay(2000);
  }
  Serial.println("mqtt Connectado com sucesso!");
}

void conexaoWifi(){
  Serial.println("Iniciando conexão com rede Wi-Fi");
  Serial.print("Conectando");
  WiFi.begin(SSID,PSWD);
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(5000);
  }
  Serial.println("\nConectado");
}

void setup() {
  Serial.begin(9600);
  dht.begin();
  conexaoWifi();
  conexaoBroker();
}

void loop() {
  delay(1000);
  if(WiFi.status() != WL_CONNECTED){
    conexaoWifi();
  }

  if(!mqttClient.connected()){
    conexaoBroker();
  }


}
