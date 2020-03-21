  #include <Arduino.h>
  #include <ESP8266WiFi.h>
  #include <Hash.h>
  #include <ESPAsyncTCP.h>
  #include <ESPAsyncWebServer.h>
  #include <FS.h>

  const char* ssid = "try_now_sucker";
  const char* password = "lionel10messi";

// Create AsyncWebServer object on port 80
  AsyncWebServer server(80);



float filter[23]={-0.0017  , -0.0006 ,   0.0063 ,   0.0125 ,   0.0015 ,  -0.0301 ,  -0.0491 ,  -0.0024 ,   0.1249  , 0.2711 ,   0.3361 ,   0.2711  ,  0.1249 ,  -0.0024  , -0.0491 ,   -0.0301 ,   0.0015 ,   0.0125,   0.0063  , -0.0006 ,  -0.0017 }   ;         
float m=0;
//float fs=8000;
float dt=1.0/8000;


//filter code


String filtering( ){
/*
  float k=0;
  for(int i=n;i>=0;i--)
  k+=a[n]*filter[n];
*/

  double k=sin(6.28*50*m);
    m+=dt;
    k=512+512*k;
   // analogWrite(LED_BUILTIN,k);
    Serial.println(k);
    delay(50);
    if(m>10) m=0;
  
  return String(k);
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
    request->send(SPIFFS, "/index.html", filtering().c_str());
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", filtering().c_str());
  });

  server.begin();
}
 
void loop(){
  
}
