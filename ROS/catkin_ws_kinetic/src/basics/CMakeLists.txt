cmake_minimum_required(VERSION 2.8.3)
project(basics)

find_package(catkin REQUIRED COMPONENTS
  rospy
  roscpp
  std_msgs
  message_generation
  actionlib_msgs
)

add_message_files(
	FILES
	Complex.msg
	)

add_service_files(
  FILES
  WordCount.srv
)

add_action_files(
	DIRECTORY action
	FILES
	Timer.action
)

generate_messages(
	DEPENDENCIES
	std_msgs 
		actionlib_msgs
	)

catkin_package(
	#	INCLUDE_DIRS include
	#LIBRARIES basics
	#CATKIN_DEPENDS rospy
	#DEPENDS system_lib
	CATKIN_DEPENDS message_runtime
	CATKIN_DEPENDS actionlib_msgs
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)
