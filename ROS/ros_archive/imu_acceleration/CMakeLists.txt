cmake_minimum_required(VERSION 2.8.3)
project(imu_acceleration)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)

catkin_package(
  INCLUDE_DIRS include
  #  LIBRARIES imu_acceleration
  CATKIN_DEPENDS roscpp std_msgs
  DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(imu_acceleration_node src/imu_acceleration_node.cpp)
add_dependencies(imu_acceleration_node imu_acceleration_generate_messages_cpp)
target_link_libraries(imu_acceleration_node ${catkin_LIBRARIES})
