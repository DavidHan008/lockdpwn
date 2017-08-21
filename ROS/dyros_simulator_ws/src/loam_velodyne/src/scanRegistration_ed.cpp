#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ros/ros.h>

#include <nav_msgs/Odometry.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/PointCloud2.h>

#include <tf/transform_datatypes.h>
#include <tf/transform_broadcaster.h>

#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>

// ed: Global Mapping용 헤더 추가
#include <pcl/filters/crop_box.h>
#include <pcl/io/pcd_io.h>
#include <pcl_ros/point_cloud.h>


#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/kdtree/kdtree_flann.h>

using namespace std;

const double PI = 3.1415926;

const float scanPeriod = 0.1;

const int systemDelay = 20;
int systemInitCount = 0;
bool systemInited = false;


// ed: Global Map을 사용하기 위한 변수 추가
std::string map_file("edward.pcd");
Eigen::Vector3f translate_pt;
pcl::PointCloud<pcl::PointXYZI>::Ptr globalMap_(new pcl::PointCloud<pcl::PointXYZI>());
pcl::PointCloud<pcl::PointXYZI>::Ptr cloud_out_ptr_source(new pcl::PointCloud<pcl::PointXYZI>());
pcl::PointCloud<pcl::PointXYZI> cloud_out_source;
pcl::CropBox<pcl::PointXYZI> cropBoxFilter_source (true);  // ed: CropBox 코드 추가. PointCloud를 원하는 영역만큼 잘라서 사용할 수 있다
// ed: 자를 영역을 설정하는 변수들
Eigen::Vector4f min_pt (-25.0f, -25.0f, -25.0f, 25.0f);
Eigen::Vector4f max_pt (25.0f, 25.0f, 25.0f, 25.0f);
void update_cropped_map();


pcl::PointCloud<pcl::PointXYZ>::Ptr laserCloudIn(new pcl::PointCloud<pcl::PointXYZ>());
pcl::PointCloud<pcl::PointXYZI>::Ptr laserCloud(new pcl::PointCloud<pcl::PointXYZI>());
pcl::PointCloud<pcl::PointXYZI>::Ptr cornerPointsSharp(new pcl::PointCloud<pcl::PointXYZI>());
pcl::PointCloud<pcl::PointXYZI>::Ptr cornerPointsLessSharp(new pcl::PointCloud<pcl::PointXYZI>());
pcl::PointCloud<pcl::PointXYZI>::Ptr surfPointsFlat(new pcl::PointCloud<pcl::PointXYZI>());
pcl::PointCloud<pcl::PointXYZI>::Ptr surfPointsLessFlat(new pcl::PointCloud<pcl::PointXYZI>());
pcl::PointCloud<pcl::PointXYZI>::Ptr surfPointsLessFlatScan(new pcl::PointCloud<pcl::PointXYZI>());
pcl::PointCloud<pcl::PointXYZI>::Ptr surfPointsLessFlatScanDS(new pcl::PointCloud<pcl::PointXYZI>());
pcl::PointCloud<pcl::PointXYZ>::Ptr imuTrans(new pcl::PointCloud<pcl::PointXYZ>(4, 1));
pcl::PointCloud<pcl::PointXYZI>::Ptr laserCloudScans[16];

float cloudCurvature[50000];
int cloudSortInd[50000];
int cloudNeighborPicked[50000];
int cloudLabel[50000];

int scanStartInd[16];
int scanEndInd[16];

int imuPointerFront = 0;
int imuPointerLast = -1;
const int imuQueLength = 200;

float imuRollStart = 0, imuPitchStart = 0, imuYawStart = 0;
float imuRollCur = 0, imuPitchCur = 0, imuYawCur = 0;

float imuVeloXStart = 0, imuVeloYStart = 0, imuVeloZStart = 0;
float imuShiftXStart = 0, imuShiftYStart = 0, imuShiftZStart = 0;

float imuVeloXCur = 0, imuVeloYCur = 0, imuVeloZCur = 0;
float imuShiftXCur = 0, imuShiftYCur = 0, imuShiftZCur = 0;

float imuShiftFromStartXCur = 0, imuShiftFromStartYCur = 0, imuShiftFromStartZCur = 0;
float imuVeloFromStartXCur = 0, imuVeloFromStartYCur = 0, imuVeloFromStartZCur = 0;

double imuTime[imuQueLength] = {0};
float imuRoll[imuQueLength] = {0};
float imuPitch[imuQueLength] = {0};
float imuYaw[imuQueLength] = {0};

float imuAccX[imuQueLength] = {0};
float imuAccY[imuQueLength] = {0};
float imuAccZ[imuQueLength] = {0};

float imuVeloX[imuQueLength] = {0};
float imuVeloY[imuQueLength] = {0};
float imuVeloZ[imuQueLength] = {0};

float imuShiftX[imuQueLength] = {0};
float imuShiftY[imuQueLength] = {0};
float imuShiftZ[imuQueLength] = {0};

ros::Publisher* pubLaserCloudPointer;
ros::Publisher* pubCornerPointsSharpPointer;
ros::Publisher* pubCornerPointsLessSharpPointer;
ros::Publisher* pubSurfPointsFlatPointer;
ros::Publisher* pubSurfPointsLessFlatPointer;
ros::Publisher* pubImuTransPointer;


