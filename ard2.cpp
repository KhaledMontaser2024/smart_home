// C++ code
//

#define R_LED 6
#define BUZZER 7

char Alarm_msg;

void AlarmSystem(char Alarm);
void setup()
{
  Serial.begin(9600);
  pinMode(BUZZER, OUTPUT);
  pinMode(R_LED, OUTPUT);
  
}

void loop()
{
 	Alarm_msg = Serial.read();
	AlarmSystem(Alarm_msg);

}




void AlarmSystem(char Alarm)
{
	switch (Alarm)
    {
      case 'H':
		digitalWrite(BUZZER,HIGH);
  		digitalWrite(R_LED,HIGH);
     	break;
     
      case 'C':
		digitalWrite(BUZZER,LOW);
  		digitalWrite(R_LED,LOW);
    	break;
  
  	 default:
    }  

return;
}
  
  
  
  
  