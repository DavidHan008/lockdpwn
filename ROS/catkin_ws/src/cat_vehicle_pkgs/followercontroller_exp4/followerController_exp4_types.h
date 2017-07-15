/*
 * followerController_exp4_types.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "followerController_exp4".
 *
 * Model version              : 1.13
 * Simulink Coder version : 8.10 (R2016a) 10-Feb-2016
 * C++ source code generated on : Wed May 11 15:27:58 2016
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_followerController_exp4_types_h_
#define RTW_HEADER_followerController_exp4_types_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_followerController_exp4_geometry_msgs_Point_
#define DEFINED_TYPEDEF_FOR_SL_Bus_followerController_exp4_geometry_msgs_Point_

typedef struct {
  real_T X;
  real_T Y;
  real_T Z;
} SL_Bus_followerController_exp4_geometry_msgs_Point;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_followerController_exp4_geometry_msgs_Vector3_
#define DEFINED_TYPEDEF_FOR_SL_Bus_followerController_exp4_geometry_msgs_Vector3_

typedef struct {
  real_T X;
  real_T Y;
  real_T Z;
} SL_Bus_followerController_exp4_geometry_msgs_Vector3;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_followerController_exp4_geometry_msgs_Twist_
#define DEFINED_TYPEDEF_FOR_SL_Bus_followerController_exp4_geometry_msgs_Twist_

typedef struct {
  SL_Bus_followerController_exp4_geometry_msgs_Vector3 Linear;
  SL_Bus_followerController_exp4_geometry_msgs_Vector3 Angular;
} SL_Bus_followerController_exp4_geometry_msgs_Twist;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_followerController_exp4_std_msgs_Float64_
#define DEFINED_TYPEDEF_FOR_SL_Bus_followerController_exp4_std_msgs_Float64_

typedef struct {
  real_T Data;
} SL_Bus_followerController_exp4_std_msgs_Float64;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_ROSVariableLengthArrayInfo_
#define DEFINED_TYPEDEF_FOR_SL_Bus_ROSVariableLengthArrayInfo_

typedef struct {
  uint32_T CurrentLength;
  uint32_T ReceivedLength;
} SL_Bus_ROSVariableLengthArrayInfo;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_followerController_exp4_ros_time_Time_
#define DEFINED_TYPEDEF_FOR_SL_Bus_followerController_exp4_ros_time_Time_

typedef struct {
  int32_T Sec;
  int32_T Nsec;
} SL_Bus_followerController_exp4_ros_time_Time;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_followerController_exp4_std_msgs_Header_
#define DEFINED_TYPEDEF_FOR_SL_Bus_followerController_exp4_std_msgs_Header_

typedef struct {
  uint32_T Seq;
  uint8_T FrameId[128];
  SL_Bus_ROSVariableLengthArrayInfo FrameId_SL_Info;
  SL_Bus_followerController_exp4_ros_time_Time Stamp;
} SL_Bus_followerController_exp4_std_msgs_Header;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_followerController_exp4_geometry_msgs_Quaternion_
#define DEFINED_TYPEDEF_FOR_SL_Bus_followerController_exp4_geometry_msgs_Quaternion_

typedef struct {
  real_T X;
  real_T Y;
  real_T Z;
  real_T W;
} SL_Bus_followerController_exp4_geometry_msgs_Quaternion;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_followerController_exp4_geometry_msgs_Pose_
#define DEFINED_TYPEDEF_FOR_SL_Bus_followerController_exp4_geometry_msgs_Pose_

typedef struct {
  SL_Bus_followerController_exp4_geometry_msgs_Point Position;
  SL_Bus_followerController_exp4_geometry_msgs_Quaternion Orientation;
} SL_Bus_followerController_exp4_geometry_msgs_Pose;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_followerController_exp4_PoseWithCovariance_awlp9o_
#define DEFINED_TYPEDEF_FOR_SL_Bus_followerController_exp4_PoseWithCovariance_awlp9o_

typedef struct {
  real_T Covariance[36];
  SL_Bus_followerController_exp4_geometry_msgs_Pose Pose;
} SL_Bus_followerController_exp4_PoseWithCovariance_awlp9o;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_followerController_exp4_TwistWithCovariance_ig2ouq_
#define DEFINED_TYPEDEF_FOR_SL_Bus_followerController_exp4_TwistWithCovariance_ig2ouq_

typedef struct {
  real_T Covariance[36];
  SL_Bus_followerController_exp4_geometry_msgs_Twist Twist;
} SL_Bus_followerController_exp4_TwistWithCovariance_ig2ouq;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_followerController_exp4_nav_msgs_Odometry_
#define DEFINED_TYPEDEF_FOR_SL_Bus_followerController_exp4_nav_msgs_Odometry_

typedef struct {
  uint8_T ChildFrameId[128];
  SL_Bus_ROSVariableLengthArrayInfo ChildFrameId_SL_Info;
  SL_Bus_followerController_exp4_std_msgs_Header Header;
  SL_Bus_followerController_exp4_PoseWithCovariance_awlp9o Pose;
  SL_Bus_followerController_exp4_TwistWithCovariance_ig2ouq Twist;
} SL_Bus_followerController_exp4_nav_msgs_Odometry;

#endif

#ifndef struct_tag_saG5948SFTrUFnIbVUb0TZH
#define struct_tag_saG5948SFTrUFnIbVUb0TZH

struct tag_saG5948SFTrUFnIbVUb0TZH
{
  int32_T isInitialized;
};

#endif                                 /*struct_tag_saG5948SFTrUFnIbVUb0TZH*/

