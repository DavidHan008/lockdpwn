# 운영체제에 설치된 cmake 최소 요구 버전
cmake_minimum_required(VERSION 2.8.3)

# 패키지 이름
project(first_ros)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)

catkin_package(
	#  INCLUDE_DIRS include
#  LIBRARIES my_first_ros_pkg
  CATKIN_DEPENDS roscpp std_msgs
  DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(rosTest_node src/rosTest_node.cpp)
add_dependencies(rosTest_node first_ros_generate_messages_cpp)

target_link_libraries(rosTest_node
   ${catkin_LIBRARIES}
)
