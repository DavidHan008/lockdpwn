# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "rndf_manager: 0 messages, 1 services")

set(MSG_I_FLAGS "-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(rndf_manager_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/dyros-vehicle/catkin_ws/src/rndf_manager/srv/srvHeightMap.srv" NAME_WE)
add_custom_target(_rndf_manager_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "rndf_manager" "/home/dyros-vehicle/catkin_ws/src/rndf_manager/srv/srvHeightMap.srv" ""
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages

### Generating Services
_generate_srv_cpp(rndf_manager
  "/home/dyros-vehicle/catkin_ws/src/rndf_manager/srv/srvHeightMap.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/rndf_manager
)

### Generating Module File
_generate_module_cpp(rndf_manager
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/rndf_manager
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(rndf_manager_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(rndf_manager_generate_messages rndf_manager_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/dyros-vehicle/catkin_ws/src/rndf_manager/srv/srvHeightMap.srv" NAME_WE)
add_dependencies(rndf_manager_generate_messages_cpp _rndf_manager_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(rndf_manager_gencpp)
add_dependencies(rndf_manager_gencpp rndf_manager_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS rndf_manager_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages

### Generating Services
_generate_srv_lisp(rndf_manager
  "/home/dyros-vehicle/catkin_ws/src/rndf_manager/srv/srvHeightMap.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/rndf_manager
)

### Generating Module File
_generate_module_lisp(rndf_manager
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/rndf_manager
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(rndf_manager_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(rndf_manager_generate_messages rndf_manager_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/dyros-vehicle/catkin_ws/src/rndf_manager/srv/srvHeightMap.srv" NAME_WE)
add_dependencies(rndf_manager_generate_messages_lisp _rndf_manager_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(rndf_manager_genlisp)
add_dependencies(rndf_manager_genlisp rndf_manager_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS rndf_manager_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages

### Generating Services
_generate_srv_py(rndf_manager
  "/home/dyros-vehicle/catkin_ws/src/rndf_manager/srv/srvHeightMap.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/rndf_manager
)

### Generating Module File
_generate_module_py(rndf_manager
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/rndf_manager
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(rndf_manager_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(rndf_manager_generate_messages rndf_manager_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/dyros-vehicle/catkin_ws/src/rndf_manager/srv/srvHeightMap.srv" NAME_WE)
add_dependencies(rndf_manager_generate_messages_py _rndf_manager_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(rndf_manager_genpy)
add_dependencies(rndf_manager_genpy rndf_manager_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS rndf_manager_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/rndf_manager)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/rndf_manager
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
add_dependencies(rndf_manager_generate_messages_cpp std_msgs_generate_messages_cpp)

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/rndf_manager)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/rndf_manager
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
add_dependencies(rndf_manager_generate_messages_lisp std_msgs_generate_messages_lisp)

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/rndf_manager)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/rndf_manager\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/rndf_manager
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
add_dependencies(rndf_manager_generate_messages_py std_msgs_generate_messages_py)
