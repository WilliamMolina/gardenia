#include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"
#include "esp_pm.h"
#include "esp32/pm.h"
#include "esp32-hal-cpu.h"

const char* ssid = "wondercode";
const char* password =  "violeta321";
const char* mqttServer = "iot.eclipse.org";
const int mqttPort = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void sendMessage(String sensor, String value){
  String topic = "gardenia/plant/";
  topic.concat(sensor);
  if (client.publish(topic.c_str(), value.c_str()) == true) {
    Serial.println("Success sending sensor info");
  } else {
    Serial.println("Error sending message");
    Serial.println(client.state());
  }
}

void setup() { 
  setCpuFrequencyMhz(80);
  Serial.begin(115200);
  Serial.println("Starting Gardenia sensors");
  connect_wifi(); 
  client.setServer(mqttServer, mqttPort);
  connect_mqtt();
}

void connect_mqtt(){
  while (!client.connected()) {
    Serial.println("Connecting to MQTT..."); 
    if (client.connect("ESP32Client")) { 
      Serial.println("connected"); 
    } else { 
      Serial.print("failed with state ");
      Serial.println(client.state());
    }
  }  
}

void connect_wifi(){
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  } 
  Serial.println(WiFi.localIP());
  Serial.println("Connected to the WiFi network");
}

void get_temperature(){
  String temperature = (String) random(0, 50);
  sendMessage("temperature", temperature);
}

void get_humidity(){
  String humidity = (String) random(0, 50);
  sendMessage("humidity", humidity);
}

void get_moisture(){
  String moisture = (String) random(0, 50); 
  sendMessage("moisture", moisture);
}

void loop() {
  //esp_sleep_enable_timer_wakeup(60 * 1000000);
  //esp_deep_sleep_start();
  Serial.println("Sensing...");
  if(WiFi.status() != WL_CONNECTED) {
    Serial.println("Retrying to connect WiFi..");
    connect_wifi();
  }  
  if(!client.connected()){
    Serial.println("Retrying to connect to MQTT Server..");
    connect_mqtt();  
  }
  get_temperature();
  get_humidity();
  get_moisture(); 
  delay(3000);
}
