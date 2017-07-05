# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "motion_planner: 0 messages, 2 services")

set(MSG_I_FLAGS "-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(motion_planner_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/dyros-vehicle/catkin_ws/src/motion_planner/srv/srvHeightMap.srv" NAME_WE)
add_custom_target(_motion_planner_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "motion_planner" "/home/dyros-vehicle/catkin_ws/src/motion_planner/srv/srvHeightMap.srv" ""
)

get_filename_component(_filename "/home/dyros-vehicle/catkin_ws/src/motion_planner/srv/srvParkingCmd.srv" NAME_WE)
add_custom_target(_motion_planner_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "motion_planner" "/home/dyros-vehicle/catkin_ws/src/motion_planner/srv/srvParkingCmd.srv" ""
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages

### Generating Services
_generate_srv_cpp(motion_planner
  "/home/dyros-vehicle/catkin_ws/src/motion_planner/srv/srvHeightMap.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/motion_planner
)
_generate_srv_cpp(motion_planner
  "/home/dyros-vehicle/catkin_ws/src/motion_planner/srv/srvParkingCmd.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/motion_planner
)

### Generating Module File
_generate_module_cpp(motion_planner
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/motion_planner
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(motion_planner_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(motion_planner_generate_messages motion_planner_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/dyros-vehicle/catkin_ws/src/motion_planner/srv/srvHeightMap.srv" NAME_WE)
add_dependencies(motion_planner_generate_messages_cpp _motion_planner_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dyros-vehicle/catkin_ws/src/motion_planner/srv/srvParkingCmd.srv" NAME_WE)
add_dependencies(motion_planner_generate_messages_cpp _motion_planner_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(motion_planner_gencpp)
add_dependencies(motion_planner_gencpp motion_planner_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS motion_planner_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages

### Generating Services
_generate_srv_lisp(motion_planner
  "/home/dyros-vehicle/catkin_ws/src/motion_planner/srv/srvHeightMap.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/motion_planner
)
_generate_srv_lisp(motion_planner
  "/home/dyros-vehicle/catkin_ws/src/motion_planner/srv/srvParkingCmd.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/motion_planner
)

### Generating Module File
_generate_module_lisp(motion_planner
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/motion_planner
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(motion_planner_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(motion_planner_generate_messages motion_planner_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/dyros-vehicle/catkin_ws/src/motion_planner/srv/srvHeightMap.srv" NAME_WE)
add_dependencies(motion_planner_generate_messages_lisp _motion_planner_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dyros-vehicle/catkin_ws/src/motion_planner/srv/srvParkingCmd.srv" NAME_WE)
add_dependencies(motion_planner_generate_messages_lisp _motion_planner_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(motion_planner_genlisp)
add_dependencies(motion_planner_genlisp motion_planner_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS motion_planner_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages

### Generating Services
_generate_srv_py(motion_planner
  "/home/dyros-vehicle/catkin_ws/src/motion_planner/srv/srvHeightMap.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/motion_planner
)
_generate_srv_py(motion_planner
  "/home/dyros-vehicle/catkin_ws/src/motion_planner/srv/srvParkingCmd.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/motion_planner
)

### Generating Module File
_generate_module_py(motion_planner
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/motion_planner
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(motion_planner_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(motion_planner_generate_messages motion_planner_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/dyros-vehicle/catkin_ws/src/motion_planner/srv/srvHeightMap.srv" NAME_WE)
add_dependencies(motion_planner_generate_messages_py _motion_planner_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dyros-vehicle/catkin_ws/src/motion_planner/srv/srvParkingCmd.srv" NAME_WE)
add_dependencies(motion_planner_generate_messages_py _motion_planner_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(motion_planner_genpy)
add_dependencies(motion_planner_genpy motion_planner_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS motion_planner_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/motion_planner)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/motion_planner
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
add_dependencies(motion_planner_generate_messages_cpp std_msgs_generate_messages_cpp)

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/motion_planner)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/motion_planner
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
add_dependencies(motion_planner_generate_messages_lisp std_msgs_generate_messages_lisp)

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/motion_planner)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/motion_planner\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/motion_planner
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
add_dependencies(motion_planner_generate_messages_py std_msgs_generate_messages_py)
