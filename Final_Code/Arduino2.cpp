#include <Servo.h>
#include <EEPROM.h>
#include <ros.h>
#include <std_msgs/Char.h>
#include <std_msgs/Int16.h>
#include <std_msgs/String.h>

#define Servo1 3 
#define Servo2 5 
#define H1 12
#define H2 13
#define EN 11
#define R_LED 7
#define W_LED 8
#define BUZZER 6
#define CloseCurtains 0xF0
#define OpenCurtains 0xE0
#define OpenDoor write(100)
#define CloseDoor write(0)
#define interval 1000


bool curtain_flag = 0;
unsigned long OpenDoor_time = 0;
unsigned long Current_millis = 0;


Servo home_door ;
Servo room_door ;

ros::NodeHandle nh2;              // creating ROS node
std_msgs::String CheckPassword;   // creting variable with ROS String data type 


void curtains(char message);
void homedoor(short signed int password);
void AlarmSystem();
void motorclose();
void motoropen();
void motorstop();
void roomdoor();
void Actuators_CallBack(const std_msgs::Char &SensorsMessage);        
void password_CallBack(const std_msgs::Int16 &PasswordMessage);

ros::Subscriber<std_msgs::Char> sub("/sensors_reads",Actuators_CallBack);         // subscriber receives from Arduino 1 
ros::Subscriber<std_msgs::Int16> sub2("/password_to_arduino",password_CallBack);  // subscriber receives from password node on terminal
ros::Publisher pub("/wrongpassword", &CheckPassword);                             // publisher sends to password node on terminal



void setup() 
{
  nh2.initNode();
  nh2.subscribe(sub);
  nh2.subscribe(sub2);
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
  Current_millis = millis();
  roomdoor();
  nh2.spinOnce();
  delay(500); 
  
}

void Actuators_CallBack(const std_msgs::Char &SensorsMessage)
{
  switch (SensorsMessage.data)
  {/*switching on the received data from arduino 1 to call the proper func*/
  case 0xFF:
    AlarmSystem();
    break;

  case 0x0F:
    room_door.OpenDoor;
    OpenDoor_time = millis();     // storing when the door opened to determine when to close it  
    break;

  case 0xF0:
    curtains(CloseCurtains);
    break;

  case 0xE0:
    curtains(OpenCurtains);
    break;

  default:
    break;
  }

}
void password_CallBack(const std_msgs::Int16 &PasswordMessage)
{/*sending received password from terminal for comparison with the correct one*/
  homedoor(PasswordMessage.data); 
}
void homedoor(short signed int password)
{   
    if (password == EEPROM[0])//check if the recieved password is correct
    {
      home_door.OpenDoor;
      CheckPassword.data="Welcome Home"; // sending feedback
      pub.publish(&CheckPassword);
    }
    else 
    {
      CheckPassword.data="Wrong Password Try Again";
      pub.publish(&CheckPassword);
    }
return;
}
void curtains(char message)
{  
    if (message == OpenCurtains && curtain_flag == 0 )
    {
      curtain_flag =1;        // flag to make sure not to open the curtains while its already opened and vice versa 
      digitalWrite(W_LED,LOW);
      motoropen();
      delay(1000);
      motorstop();
    }
    else if (message == CloseCurtains && curtain_flag == 1 )
    {
      curtain_flag =0;
      digitalWrite(W_LED,HIGH);
      motorclose();
      delay(1000);
      motorstop();
    }  
 return;
}
void AlarmSystem()
{
    digitalWrite(BUZZER,HIGH);
    digitalWrite(R_LED,HIGH);
    home_door.OpenDoor;
    room_door.OpenDoor;
    curtains(OpenCurtains);   
return;
}
void motorclose()
{
  analogWrite(EN, 100);
  digitalWrite(H2, HIGH);
  digitalWrite(H1, LOW);
  return;
}
void motoropen()
{
  analogWrite(EN, 100);
  digitalWrite(H1, HIGH);
  digitalWrite(H2, LOW);
  return;
}
void motorstop()
{
  analogWrite(EN, 0);
  digitalWrite(H1, LOW);
  digitalWrite(H2, LOW);
  return;
}
void roomdoor()
{
  if (OpenDoor_time - Current_millis >=interval) // calculating how much time had passed since the door has been opened 
  {                                              // if the time passed is greater than (interval) door will automaticlly close 
    room_door.CloseDoor;
  }
return;
}