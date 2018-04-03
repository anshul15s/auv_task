# auv_task
This is the repository to the auv tasks.

TASK1 - beginner_tutorials

TASK2 - actionlib_tutorials

steps to run task 1

In a new terminal

cd catkin-ws
rosrun beginner_tutorials talker
// here you can give the sum of two dices

on a new terminal 

cd catkin_ws
rosrun beginner_tutorials listener
// Here you can see the output

Steps to run task 2

In a new terminal run 
cd catkin-ws
rosrun actiolib_tutorials newton_server

open a new terminal and run
cd catkin_ws
rosrun actionlib_tutorials newton_client

And on a third terminal see the output by running
cd catkin_ws
rostopic echo /newton/feedback
