# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "localization: 3 messages, 0 services")

set(MSG_I_FLAGS "-Ilocalization:/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/src/dyros/localization/msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(localization_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/src/dyros/localization/msg/LocalizationData.msg" NAME_WE)
add_custom_target(_localization_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "localization" "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/src/dyros/localization/msg/LocalizationData.msg" ""
)

get_filename_component(_filename "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/src/dyros/localization/msg/CarCanData.msg" NAME_WE)
add_custom_target(_localization_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "localization" "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/src/dyros/localization/msg/CarCanData.msg" ""
)

get_filename_component(_filename "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/src/dyros/localization/msg/GpsReceiverData.msg" NAME_WE)
add_custom_target(_localization_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "localization" "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/src/dyros/localization/msg/GpsReceiverData.msg" ""
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(localization
  "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/src/dyros/localization/msg/LocalizationData.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/localization
)
_generate_msg_cpp(localization
  "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/src/dyros/localization/msg/CarCanData.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/localization
)
_generate_msg_cpp(localization
  "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/src/dyros/localization/msg/GpsReceiverData.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/localization
)

### Generating Services

### Generating Module File
_generate_module_cpp(localization
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/localization
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(localization_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(localization_generate_messages localization_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/src/dyros/localization/msg/LocalizationData.msg" NAME_WE)
add_dependencies(localization_generate_messages_cpp _localization_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/src/dyros/localization/msg/CarCanData.msg" NAME_WE)
add_dependencies(localization_generate_messages_cpp _localization_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/src/dyros/localization/msg/GpsReceiverData.msg" NAME_WE)
add_dependencies(localization_generate_messages_cpp _localization_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(localization_gencpp)
add_dependencies(localization_gencpp localization_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS localization_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(localization
  "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/src/dyros/localization/msg/LocalizationData.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/localization
)
_generate_msg_lisp(localization
  "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/src/dyros/localization/msg/CarCanData.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/localization
)
_generate_msg_lisp(localization
  "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/src/dyros/localization/msg/GpsReceiverData.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/localization
)

### Generating Services

### Generating Module File
_generate_module_lisp(localization
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/localization
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(localization_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(localization_generate_messages localization_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/src/dyros/localization/msg/LocalizationData.msg" NAME_WE)
add_dependencies(localization_generate_messages_lisp _localization_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/src/dyros/localization/msg/CarCanData.msg" NAME_WE)
add_dependencies(localization_generate_messages_lisp _localization_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/src/dyros/localization/msg/GpsReceiverData.msg" NAME_WE)
add_dependencies(localization_generate_messages_lisp _localization_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(localization_genlisp)
add_dependencies(localization_genlisp localization_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS localization_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(localization
  "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/src/dyros/localization/msg/LocalizationData.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/localization
)
_generate_msg_py(localization
  "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/src/dyros/localization/msg/CarCanData.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/localization
)
_generate_msg_py(localization
  "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/src/dyros/localization/msg/GpsReceiverData.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/localization
)

### Generating Services

### Generating Module File
_generate_module_py(localization
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/localization
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(localization_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(localization_generate_messages localization_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/src/dyros/localization/msg/LocalizationData.msg" NAME_WE)
add_dependencies(localization_generate_messages_py _localization_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/src/dyros/localization/msg/CarCanData.msg" NAME_WE)
add_dependencies(localization_generate_messages_py _localization_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/src/dyros/localization/msg/GpsReceiverData.msg" NAME_WE)
add_dependencies(localization_generate_messages_py _localization_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(localization_genpy)
add_dependencies(localization_genpy localization_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS localization_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/localization)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/localization
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(localization_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/localization)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/localization
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(localization_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/localization)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/localization\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/localization
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(localization_generate_messages_py std_msgs_generate_messages_py)
endif()
