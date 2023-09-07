#include <ros.h>
#include <std_msgs/Char.h>  

#define trig 6 
#define echo 2
#define GAS_Sensor 3
#define LDR A0

ros::NodeHandle nh;
std_msgs::Char msgg;  
ros::Publisher pub("chatter", &msgg);
bool flag = 0; 

int light;
float distance = 0 ; 
float duration =0 ;
bool state ;


void SetBit(char bt)
{
  msgg.data |= (1<<bt); 

}
void ClearBit(char bt)
{
  msgg.data &= ~(1<<bt); 

}



void LDR_sensor(int light)
{
    if (light > 50 && flag == 0)
    {
      SetBit(1);
      flag = 1;
    }
    else if (light < 50 && flag == 1)
    {
      ClearBit(1);
      flag = 0;
    }
}


void changestate ()
{  
    distance = duration / 57 ;//57 = 1/(speed of air in specific conditions(cm\ms)/2)
    if (distance <= 5 )
    {
      SetBit(0);
    }
    else 
    {
      ClearBit(0);
    
    }
}

void Ultra_sensor()
{
  digitalWrite(trig,LOW);
  delay(3);
  digitalWrite(trig,HIGH);
  delay(10);
  digitalWrite(trig,LOW);
  duration = pulseIn(echo,HIGH);
}

void ALARM_ISR()
{
    msgg.data=0xFF;
    pub.publish(&msgg);
}


void setup() 
{
  nh.initNode();
  nh.advertise(pub);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(GAS_Sensor, INPUT);
  attachInterrupt(digitalPinToInterrupt(echo), changestate  , FALLING);
  attachInterrupt(digitalPinToInterrupt(GAS_Sensor), ALARM_ISR, FALLING);

}



void loop() {
  Ultra_sensor();
  light = analogRead(LDR);
  LDR_sensor( light);
  pub.publish(&msgg);
  msgg.data=0;
  nh.spinOnce();
  delay(500);
}