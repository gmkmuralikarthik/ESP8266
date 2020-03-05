   float Fs = 800;                   // samples per second
   float dt = 1/Fs;                   // seconds per sample
   float  F = 50;  
   float t=0.0;
void setup() 
{
 Serial.begin(115200);

}

void loop() 
{

   t = t+dt;     //seconds
   double x = sin(2*3.14*F*t);
   if (t>0.25)
    {
      t=0;
    }
    Serial.println(x);
    delay(100);

}
