
//state definition
#define INIT 0
#define RUNNING 1
#define MAPPING 2
#define PATH_PLANNING 3
#define FINISH -1

#include <unistd.h>
#include <cmath>
#include <ros/ros.h>
#include <gazebo_msgs/SpawnModel.h>
#include <gazebo_msgs/SetModelState.h>
#include <gazebo_msgs/ModelStates.h>
#include <project3/purePursuit.h>
#include <project3/rrtTree.h>
#include <tf/transform_datatypes.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>

#include <cv_bridge/cv_bridge.h>//add
#include <opencv2/highgui/highgui.hpp>//add
#include <opencv2/imgproc/imgproc.hpp>//add

//map spec
cv::Mat map;
cv::Mat dynamic_map; //use this variable at dynamic mapping
double res;
int map_y_range;
int map_x_range;
double map_origin_x;
double map_origin_y;
double world_x_min;
double world_x_max;
double world_y_min;
double world_y_max;
bool popup_flag;    //add

//way points
std::vector<point> waypoints;

//path
std::vector<point> path_RRT;

//robot
point robot_pose;
geometry_msgs::Twist cmd_vel;

//point cloud data from kinect
pcl::PointCloud<pcl::PointXYZ> point_cloud;

//FSM state
int state;

//function definition
bool isCollision();
void dynamic_mapping();
void set_waypoints();
void generate_path_RRT();
//void generate_path_RRT(int flag);
void callback_state(gazebo_msgs::ModelStatesConstPtr msgs);
void callback_points(sensor_msgs::PointCloud2ConstPtr msgs);
void setcmdvel(double v, double w);
void kinect_callback(sensor_msgs::ImageConstPtr msgs);//add