void ShiftToStartIMU(float pointTime){
  imuShiftFromStartXCur = imuShiftXCur - imuShiftXStart - imuVeloXStart * pointTime;
  imuShiftFromStartYCur = imuShiftYCur - imuShiftYStart - imuVeloYStart * pointTime;
  imuShiftFromStartZCur = imuShiftZCur - imuShiftZStart - imuVeloZStart * pointTime;

  float x1 = cos(imuYawStart) * imuShiftFromStartXCur - sin(imuYawStart) * imuShiftFromStartZCur;
  float y1 = imuShiftFromStartYCur;
  float z1 = sin(imuYawStart) * imuShiftFromStartXCur + cos(imuYawStart) * imuShiftFromStartZCur;

  float x2 = x1;
  float y2 = cos(imuPitchStart) * y1 + sin(imuPitchStart) * z1;
  float z2 = -sin(imuPitchStart) * y1 + cos(imuPitchStart) * z1;

  imuShiftFromStartXCur = cos(imuRollStart) * x2 + sin(imuRollStart) * y2;
  imuShiftFromStartYCur = -sin(imuRollStart) * x2 + cos(imuRollStart) * y2;
  imuShiftFromStartZCur = z2;
}


void VeloToStartIMU(){
  imuVeloFromStartXCur = imuVeloXCur - imuVeloXStart;
  imuVeloFromStartYCur = imuVeloYCur - imuVeloYStart;
  imuVeloFromStartZCur = imuVeloZCur - imuVeloZStart;

  float x1 = cos(imuYawStart) * imuVeloFromStartXCur - sin(imuYawStart) * imuVeloFromStartZCur;
  float y1 = imuVeloFromStartYCur;
  float z1 = sin(imuYawStart) * imuVeloFromStartXCur + cos(imuYawStart) * imuVeloFromStartZCur;

  float x2 = x1;
  float y2 = cos(imuPitchStart) * y1 + sin(imuPitchStart) * z1;
  float z2 = -sin(imuPitchStart) * y1 + cos(imuPitchStart) * z1;

  imuVeloFromStartXCur = cos(imuRollStart) * x2 + sin(imuRollStart) * y2;
  imuVeloFromStartYCur = -sin(imuRollStart) * x2 + cos(imuRollStart) * y2;
  imuVeloFromStartZCur = z2;
}


void TransformToStartIMU(pcl::PointXYZI *p){
  float x1 = cos(imuRollCur) * p->x - sin(imuRollCur) * p->y;
  float y1 = sin(imuRollCur) * p->x + cos(imuRollCur) * p->y;
  float z1 = p->z;

  float x2 = x1;
  float y2 = cos(imuPitchCur) * y1 - sin(imuPitchCur) * z1;
  float z2 = sin(imuPitchCur) * y1 + cos(imuPitchCur) * z1;

  float x3 = cos(imuYawCur) * x2 + sin(imuYawCur) * z2;
  float y3 = y2;
  float z3 = -sin(imuYawCur) * x2 + cos(imuYawCur) * z2;

  float x4 = cos(imuYawStart) * x3 - sin(imuYawStart) * z3;
  float y4 = y3;
  float z4 = sin(imuYawStart) * x3 + cos(imuYawStart) * z3;

  float x5 = x4;
  float y5 = cos(imuPitchStart) * y4 + sin(imuPitchStart) * z4;
  float z5 = -sin(imuPitchStart) * y4 + cos(imuPitchStart) * z4;

  p->x = cos(imuRollStart) * x5 + sin(imuRollStart) * y5 + imuShiftFromStartXCur;
  p->y = -sin(imuRollStart) * x5 + cos(imuRollStart) * y5 + imuShiftFromStartYCur;
  p->z = z5 + imuShiftFromStartZCur;
}


void AccumulateIMUShift(){
  float roll = imuRoll[imuPointerLast];
  float pitch = imuPitch[imuPointerLast];
  float yaw = imuYaw[imuPointerLast];
  float accX = imuAccX[imuPointerLast];
  float accY = imuAccY[imuPointerLast];
  float accZ = imuAccZ[imuPointerLast];

  float x1 = cos(roll) * accX - sin(roll) * accY;
  float y1 = sin(roll) * accX + cos(roll) * accY;
  float z1 = accZ;

  float x2 = x1;
  float y2 = cos(pitch) * y1 - sin(pitch) * z1;
  float z2 = sin(pitch) * y1 + cos(pitch) * z1;

  accX = cos(yaw) * x2 + sin(yaw) * z2;
  accY = y2;
  accZ = -sin(yaw) * x2 + cos(yaw) * z2;

  int imuPointerBack = (imuPointerLast + imuQueLength - 1) % imuQueLength;
  double timeDiff = imuTime[imuPointerLast] - imuTime[imuPointerBack];
  if (timeDiff < 0.1) {

    imuShiftX[imuPointerLast] = imuShiftX[imuPointerBack] + imuVeloX[imuPointerBack] * timeDiff 
                                + accX * timeDiff * timeDiff / 2;
    imuShiftY[imuPointerLast] = imuShiftY[imuPointerBack] + imuVeloY[imuPointerBack] * timeDiff 
                                + accY * timeDiff * timeDiff / 2;
    imuShiftZ[imuPointerLast] = imuShiftZ[imuPointerBack] + imuVeloZ[imuPointerBack] * timeDiff 
                                + accZ * timeDiff * timeDiff / 2;

    imuVeloX[imuPointerLast] = imuVeloX[imuPointerBack] + accX * timeDiff;
    imuVeloY[imuPointerLast] = imuVeloY[imuPointerBack] + accY * timeDiff;
    imuVeloZ[imuPointerLast] = imuVeloZ[imuPointerBack] + accZ * timeDiff;
  }
}

// ed: gps 데이터를 섭스크라이브하는 콜백함수 추가
void gps_callback(const geometry_msgs::Vector3Stamped::ConstPtr& msg) {
  // ed: x : 500000
  //     y : 4982950

  translate_pt(0) =  msg->vector.x - 500000;
  translate_pt(1) =  msg->vector.y - 4982950;
}

