# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "grid_map_msgs: 2 messages, 3 services")

set(MSG_I_FLAGS "-Igrid_map_msgs:/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/indigo/share/geometry_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(grid_map_msgs_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/srv/GetGridMap.srv" NAME_WE)
add_custom_target(_grid_map_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "grid_map_msgs" "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/srv/GetGridMap.srv" "grid_map_msgs/GridMapInfo:geometry_msgs/Point:std_msgs/Float32MultiArray:std_msgs/MultiArrayLayout:grid_map_msgs/GridMap:geometry_msgs/Quaternion:std_msgs/MultiArrayDimension:geometry_msgs/Pose:std_msgs/Header"
)

get_filename_component(_filename "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/srv/ProcessFile.srv" NAME_WE)
add_custom_target(_grid_map_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "grid_map_msgs" "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/srv/ProcessFile.srv" ""
)

get_filename_component(_filename "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/msg/GridMap.msg" NAME_WE)
add_custom_target(_grid_map_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "grid_map_msgs" "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/msg/GridMap.msg" "grid_map_msgs/GridMapInfo:geometry_msgs/Point:std_msgs/Float32MultiArray:std_msgs/MultiArrayLayout:geometry_msgs/Quaternion:std_msgs/MultiArrayDimension:geometry_msgs/Pose:std_msgs/Header"
)

get_filename_component(_filename "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/srv/GetGridMapInfo.srv" NAME_WE)
add_custom_target(_grid_map_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "grid_map_msgs" "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/srv/GetGridMapInfo.srv" "grid_map_msgs/GridMapInfo:geometry_msgs/Quaternion:std_msgs/Header:geometry_msgs/Point:geometry_msgs/Pose"
)

