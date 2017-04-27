# CMakeList.txt 

	# python을 사용할 때 설정하는 옵션이다
	catkin_python_setup()















# catkin_create_pkg  : 패키지를 생성합니다

	# my_first_ros_pkg 라는 이름의 패키지를 ROS 표준라이브러리인 std_msgs와 C++ 클라이언트 라이브러리인 roscpp를 사용해서 생성합니다
	catkin_create_pkg my_first_ros_pkg std_msgs roscpp
	
	












# catkin_make : catkin 빌드 명령어 












# catkin_init_workspace




# rosbash



# rosls   : 패키지의 파일 목록 확인 

	# turtlesim 패키지의 파일목록을 확인합니다
	rosls turtlesim







# rosed  : ros 편집 명렁어

	# turtlesim 패키지의 package.xml을 수정합니다
	rosed turtlesim package.xml




# roscp

# rospd

# rosd

# roslaunch  : 노드 여럿 실행하기

	# openni_launch 패키지에서 openni.launch 노드만 실행시킵니다
	roslaunch openni_launch openni.launch





# rosclean  : ros 로그 검사 및 삭제

	# ros 로그의 총 사용량을 확인합니다
	rosclean check


	
	# ros 로그 저장소 ~/.ros/log 폴더의 로그를 전부 삭제합니다
	rosclean purge





# rosrun

# rostopic

	# list
		# 활성화된 토픽 목록을 확인합니다. -v : 좀 더 자세히 봅니다
		rostopic list -v



	# echo 
		# turtle1/pose 토픽을 구성하는 데이터를 실시간으로 확인합니다 
		rostopic echo /turtle1/pose




	# find
		# 지정된 타입의 메세지를 사용하는 토픽을 표시합니다
		rostopic find turtlesim/Pose





	# type
		# turtle1/pose 토픽의 메세지 타입을 확인합니다
		rostopic type turtle1/pose




	# bw
		# turtle1/pose 토픽의 데이터 대역폭을 표시합니다
		rostopic bw /turtle1/pose




	# hz
		# turtle1/pose 토픽의 데이터 퍼블리시 주기를 표시합니다
		rostopic hz /turtle1/pose




	# info
		# turtle1/pose 토픽의 정보를 표시합니다
		rostopic info /turtle1/pose






# rosnode   : ros 노드

	
	# list
		# 활성화된 노드 목록을 확인합니다
		rosnode list



	# ping
		# turtlesim 노드가 현재 컴퓨터와 연결되어 있는지 테스트합니다. 연결되어 있다면 xmlrpc 응답을 받게됩니다
		rosnode ping /turtlesim



	# info
		# turtlesim 노드의 정보를 확인합니다
		rosnode info /turtlesim




	# kill
		# turtlesim 노드를 종료합니다
		rosnode kill /turtlesim




	# machine
		# 해당 ip의 pc에서 실행되고 있는 노드목록을 확인합니다
		rosnode machine 192.168.4.100


	

	# cleanup
		# 연결정보가 확인 안되는 노드들을 전부 삭제합니다
		rosnode cleanup



	


# rosservice

	# list


	# info


	# type


	# find


	# uri

	
	# args
	
	
	# call




# rosparam

	# list


	# get


	# set


	# dump


	# load


	# delete





# rossrv  : ros 서비스 정보


	# list
	# show
	# md5

	# package
	# packages







# rosmsg

	# list
	
	
	# show
	
	
	# md5 


	# package


	# packages




# rosbag  : ros 로그 정보

	# record
	# info
	# play
	# compress
	# decompress
	# filter
	# reindex bag
	# check bag
	# fix







# rosversion

# rospack

# roscd

# roscore  : master 실행



