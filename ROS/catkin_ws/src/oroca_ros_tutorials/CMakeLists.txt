# 운영체제에 설치된 cmake의 최소 요구버전
cmake_minimum_required(VERSION 2.8.3)
# 패키지 이름
project(oroca_ros_tutorials)

# 캐킨 빌드 시 요구되는 구성요소 패키지들
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
)

# 노드에서 사용하는 메세제파일을 추가하는 옵션
add_message_files(FILES msgTutorial.msg)

# 의존하는 메세지를 설정하는 옵션
generate_messages(DEPENDENCIES std_msgs)

# 캐킨 빌드옵션
catkin_package(
#  INCLUDE_DIRS include
  LIBRARIES oroca_ros_tutorials
  CATKIN_DEPENDS roscpp std_msgs
  DEPENDS system_lib
)

# 인클루드 폴더 지정
include_directories(
  ${catkin_INCLUDE_DIRS}
)

# Publisher 옵션 
# 소스코드 파일 지정, 빌드 후 생성할 실행파일명 지정
add_executable(ros_tutorial_msg_publisher src/ros_tutorial_msg_publisher.cpp)
# 링크해야하는 라이브러리와 실행파일들을 지정
target_link_libraries(ros_tutorial_msg_publisher ${catkin_LIBRARIES})
add_dependencies(ros_tutorial_msg_publisher oroca_ros_tutorials_generate_messages_cpp)



# Subscirber 옵션
add_executable(ros_tutorial_msg_subscriber src/ros_tutorial_msg_subscriber.cpp)
target_link_libraries(ros_tutorial_msg_subscriber ${catkin_LIBRARIES})
add_dependencies(ros_tutorial_msg_subscriber oroca_ros_tutorials_generate_messages_cpp)
