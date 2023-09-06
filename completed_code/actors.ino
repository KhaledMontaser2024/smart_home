#include <Servo.h>
#include <EEPROM.h>
#define pin1 9 
#define pin2 10 
#define switchpin 11
#define H1 7
#define H2 8
#define EN 6
#define R_LED 6
#define BUZZER 7

char Alarm_msg;
int light = 0;
int flag = 0; 
Servo home_door ;
Servo room_door ;
float distance = 0 ;//would be recived from arduino 1

int ent_pass ;//would be recieved from pass node

void roomdoor(float distance){
  if (distance <= 100 )
    {room_door.write(100);
    }
    else 
    {
    room_door.write(0);
    }

    } 
void homedoor(){ 
  
    if (ent_pass == EEPROM[0])//check if the recieved pass is correct
    {home_door.write(100);
     delay(3000);
    home_door.write(0);
    }

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
  
    
    }  

return;
}

  void motorclose()
{
  analogWrite(EN, 100);
  digitalWrite(H2, HIGH);
  digitalWrite(H1, LOW);
  delay(1000);
}

void motoropen()
{
  analogWrite(EN, 100);
  digitalWrite(H1, HIGH);
  digitalWrite(H2, LOW);
  delay(1000);
}

void motorstop()
{
  analogWrite(EN, 0);
  digitalWrite(H1, LOW);
  digitalWrite(H2, LOW);
}


void setup() {
  Serial.begin(9600);
  home_door.attach(pin1) ; 
  room_door.attach(pin2) ; 
  pinMode(switchpin,INPUT);
  pinMode(H1, OUTPUT);
  pinMode(H2, OUTPUT);
  pinMode(EN, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(R_LED, OUTPUT);
  
  EEPROM.update(0,123) ;

}

void loop() {
homedoor(); 
roomdoor(distance);
if (Serial.available() >= sizeof(light)) {   
    Serial.readBytes((char*)&light, sizeof(light));

      if (light > 50 && flag == 0)
    {
      motoropen();
      delay(1000);
      motorstop();
      flag = 1;
    }
    else if (light < 50 && flag == 1)
    {
      motorclose();
      delay(1000);
      motorstop();
      flag = 0;
    }
}

Alarm_msg = Serial.read();
  AlarmSystem(Alarm_msg);

}
