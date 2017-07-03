# Install script for directory: /root/gitrepo/lockdpwn/ROS/catkin_ws_indigo/src/myahrs_driver_ed

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/root/gitrepo/lockdpwn/ROS/catkin_ws_indigo/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/root/gitrepo/lockdpwn/ROS/catkin_ws_indigo/build/myahrs_driver_ed/catkin_generated/installspace/myahrs_driver_ed.pc")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/myahrs_driver_ed/cmake" TYPE FILE FILES
    "/root/gitrepo/lockdpwn/ROS/catkin_ws_indigo/build/myahrs_driver_ed/catkin_generated/installspace/myahrs_driver_edConfig.cmake"
    "/root/gitrepo/lockdpwn/ROS/catkin_ws_indigo/build/myahrs_driver_ed/catkin_generated/installspace/myahrs_driver_edConfig-version.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/myahrs_driver_ed" TYPE FILE FILES "/root/gitrepo/lockdpwn/ROS/catkin_ws_indigo/src/myahrs_driver_ed/package.xml")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/myahrs_driver_ed/myahrs_driver_ed" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/myahrs_driver_ed/myahrs_driver_ed")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/myahrs_driver_ed/myahrs_driver_ed"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/myahrs_driver_ed" TYPE EXECUTABLE FILES "/root/gitrepo/lockdpwn/ROS/catkin_ws_indigo/devel/lib/myahrs_driver_ed/myahrs_driver_ed")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/myahrs_driver_ed/myahrs_driver_ed" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/myahrs_driver_ed/myahrs_driver_ed")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/myahrs_driver_ed/myahrs_driver_ed"
         OLD_RPATH "/opt/ros/kinetic/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/myahrs_driver_ed/myahrs_driver_ed")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/myahrs_driver_ed" TYPE DIRECTORY FILES "/root/gitrepo/lockdpwn/ROS/catkin_ws_indigo/src/myahrs_driver_ed/include/myahrs_driver_ed/" FILES_MATCHING REGEX "/[^/]*\\.h$" REGEX "/[^/]*\\.hpp$")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/myahrs_driver_ed" TYPE FILE FILES
    "/root/gitrepo/lockdpwn/ROS/catkin_ws_indigo/src/myahrs_driver_ed/rviz_cfg/imu_test.rviz"
    "/root/gitrepo/lockdpwn/ROS/catkin_ws_indigo/src/myahrs_driver_ed/launch/myahrs_driver_ed.launch"
    )
endif()

