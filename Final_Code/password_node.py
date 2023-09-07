#!/usr/bin/env python3
import rospy
from std_msgs.msg import Int16

def print_callback(msg):
    rospy.loginfo("Wrong Password Try Again")

if __name__ == '__main__':
    rospy.init_node("PassNode")
    rate = rospy.Rate(10)
    pup = rospy.Publisher("topic1", Int16 ,queue_size=10)
    sub = rospy.Subscriber("topic2", Int16 ,callback=print_callback)
    rospy.loginfo("Enter Password to open the door:")
    while not rospy.is_shutdown():
        pas = int(input())
        pup.publish(pas)
        rate.sleep()