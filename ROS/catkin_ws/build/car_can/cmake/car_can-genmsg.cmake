# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "car_can: 1 messages, 0 services")

set(MSG_I_FLAGS "-Icar_can:/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/src/car_can/msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(car_can_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/src/car_can/msg/CarCanData.msg" NAME_WE)
add_custom_target(_car_can_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "car_can" "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/src/car_can/msg/CarCanData.msg" ""
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(car_can
  "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/src/car_can/msg/CarCanData.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/car_can
)

### Generating Services

### Generating Module File
_generate_module_cpp(car_can
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/car_can
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(car_can_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(car_can_generate_messages car_can_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/src/car_can/msg/CarCanData.msg" NAME_WE)
add_dependencies(car_can_generate_messages_cpp _car_can_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(car_can_gencpp)
add_dependencies(car_can_gencpp car_can_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS car_can_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(car_can
  "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/src/car_can/msg/CarCanData.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/car_can
)

### Generating Services

### Generating Module File
_generate_module_lisp(car_can
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/car_can
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(car_can_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(car_can_generate_messages car_can_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/src/car_can/msg/CarCanData.msg" NAME_WE)
add_dependencies(car_can_generate_messages_lisp _car_can_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(car_can_genlisp)
add_dependencies(car_can_genlisp car_can_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS car_can_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(car_can
  "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/src/car_can/msg/CarCanData.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/car_can
)

### Generating Services

### Generating Module File
_generate_module_py(car_can
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/car_can
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(car_can_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(car_can_generate_messages car_can_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/src/car_can/msg/CarCanData.msg" NAME_WE)
add_dependencies(car_can_generate_messages_py _car_can_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(car_can_genpy)
add_dependencies(car_can_genpy car_can_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS car_can_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/car_can)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/car_can
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(car_can_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/car_can)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/car_can
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(car_can_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/car_can)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/car_can\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/car_can
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(car_can_generate_messages_py std_msgs_generate_messages_py)
endif()