int main(int argc, char** argv){
  ros::init(argc, argv, "rrt_main");
  ros::NodeHandle n;

  // Initialize topics
  ros::Subscriber gazebo_pose_sub = n.subscribe("/gazebo/model_states",1,callback_state);
  ros::Subscriber gazebo_kinect_sub = n.subscribe("/camera/depth/points",1,callback_points);

  ros::Publisher cmd_vel_pub = n.advertise<geometry_msgs::Twist>("/RosAria/cmd_vel",1);

  // ed: 모델을 가제보상에 불러올 수 있게 해주는 서비스인듯하다
  ros::ServiceClient gazebo_spawn = n.serviceClient<gazebo_msgs::SpawnModel>("/gazebo/spawn_urdf_model");
  ros::ServiceClient gazebo_set = n.serviceClient<gazebo_msgs::SetModelState>("/gazebo/set_model_state");
  printf("Initialize topics\n");

  // Load Map
  char* user = getlogin();

  // ed: 맵파일 경로 코드 수정했다
  map = cv::imread((std::string("/home/dyros-vehicle/gitrepo/lockdpwn/ROS")+
                    // std::string(user)+
                    std::string("/catkin_ws/src/project3/src/ground_truth_map.pgm")).c_str(), CV_LOAD_IMAGE_GRAYSCALE);
  dynamic_map = map.clone();
  map_y_range = map.cols;
  map_x_range = map.rows;
  map_origin_x = map_x_range/2.0 - 0.5;
  map_origin_y = map_y_range/2.0 - 0.5;
  world_x_min = -10.0;
  world_x_max = 10.0;
  world_y_min = -10.0;
  world_y_max = 10.0;
  res = 0.05;
  printf("Load map\n");

  // Set Way Points
  set_waypoints();
  printf("Set way points\n");

  // RRT
  generate_path_RRT();
  printf("Generate RRT\n");


  // FSM
  state = INIT;

  bool running = true;
  purePursuit pure_pursuit;
  int look_ahead_idx;
  ros::Rate control_rate(10);


  while(running){
    switch (state) {
      case INIT: {
        look_ahead_idx = 0;

        //visualize path
        for(int i = 0; i < path_RRT.size(); i++){
          gazebo_msgs::SpawnModel model;

          // ed: gazebo에 파란색 공이 추가되는 코드
          model.request.model_xml = std::string("<robot name=\"simple_ball\">") +
                                    std::string("<link name=\"ball\">") +
                                    std::string("<inertial>") +
                                    std::string("<mass value=\"1.0\" />") +
                                    std::string("<origin xyz=\"0 0 0\" />") +
                                    std::string("<inertia  ixx=\"1.0\" ixy=\"0.0\"  ixz=\"0.0\"  iyy=\"1.0\"  iyz=\"0.0\"  izz=\"1.0\" />") +
                                    std::string("</inertial>") +
                                    std::string("<visual>") +
                                    std::string("<origin xyz=\"0 0 0\" rpy=\"0 0 0\" />") +
                                    std::string("<geometry>") +
                                    std::string("<sphere radius=\"0.09\"/>") +
                                    std::string("</geometry>") +
                                    std::string("</visual>") +
                                    std::string("<collision>") +
                                    std::string("<origin xyz=\"0 0 0\" rpy=\"0 0 0\" />") +
                                    std::string("<geometry>") +
                                    std::string("<sphere radius=\"0\"/>") +
                                    std::string("</geometry>") +
                                    std::string("</collision>") +
                                    std::string("</link>") +
                                    std::string("<gazebo reference=\"ball\">") +
                                    std::string("<mu1>10</mu1>") +
                                    std::string("<mu2>10</mu2>") +
                                    std::string("<material>Gazebo/Blue</material>") +
                                    std::string("<turnGravityOff>true</turnGravityOff>") +
                                    std::string("</gazebo>") +
                                    std::string("</robot>");

          std::ostringstream ball_name;
          ball_name << i;
          model.request.model_name = ball_name.str();
          model.request.reference_frame = "world";
          model.request.initial_pose.position.x = path_RRT[i].x;
          model.request.initial_pose.position.y = path_RRT[i].y;
          model.request.initial_pose.position.z = 0.7;
          model.request.initial_pose.orientation.w = 0.0;
          model.request.initial_pose.orientation.x = 0.0;
          model.request.initial_pose.orientation.y = 0.0;
          model.request.initial_pose.orientation.z = 0.0;

          // ed: 파란색 공을 가제보상에서 생성한다
          gazebo_spawn.call(model);

          ros::spinOnce();
          //ros::Rate(1000).sleep();
        }
        printf("Spawn path\n");

        //initialize robot position
        geometry_msgs::Pose model_pose;

        // ed: 초기에 로봇은 웨이포인트[0]에 위치하게 된다
        model_pose.position.x = waypoints[0].x;
        model_pose.position.y = waypoints[0].y;
        model_pose.position.z = 0.3;
        model_pose.orientation.x = 0.0;
        model_pose.orientation.y = 0.0;
        model_pose.orientation.z = 0.0;
        model_pose.orientation.w = 0.0;

        geometry_msgs::Twist model_twist;
        model_twist.linear.x = 0.0;
        model_twist.linear.y = 0.0;
        model_twist.linear.z = 0.0;
        model_twist.angular.x = 0.0;
        model_twist.angular.y = 0.0;
        model_twist.angular.z = 0.0;

        gazebo_msgs::ModelState modelstate;
        modelstate.model_name = "RosAria";
        modelstate.reference_frame = "world";
        modelstate.pose = model_pose;
        modelstate.twist = model_twist;

        gazebo_msgs::SetModelState setmodelstate;
        setmodelstate.request.model_state = modelstate;

        // ed: 로봇의 초기 상태를 설정한다
        gazebo_set.call(setmodelstate);
        ros::spinOnce();
        ros::Rate(0.33).sleep();
        printf("Initialize ROBOT\n");

        state = RUNNING;
      } break;

      case RUNNING: {
        //TODO
        /*
         * 1. make control fallowing point in the variable "path_RRT"
         *		use function setcmdvel(double v, double w) which set cmd_vel as desired input value.
         * 2. publish
         * 3. check distance between robot and current pursuit point
         * 4. if distance is less than 0.2 ( update pursuit point )
         *      look_ahead_idx++
         * 5. if robot reach the goal (state transition)
         *      finish RUNNING ( state = FINISH )
         */

        control ctrl;
        ctrl = pure_pursuit.get_control(robot_pose, path_RRT[look_ahead_idx]);

        // ed: 아래 두줄을 통해 로봇이 움직인다
        setcmdvel(ctrl.v, ctrl.w);
        cmd_vel_pub.publish(cmd_vel);

        double dt = 0.001;
        if(isCollision()) {

          dynamic_map = map.clone();
          std::cout << "Obstacle detected" << std::endl;
          for(double i = cmd_vel.linear.x/2 ; i >= 0 ; i-=0.1 )
          {
            setcmdvel(i, 0);
            cmd_vel_pub.publish(cmd_vel);
            std::cout << "back : " << cmd_vel.linear.x << std::endl;
            ros::Rate(0.9).sleep();
          }
          setcmdvel(0, 0);
          cmd_vel_pub.publish(cmd_vel);
          ros::Rate(0.5).sleep();
          state = PATH_PLANNING;
          break;
        }

        double dist = sqrt((pow((robot_pose.x - path_RRT[look_ahead_idx].x),2))
                           +(pow((robot_pose.y - path_RRT[look_ahead_idx].y),2)));


        // ed: 파란색 공과 로봇의 위치가 0.2m 이하로 가까워지면 다음 웨이포인트로 이동한다
        if(dist < 0.2)
          look_ahead_idx += 1;
        std::cout << "look_ahead_idx : " << look_ahead_idx << std::endl;


        if(look_ahead_idx == path_RRT.size())
        {
          state = FINISH;
          std::cout
              <<"----------------------------------" << std::endl
              <<"--------------FINISH--------------" << std::endl
              <<"----------------------------------" << std::endl << std::endl;

          break;
        }

        ros::spinOnce();
        control_rate.sleep();
      } break;
	
      case MAPPING: {

      } break;

      case PATH_PLANNING: {
        //dynamic_mapping();
        //cv::namedWindow("Dynamic Mapping");
        //cv::imshow("Dynamic Mapping", dynamic_map);
        //cv::waitKey(1);
        /////////////////////////////////////////////////////////////////////////////////////////////////////////

        setcmdvel(-0.1, 0);
        std::cout << "back : " << cmd_vel.linear.x << std::endl;
        cmd_vel_pub.publish(cmd_vel);
        ros::Rate(0.3).sleep();
        setcmdvel(0.0, 0);
        std::cout << "stop : " << cmd_vel.linear.x << std::endl;
        cmd_vel_pub.publish(cmd_vel);
        ros::Rate(0.3).sleep();

        dynamic_mapping();
        cv::namedWindow("Dynamic Mapping");
        cv::imshow("Dynamic Mapping", dynamic_map);
        cv::waitKey(1);
        cv::namedWindow("Dynamic Mapping");
        cv::imshow("Dynamic Mapping", dynamic_map);
        cv::waitKey(1);

        while(1);
        /////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*
          int tmp_idx = 0;
          int min_it = 399;
          double max_step = 0.9;
          double Radius = max_step*2.5;
          int margin = 9;
          std::vector<point> tmp_RRT;

          int gen_pt = 0;
          rrtTree rrtst_(robot_pose, path_RRT[++look_ahead_idx], dynamic_map, map_origin_x, map_origin_y, res, margin);
          while(1)
          {

          setcmdvel(0, 0);
          cmd_vel_pub.publish(cmd_vel);

          printf("New path generated\n");

          if (gen_pt != 0)
          break;
          gen_pt = rrtst_.generateRRTst(world_x_max, world_x_min, world_y_max, world_y_min, min_it, max_step, Radius);
          }
          tmp_RRT = rrtst_.backtracking();

          while(1)
          {
          if(look_ahead_idx == tmp_idx)
          break;

          control ctrl;
          ctrl = pure_pursuit.get_control(robot_pose, tmp_RRT[tmp_idx]);

          setcmdvel(ctrl.v, ctrl.w);
          cmd_vel_pub.publish(cmd_vel);

          double dist = sqrt((pow((robot_pose.x - tmp_RRT[tmp_idx].x),2))
          +(pow((robot_pose.y - tmp_RRT[tmp_idx].y),2)));
          if(dist < 0.2)
          tmp_idx += 1;
          std::cout << "tmp_idx : " << tmp_idx << std::endl;
          }

          setcmdvel(0, 0);
          cmd_vel_pub.publish(cmd_vel);
          /////////////////////////////////////////////////////////////////////////////////////////////////////////

          state = RUNNING;
        */
      } break;

      case FINISH: {
        setcmdvel(0, 0);
        cmd_vel_pub.publish(cmd_vel);
        running = false;

        ros::spinOnce();
        control_rate.sleep();
      } break;

      default: {
      } break;
    }

    printf("curr state : %d\ncurr robot pos : %.2f,%.2f\ncurr path pos : %.2f,%.2f\ncurr robot vel : %.2f,%.2f\n"
           ,state
           ,robot_pose.x
           ,robot_pose.y
           ,path_RRT[look_ahead_idx].x
           ,path_RRT[look_ahead_idx].y
           ,cmd_vel.linear.x
           ,cmd_vel.angular.z);
  }

  return 0;


}

