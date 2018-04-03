#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Int8.h"
#include "cv_bridge/cv_bridge.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include<stdio.h>
#include<iostream>

using namespace cv;
using namespace std;

 
   void chatterCallback(const std_msgs::Int8::ConstPtr& num)
   {
     ROS_INFO("sum of dice: [%d]", num->data.);
   }
   
   int main(int argc, char **argv)
   {
   ros::init(argc, argv, "listener");
   ros::NodeHandle n;
   
Mat img,img2;
int i,j,A[7],a=0,c=0,num;
Mat im=imread("auv.jpg",1);
cvtColor(im,img,CV_BGR2GRAY);
Mat img1(im.rows,im.cols,CV_8UC1,Scalar(0));
Mat out(im.rows,im.cols,CV_8UC1,Scalar(0));

for(i=0;i<img.rows;i++)
    for(j=0;j<img.cols;j++)
 	{
		if(img.at<uchar>(i,j)>190)
			img1.at<uchar>(i,j)=255;
		else
			img1.at<uchar>(i,j)=0;
	}
vector<vector<Point> >contours;
vector<vector<Point> >cont;
vector<Vec4i> hierarchy;

Canny(img1,img2,50,75,5,4);

findContours(img2,contours,hierarchy,CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE,Point(0,0));

 
 
  for( int i = 0; i< contours.size(); i++ )
     {
    if((arcLength(contours[i],1)>=200)&&(arcLength(contours[i],1)<=2000))
      {
       cont.push_back(contours[i]);
       if(a>0)
        A[c++]=a;
       a=0;
           
       drawContours( im, contours,i,  Scalar(0,0,255), 2, 8, hierarchy, 0, Point() );
      
       i=i+1;
      }
      
    else if(arcLength(contours[i],1)<=200)
       if((contourArea(contours[i],0)>=250||contourArea(contours[i],0)<=-250))
       if(i!=27)
          {
    		a++;
    		Point2f center;
     		float radius;
     		minEnclosingCircle(contours[i],center,radius);
     		circle(im,center,cvRound(radius),Scalar(0,255,0),2);
   		i++;
          }
       
      }
       
       A[6]=a;
       
       for(i=0;i<7;i++)
       { 
         int m;
         for(m=0;m<7;m++)
             if(m!=i)
             if(A[m]==num->data-A[i])
              {
                cout<<i+1<<endl;
        	Point2f v[4];
        	RotatedRect box = minAreaRect(cont[i]);
       		box.points(v);
        	int j,k;
        	int xl=v[0].x,xh=v[0].x,yl=v[0].y,yh=v[0].y;
                for( j = 0; j < 4; j++ )
                   {
			if(v[j].x<xl)
				xl=v[j].x;
			if(v[j].x>xh)
				xh=v[j].x;
			if(v[j].y<yl)
				yl=v[j].y;
			if(v[j].y>yh)
				yh=v[j].y;
		   }
		for(j=yl;j<yh;j++)
		for(k=xl;k<xh;k++)
			out.at<uchar>(j,k)=img1.at<uchar>(j,k);

          
     	      }
       }
cout<<endl;
cout<<"over";
namedWindow("win",WINDOW_NORMAL);
imshow("win",im);
namedWindow("win2",WINDOW_NORMAL);
imshow("win2",out);
waitKey(0);

}
     ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);
   
     
     ros::spin();
   
     return 0;
   }