#ifndef typedef_robotics_slros_internal_block_T
#define typedef_robotics_slros_internal_block_T

typedef struct tag_saG5948SFTrUFnIbVUb0TZH robotics_slros_internal_block_T;

#endif                                 /*typedef_robotics_slros_internal_block_T*/

#ifndef struct_tag_saG5948SFTrUFnIbVUb0TZH
#define struct_tag_saG5948SFTrUFnIbVUb0TZH

struct tag_saG5948SFTrUFnIbVUb0TZH
{
  int32_T isInitialized;
};

#endif                                 /*struct_tag_saG5948SFTrUFnIbVUb0TZH*/

#ifndef typedef_robotics_slros_internal_blo_k_T
#define typedef_robotics_slros_internal_blo_k_T

typedef struct tag_saG5948SFTrUFnIbVUb0TZH robotics_slros_internal_blo_k_T;

#endif                                 /*typedef_robotics_slros_internal_blo_k_T*/

#ifndef typedef_struct_T_followerController_e_T
#define typedef_struct_T_followerController_e_T

typedef struct {
  char_T f0[4];
} struct_T_followerController_e_T;

#endif                                 /*typedef_struct_T_followerController_e_T*/

#ifndef typedef_struct_T_followerController_k_T
#define typedef_struct_T_followerController_k_T

typedef struct {
  char_T f0[8];
} struct_T_followerController_k_T;

#endif                                 /*typedef_struct_T_followerController_k_T*/

#ifndef typedef_struct_T_followerControlle_k4_T
#define typedef_struct_T_followerControlle_k4_T

typedef struct {
  char_T f0[7];
} struct_T_followerControlle_k4_T;

#endif                                 /*typedef_struct_T_followerControlle_k4_T*/

#ifndef typedef_struct_T_followerControll_k40_T
#define typedef_struct_T_followerControll_k40_T

typedef struct {
  char_T f0[8];
  char_T f1[7];
  char_T f2[6];
} struct_T_followerControll_k40_T;

#endif                                 /*typedef_struct_T_followerControll_k40_T*/

/* Parameters for system: '<S4>/Enabled Subsystem' */
typedef struct P_EnabledSubsystem_followerCo_T_ P_EnabledSubsystem_followerCo_T;

/* Parameters (auto storage) */
typedef struct P_followerController_exp4_T_ P_followerController_exp4_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_followerController_ex_T RT_MODEL_followerController_e_T;

#endif                                 /* RTW_HEADER_followerController_exp4_types_h_ */