// ed: RRT 경로를 생성하는 함수
void generate_path_RRT(){
  //TODO
  /*
   * copy your code from previous project2
   * change method to rrt*
   */
  ////////////////////////////////////////////////////////////////////////////////////
  //    RRT
  ////////////////////////////////////////////////////////////////////////////////////
  //copy your code from previous project2
  //TODO
  /*
   * 1. for loop
   * 2.  call RRT generate function in order to make a path which connects i way point to i+1 way point.
   * 3.  store path to variable "path_RRT"
   * 4.  when you store path, you have to reverse the order of points in the generated path
   *      since BACKTRACKING makes a path in a reverse order (goal -> start).
   * 5. end
   */
  /*
    int min_it = 1;
    double max_step = 1.7;
    std::vector<point> tmp_RRT;
    //K : minimum iteration number.
    //MaxStep : maximum distance from x_near to x_new.

    ////
    //// 0->1
    ////
    int gen_pt = 0;
    rrtTree rrt(waypoints[0], waypoints[1], map, map_origin_x, map_origin_y, res, 0.1);
    while(1)
    {
    if (gen_pt != 0)
    break;
    gen_pt = rrt.generateRRT(world_x_max, world_x_min, world_y_max, world_y_min, min_it, max_step);
    }

    tmp_RRT = rrt.backtracking();
    for(int i = 0; i < tmp_RRT.size() ; i++)
    {
    path_RRT.push_back(tmp_RRT[i]);
    //std::cout <<"[" << i << "] "<< "X : " << path_RRT[i].x << ", Y : " << path_RRT[i].y << std::endl;
    }//std::cout << " tmp_RRT.size() : " << tmp_RRT.size() << std::endl;

    ////
    //// 1->2
    ////
    gen_pt = 0;
    rrtTree rrt1(waypoints[1], waypoints[2], map, map_origin_x, map_origin_y, res, 0.5);
    while(1)
    {
    if (gen_pt != 0)
    break;
    gen_pt = rrt1.generateRRT(world_x_max, world_x_min, world_y_max, world_y_min, min_it, max_step);
    }

    tmp_RRT = rrt1.backtracking();
    for(int i = 0; i < tmp_RRT.size() ; i++)
    {
    path_RRT.push_back(tmp_RRT[i]);
    //std::cout <<"[" << i << "] "<< "X : " << path_RRT[i].x << ", Y : " << path_RRT[i].y << std::endl;
    }//std::cout << " tmp_RRT.size() : " << tmp_RRT.size() << std::endl;

    ////
    //// 0->1
    ////
    gen_pt = 0;
    rrtTree rrt2(waypoints[2], waypoints[3], map, map_origin_x, map_origin_y, res, 0.5);
    while(1)
    {
    if (gen_pt != 0)
    break;
    gen_pt = rrt2.generateRRT(world_x_max, world_x_min, world_y_max, world_y_min, min_it, max_step);
    }
    tmp_RRT = rrt2.backtracking();
    for(int i = 0; i < tmp_RRT.size() ; i++)
    {
    path_RRT.push_back(tmp_RRT[i]);
    //std::cout <<"[" << i << "] "<< "X : " << path_RRT[i].x << ", Y : " << path_RRT[i].y << std::endl;
    }//std::cout << " tmp_RRT.size() : " << tmp_RRT.size() << std::endl;

    std::cout << " path_RRT.size() : " << path_RRT.size() << std::endl;
    for(int i = 0; i < path_RRT.size() ; i++)
    std::cout <<"[" << i << "] "<< "X : " << path_RRT[i].x << ", Y : " << path_RRT[i].y << std::endl;
  */
  ////////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////////
  //    RRT star
  ////////////////////////////////////////////////////////////////////////////////////

  int min_it = 999;
  double max_step = 1.9;
  double Radius = max_step*2.5;
  int margin = 15;
  std::vector<point> tmp_RRT;
  //K : minimum iteration number.
  //MaxStep : maximum distance from x_near to x_new.

  ////
  //// 0->1
  ////
  int gen_pt = 0;
  rrtTree rrtst(waypoints[0], waypoints[1], map, map_origin_x, map_origin_y, res, margin);
  while(1)
  {
    if (gen_pt != 0)
      break;
    gen_pt = rrtst.generateRRTst(world_x_max, world_x_min, world_y_max, world_y_min, min_it, max_step, Radius);
  }
  tmp_RRT = rrtst.backtracking();
  for(int i = 0; i < tmp_RRT.size() ; i++)
  {
    path_RRT.push_back(tmp_RRT[i]);
    //std::cout <<"[" << i << "] "<< "X : " << path_RRT[i].x << ", Y : " << path_RRT[i].y << std::endl;
  }//std::cout << " tmp_RRT.size() : " << tmp_RRT.size() << std::endl;

  ////
  //// 1->2
  ////
  gen_pt = 0;
  rrtTree rrtst1(waypoints[1], waypoints[2], map, map_origin_x, map_origin_y, res, margin);
  while(1)
  {
    if (gen_pt != 0)
      break;
    gen_pt = rrtst1.generateRRTst(world_x_max, world_x_min, world_y_max, world_y_min, min_it, max_step, Radius);
  }

  tmp_RRT = rrtst1.backtracking();
  for(int i = 0; i < tmp_RRT.size() ; i++)
  {
    path_RRT.push_back(tmp_RRT[i]);
    //std::cout <<"[" << i << "] "<< "X : " << path_RRT[i].x << ", Y : " << path_RRT[i].y << std::endl;
  }//std::cout << " tmp_RRT.size() : " << tmp_RRT.size() << std::endl;

  ////
  //// 0->1
  ////
  gen_pt = 0;
  rrtTree rrtst2(waypoints[2], waypoints[3], map, map_origin_x, map_origin_y, res, margin);
  while(1) {
    if (gen_pt != 0)
      break;
    gen_pt = rrtst2.generateRRTst(world_x_max, world_x_min, world_y_max, world_y_min, min_it, max_step, Radius);
  }
  tmp_RRT = rrtst2.backtracking();
  for(int i = 0; i < tmp_RRT.size() ; i++)
  {
    path_RRT.push_back(tmp_RRT[i]);
    //std::cout <<"[" << i << "] "<< "X : " << path_RRT[i].x << ", Y : " << path_RRT[i].y << std::endl;
  }//std::cout << " tmp_RRT.size() : " << tmp_RRT.size() << std::endl;

  std::cout << " path_RRT.size() : " << path_RRT.size() << std::endl;
  for(int i = 0; i < path_RRT.size() ; i++)
    std::cout <<"[" << i << "] "<< "X : " << path_RRT[i].x << ", Y : " << path_RRT[i].y << std::endl;
  ////////////////////////////////////////////////////////////////////////////////////

}

