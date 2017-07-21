cmake_minimum_required(VERSION 2.8.3)
project(all_in_one)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  cmake_modules
  message_generation
  geometry_msgs
  rospy
  sensor_msgs
  gazebo_msgs
  velodyne_pointcloud
)
find_package(Eigen REQUIRED)

## System dependencies are found with CMake's conventions
find_package(Boost REQUIRED COMPONENTS system)

##################################### QT ##########################################
find_package(Qt4 REQUIRED COMPONENTS QtCore QtGui)

include(${QT_USE_FILE})

# add_service_files(
#   DIRECTORY srv
#   FILES
#   srvHeightMap.srv
#   srvParkingCmd.srv
# )

# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

#generate_messages(
#  DEPENDENCIES
#  std_msgs
#)

catkin_package(
  INCLUDE_DIRS inc
#  LIBRARIES lib
  CATKIN_DEPENDS geometry_msgs roscpp rospy sensor_msgs std_msgs velodyne_pointcloud tf
  DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${Eigen_INCLUDE_DIRS}
)

include (FindPkgConfig)
if (PKG_CONFIG_FOUND)
  pkg_check_modules(GAZEBO gazebo)
endif()
include_directories(${GAZEBO_INCLUDE_DIRS}
# ${catkin_INCLUDE_DIRS}
                   )

link_directories(${GAZEBO_LIBRARY_DIRS})
include_directories(include)



######################## test_ui_node #################################
set( HDR_FILES_QT_UI_NODE inc/all_in_one_main.h inc/CatmullRomSpline.h ${HDR_NABO_FILES} )
set( SRC_FILES_QT_UI_NODE src/all_in_one_main.cpp  ${MOC_FILES} ${SRC_NABO_FILES})
set( FORM_FILES_QT_UI_NODE ui/all_in_one_gui.ui)

QT4_WRAP_CPP(MOC_SRC_H_QT_UI_NODE ${HDR_FILES_QT_UI_NODE})
QT4_WRAP_UI(MOC_GUI_H_QT_UI_NODE ${FORM_FILES_QT_UI_NODE})

add_executable(all_in_one ${SRC_FILES_QT_UI_NODE} ${HDR_FILES_QT_UI_NODE} ${MOC_SRC_H_QT_UI_NODE} ${MOC_GUI_H_QT_UI_NODE})

target_link_libraries(
    all_in_one
   ${QT_LIBRARIES}
   ${catkin_LIBRARIES}
   ${Eigen_LIBRARIES}
)


add_library(allinonegazebo SHARED src/cont.cc ./inc/cont.hh)
target_link_libraries(allinonegazebo ${GAZEBO_LIBRARIES} ${catkin_LIBRARIES} ${Boost_LIBRARIES})

add_executable( distanceEstimator src/distanceEstimator.cpp )
target_link_libraries( distanceEstimator ${catkin_LIBRARIES} )

add_executable( firstOrderController src/firstOrderController.cc )
target_link_libraries( firstOrderController ${catkin_LIBRARIES} )


install(DIRECTORY launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

install(DIRECTORY meshes
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

install(DIRECTORY urdf
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

install(DIRECTORY worlds
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
# JMS: end note

## Mark executables and/or libraries for installation
install(TARGETS allinonegazebo
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
