cmake_minimum_required(VERSION 2.8.3)
project(rasp_odroid_py_test)

find_package(catkin REQUIRED COMPONENTS
  rospy
  std_msgs
)

catkin_package(
# INCLUDE_DIRS include
  LIBRARIES rasp_odroid_py_test
  CATKIN_DEPENDS rospy std_msgs
  DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(rasp_odroid_py_test_node src/rasp_odroid_py_test_node.py)

add_dependencies(rasp_odroid_py_test_node rasp_odroid_py_test_generate_messages_py)

target_link_libraries(rasp_odroid_py_test_node
${catkin_LIBRARIES}
 )