// ed: map에서 특정 공간의 좌표를 웨이포인트로 설정하는 함수
void set_waypoints(){
  point waypoint_candid[4];
  waypoint_candid[0].x = 5.0;    waypoint_candid[0].y = -8.0;
  waypoint_candid[1].x = -6.0;    waypoint_candid[1].y = -7.0;
  waypoint_candid[2].x = -8.0;    waypoint_candid[2].y = 8.0;
  waypoint_candid[3].x = 3.0;    waypoint_candid[3].y = 7.0;

  int order[] = {3,1,2,3};
  int order_size = 4;

  for(int i = 0; i < order_size; i++){
    waypoints.push_back(waypoint_candid[order[i]]);
  }
}

// ed: /gazebo/model_state에 대한 섭스크라이브 콜백함수
void callback_state(gazebo_msgs::ModelStatesConstPtr msgs){

  for(int i; i < msgs->name.size(); i++){
    if(std::strcmp(msgs->name[i].c_str(),"RosAria") == 0){

      // ed: 여기서 로봇의 위치값을 받아온다
      robot_pose.x = msgs->pose[i].position.x;
      robot_pose.y = msgs->pose[i].position.y;
      robot_pose.th = tf::getYaw(msgs->pose[i].orientation);
    }
  }
}

void callback_points(sensor_msgs::PointCloud2ConstPtr msgs){
  pcl::fromROSMsg(*msgs,point_cloud);
}

