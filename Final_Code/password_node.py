#!/usr/bin/env python3
import rospy
from std_msgs.msg import Int16
from std_msgs.msg import String

def Password_state(msg):
    rospy.loginfo(msg)

if __name__ == '__main__':
    rospy.init_node("PassNode")             ##creating node
    rate = rospy.Rate(10)                   
    pup = rospy.Publisher("/password_to_arduino", Int16 ,queue_size=10)         ## publisher to send password to Arduino2
    sub = rospy.Subscriber("/wrongpassword", String ,callback=Password_state)   ## subscriber to get feedback from Arduino2
    rospy.loginfo("Enter Password to open the door:")
    
    
    while not rospy.is_shutdown():
        password = int(input())     ## taking password as integer 
        pup.publish(password)
        rate.sleep()