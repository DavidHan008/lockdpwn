cmake_minimum_required(VERSION 2.8.3)
project(my_first_ros_pkg)
find_package(catkin REQUIRED COMPONENTS roscpp std_msgs)

catkin_package(
	INCLUDE_DIRS include
	CATKIN_DEPENDS roscpp std_msgs
	DEPENDS system_lib
)

include_directories(${catkin_INCLUDE_DIRS})
add_executable(rosTest_node src/rosTest_node.cpp)
add_dependencies(rosTest_node my_first_ros_pkg_generate_messages_cpp)
target_link_libraries(rosTest_node ${catkin_LIBRARIES})