void kinect_callback(sensor_msgs::ImageConstPtr msgs){
  if (popup_flag)
  {
    cv::imshow("kinect",cv_bridge::toCvCopy(msgs)->image);
    cv::waitKey(1);
  }
}

bool isCollision()
{
  bool result = false;
  int count = 0;

  for (int i = 0; i < point_cloud.size(); i ++) {
    if (point_cloud[i].z < 0.9 && point_cloud[i].y > -0.3 && point_cloud[i].y < -0.1
        && point_cloud[i].y > 0.1 && point_cloud[i].y < 0.3)
    {
      count++;
      if (count > 7000) {
        result = true;
      }
    }
  }

  /*
    for (int i = 0; i < point_cloud.size(); i += 2) {
    if (point_cloud[i].z < 0.6 && point_cloud[i].y > -0.3 && point_cloud[i].y < -0.1
    ){//&& point_cloud[i].y < 0.3 && point_cloud[i].y > 0.1) {
    count++;
    if (count > 3500) {
    result = true;
    }
    }
    }
  */
  return result;
}


void dynamic_mapping()
{

  point_3D *point_array = new point_3D[point_cloud.size()];
  point_3D *temp_array  = new point_3D[point_cloud.size()];

  // Kinect frame -> Robot frame
  for (int i = 0; i < point_cloud.size(); i++) {
    temp_array[i].x = point_cloud[i].z;
    temp_array[i].y = (-point_cloud[i].x);
    temp_array[i].z = (-point_cloud[i].y);

  }
  /*
    for (int i = 0; i < point_cloud.size(); i++) {
    if (point_cloud[i].z <= 0.7 && point_cloud[i].y >= -0.3 && point_cloud[i].y <= -0.1)
    {
    temp_array[i].x =  point_cloud[i].z;
    temp_array[i].y = -point_cloud[i].x;
    temp_array[i].z = -point_cloud[i].y;
    }

    }
  */
  for (int i = 0; i < point_cloud.size(); i++) {
    point_array[i].x =  temp_array[i].x;
    point_array[i].y =  temp_array[i].y;
    point_array[i].z =  temp_array[i].z;
  }

  // Robot frame -> World frame
  for (int i = 0; i < point_cloud.size(); i++) {
    temp_array[i].x = robot_pose.x + cos(robot_pose.th) * point_array[i].x
                      - sin(robot_pose.th) * point_array[i].y;
    temp_array[i].y = robot_pose.y + sin(robot_pose.th) * point_array[i].x
                      + cos(robot_pose.th) * point_array[i].y;
  }

  for (int i = 0; i < point_cloud.size(); i++) {
    point_array[i].x = temp_array[i].x;
    point_array[i].y = temp_array[i].y;
  }

  // World frame -> Grid map frame
  int *x = new int [point_cloud.size()]; // Row pixel location of the dynamic map image
  int *y = new int [point_cloud.size()]; // Column pixel location of the dynamic map image

  // Type cast from double to int, always round down
  for (int i = 0; i < point_cloud.size(); i++) {
    x[i] = (int)(point_array[i].x/res + map_origin_x); //T.A add!
    y[i] = (int)(point_array[i].y/res + map_origin_y);
  }

  // Draw obstacles on dynamic_map
  int xSize = dynamic_map.rows;
  int ySize = dynamic_map.cols;
  for (int i = 0; i < point_cloud.size(); i++) {
    if (x[i] < xSize && y[i] < ySize && x[i] > 0 && y[i] > 0) {
      dynamic_map.at<uchar>(x[i], y[i]) = 0;
    }
  }

  delete[] point_array;
  delete[] temp_array;
  delete[] x;
  delete[] y;
}

void setcmdvel(double v, double w){
  cmd_vel.linear.x = v;
  cmd_vel.linear.y = 0.0;
  cmd_vel.linear.z = 0.0;
  cmd_vel.angular.x = 0.0;
  cmd_vel.angular.y = 0.0;
  cmd_vel.angular.z = w;
}
