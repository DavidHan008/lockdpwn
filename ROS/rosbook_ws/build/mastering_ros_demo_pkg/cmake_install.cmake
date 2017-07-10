# Install script for directory: /home/dyros-vehicle/gitrepo/lockdpwn/ROS/rosbook_ws/src/mastering_ros_demo_pkg

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/rosbook_ws/install")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/mastering_ros_demo_pkg/msg" TYPE FILE FILES "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/rosbook_ws/src/mastering_ros_demo_pkg/msg/demo_msg.msg")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/mastering_ros_demo_pkg/srv" TYPE FILE FILES "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/rosbook_ws/src/mastering_ros_demo_pkg/srv/demo_srv.srv")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/mastering_ros_demo_pkg/action" TYPE FILE FILES "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/rosbook_ws/src/mastering_ros_demo_pkg/action/Demo_action.action")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/mastering_ros_demo_pkg/msg" TYPE FILE FILES
    "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/rosbook_ws/devel/share/mastering_ros_demo_pkg/msg/Demo_actionAction.msg"
    "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/rosbook_ws/devel/share/mastering_ros_demo_pkg/msg/Demo_actionActionGoal.msg"
    "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/rosbook_ws/devel/share/mastering_ros_demo_pkg/msg/Demo_actionActionResult.msg"
    "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/rosbook_ws/devel/share/mastering_ros_demo_pkg/msg/Demo_actionActionFeedback.msg"
    "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/rosbook_ws/devel/share/mastering_ros_demo_pkg/msg/Demo_actionGoal.msg"
    "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/rosbook_ws/devel/share/mastering_ros_demo_pkg/msg/Demo_actionResult.msg"
    "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/rosbook_ws/devel/share/mastering_ros_demo_pkg/msg/Demo_actionFeedback.msg"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/mastering_ros_demo_pkg/cmake" TYPE FILE FILES "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/rosbook_ws/build/mastering_ros_demo_pkg/catkin_generated/installspace/mastering_ros_demo_pkg-msg-paths.cmake")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/rosbook_ws/devel/include/mastering_ros_demo_pkg")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/rosbook_ws/devel/share/roseus/ros/mastering_ros_demo_pkg")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/rosbook_ws/devel/share/common-lisp/ros/mastering_ros_demo_pkg")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  execute_process(COMMAND "/usr/bin/python" -m compileall "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/rosbook_ws/devel/lib/python2.7/dist-packages/mastering_ros_demo_pkg")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/rosbook_ws/devel/lib/python2.7/dist-packages/mastering_ros_demo_pkg")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/rosbook_ws/build/mastering_ros_demo_pkg/catkin_generated/installspace/mastering_ros_demo_pkg.pc")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/mastering_ros_demo_pkg/cmake" TYPE FILE FILES "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/rosbook_ws/build/mastering_ros_demo_pkg/catkin_generated/installspace/mastering_ros_demo_pkg-msg-extras.cmake")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/mastering_ros_demo_pkg/cmake" TYPE FILE FILES
    "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/rosbook_ws/build/mastering_ros_demo_pkg/catkin_generated/installspace/mastering_ros_demo_pkgConfig.cmake"
    "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/rosbook_ws/build/mastering_ros_demo_pkg/catkin_generated/installspace/mastering_ros_demo_pkgConfig-version.cmake"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/mastering_ros_demo_pkg" TYPE FILE FILES "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/rosbook_ws/src/mastering_ros_demo_pkg/package.xml")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

