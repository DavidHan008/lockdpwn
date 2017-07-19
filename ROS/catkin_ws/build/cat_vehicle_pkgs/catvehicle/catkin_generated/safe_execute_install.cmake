execute_process(COMMAND "/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/build/cat_vehicle_pkgs/catvehicle/catkin_generated/python_distutils_install.sh" RESULT_VARIABLE res)

if(NOT res EQUAL 0)
  message(FATAL_ERROR "execute_process(/home/dyros-vehicle/gitrepo/lockdpwn/ROS/catkin_ws/build/cat_vehicle_pkgs/catvehicle/catkin_generated/python_distutils_install.sh) returned error code ")
endif()
