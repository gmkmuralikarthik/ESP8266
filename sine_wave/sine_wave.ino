
float m;
float fs=8000;
float dt=1/fs;
void setup() {

 Serial.begin(115200);
 m=0;
}

void loop() {
  double k=sin(6.28*50*m);
  m+=dt;
k=512+512*k;
analogWrite(LED_BUILTIN,k);
Serial.println(k);
delay(50);
  if(m>10) m=0;
}
