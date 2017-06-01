cmake_minimum_required(VERSION 2.8.3)
project(arduino_test)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)

catkin_package(
  INCLUDE_DIRS include
  #LIBRARIES arduino_test
  CATKIN_DEPENDS roscpp std_msgs
  DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(arduino_test_sub src/arduino_test_subscriber.cpp)
target_link_libraries(arduino_test_sub ${catkin_LIBRARIES})
add_dependencies(arduino_test_sub arduino_test_generate_messages_cpp)

