cmake_minimum_required(VERSION 2.8.3)
project(motion_planner_gazebo)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  cmake_modules
  message_generation
)
find_package(Eigen REQUIRED)

##################################### QT ##########################################
find_package(Qt4 REQUIRED COMPONENTS QtCore QtGui)
include(${QT_USE_FILE})

 add_service_files(
   DIRECTORY srv
   FILES
   srvHeightMap.srv
   srvParkingCmd.srv
 )

# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

 generate_messages(
   DEPENDENCIES
   std_msgs
 )

catkin_package(
#  INCLUDE_DIRS inc
#  LIBRARIES lib
  CATKIN_DEPENDS roscpp std_msgs
  DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${Eigen_INCLUDE_DIRS}
)

######################## test_ui_node #################################
set( HDR_FILES_QT_UI_NODE inc/motion_planner_main.h inc/LocalPlannerThread.h inc/CatmullRomSpline.h ${HDR_NABO_FILES} )
set( SRC_FILES_QT_UI_NODE src/motion_planner_main.cpp src/LocalPlannerThread.cpp  ${MOC_FILES} ${SRC_NABO_FILES})
set( FORM_FILES_QT_UI_NODE ui/motion_planner_gui.ui)

QT4_WRAP_CPP(MOC_SRC_H_QT_UI_NODE ${HDR_FILES_QT_UI_NODE})
QT4_WRAP_UI(MOC_GUI_H_QT_UI_NODE ${FORM_FILES_QT_UI_NODE})

add_executable(motion_planner_gazebo ${SRC_FILES_QT_UI_NODE} ${HDR_FILES_QT_UI_NODE} ${MOC_SRC_H_QT_UI_NODE} ${MOC_GUI_H_QT_UI_NODE})

target_link_libraries(motion_planner_gazebo
   ${QT_LIBRARIES}
   ${catkin_LIBRARIES}
   ${Eigen_LIBRARIES}
 )
