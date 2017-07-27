cmake_minimum_required(VERSION 2.8.3)
project(dbw_mkz_parking_lot)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  geometry_msgs
)


catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)

