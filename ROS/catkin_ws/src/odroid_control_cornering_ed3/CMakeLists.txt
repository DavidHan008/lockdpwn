cmake_minimum_required(VERSION 2.8.3)
project(odroid_control_cornering_ed3)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)

catkin_package(
  INCLUDE_DIRS include
  #LIBRARIES odroid_control_cornering_ed3
  CATKIN_DEPENDS roscpp std_msgs
  DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(odroid_control_cornering_ed3_sub src/odroid_control_cornering_ed3_node.cpp)
target_link_libraries(odroid_control_cornering_ed3_sub ${catkin_LIBRARIES})
add_dependencies(odroid_control_cornering_ed3_sub odroid_control_cornering_ed3_generate_messages_cpp)

