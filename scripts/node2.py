#!/usr/bin/env python3
import rospy 
from std_msgs.msg import String
def msg (msg):
   rospy.loginfo(msg)

if __name__ == '__main__' :
    rospy.init_node("node2")
    sub = rospy.Subscriber("topic1",String, callback=msg)
   
    
    
    
    rospy.spin()