get_filename_component(_filename "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/msg/GridMapInfo.msg" NAME_WE)
add_custom_target(_grid_map_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "grid_map_msgs" "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/msg/GridMapInfo.msg" "geometry_msgs/Point:geometry_msgs/Quaternion:std_msgs/Header:geometry_msgs/Pose"
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(grid_map_msgs
  "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/msg/GridMap.msg"
  "${MSG_I_FLAGS}"
  "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/msg/GridMapInfo.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Float32MultiArray.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/MultiArrayLayout.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/MultiArrayDimension.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/grid_map_msgs
)
_generate_msg_cpp(grid_map_msgs
  "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/msg/GridMapInfo.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/grid_map_msgs
)

### Generating Services
_generate_srv_cpp(grid_map_msgs
  "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/srv/GetGridMap.srv"
  "${MSG_I_FLAGS}"
  "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/msg/GridMapInfo.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Float32MultiArray.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/MultiArrayLayout.msg;/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/msg/GridMap.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/MultiArrayDimension.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/grid_map_msgs
)
_generate_srv_cpp(grid_map_msgs
  "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/srv/ProcessFile.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/grid_map_msgs
)
_generate_srv_cpp(grid_map_msgs
  "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/srv/GetGridMapInfo.srv"
  "${MSG_I_FLAGS}"
  "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/msg/GridMapInfo.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/grid_map_msgs
)

### Generating Module File
_generate_module_cpp(grid_map_msgs
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/grid_map_msgs
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(grid_map_msgs_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(grid_map_msgs_generate_messages grid_map_msgs_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/srv/GetGridMap.srv" NAME_WE)
add_dependencies(grid_map_msgs_generate_messages_cpp _grid_map_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/srv/ProcessFile.srv" NAME_WE)
add_dependencies(grid_map_msgs_generate_messages_cpp _grid_map_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/msg/GridMap.msg" NAME_WE)
add_dependencies(grid_map_msgs_generate_messages_cpp _grid_map_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/srv/GetGridMapInfo.srv" NAME_WE)
add_dependencies(grid_map_msgs_generate_messages_cpp _grid_map_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/msg/GridMapInfo.msg" NAME_WE)
add_dependencies(grid_map_msgs_generate_messages_cpp _grid_map_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(grid_map_msgs_gencpp)
add_dependencies(grid_map_msgs_gencpp grid_map_msgs_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS grid_map_msgs_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(grid_map_msgs
  "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/msg/GridMap.msg"
  "${MSG_I_FLAGS}"
  "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/msg/GridMapInfo.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Float32MultiArray.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/MultiArrayLayout.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/MultiArrayDimension.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/grid_map_msgs
)
_generate_msg_lisp(grid_map_msgs
  "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/msg/GridMapInfo.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/grid_map_msgs
)

### Generating Services
_generate_srv_lisp(grid_map_msgs
  "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/srv/GetGridMap.srv"
  "${MSG_I_FLAGS}"
  "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/msg/GridMapInfo.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Float32MultiArray.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/MultiArrayLayout.msg;/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/msg/GridMap.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/MultiArrayDimension.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/grid_map_msgs
)
_generate_srv_lisp(grid_map_msgs
  "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/srv/ProcessFile.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/grid_map_msgs
)
_generate_srv_lisp(grid_map_msgs
  "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/srv/GetGridMapInfo.srv"
  "${MSG_I_FLAGS}"
  "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/msg/GridMapInfo.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/grid_map_msgs
)

### Generating Module File
_generate_module_lisp(grid_map_msgs
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/grid_map_msgs
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(grid_map_msgs_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(grid_map_msgs_generate_messages grid_map_msgs_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/srv/GetGridMap.srv" NAME_WE)
add_dependencies(grid_map_msgs_generate_messages_lisp _grid_map_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/srv/ProcessFile.srv" NAME_WE)
add_dependencies(grid_map_msgs_generate_messages_lisp _grid_map_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/msg/GridMap.msg" NAME_WE)
add_dependencies(grid_map_msgs_generate_messages_lisp _grid_map_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/srv/GetGridMapInfo.srv" NAME_WE)
add_dependencies(grid_map_msgs_generate_messages_lisp _grid_map_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/msg/GridMapInfo.msg" NAME_WE)
add_dependencies(grid_map_msgs_generate_messages_lisp _grid_map_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(grid_map_msgs_genlisp)
add_dependencies(grid_map_msgs_genlisp grid_map_msgs_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS grid_map_msgs_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(grid_map_msgs
  "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/msg/GridMap.msg"
  "${MSG_I_FLAGS}"
  "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/msg/GridMapInfo.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Float32MultiArray.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/MultiArrayLayout.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/MultiArrayDimension.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/grid_map_msgs
)
_generate_msg_py(grid_map_msgs
  "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/msg/GridMapInfo.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/grid_map_msgs
)

### Generating Services
_generate_srv_py(grid_map_msgs
  "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/srv/GetGridMap.srv"
  "${MSG_I_FLAGS}"
  "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/msg/GridMapInfo.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Float32MultiArray.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/MultiArrayLayout.msg;/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/msg/GridMap.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/MultiArrayDimension.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/grid_map_msgs
)
_generate_srv_py(grid_map_msgs
  "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/srv/ProcessFile.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/grid_map_msgs
)
_generate_srv_py(grid_map_msgs
  "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/srv/GetGridMapInfo.srv"
  "${MSG_I_FLAGS}"
  "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/msg/GridMapInfo.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/grid_map_msgs
)

### Generating Module File
_generate_module_py(grid_map_msgs
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/grid_map_msgs
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(grid_map_msgs_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(grid_map_msgs_generate_messages grid_map_msgs_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/srv/GetGridMap.srv" NAME_WE)
add_dependencies(grid_map_msgs_generate_messages_py _grid_map_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/srv/ProcessFile.srv" NAME_WE)
add_dependencies(grid_map_msgs_generate_messages_py _grid_map_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/msg/GridMap.msg" NAME_WE)
add_dependencies(grid_map_msgs_generate_messages_py _grid_map_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/srv/GetGridMapInfo.srv" NAME_WE)
add_dependencies(grid_map_msgs_generate_messages_py _grid_map_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dyros-vehicle/catkin_ws/src/grid_map/grid_map_msgs/msg/GridMapInfo.msg" NAME_WE)
add_dependencies(grid_map_msgs_generate_messages_py _grid_map_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(grid_map_msgs_genpy)
add_dependencies(grid_map_msgs_genpy grid_map_msgs_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS grid_map_msgs_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/grid_map_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/grid_map_msgs
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
add_dependencies(grid_map_msgs_generate_messages_cpp std_msgs_generate_messages_cpp)
add_dependencies(grid_map_msgs_generate_messages_cpp geometry_msgs_generate_messages_cpp)

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/grid_map_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/grid_map_msgs
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
add_dependencies(grid_map_msgs_generate_messages_lisp std_msgs_generate_messages_lisp)
add_dependencies(grid_map_msgs_generate_messages_lisp geometry_msgs_generate_messages_lisp)

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/grid_map_msgs)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/grid_map_msgs\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/grid_map_msgs
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
add_dependencies(grid_map_msgs_generate_messages_py std_msgs_generate_messages_py)
add_dependencies(grid_map_msgs_generate_messages_py geometry_msgs_generate_messages_py)