// ed: /velodyne_points를 섭스크라이브하는 콜백함수
void laserCloudHandler(const sensor_msgs::PointCloud2ConstPtr& laserCloudIn2){
  if (!systemInited) {
    systemInitCount++;

    if (systemInitCount >= systemDelay)
      systemInited = true;
    return;
  }

  /*
   # sensor_msgs/PointCloud2
	* Header header
	* uint32 height
	* uint32 width
	* PointField[] fields
	* bool is_bigendian
	* uint32 point_step
	* uint32 row_st\ep
	* uint8[] data
	* bool is_dense
   */

  double timeScanCur = laserCloudIn2->header.stamp.toSec();

  pcl::fromROSMsg(*laserCloudIn2, *laserCloudIn);

  int cloudSize_tmp = laserCloudIn->points.size();
  int cloudSize ;

  float startOri = -atan2(laserCloudIn->points[0].y, laserCloudIn->points[0].x);
  float endOri = -atan2(laserCloudIn->points[cloudSize_tmp - 1].y, 
                        laserCloudIn->points[cloudSize_tmp - 1].x) + 2 * PI;

  if (endOri - startOri > 3 * PI)
    endOri -= 2 * PI;
  else if (endOri - startOri < PI)
    endOri += 2 * PI;

  bool halfPassed = false;

  // ed: x,y,z & intensity
  pcl::PointXYZI point;

  for (int i = 0; i < cloudSize_tmp; i++) {
    // ed: 이 부분에서 Velodyne --> Loam 으로 좌표계 변환이 되는듯하다. (기존코드 수정 안함)
    point.x = laserCloudIn->points[i].x;
    point.y = laserCloudIn->points[i].y;
    point.z = laserCloudIn->points[i].z;

    float angle = atan(point.z / sqrt(point.y * point.y + point.x * point.x)) * 180 / PI;
    int scanID;

     // ed: 0 ~ -30 degree를 -60 ~ +60 degree로 수정했다
    if(angle >= -60     && angle <   -29     ) { scanID =    0   ;}
    else if(angle >=     -28     && angle <   -27     ) { scanID =    1   ;}
    else if(angle >=     -26     && angle <   -25     ) { scanID =    2   ;}
    else if(angle >=     -24     && angle <   -23     ) { scanID =    3   ;}
    else if(angle >=     -22     && angle <   -21     ) { scanID =    4   ;}
    else if(angle >=     -20     && angle <   -19     ) { scanID =    5   ;}
    else if(angle >=     -18     && angle <   -17     ) { scanID =    6   ;}
    else if(angle >=     -16     && angle <   -15     ) { scanID =    7   ;}
    else if(angle >=     -14     && angle <   -13     ) { scanID =    8   ;}
    else if(angle >=     -12     && angle <   -11     ) { scanID =    9   ;}
    else if(angle >=     -10     && angle <   -8.5    ) { scanID =    10  ;}
    else if(angle >=     -8  && angle <   -7  ) { scanID =    11  ;}
    else if(angle >=     -6  && angle <   -4.5    ) { scanID =    12  ;}
    else if(angle >=     -4  && angle <   -2.5    ) { scanID =    13  ;}
    else if(angle >=     -2  && angle <   0   ) { scanID =    14  ;}
    else if(angle >=     0   && angle <   60   ) { scanID =    15  ;}
    else
      continue;

    /*   // ed: HDL-32E 32채널용 velodyne에 맞게 새로 추가한 코드
    if(angle >= -30     && angle <   -29     ) { scanID =    0   ;}
    else if(angle >=     -28     && angle <   -27     ) { scanID =    1   ;}
    else if(angle >=     -26     && angle <   -25     ) { scanID =    2   ;}
    else if(angle >=     -24     && angle <   -23     ) { scanID =    3   ;}
    else if(angle >=     -22     && angle <   -21     ) { scanID =    4   ;}
    else if(angle >=     -20     && angle <   -19     ) { scanID =    5   ;}
    else if(angle >=     -18     && angle <   -17     ) { scanID =    6   ;}
    else if(angle >=     -16     && angle <   -15     ) { scanID =    7   ;}
    else if(angle >=     -14     && angle <   -13     ) { scanID =    8   ;}
    else if(angle >=     -12     && angle <   -11     ) { scanID =    9   ;}
    else if(angle >=     -10     && angle <   -8.5    ) { scanID =    10  ;}
    else if(angle >=     -8  && angle <   -7  ) { scanID =    11  ;}
    else if(angle >=     -6  && angle <   -4.5    ) { scanID =    12  ;}
    else if(angle >=     -4  && angle <   -2.5    ) { scanID =    13  ;}
    else if(angle >=     -2  && angle <   0   ) { scanID =    14  ;}
    else if(angle >=     0   && angle <   100   ) { scanID =    15  ;}
    else
      continue;
*/
    /*
       if(angle >= 	-14.2 	&& angle < 	-14 	) { scanID =  	0 	;}
       else if(angle >= 	-13.5 	&& angle < 	-13 	) { scanID =  	1 	;}
       else if(angle >= 	-12.5 	&& angle < 	-12 	) { scanID =  	2 	;}
       else if(angle >= 	-11.5 	&& angle < 	-11 	) { scanID =  	3 	;}
       else if(angle >= 	-10.5 	&& angle < 	-10 	) { scanID =  	4 	;}
       else if(angle >= 	-9.5 	&& angle < 	-9 	) { scanID =  	5 	;}
       else if(angle >= 	-8.5 	&& angle < 	-8 	) { scanID =  	6 	;}
       else if(angle >= 	-7.5 	&& angle < 	-7 	) { scanID =  	7 	;}
       else if(angle >= 	-6.3 	&& angle < 	-6 	) { scanID =  	8 	;}
       else if(angle >= 	-5.4 	&& angle < 	-5 	) { scanID =  	9 	;}
       else if(angle >= 	-4.4 	&& angle < 	-4 	) { scanID =  	10 	;}
       else if(angle >= 	-3.4 	&& angle < 	-3 	) { scanID =  	11 	;}
       else if(angle >= 	-2.3 	&& angle < 	-2 	) { scanID =  	12 	;}
       else if(angle >= 	-1.3 	&& angle < 	-1 	) { scanID =  	13 	;}
       else if(angle >= 	-0.5 	&& angle < 	-0.2 	) { scanID =  	14 	;}
       else if(angle >= 	0 	&& angle < 	0.1 	) { scanID =  	15 	;}
       else
    */
    /*
    // ed: 실체 차량의 HDL-64E를 사용할 때는 아래 코드를 활성화시켜야한다
    if(angle >= 	-13.5 	&& angle < 	-13.4 	) { scanID =  	0 	;}
    else if(angle >= 	-13.4 	&& angle < 	-13 	) { scanID =  	1 	;}
    else if(angle >= 	-12.4 	&& angle < 	-12 	) { scanID =  	2 	;}
    else if(angle >= 	-11.3 	&& angle < 	-11 	) { scanID =  	3 	;}
    else if(angle >= 	-10.3 	&& angle < 	-10 	) { scanID =  	4 	;}
    else if(angle >= 	-9.4 	&& angle < 	-9.1 	) { scanID =  	5 	;}
    else if(angle >= 	-8.3 	&& angle < 	-8 	) { scanID =  	6 	;}
    else if(angle >= 	-7.4 	&& angle < 	-7.0 	) { scanID =  	7 	;}
    else if(angle >= 	-6.3 	&& angle < 	-6 	) { scanID =  	8 	;}
    else if(angle >= 	-5.3 	&& angle < 	-5.1 	) { scanID =  	9 	;}
    else if(angle >= 	-4.3 	&& angle < 	-4.1 	) { scanID =  	10 	;}
    else if(angle >= 	-3.2 	&& angle < 	-3 	) { scanID =  	11 	;}
    else if(angle >= 	-2.3 	&& angle < 	-2 	) { scanID =  	12 	;}
    else if(angle >= 	-1.3 	&& angle < 	-1.1 	) { scanID =  	13 	;}
    else if(angle >= 	-0.5 	&& angle < 	-0.3 	) { scanID =  	14 	;}
    else if(angle >= 	0 	&& angle < 	0.1 	) { scanID =  	15 	;}
    else
      continue;
    */


    float ori = -atan2(point.y, point.x);

    if (!halfPassed) {
      if (ori < startOri - PI / 2) {
        ori += 2 * PI;
      }
      else if (ori > startOri + PI * 3 / 2) {
        ori -= 2 * PI;
      }

      if (ori - startOri > PI) {
        halfPassed = true;
      }
    }
    else {
      ori += 2 * PI;

      if (ori < endOri - PI * 3 / 2)
        ori += 2 * PI;
      else if (ori > endOri + PI / 2)
        ori -= 2 * PI;
    }

    float relTime = (ori - startOri) / (endOri - startOri);
    point.intensity = scanID + 0.1 * relTime;

    if (imuPointerLast >= 0) {
      float pointTime = relTime * scanPeriod;

      while (imuPointerFront != imuPointerLast) {
        if (timeScanCur + pointTime < imuTime[imuPointerFront])
          break;

        imuPointerFront = (imuPointerFront + 1) % imuQueLength;
      }

      if (timeScanCur + pointTime > imuTime[imuPointerFront]) {
        imuRollCur = imuRoll[imuPointerFront];
        imuPitchCur = imuPitch[imuPointerFront];
        imuYawCur = imuYaw[imuPointerFront];

        imuVeloXCur = imuVeloX[imuPointerFront];
        imuVeloYCur = imuVeloY[imuPointerFront];
        imuVeloZCur = imuVeloZ[imuPointerFront];

        imuShiftXCur = imuShiftX[imuPointerFront];
        imuShiftYCur = imuShiftY[imuPointerFront];
        imuShiftZCur = imuShiftZ[imuPointerFront];
      }
      else {
        int imuPointerBack = (imuPointerFront + imuQueLength - 1) % imuQueLength;
        float ratioFront = (timeScanCur + pointTime - imuTime[imuPointerBack]) 
                           / (imuTime[imuPointerFront] - imuTime[imuPointerBack]);
        float ratioBack = (imuTime[imuPointerFront] - timeScanCur - pointTime) 
                          / (imuTime[imuPointerFront] - imuTime[imuPointerBack]);

        imuRollCur = imuRoll[imuPointerFront] * ratioFront + imuRoll[imuPointerBack] * ratioBack;
        imuPitchCur = imuPitch[imuPointerFront] * ratioFront + imuPitch[imuPointerBack] * ratioBack;
        if (imuYaw[imuPointerFront] - imuYaw[imuPointerBack] > PI) {
          imuYawCur = imuYaw[imuPointerFront] * ratioFront + (imuYaw[imuPointerBack] + 2 * PI) * ratioBack;
        }
        else if (imuYaw[imuPointerFront] - imuYaw[imuPointerBack] < -PI) {
          imuYawCur = imuYaw[imuPointerFront] * ratioFront + (imuYaw[imuPointerBack] - 2 * PI) * ratioBack;
        }
        else {
          imuYawCur = imuYaw[imuPointerFront] * ratioFront + imuYaw[imuPointerBack] * ratioBack;
        }

        imuVeloXCur = imuVeloX[imuPointerFront] * ratioFront + imuVeloX[imuPointerBack] * ratioBack;
        imuVeloYCur = imuVeloY[imuPointerFront] * ratioFront + imuVeloY[imuPointerBack] * ratioBack;
        imuVeloZCur = imuVeloZ[imuPointerFront] * ratioFront + imuVeloZ[imuPointerBack] * ratioBack;

        imuShiftXCur = imuShiftX[imuPointerFront] * ratioFront + imuShiftX[imuPointerBack] * ratioBack;
        imuShiftYCur = imuShiftY[imuPointerFront] * ratioFront + imuShiftY[imuPointerBack] * ratioBack;
        imuShiftZCur = imuShiftZ[imuPointerFront] * ratioFront + imuShiftZ[imuPointerBack] * ratioBack;
      }

      // ed: 대부분의 경우 i != 0 이므로 아래 else문이 실행될 것 같다
      if (i == 0) {
        imuRollStart = imuRollCur;
        imuPitchStart = imuPitchCur;
        imuYawStart = imuYawCur;

        imuVeloXStart = imuVeloXCur;
        imuVeloYStart = imuVeloYCur;
        imuVeloZStart = imuVeloZCur;

        imuShiftXStart = imuShiftXCur;
        imuShiftYStart = imuShiftYCur;
        imuShiftZStart = imuShiftZCur;
      }
      else {
        ShiftToStartIMU(pointTime);
        VeloToStartIMU();
        TransformToStartIMU(&point);
      }
    }

    laserCloudScans[scanID]->push_back(point);
  }

  for (int i = 0; i < 16; i++) {
    *laserCloud += *laserCloudScans[i];
    //printf("i: %d, %d\n", i, laserCloudScans[i]->size());
  }

  // ed: laserCloud->points를 cloud_out_ptr_source->points로 변경했다
  //cloudSize = laserCloud->points.size();   //JH
  cloudSize = cloud_out_ptr_source->points.size();   //JH
  //printf("%d\n",cloudSize);

  // ed: 함수 추가
  update_cropped_map();
  cout << "good " << endl;
  cout << "cloudsize " << cloudSize << endl;

  int scanCount = -1;
  for (int i = 5; i < cloudSize - 5; i++) {
    float diffX = cloud_out_ptr_source->points[i - 5].x + cloud_out_ptr_source->points[i - 4].x
                  + cloud_out_ptr_source->points[i - 3].x + cloud_out_ptr_source->points[i - 2].x
                  + cloud_out_ptr_source->points[i - 1].x - 10 * cloud_out_ptr_source->points[i].x
                  + cloud_out_ptr_source->points[i + 1].x + cloud_out_ptr_source->points[i + 2].x
                  + cloud_out_ptr_source->points[i + 3].x + cloud_out_ptr_source->points[i + 4].x
                  + cloud_out_ptr_source->points[i + 5].x;
    float diffY = cloud_out_ptr_source->points[i - 5].y + cloud_out_ptr_source->points[i - 4].y
                  + cloud_out_ptr_source->points[i - 3].y + cloud_out_ptr_source->points[i - 2].y
                  + cloud_out_ptr_source->points[i - 1].y - 10 * cloud_out_ptr_source->points[i].y
                  + cloud_out_ptr_source->points[i + 1].y + cloud_out_ptr_source->points[i + 2].y
                  + cloud_out_ptr_source->points[i + 3].y + cloud_out_ptr_source->points[i + 4].y
                  + cloud_out_ptr_source->points[i + 5].y;
    float diffZ = cloud_out_ptr_source->points[i - 5].z + cloud_out_ptr_source->points[i - 4].z
                  + cloud_out_ptr_source->points[i - 3].z + cloud_out_ptr_source->points[i - 2].z
                  + cloud_out_ptr_source->points[i - 1].z - 10 * cloud_out_ptr_source->points[i].z
                  + cloud_out_ptr_source->points[i + 1].z + cloud_out_ptr_source->points[i + 2].z
                  + cloud_out_ptr_source->points[i + 3].z + cloud_out_ptr_source->points[i + 4].z
                  + cloud_out_ptr_source->points[i + 5].z;
    
    cloudCurvature[i] = diffX * diffX + diffY * diffY + diffZ * diffZ;
    cloudSortInd[i] = i;
    cloudNeighborPicked[i] = 0;
    cloudLabel[i] = 0;

    //if (int(cloud_out_ptr_source->points[i].intensity) != scanCount) {
    //  scanCount = int(cloud_out_ptr_source->points[i].intensity);

    //   if (scanCount > 0) {
    //    scanStartInd[scanCount] = i + 5;
    //  scanEndInd[scanCount - 1] = i - 5;
    // }
  //}
  }
  scanStartInd[0] = 5;
  scanEndInd[15] = cloudSize - 5;

  for (int i = 5; i < cloudSize - 6; i++) {
    float diffX = cloud_out_ptr_source->points[i + 1].x - cloud_out_ptr_source->points[i].x;
    float diffY = cloud_out_ptr_source->points[i + 1].y - cloud_out_ptr_source->points[i].y;
    float diffZ = cloud_out_ptr_source->points[i + 1].z - cloud_out_ptr_source->points[i].z;
    float diff = diffX * diffX + diffY * diffY + diffZ * diffZ;

    if (diff > 0.1) {
      // ed: sqrt(x^2 + y^2 + z^2) for i
      float depth1 = sqrt(cloud_out_ptr_source->points[i].x * cloud_out_ptr_source->points[i].x +
                          cloud_out_ptr_source->points[i].y * cloud_out_ptr_source->points[i].y +
                          cloud_out_ptr_source->points[i].z * cloud_out_ptr_source->points[i].z);

      // ed: sqrt(x^2 + y^2 + z^2) for i+1
      float depth2 = sqrt(cloud_out_ptr_source->points[i + 1].x * cloud_out_ptr_source->points[i + 1].x +
                          cloud_out_ptr_source->points[i + 1].y * cloud_out_ptr_source->points[i + 1].y +
                          cloud_out_ptr_source->points[i + 1].z * cloud_out_ptr_source->points[i + 1].z);

      if (depth1 > depth2) {
        diffX = cloud_out_ptr_source->points[i + 1].x - cloud_out_ptr_source->points[i].x * depth2 / depth1;
        diffY = cloud_out_ptr_source->points[i + 1].y - cloud_out_ptr_source->points[i].y * depth2 / depth1;
        diffZ = cloud_out_ptr_source->points[i + 1].z - cloud_out_ptr_source->points[i].z * depth2 / depth1;

        if (sqrt(diffX * diffX + diffY * diffY + diffZ * diffZ) / depth2 < 0.1) {
          cloudNeighborPicked[i - 5] = 1;
          cloudNeighborPicked[i - 4] = 1;
          cloudNeighborPicked[i - 3] = 1;
          cloudNeighborPicked[i - 2] = 1;
          cloudNeighborPicked[i - 1] = 1;
          cloudNeighborPicked[i] = 1;
        }
      }
      else {
        diffX = cloud_out_ptr_source->points[i + 1].x * depth1 / depth2 - cloud_out_ptr_source->points[i].x;
        diffY = cloud_out_ptr_source->points[i + 1].y * depth1 / depth2 - cloud_out_ptr_source->points[i].y;
        diffZ = cloud_out_ptr_source->points[i + 1].z * depth1 / depth2 - cloud_out_ptr_source->points[i].z;

        if (sqrt(diffX * diffX + diffY * diffY + diffZ * diffZ) / depth1 < 0.1) {
          cloudNeighborPicked[i + 1] = 1;
          cloudNeighborPicked[i + 2] = 1;
          cloudNeighborPicked[i + 3] = 1;
          cloudNeighborPicked[i + 4] = 1;
          cloudNeighborPicked[i + 5] = 1;
          cloudNeighborPicked[i + 6] = 1;
        }
      }
    }

    float diffX2 = cloud_out_ptr_source->points[i].x - cloud_out_ptr_source->points[i - 1].x;
    float diffY2 = cloud_out_ptr_source->points[i].y - cloud_out_ptr_source->points[i - 1].y;
    float diffZ2 = cloud_out_ptr_source->points[i].z - cloud_out_ptr_source->points[i - 1].z;
    float diff2 = diffX2 * diffX2 + diffY2 * diffY2 + diffZ2 * diffZ2;

    float dis = cloud_out_ptr_source->points[i].x * cloud_out_ptr_source->points[i].x
                + cloud_out_ptr_source->points[i].y * cloud_out_ptr_source->points[i].y
                + cloud_out_ptr_source->points[i].z * cloud_out_ptr_source->points[i].z;

    if (diff > 0.0002 * dis && diff2 > 0.0002 * dis)
      cloudNeighborPicked[i] = 1;

  }

  for (int i = 0; i < 16; i++) {
    surfPointsLessFlatScan->clear();

    for (int j = 0; j < 6; j++) {
      int sp = (scanStartInd[i] * (6 - j)  + scanEndInd[i] * j) / 6;
      int ep = (scanStartInd[i] * (5 - j)  + scanEndInd[i] * (j + 1)) / 6 - 1;

      for (int k = sp + 1; k <= ep; k++) {
        for (int l = k; l >= sp + 1; l--) {
          if (cloudCurvature[cloudSortInd[l]] < cloudCurvature[cloudSortInd[l - 1]]) {
            int temp = cloudSortInd[l - 1];
            cloudSortInd[l - 1] = cloudSortInd[l];
            cloudSortInd[l] = temp;
          }
        }
      }
      int largestPickedNum = 0;

      for (int k = ep; k >= sp; k--) {
        int ind = cloudSortInd[k];

        if (cloudNeighborPicked[ind] == 0 && cloudCurvature[ind] > 0.1) {
          largestPickedNum++;

          if (largestPickedNum <= 2) {
            cloudLabel[ind] = 2;
            cornerPointsSharp->push_back(cloud_out_ptr_source->points[ind]);
            cornerPointsLessSharp->push_back(cloud_out_ptr_source->points[ind]);
          }
          else if (largestPickedNum <= 20) {
            cloudLabel[ind] = 1;
            cornerPointsLessSharp->push_back(cloud_out_ptr_source->points[ind]);
          }
          else {
            break;
          }

          cloudNeighborPicked[ind] = 1;
          for (int l = 1; l <= 5; l++) {
            float diffX = cloud_out_ptr_source->points[ind + l].x
                          - cloud_out_ptr_source->points[ind + l - 1].x;
            float diffY = cloud_out_ptr_source->points[ind + l].y
                          - cloud_out_ptr_source->points[ind + l - 1].y;
            float diffZ = cloud_out_ptr_source->points[ind + l].z
                          - cloud_out_ptr_source->points[ind + l - 1].z;
            if (diffX * diffX + diffY * diffY + diffZ * diffZ > 0.05) {
              break;
            }

            cloudNeighborPicked[ind + l] = 1;
          }
          for (int l = -1; l >= -5; l--) {
            float diffX = cloud_out_ptr_source->points[ind + l].x
                          - cloud_out_ptr_source->points[ind + l + 1].x;
            float diffY = cloud_out_ptr_source->points[ind + l].y
                          - cloud_out_ptr_source->points[ind + l + 1].y;
            float diffZ = cloud_out_ptr_source->points[ind + l].z
                          - cloud_out_ptr_source->points[ind + l + 1].z;
            if (diffX * diffX + diffY * diffY + diffZ * diffZ > 0.05) {
              break;
            }

            cloudNeighborPicked[ind + l] = 1;
          }
        }
      }
      int smallestPickedNum = 0;

      for (int k = sp; k <= ep; k++) {
        int ind = cloudSortInd[k];

        if (cloudNeighborPicked[ind] == 0 &&  cloudCurvature[ind] < 0.1) {
          cloudLabel[ind] = -1;
          surfPointsFlat->push_back(cloud_out_ptr_source->points[ind]);
          smallestPickedNum++;

          if (smallestPickedNum >= 4) {
            break;
          }

          cloudNeighborPicked[ind] = 1;
          for (int l = 1; l <= 5; l++) {
            float diffX = cloud_out_ptr_source->points[ind + l].x
                          - cloud_out_ptr_source->points[ind + l - 1].x;
            float diffY = cloud_out_ptr_source->points[ind + l].y
                          - cloud_out_ptr_source->points[ind + l - 1].y;
            float diffZ = cloud_out_ptr_source->points[ind + l].z
                          - cloud_out_ptr_source->points[ind + l - 1].z;
            if (diffX * diffX + diffY * diffY + diffZ * diffZ > 0.05) {
              break;
            }
            cloudNeighborPicked[ind + l] = 1;
          }
          for (int l = -1; l >= -5; l--) {
            float diffX = cloud_out_ptr_source->points[ind + l].x
                          - cloud_out_ptr_source->points[ind + l + 1].x;
            float diffY = cloud_out_ptr_source->points[ind + l].y
                          - cloud_out_ptr_source->points[ind + l + 1].y;
            float diffZ = cloud_out_ptr_source->points[ind + l].z
                          - cloud_out_ptr_source->points[ind + l + 1].z;
            if (diffX * diffX + diffY * diffY + diffZ * diffZ > 0.05)
              break;

            cloudNeighborPicked[ind + l] = 1;
          }
        }
      }

      for (int k = sp; k <= ep; k++) {
        if (cloudLabel[k] <= 0)
          surfPointsLessFlatScan->push_back(cloud_out_ptr_source->points[k]);
      }
    }

    surfPointsLessFlatScanDS->clear();
    pcl::VoxelGrid<pcl::PointXYZI> downSizeFilter;
    downSizeFilter.setInputCloud(surfPointsLessFlatScan);
    downSizeFilter.setLeafSize(0.2, 0.2, 0.2);
    downSizeFilter.filter(*surfPointsLessFlatScanDS);

    *surfPointsLessFlat += *surfPointsLessFlatScanDS;
  }

  sensor_msgs::PointCloud2 laserCloud2;
  pcl::toROSMsg(*laserCloud, laserCloud2);

  laserCloud2.header.stamp = laserCloudIn2->header.stamp;
  laserCloud2.header.frame_id = "/dyros/base_footprint";

  // ed: /velodyne_cloud_2 토픽으로 퍼블리시한다
  pubLaserCloudPointer->publish(laserCloud2);



  sensor_msgs::PointCloud2 cornerPointsSharp2;
  pcl::toROSMsg(*cornerPointsSharp, cornerPointsSharp2);

  cornerPointsSharp2.header.stamp = laserCloudIn2->header.stamp;
  cornerPointsSharp2.header.frame_id = "/dyros/base_footprint";

  // ed: /laser_cloud_sharp 토픽으로 퍼블리시한다
  pubCornerPointsSharpPointer->publish(cornerPointsSharp2);



  sensor_msgs::PointCloud2 cornerPointsLessSharp2;
  pcl::toROSMsg(*cornerPointsLessSharp, cornerPointsLessSharp2);

  cornerPointsLessSharp2.header.stamp = laserCloudIn2->header.stamp;
  cornerPointsLessSharp2.header.frame_id = "/dyros/base_footprint";

  // ed: /laser_cloud_less_sharp 토픽으로 퍼블리시한다
  pubCornerPointsLessSharpPointer->publish(cornerPointsLessSharp2);



  sensor_msgs::PointCloud2 surfPointsFlat2;
  pcl::toROSMsg(*surfPointsFlat, surfPointsFlat2);

  surfPointsFlat2.header.stamp = laserCloudIn2->header.stamp;
  surfPointsFlat2.header.frame_id = "/dyros/base_footprint";

  // ed: /laser_cloud_flat으로 퍼블리시한다
  pubSurfPointsFlatPointer->publish(surfPointsFlat2);


  sensor_msgs::PointCloud2 surfPointsLessFlat2;
  pcl::toROSMsg(*surfPointsLessFlat, surfPointsLessFlat2);

  surfPointsLessFlat2.header.stamp = laserCloudIn2->header.stamp;
  surfPointsLessFlat2.header.frame_id = "/dyros/base_footprint";

  // ed: /laser_cloud_less_flat으로 퍼블리시한다
  pubSurfPointsLessFlatPointer->publish(surfPointsLessFlat2);

  imuTrans->points[0].x = imuRollStart;
  imuTrans->points[0].y = imuPitchStart;
  imuTrans->points[0].z = imuYawStart;

  imuTrans->points[1].x = imuRollCur;
  imuTrans->points[1].y = imuPitchCur;
  imuTrans->points[1].z = imuYawCur;

  imuTrans->points[2].x = imuShiftFromStartXCur;
  imuTrans->points[2].y = imuShiftFromStartYCur;
  imuTrans->points[2].z = imuShiftFromStartZCur;

  imuTrans->points[3].x = imuVeloFromStartXCur;
  imuTrans->points[3].y = imuVeloFromStartYCur;
  imuTrans->points[3].z = imuVeloFromStartZCur;

  sensor_msgs::PointCloud2 imuTrans2;
  pcl::toROSMsg(*imuTrans, imuTrans2);

  imuTrans2.header.stamp = laserCloudIn2->header.stamp;
  imuTrans2.header.frame_id = "/dyros/base_footprint";

  // ed: /imu_trans로 퍼블리시한다
  pubImuTransPointer->publish(imuTrans2);


  laserCloudIn->clear();
  laserCloud->clear();
  cornerPointsSharp->clear();
  cornerPointsLessSharp->clear();
  surfPointsFlat->clear();
  surfPointsLessFlat->clear();

  for (int i = 0; i < 16; i++)
    laserCloudScans[i]->points.clear();

}

