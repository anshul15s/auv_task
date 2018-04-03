   #include "ros/ros.h"
   #include "std_msgs/String.h"
   #include "std_msgs/Int8.h"
   
   #include <sstream>
   #include <iostream>
   
  
   int main(int argc, char **argv)
   {
  
     ros::init(argc, argv, "talker");
   
    
     ros::NodeHandle n;
   
   
     ros::Publisher chatter_pub = n.advertise<std_msgs::Int8>("chatter", 1000);
   
     ros::Rate loop_rate(10);
  
     int count = 0;
     while (ros::ok())
     {
  
       std_msgs::String msg;
       std_msgs::Int8 num;
       int a;
       std::cin>>a;
       num.data=a;
       std::stringstream ss;
       ss << "sum of dice :" << a;
       msg.data = ss.str();
   
       ROS_INFO("%s", msg.data.c_str());
       ROS_INFO("%d", num.data);
     
      chatter_pub.publish(num);
  
      ros::spinOnce();
  
      loop_rate.sleep();
     
    }
  
  
    return 0;
  }

