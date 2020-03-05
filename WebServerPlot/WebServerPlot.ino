  #include <Arduino.h>
  #include <ESP8266WiFi.h>
  #include <Hash.h>
  #include <ESPAsyncTCP.h>
  #include <ESPAsyncWebServer.h>
  #include <FS.h>
   float Fs = 2000;                   // samples per second
   float dt = 1/Fs;                   // seconds per sample
   float  F = 100;  
   float t=0.0;
  const char* ssid = "SNR_Arvind";
  const char* password = "akgIIT13";

// Create AsyncWebServer object on port 80
  AsyncWebServer server(80);

String readSine() 
{
   t = t+dt;     //seconds
   double x = sin(2*3.14*F*t);
   if (t>1)
    {
      t=0;
    }
    Serial.println(x);

  if (isnan(t)) {    
    Serial.println("Failed to read from BME280 sensor!");
    return "";
  }
  else {
    Serial.println(x);
    return String(x);
  }
}


void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  
  // Initialize SPIFFS
  if(!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html");
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readSine().c_str());
  });

  server.begin();
}
 
void loop(){
  
}
