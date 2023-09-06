#define GAS_Sensor 2


void setup()
{
    pinMode(GAS_Sensor, INPUT);
    attachInterrupt(digitalPinToInterrupt(GAS_Sensor), ALARM_ISR, RISING );
  	Serial.begin(9600);
}
void ALARM_ISR()
{
  	Serial.write('H');

}

void loop()
{
  digitalRead(GAS_Sensor);
  
}