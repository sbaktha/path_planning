#include "ros/ros.h"
#include "geometry_msgs/PointStamped.h"
#include "geometry_msgs/PoseStamped.h"
class GoalShifter
{
public:
  GoalShifter()
  {
    pub_ = nh_.advertise<geometry_msgs::PointStamped>("/clicked_point_with_elevation", 10);
    //sub_ = nh_.subscribe("/clicked_point", 1, &GoalShifter::callback, this);
    sub_ = nh_.subscribe("/move_base_simple/goal", 1, &GoalShifter::callback, this);
  }
//void callback(const geometry_msgs::PointStamped::ConstPtr & msg)
  void callback(const geometry_msgs::PoseStamped::ConstPtr & msg)
  {
    geometry_msgs::PointStamped elevated_goal;
    //geometry_msgs::PointStamped current_goal;
    geometry_msgs::PoseStamped current_goal;
    current_goal = *msg;
    elevated_goal.point.x = current_goal.pose.position.x;
    elevated_goal.point.y = current_goal.pose.position.y;
    elevated_goal.point.z = current_goal.pose.position.z + 2.0;
    elevated_goal.header = current_goal.header;
    pub_.publish(elevated_goal);
  }

private:
  ros::NodeHandle nh_;
  ros::Publisher pub_;
  ros::Subscriber sub_;
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "Goal Shifter");

  GoalShifter shifted_goal_object;
  ros::spin();

  return 0;
}
