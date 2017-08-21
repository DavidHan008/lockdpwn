cmake_minimum_required(VERSION 2.8.3)
project(dyros_simulator)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  geometry_msgs
  dbw_mkz_msgs
)

catkin_package(
  #INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp std_msgs
  DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(veltest_ed src/veltest_ed.cpp)
target_link_libraries(veltest_ed ${catkin_LIBRARIES})
add_dependencies(veltest_ed veltest_ed_generate_messages_cpp)