// ed: 주석처리되어 현재는 사용하지 않는 섭스크라이브의 콜백함수
void imuHandler(const sensor_msgs::Imu::ConstPtr& imuIn){
  double roll, pitch, yaw;
  //  tf::Quaternion orientation;
  //  tf::quaternionMsgToTF(imuIn->orientation, orientation);
  //  tf::Matrix3x3(orientation).getRPY(roll, pitch, yaw);

  //  float accY = imuIn->linear_acceleration.y - sin(roll) * cos(pitch) * 9.81;
  //  float accZ = imuIn->linear_acceleration.z - cos(roll) * cos(pitch) * 9.81;
  //  float accX = imuIn->linear_acceleration.x + sin(pitch) * 9.81;
  float accY = imuIn->linear_acceleration.y;
  float accZ = imuIn->linear_acceleration.z;
  float accX = imuIn->linear_acceleration.x ;
  roll=imuIn->orientation.x;
  pitch=imuIn->orientation.y;
  yaw=imuIn->orientation.z;
  imuPointerLast = (imuPointerLast + 1) % imuQueLength;

  imuTime[imuPointerLast] = imuIn->header.stamp.toSec();
  imuRoll[imuPointerLast] = roll;
  imuPitch[imuPointerLast] = pitch;
  imuYaw[imuPointerLast] = yaw;
  imuAccX[imuPointerLast] = accX;
  imuAccY[imuPointerLast] = accY;
  imuAccZ[imuPointerLast] = accZ;
  //printf("%lf, %lf, %lf\n", roll, pitch, yaw);
  //printf("%f, %f, %f \n",accX,accY,accZ);
  AccumulateIMUShift();
}

