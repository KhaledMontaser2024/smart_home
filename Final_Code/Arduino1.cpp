#include <ros.h>
#include <std_msgs/Char.h>  

#define US_trig 6 
#define US_echo 2
#define GAS_Sensor 3
#define LDR A0

ros::NodeHandle nh;                               // creating ROS node
std_msgs::Char message;                           // creting variable with ROS Char data type 
ros::Publisher pub("/sensors_reads", &message);   // publisher sends to Arduino 2


bool LDR_flag = 0; 
int light = 0;
int distance = 0 ; 
int duration = 0 ;

void LDR_sensor();
void UltraSonic_ISR ();
void Ultra_sensor();
void ALARM_ISR();


void setup() 
{
  nh.initNode();
  nh.advertise(pub);
  pinMode(US_trig,OUTPUT);
  pinMode(US_echo,INPUT);
  pinMode(GAS_Sensor, INPUT);
  attachInterrupt(digitalPinToInterrupt(US_echo), UltraSonic_ISR , FALLING);
  attachInterrupt(digitalPinToInterrupt(GAS_Sensor), ALARM_ISR, FALLING);
}

void loop() 
{
  Ultra_sensor();
  light = analogRead(LDR);
  LDR_sensor();
  nh.spinOnce();
}

void LDR_sensor()
{
    if (light > 50 && LDR_flag == 0)    // flag to make sure not to send the same command twice 
    {
      LDR_flag = 1;
      message.data=0xF0;
      pub.publish(&message);
      message.data=0x00;
    }
    else if (light < 50 && LDR_flag == 1)
    {
      LDR_flag = 0;
      message.data=0xE0;
      pub.publish(&message);
      message.data=0x00;
    }
    return;
}
void UltraSonic_ISR()
{  
  distance = (duration/57); //57 = 1/(speed of air in specific conditions(cm\ms)/2)
  switch (distance)
  {
    case 0 ... 5 :
      message.data=0x0F;
      pub.publish(&message);
      message.data=0x00;
      break;
    
    default:
      break;
  }
}
void Ultra_sensor()
{
  digitalWrite(US_trig,LOW);
  delay(3);
  digitalWrite(US_trig,HIGH);
  delay(10);
  digitalWrite(US_trig,LOW);
  duration = pulseIn(US_echo,HIGH);
  return;
}
void ALARM_ISR()
{
    message.data=0xFF;
    pub.publish(&message);
    message.data=0x00;
}

