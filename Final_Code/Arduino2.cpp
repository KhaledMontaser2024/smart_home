#include <Servo.h>
#include <EEPROM.h>
#include <ros.h>
#include <std_msgs/Char.h>
#include <std_msgs/Int16.h>

#define Servo1 3 
#define Servo2 5 
#define H1 12
#define H2 13
#define EN 11
#define R_LED 7
#define W_LED 8
#define BUZZER 6



char msgg;
Servo home_door ;
Servo room_door ;

ros::NodeHandle nh;

void messageCB(const std_msgs::Char &toggle_msg)
{
  msgg=toggle_msg.data;
}
void password (const std_msgs::Int16 &toggl_msg)
{
  homedoor(toggl_msg.data); 
  
}
ros::Subscriber<std_msgs::Char> sub("chatter",messageCB);
ros::Subscriber<std_msgs::Int16> sub2("topic1",password);


int GetBit(char msg,char bt)
{
  return ((msg>>bt)&1);
}


void curtains(char msgg)
{  
    if (GetBit(msgg,1))
    {
      digitalWrite(W_LED,LOW);
      motoropen();
      delay(1000);
      motorstop();
    }
    else if (!GetBit(msgg,1))
    {
      
      digitalWrite(W_LED,HIGH);
      motorclose();
      delay(1000);
      motorstop();
    }  
 return;
}
void roomdoor(char msgg){
  if (GetBit(msgg,0))
    {
      room_door.write(100);
    }
    else if (! GetBit(msgg,0))
    {
    room_door.write(0);
    }

    } 
void homedoor(short signed int password)
{   
    if (password == EEPROM[0] )//check if the recieved pass is correct
    {home_door.write(100);
     delay(3000);
     home_door.write(0);
    }

}

void AlarmSystem(char Alarm)
{
    digitalWrite(BUZZER,HIGH);
    digitalWrite(R_LED,HIGH);
    home_door.write(100);
    room_door.write(100);
    curtains(Alarm);    
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


void setup() 
{
  nh.initNode();
  nh.subscribe(sub);
  nh.subscribe(sub2);
  home_door.attach(Servo1) ; 
  room_door.attach(Servo2) ; 
  pinMode(H1, OUTPUT);
  pinMode(H2, OUTPUT);
  pinMode(EN, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(R_LED, OUTPUT);
  pinMode(W_LED, OUTPUT);  
  EEPROM.update(0,123) ;
}

void loop() 
{
  nh.spinOnce();
  delay(500); 
  if (msgg>=250)
  {
    AlarmSystem(msgg);
  }
  else 
  { 
    roomdoor(msgg);
    curtains(msgg);
  }
  
}