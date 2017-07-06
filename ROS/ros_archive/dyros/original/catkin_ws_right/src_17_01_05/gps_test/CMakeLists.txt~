cmake_minimum_required(VERSION 2.8.3)
project(gps_test)

find_package(catkin REQUIRED COMPONENTS roscpp std_msgs message_generation)
## 의존하는 메시지를 설정하는 옵션이다.
## std_msgs가 설치되어 있지 않다면 빌드 도중에 에러가 난다.
generate_messages(DEPENDENCIES std_msgs)
## 캐킨 패키지 옵션으로 라이브러리, 캐킨 빌드 의존성, 시스템 의존 패키지를 기술한다.

catkin_package(
#INCLUDE_DIRS include
LIBRARIES gps_test
CATKIN_DEPENDS roscpp std_msgs
DEPENDS system_lib
)

## 인클루드 디렉터리를 설정한다.
include_directories(include ${catkin_INCLUDE_DIRS})

## ros_tutorial_msg_publisher 노드에 대한 빌드 옵션이다.
## 실행 파일, 타겟 링크 라이브러리, 추가 의존성 등을 설정한다.
add_executable(gps_test_node src/gps_test_node.cpp src/gps_test.cpp)
target_link_libraries(gps_test_node ${catkin_LIBRARIES})
add_dependencies(gps_test_node gps_test_node_cpp)

