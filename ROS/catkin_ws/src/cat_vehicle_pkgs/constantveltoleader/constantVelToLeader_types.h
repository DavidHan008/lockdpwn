/*
 * constantVelToLeader_types.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "constantVelToLeader".
 *
 * Model version              : 1.22
 * Simulink Coder version : 8.10 (R2016a) 10-Feb-2016
 * C++ source code generated on : Sun May  8 13:05:07 2016
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_constantVelToLeader_types_h_
#define RTW_HEADER_constantVelToLeader_types_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_constantVelToLeader_geometry_msgs_Vector3_
#define DEFINED_TYPEDEF_FOR_SL_Bus_constantVelToLeader_geometry_msgs_Vector3_

typedef struct {
  real_T X;
  real_T Y;
  real_T Z;
} SL_Bus_constantVelToLeader_geometry_msgs_Vector3;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_constantVelToLeader_geometry_msgs_Twist_
#define DEFINED_TYPEDEF_FOR_SL_Bus_constantVelToLeader_geometry_msgs_Twist_

typedef struct {
  SL_Bus_constantVelToLeader_geometry_msgs_Vector3 Linear;
  SL_Bus_constantVelToLeader_geometry_msgs_Vector3 Angular;
} SL_Bus_constantVelToLeader_geometry_msgs_Twist;

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

#ifndef typedef_struct_T_constantVelToLeader_T
#define typedef_struct_T_constantVelToLeader_T

typedef struct {
  char_T f0[4];
} struct_T_constantVelToLeader_T;

#endif                                 /*typedef_struct_T_constantVelToLeader_T*/

#ifndef typedef_struct_T_constantVelToLeade_e_T
#define typedef_struct_T_constantVelToLeade_e_T

typedef struct {
  char_T f0[8];
} struct_T_constantVelToLeade_e_T;

#endif                                 /*typedef_struct_T_constantVelToLeade_e_T*/

#ifndef typedef_struct_T_constantVelToLead_em_T
#define typedef_struct_T_constantVelToLead_em_T

typedef struct {
  char_T f0[7];
} struct_T_constantVelToLead_em_T;

#endif                                 /*typedef_struct_T_constantVelToLead_em_T*/

#ifndef typedef_struct_T_constantVelToLea_emq_T
#define typedef_struct_T_constantVelToLea_emq_T

typedef struct {
  char_T f0[8];
  char_T f1[7];
  char_T f2[6];
} struct_T_constantVelToLea_emq_T;

#endif                                 /*typedef_struct_T_constantVelToLea_emq_T*/

/* Parameters (auto storage) */
typedef struct P_constantVelToLeader_T_ P_constantVelToLeader_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_constantVelToLeader_T RT_MODEL_constantVelToLeader_T;

#endif                                 /* RTW_HEADER_constantVelToLeader_types_h_ */
