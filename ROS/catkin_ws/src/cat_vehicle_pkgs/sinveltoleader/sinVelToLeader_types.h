/*
 * sinVelToLeader_types.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "sinVelToLeader".
 *
 * Model version              : 1.23
 * Simulink Coder version : 8.10 (R2016a) 10-Feb-2016
 * C++ source code generated on : Sun May  8 13:11:46 2016
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_sinVelToLeader_types_h_
#define RTW_HEADER_sinVelToLeader_types_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_sinVelToLeader_geometry_msgs_Vector3_
#define DEFINED_TYPEDEF_FOR_SL_Bus_sinVelToLeader_geometry_msgs_Vector3_

typedef struct {
  real_T X;
  real_T Y;
  real_T Z;
} SL_Bus_sinVelToLeader_geometry_msgs_Vector3;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_sinVelToLeader_geometry_msgs_Twist_
#define DEFINED_TYPEDEF_FOR_SL_Bus_sinVelToLeader_geometry_msgs_Twist_

typedef struct {
  SL_Bus_sinVelToLeader_geometry_msgs_Vector3 Linear;
  SL_Bus_sinVelToLeader_geometry_msgs_Vector3 Angular;
} SL_Bus_sinVelToLeader_geometry_msgs_Twist;

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

#ifndef typedef_struct_T_sinVelToLeader_T
#define typedef_struct_T_sinVelToLeader_T

typedef struct {
  char_T f0[4];
} struct_T_sinVelToLeader_T;

#endif                                 /*typedef_struct_T_sinVelToLeader_T*/

#ifndef typedef_struct_T_sinVelToLeader_m_T
#define typedef_struct_T_sinVelToLeader_m_T

typedef struct {
  char_T f0[8];
} struct_T_sinVelToLeader_m_T;

#endif                                 /*typedef_struct_T_sinVelToLeader_m_T*/

#ifndef typedef_struct_T_sinVelToLeader_mw_T
#define typedef_struct_T_sinVelToLeader_mw_T

typedef struct {
  char_T f0[7];
} struct_T_sinVelToLeader_mw_T;

#endif                                 /*typedef_struct_T_sinVelToLeader_mw_T*/

#ifndef typedef_struct_T_sinVelToLeader_mw3_T
#define typedef_struct_T_sinVelToLeader_mw3_T

typedef struct {
  char_T f0[8];
  char_T f1[7];
  char_T f2[6];
} struct_T_sinVelToLeader_mw3_T;

#endif                                 /*typedef_struct_T_sinVelToLeader_mw3_T*/

/* Parameters (auto storage) */
typedef struct P_sinVelToLeader_T_ P_sinVelToLeader_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_sinVelToLeader_T RT_MODEL_sinVelToLeader_T;

#endif                                 /* RTW_HEADER_sinVelToLeader_types_h_ */
