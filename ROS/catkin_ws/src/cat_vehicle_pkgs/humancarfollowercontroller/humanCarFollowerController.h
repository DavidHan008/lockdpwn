/*
 * humanCarFollowerController.h
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

#ifndef RTW_HEADER_humanCarFollowerController_h_
#define RTW_HEADER_humanCarFollowerController_h_
#include <math.h>
#include <stddef.h>
#include <string.h>
#ifndef humanCarFollowerController_COMMON_INCLUDES_
# define humanCarFollowerController_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "slros_initialize.h"
#endif                                 /* humanCarFollowerController_COMMON_INCLUDES_ */

#include "humanCarFollowerController_types.h"

/* Shared type includes */
#include "multiword_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals for system '<S3>/Enabled Subsystem' */
typedef struct {
  SL_Bus_humanCarFollowerController_nav_msgs_Odometry In1;/* '<S7>/In1' */
} B_EnabledSubsystem_humanCarFo_T;

/* Block signals (auto storage) */
typedef struct {
  SL_Bus_humanCarFollowerController_nav_msgs_Odometry SourceBlock_o2;/* '<S4>/SourceBlock' */
  SL_Bus_humanCarFollowerController_geometry_msgs_Twist In1;/* '<S9>/In1' */
  SL_Bus_humanCarFollowerController_geometry_msgs_Twist BusAssignment1;/* '<Root>/Bus Assignment1' */
  char_T cv0[22];
  B_EnabledSubsystem_humanCarFo_T EnabledSubsystem_f;/* '<S4>/Enabled Subsystem' */
  B_EnabledSubsystem_humanCarFo_T EnabledSubsystem;/* '<S3>/Enabled Subsystem' */
} B_humanCarFollowerController_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  void *SinkBlock_PWORK;               /* '<S6>/SinkBlock' */
  void *SourceBlock_PWORK;             /* '<S5>/SourceBlock' */
  void *SourceBlock_PWORK_a;           /* '<S4>/SourceBlock' */
  void *SourceBlock_PWORK_n;           /* '<S3>/SourceBlock' */
  robotics_slros_internal_block_T obj; /* '<S5>/SourceBlock' */
  robotics_slros_internal_block_T obj_f;/* '<S4>/SourceBlock' */
  robotics_slros_internal_block_T obj_ff;/* '<S3>/SourceBlock' */
  robotics_slros_internal_blo_k_T obj_m;/* '<S6>/SinkBlock' */
  boolean_T objisempty;                /* '<S6>/SinkBlock' */
  boolean_T objisempty_l;              /* '<S5>/SourceBlock' */
  boolean_T objisempty_h;              /* '<S4>/SourceBlock' */
  boolean_T objisempty_a;              /* '<S3>/SourceBlock' */
} DW_humanCarFollowerController_T;

/* Parameters for system: '<S3>/Enabled Subsystem' */
struct P_EnabledSubsystem_humanCarFo_T_ {
  SL_Bus_humanCarFollowerController_nav_msgs_Odometry Out1_Y0;/* Computed Parameter: Out1_Y0
                                                               * Referenced by: '<S7>/Out1'
                                                               */
};

/* Parameters (auto storage) */
struct P_humanCarFollowerController_T_ {
  SL_Bus_humanCarFollowerController_nav_msgs_Odometry Constant_Value;/* Computed Parameter: Constant_Value
                                                                      * Referenced by: '<S3>/Constant'
                                                                      */
  SL_Bus_humanCarFollowerController_nav_msgs_Odometry Constant_Value_j;/* Computed Parameter: Constant_Value_j
                                                                      * Referenced by: '<S4>/Constant'
                                                                      */
  SL_Bus_humanCarFollowerController_geometry_msgs_Twist Out1_Y0;/* Computed Parameter: Out1_Y0
                                                                 * Referenced by: '<S9>/Out1'
                                                                 */
  SL_Bus_humanCarFollowerController_geometry_msgs_Twist Constant_Value_h;/* Computed Parameter: Constant_Value_h
                                                                      * Referenced by: '<S5>/Constant'
                                                                      */
  SL_Bus_humanCarFollowerController_geometry_msgs_Twist Constant_Value_l;/* Computed Parameter: Constant_Value_l
                                                                      * Referenced by: '<S1>/Constant'
                                                                      */
  real_T u30_Value;                    /* Expression: 1/30
                                        * Referenced by: '<Root>/1//30'
                                        */
  real_T u3_Value;                     /* Expression: 2/3
                                        * Referenced by: '<Root>/2//3'
                                        */
  real_T Steeringangle_Value;          /* Expression: 0.0
                                        * Referenced by: '<Root>/Steering angle'
                                        */
  P_EnabledSubsystem_humanCarFo_T EnabledSubsystem_f;/* '<S4>/Enabled Subsystem' */
  P_EnabledSubsystem_humanCarFo_T EnabledSubsystem;/* '<S3>/Enabled Subsystem' */
};

/* Real-time Model Data Structure */
struct tag_RTM_humanCarFollowerContr_T {
  const char_T *errorStatus;
};

/* Block parameters (auto storage) */
#ifdef __cplusplus

extern "C" {

#endif

  extern P_humanCarFollowerController_T humanCarFollowerController_P;

#ifdef __cplusplus

}
#endif

/* Block signals (auto storage) */
extern B_humanCarFollowerController_T humanCarFollowerController_B;

/* Block states (auto storage) */
extern DW_humanCarFollowerController_T humanCarFollowerController_DW;

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
  extern void humanCarFollowerController_initialize(void);
  extern void humanCarFollowerController_step(void);
  extern void humanCarFollowerController_terminate(void);

#ifdef __cplusplus

}
#endif

/* Real-time Model object */
#ifdef __cplusplus

extern "C" {

#endif

  extern RT_MODEL_humanCarFollowerCont_T *const humanCarFollowerController_M;

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
 * '<Root>' : 'humanCarFollowerController'
 * '<S1>'   : 'humanCarFollowerController/Blank Message Follower1'
 * '<S2>'   : 'humanCarFollowerController/Distance between  leader and follower'
 * '<S3>'   : 'humanCarFollowerController/Follower's positions'
 * '<S4>'   : 'humanCarFollowerController/Leader's Position'
 * '<S5>'   : 'humanCarFollowerController/Leader's Velocity'
 * '<S6>'   : 'humanCarFollowerController/Publish for follower vel'
 * '<S7>'   : 'humanCarFollowerController/Follower's positions/Enabled Subsystem'
 * '<S8>'   : 'humanCarFollowerController/Leader's Position/Enabled Subsystem'
 * '<S9>'   : 'humanCarFollowerController/Leader's Velocity/Enabled Subsystem'
 */
#endif                                 /* RTW_HEADER_humanCarFollowerController_h_ */
