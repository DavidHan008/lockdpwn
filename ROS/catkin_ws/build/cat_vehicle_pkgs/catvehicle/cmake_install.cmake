# Install script for directory: /home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/src/cat_vehicle_pkgs/catvehicle

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/install")
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
  include("/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/build/cat_vehicle_pkgs/catvehicle/catkin_generated/safe_execute_install.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/build/cat_vehicle_pkgs/catvehicle/catkin_generated/installspace/catvehicle.pc")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/catvehicle/cmake" TYPE FILE FILES
    "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/build/cat_vehicle_pkgs/catvehicle/catkin_generated/installspace/catvehicleConfig.cmake"
    "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/build/cat_vehicle_pkgs/catvehicle/catkin_generated/installspace/catvehicleConfig-version.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/catvehicle" TYPE FILE FILES "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/src/cat_vehicle_pkgs/catvehicle/package.xml")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/catvehicle" TYPE DIRECTORY FILES "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/src/cat_vehicle_pkgs/catvehicle/launch")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/catvehicle" TYPE DIRECTORY FILES "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/src/cat_vehicle_pkgs/catvehicle/meshes")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/catvehicle" TYPE DIRECTORY FILES "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/src/cat_vehicle_pkgs/catvehicle/urdf")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/catvehicle" TYPE DIRECTORY FILES "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/src/cat_vehicle_pkgs/catvehicle/worlds")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcatvehiclegazebo.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcatvehiclegazebo.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcatvehiclegazebo.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/devel/lib/libcatvehiclegazebo.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcatvehiclegazebo.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcatvehiclegazebo.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcatvehiclegazebo.so"
         OLD_RPATH "/usr/lib/x86_64-linux-gnu/gazebo-2.2/plugins:/opt/ros/indigo/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcatvehiclegazebo.so")
    endif()
  endif()
endif()

