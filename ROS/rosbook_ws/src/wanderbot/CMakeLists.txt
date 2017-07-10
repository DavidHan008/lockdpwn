cmake_minimum_required(VERSION 2.8.3)
project(wanderbot)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  rospy
  sensor_msgs
)

# add_message_files(
#   FILES
#   Message1.msg
#   Message2.msg
# )

# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

#generate_messages(
#  DEPENDENCIES
#  geometry_msgs   
#  sensor_msgs
#)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