// ed: Global Map을 사용하기 위한 함수 추가
void load_and_crop_global_map(){
  int error = pcl::io::loadPCDFile<pcl::PointXYZI>("edward.pcd", *globalMap_);

  if (error < 0)
    ROS_ERROR("PCD File load failed. \n filename = %s",map_file.c_str());

  cropBoxFilter_source.setInputCloud (globalMap_);

  //Cropbox slighlty bigger then bounding box of points
  cropBoxFilter_source.setMin (min_pt);
  cropBoxFilter_source.setMax (max_pt);
}

// ed: 지속적으로 gps 위치를 받으면서 구간을 잘라서 pointcloud를 생성하는 함수
void update_cropped_map(){
  // ed: GPS의 데이터를 사용해 특정지역에서 Crop하기 위해 아래 코드를 추가한다
  cropBoxFilter_source.setTranslation (translate_pt);

  // ed : 위의 제약조건에 의해 필터링된 포인트클라우드를 생성한다
  cropBoxFilter_source.filter (cloud_out_source);
  cloud_out_ptr_source = cloud_out_source.makeShared();
}


int main(int argc, char** argv){
  ros::init(argc, argv, "scanRegistration");
  ros::NodeHandle nh;

  for (int i = 0; i < 16; i++)
    laserCloudScans[i].reset(new pcl::PointCloud<pcl::PointXYZI>());

    // ed: gps 데이터를 받는 섭스크라이버 추가
  ros::Subscriber sub_gps = nh.subscribe<geometry_msgs::Vector3Stamped>("/dyros/gps/utm", 1, gps_callback);
  ros::Subscriber subLaserCloud = nh.subscribe<sensor_msgs::PointCloud2>("/velodyne_points", 2, laserCloudHandler);
  //ros::Subscriber subImu = nh.subscribe<sensor_msgs::Imu> ("/imu/data", 50, imuHandler);


  ros::Publisher pubLaserCloud = nh.advertise<sensor_msgs::PointCloud2>("/velodyne_cloud_2", 2);
  ros::Publisher pubCornerPointsSharp = nh.advertise<sensor_msgs::PointCloud2>("/laser_cloud_sharp", 2);
  ros::Publisher pubCornerPointsLessSharp = nh.advertise<sensor_msgs::PointCloud2>("/laser_cloud_less_sharp", 2);
  ros::Publisher pubSurfPointsFlat = nh.advertise<sensor_msgs::PointCloud2>("/laser_cloud_flat", 2);
  ros::Publisher pubSurfPointsLessFlat = nh.advertise<sensor_msgs::PointCloud2>("/laser_cloud_less_flat", 2);
  ros::Publisher pubImuTrans = nh.advertise<sensor_msgs::PointCloud2> ("/imu_trans", 5);

  pubLaserCloudPointer = &pubLaserCloud;
  pubCornerPointsSharpPointer = &pubCornerPointsSharp;
  pubCornerPointsLessSharpPointer = &pubCornerPointsLessSharp;
  pubSurfPointsFlatPointer = &pubSurfPointsFlat;
  pubSurfPointsLessFlatPointer = &pubSurfPointsLessFlat;
  pubImuTransPointer = &pubImuTrans;

  // ed: Global map 불러오는 함수 호출
  load_and_crop_global_map();

  ros::spin();

  return 0;
}
