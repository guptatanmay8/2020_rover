#include<ros/ros.h>
#include<geometry_msgs/Pose.h>
#include<nav_msgs/Odometry.h>
#include<geometry_msgs/Twist.h>
#include<std_msgs/Float64.h>
#include<cmath>

float dest_x,dest_y,curr_pos_x,curr_pos_y;
geometry_msgs::Twist ans;
void dest_cb(geometry_msgs::Pose msg)
{
    dest_x=msg.position.x;
    dest_y=msg.position.y;
}

void curr_pos_cb(nav_msgs::Odometry msg)
{
    curr_pos_x= msg.pose.pose.position.x;
    curr_pos_y= msg.pose.pose.position.y;
}

int main(int argc , char** argv)
{
    ros::init(argc,argv,"reachdest");
    ros::NodeHandle nh;

    ros::Subscriber sub_dest = nh.subscribe("/rover/cmd_pose",10,dest_cb);
    ros::Subscriber sub_curr_pos = nh.subscribe("/rover/odom",10,curr_pos_cb);
    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("/rover/cmd_vel",10);

    ros::Rate loopRate(10);

    while(ros::ok)
    {
        ros::spinOnce();
        float dist,angle;
        // geometry_msgs::Twist ans
        dist = sqrt((dest_x-curr_pos_x)*(dest_x-curr_pos_x)+(dest_y-curr_pos_y)*(dest_y-curr_pos_y));
        angle = (atan(curr_pos_y/curr_pos_x)-atan(dest_y-curr_pos_y)/(dest_x-curr_pos_x))*180/(2*acos(0.0));
        ans.linear.x= 10*dist;
        ans.angular.z=angle;
        pub.publish(ans);
        loopRate.sleep();
    }

}