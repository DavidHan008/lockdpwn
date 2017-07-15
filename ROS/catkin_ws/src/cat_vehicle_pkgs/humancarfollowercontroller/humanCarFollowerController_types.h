/*
 * humanCarFollowerController_types.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "humanCarFollowerController".
 *
 * Model version              : 1.10
 * Simulink Coder version : 8.10 (R2016a) 10-Feb-2016
 * C++ source code generated on : Sun May  8 12:46:58 2016
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_humanCarFollowerController_types_h_
#define RTW_HEADER_humanCarFollowerController_types_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_humanCarFollowerController_geometry_msgs_Vector3_
#define DEFINED_TYPEDEF_FOR_SL_Bus_humanCarFollowerController_geometry_msgs_Vector3_

typedef struct {
  real_T X;
  real_T Y;
  real_T Z;
} SL_Bus_humanCarFollowerController_geometry_msgs_Vector3;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_humanCarFollowerController_geometry_msgs_Twist_
#define DEFINED_TYPEDEF_FOR_SL_Bus_humanCarFollowerController_geometry_msgs_Twist_

typedef struct {
  SL_Bus_humanCarFollowerController_geometry_msgs_Vector3 Linear;
  SL_Bus_humanCarFollowerController_geometry_msgs_Vector3 Angular;
} SL_Bus_humanCarFollowerController_geometry_msgs_Twist;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_ROSVariableLengthArrayInfo_
#define DEFINED_TYPEDEF_FOR_SL_Bus_ROSVariableLengthArrayInfo_

typedef struct {
  uint32_T CurrentLength;
  uint32_T ReceivedLength;
} SL_Bus_ROSVariableLengthArrayInfo;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_humanCarFollowerController_ros_time_Time_
#define DEFINED_TYPEDEF_FOR_SL_Bus_humanCarFollowerController_ros_time_Time_

typedef struct {
  int32_T Sec;
  int32_T Nsec;
} SL_Bus_humanCarFollowerController_ros_time_Time;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_humanCarFollowerController_std_msgs_Header_
#define DEFINED_TYPEDEF_FOR_SL_Bus_humanCarFollowerController_std_msgs_Header_

typedef struct {
  uint32_T Seq;
  uint8_T FrameId[128];
  SL_Bus_ROSVariableLengthArrayInfo FrameId_SL_Info;
  SL_Bus_humanCarFollowerController_ros_time_Time Stamp;
} SL_Bus_humanCarFollowerController_std_msgs_Header;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_humanCarFollowerController_geometry_msgs_Point_
#define DEFINED_TYPEDEF_FOR_SL_Bus_humanCarFollowerController_geometry_msgs_Point_

typedef struct {
  real_T X;
  real_T Y;
  real_T Z;
} SL_Bus_humanCarFollowerController_geometry_msgs_Point;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_humanCarFollowerController_geometry_msgs_Quaternion_
#define DEFINED_TYPEDEF_FOR_SL_Bus_humanCarFollowerController_geometry_msgs_Quaternion_

typedef struct {
  real_T X;
  real_T Y;
  real_T Z;
  real_T W;
} SL_Bus_humanCarFollowerController_geometry_msgs_Quaternion;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_humanCarFollowerController_geometry_msgs_Pose_
#define DEFINED_TYPEDEF_FOR_SL_Bus_humanCarFollowerController_geometry_msgs_Pose_

typedef struct {
  SL_Bus_humanCarFollowerController_geometry_msgs_Point Position;
  SL_Bus_humanCarFollowerController_geometry_msgs_Quaternion Orientation;
} SL_Bus_humanCarFollowerController_geometry_msgs_Pose;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_humanCarFollowerControlle_PoseWithCovariance_x7rbgd_
#define DEFINED_TYPEDEF_FOR_SL_Bus_humanCarFollowerControlle_PoseWithCovariance_x7rbgd_

typedef struct {
  real_T Covariance[36];
  SL_Bus_humanCarFollowerController_geometry_msgs_Pose Pose;
} SL_Bus_humanCarFollowerControlle_PoseWithCovariance_x7rbgd;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_humanCarFollowerControlle_TwistWithCovariance_97r4v_
#define DEFINED_TYPEDEF_FOR_SL_Bus_humanCarFollowerControlle_TwistWithCovariance_97r4v_

typedef struct {
  real_T Covariance[36];
  SL_Bus_humanCarFollowerController_geometry_msgs_Twist Twist;
} SL_Bus_humanCarFollowerControlle_TwistWithCovariance_97r4v;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_humanCarFollowerController_nav_msgs_Odometry_
#define DEFINED_TYPEDEF_FOR_SL_Bus_humanCarFollowerController_nav_msgs_Odometry_

typedef struct {
  uint8_T ChildFrameId[128];
  SL_Bus_ROSVariableLengthArrayInfo ChildFrameId_SL_Info;
  SL_Bus_humanCarFollowerController_std_msgs_Header Header;
  SL_Bus_humanCarFollowerControlle_PoseWithCovariance_x7rbgd Pose;
  SL_Bus_humanCarFollowerControlle_TwistWithCovariance_97r4v Twist;
} SL_Bus_humanCarFollowerController_nav_msgs_Odometry;

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

#ifndef typedef_struct_T_humanCarFollowerCont_T
#define typedef_struct_T_humanCarFollowerCont_T

typedef struct {
  char_T f0[4];
} struct_T_humanCarFollowerCont_T;

#endif                                 /*typedef_struct_T_humanCarFollowerCont_T*/

#ifndef typedef_struct_T_humanCarFollowerCo_k_T
#define typedef_struct_T_humanCarFollowerCo_k_T

typedef struct {
  char_T f0[8];
} struct_T_humanCarFollowerCo_k_T;

#endif                                 /*typedef_struct_T_humanCarFollowerCo_k_T*/

#ifndef typedef_struct_T_humanCarFollowerC_k0_T
#define typedef_struct_T_humanCarFollowerC_k0_T

typedef struct {
  char_T f0[7];
} struct_T_humanCarFollowerC_k0_T;

#endif                                 /*typedef_struct_T_humanCarFollowerC_k0_T*/

#ifndef typedef_struct_T_humanCarFollower_k0n_T
#define typedef_struct_T_humanCarFollower_k0n_T

typedef struct {
  char_T f0[8];
  char_T f1[7];
  char_T f2[6];
} struct_T_humanCarFollower_k0n_T;

#endif                                 /*typedef_struct_T_humanCarFollower_k0n_T*/

/* Parameters for system: '<S3>/Enabled Subsystem' */
typedef struct P_EnabledSubsystem_humanCarFo_T_ P_EnabledSubsystem_humanCarFo_T;

/* Parameters (auto storage) */
typedef struct P_humanCarFollowerController_T_ P_humanCarFollowerController_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_humanCarFollowerContr_T RT_MODEL_humanCarFollowerCont_T;

#endif                                 /* RTW_HEADER_humanCarFollowerController_types_h_ */
