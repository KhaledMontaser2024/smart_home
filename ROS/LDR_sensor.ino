#include <ros.h>
#include <std_msgs/Int32.h>  

ros::NodeHandle nh;

std_msgs::Int32 light_msg;  
ros::Publisher light_pub("/ldr_data", &light_msg);

#define LDR A0
int light;

void setup()
{
  nh.initNode();
  nh.advertise(light_pub);

  Serial.begin(9600);
}

void loop()
{
  light = analogRead(LDR);
  light_msg.data = light;
  light_pub.publish(&light_msg);
  nh.spinOnce();

  delay(1000);
}
