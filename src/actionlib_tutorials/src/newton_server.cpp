   #include <ros/ros.h>
   #include <actionlib/server/simple_action_server.h>
   #include <actionlib_tutorials/NewtonAction.h>
   #include <math.h>
    
   class NewtonAction
    {
    protected:
    
    ros::NodeHandle nh;
     actionlib::SimpleActionServer<actionlib_tutorials::NewtonAction> ns; // NodeHandle instance must be created before this line. Otherwise strange error occurs.
     std::string action_name;
     // create messages that are used to published feedback/result
     actionlib_tutorials::NewtonFeedback feedback;
     actionlib_tutorials::NewtonResult result;
   
   public:
   
     NewtonAction(std::string name) :
       ns(nh, name, boost::bind(&NewtonAction::executeCB, this, _1), false),
       action_name(name)
     {
       ns.start();
     }
   
     ~NewtonAction(void)
     {
     }
   
     void executeCB(const actionlib_tutorials::NewtonGoalConstPtr &goal)
     {
       // helper variables
       ros::Rate r(1);
       bool success = true;
   
       // push_back the seeds for the fibonacci sequence
       feedback.sequence.clear();
       feedback.sequence.push_back(1.0);
      // feedback.sequence.push_back(1);
   
       // publish info to the console for the user
       ROS_INFO("%s: Executing, Implementing Newton Raphson Method with initial value %i", action_name.c_str(), feedback.sequence[1]);
   
       // start executing the action
       for(int i=0; i<=goal->order; i++)
       {
         // check that preempt has not been requested by the client
         if (ns.isPreemptRequested() || !ros::ok())
         {
           ROS_INFO("%s: Preempted", action_name.c_str());
           // set the action state to preempted
           ns.setPreempted();
           success = false;
           break;
         }
         feedback.sequence.push_back((2*pow(feedback.sequence[i],3)+3)/(3*pow(feedback.sequence[i],2)+5));
         // publish the feedback
         ns.publishFeedback(feedback);
         // this sleep is not necessary, the sequence is computed at 1 Hz for denstration purposes
         r.sleep();
       }
   
       if(success)
       {
         result.sequence = feedback.sequence;
         ROS_INFO("%s: Succeeded", action_name.c_str());
         // set the action state to succeeded
         ns.setSucceeded(result);
       }
     }
   
   
   };
   
   
   int main(int argc, char** argv)
   {
     ros::init(argc, argv, "newton");
   
     NewtonAction newton("newton");
     ros::spin();
   
     return 0;
   }
