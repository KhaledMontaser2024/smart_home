#!/usr/bin/env python3
import rospy
from std_msgs.msg import String
if __name__ == '__main__' :
    rospy.init_node("node1")
    pub =rospy.Publisher("topic1",String,queue_size=10)
    
    rate = rospy.Rate(5)
    
    while not rospy.is_shutdown() :
        password = String()
        password = input()
        pub.publish(password)
        rate.sleep()