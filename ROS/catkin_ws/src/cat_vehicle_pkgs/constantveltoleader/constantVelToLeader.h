/*
 * constantVelToLeader.h
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

#ifndef RTW_HEADER_constantVelToLeader_h_
#define RTW_HEADER_constantVelToLeader_h_
#include <stddef.h>
#include <string.h>
#ifndef constantVelToLeader_COMMON_INCLUDES_
# define constantVelToLeader_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "slros_initialize.h"
#endif                                 /* constantVelToLeader_COMMON_INCLUDES_ */

#include "constantVelToLeader_types.h"

/* Shared type includes */
#include "multiword_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  void *SinkBlock_PWORK;               /* '<S2>/SinkBlock' */
  robotics_slros_internal_block_T obj; /* '<S2>/SinkBlock' */
  boolean_T objisempty;                /* '<S2>/SinkBlock' */
} DW_constantVelToLeader_T;

/* Parameters (auto storage) */
struct P_constantVelToLeader_T_ {
  SL_Bus_constantVelToLeader_geometry_msgs_Twist Constant_Value;/* Computed Parameter: Constant_Value
                                                                 * Referenced by: '<S1>/Constant'
                                                                 */
  real_T ConnstantVelocity_Value;      /* Expression: 5.0
                                        * Referenced by: '<Root>/Connstant Velocity'
                                        */
  real_T Steeringangle_Value;          /* Expression: 0.0
                                        * Referenced by: '<Root>/Steering angle'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_constantVelToLeader_T {
  const char_T *errorStatus;
};

/* Block parameters (auto storage) */
#ifdef __cplusplus

extern "C" {

#endif

  extern P_constantVelToLeader_T constantVelToLeader_P;

#ifdef __cplusplus

}
#endif

/* Block states (auto storage) */
extern DW_constantVelToLeader_T constantVelToLeader_DW;

#ifdef __cplusplus

extern "C" {

#endif

#ifdef __cplusplus

}
#endif

#ifdef __cplusplus

extern "C" {

#endif

  /* Model entry point functions */
  extern void constantVelToLeader_initialize(void);
  extern void constantVelToLeader_step(void);
  extern void constantVelToLeader_terminate(void);

#ifdef __cplusplus

}
#endif

/* Real-time Model object */
#ifdef __cplusplus

extern "C" {

#endif

  extern RT_MODEL_constantVelToLeader_T *const constantVelToLeader_M;

#ifdef __cplusplus

}
#endif

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'constantVelToLeader'
 * '<S1>'   : 'constantVelToLeader/Blank Message Leader'
 * '<S2>'   : 'constantVelToLeader/Publish for Leader Vel'
 */
#endif                                 /* RTW_HEADER_constantVelToLeader_h_ */
