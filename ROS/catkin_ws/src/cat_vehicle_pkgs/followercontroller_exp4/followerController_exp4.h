/*
 * followerController_exp4.h
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

#ifndef RTW_HEADER_followerController_exp4_h_
#define RTW_HEADER_followerController_exp4_h_
#include <math.h>
#include <stddef.h>
#include <string.h>
#ifndef followerController_exp4_COMMON_INCLUDES_
# define followerController_exp4_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "slros_initialize.h"
#endif                                 /* followerController_exp4_COMMON_INCLUDES_ */

#include "followerController_exp4_types.h"

/* Shared type includes */
#include "multiword_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals for system '<S4>/Enabled Subsystem' */
typedef struct {
  SL_Bus_followerController_exp4_nav_msgs_Odometry In1;/* '<S9>/In1' */
} B_EnabledSubsystem_followerCo_T;

/* Block signals (auto storage) */
typedef struct {
  SL_Bus_followerController_exp4_nav_msgs_Odometry SourceBlock_o2;/* '<S5>/SourceBlock' */
  SL_Bus_followerController_exp4_geometry_msgs_Twist In1;/* '<S11>/In1' */
  SL_Bus_followerController_exp4_geometry_msgs_Twist BusAssignment1;/* '<Root>/Bus Assignment1' */
  char_T cv0[22];
  B_EnabledSubsystem_followerCo_T EnabledSubsystem_f;/* '<S5>/Enabled Subsystem' */
  B_EnabledSubsystem_followerCo_T EnabledSubsystem;/* '<S4>/Enabled Subsystem' */
} B_followerController_exp4_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  void *SinkBlock_PWORK;               /* '<S8>/SinkBlock' */
  void *SinkBlock_PWORK_d;             /* '<S7>/SinkBlock' */
  void *SourceBlock_PWORK;             /* '<S6>/SourceBlock' */
  void *SourceBlock_PWORK_a;           /* '<S5>/SourceBlock' */
  void *SourceBlock_PWORK_n;           /* '<S4>/SourceBlock' */
  robotics_slros_internal_block_T obj; /* '<S6>/SourceBlock' */
  robotics_slros_internal_block_T obj_f;/* '<S5>/SourceBlock' */
  robotics_slros_internal_block_T obj_ff;/* '<S4>/SourceBlock' */
  robotics_slros_internal_blo_k_T obj_l;/* '<S8>/SinkBlock' */
  robotics_slros_internal_blo_k_T obj_m;/* '<S7>/SinkBlock' */
  boolean_T objisempty;                /* '<S8>/SinkBlock' */
  boolean_T objisempty_m;              /* '<S7>/SinkBlock' */
  boolean_T objisempty_l;              /* '<S6>/SourceBlock' */
  boolean_T objisempty_h;              /* '<S5>/SourceBlock' */
  boolean_T objisempty_a;              /* '<S4>/SourceBlock' */
} DW_followerController_exp4_T;

/* Parameters for system: '<S4>/Enabled Subsystem' */
struct P_EnabledSubsystem_followerCo_T_ {
  SL_Bus_followerController_exp4_nav_msgs_Odometry Out1_Y0;/* Computed Parameter: Out1_Y0
                                                            * Referenced by: '<S9>/Out1'
                                                            */
};

/* Parameters (auto storage) */
struct P_followerController_exp4_T_ {
  SL_Bus_followerController_exp4_nav_msgs_Odometry Constant_Value;/* Computed Parameter: Constant_Value
                                                                   * Referenced by: '<S4>/Constant'
                                                                   */
  SL_Bus_followerController_exp4_nav_msgs_Odometry Constant_Value_j;/* Computed Parameter: Constant_Value_j
                                                                     * Referenced by: '<S5>/Constant'
                                                                     */
  SL_Bus_followerController_exp4_geometry_msgs_Twist Out1_Y0;/* Computed Parameter: Out1_Y0
                                                              * Referenced by: '<S11>/Out1'
                                                              */
  SL_Bus_followerController_exp4_geometry_msgs_Twist Constant_Value_h;/* Computed Parameter: Constant_Value_h
                                                                      * Referenced by: '<S6>/Constant'
                                                                      */
  SL_Bus_followerController_exp4_geometry_msgs_Twist Constant_Value_l;/* Computed Parameter: Constant_Value_l
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
  SL_Bus_followerController_exp4_std_msgs_Float64 Constant_Value_e;/* Computed Parameter: Constant_Value_e
                                                                    * Referenced by: '<S2>/Constant'
                                                                    */
  P_EnabledSubsystem_followerCo_T EnabledSubsystem_f;/* '<S5>/Enabled Subsystem' */
  P_EnabledSubsystem_followerCo_T EnabledSubsystem;/* '<S4>/Enabled Subsystem' */
};

/* Real-time Model Data Structure */
struct tag_RTM_followerController_ex_T {
  const char_T *errorStatus;
};

/* Block parameters (auto storage) */
#ifdef __cplusplus

extern "C" {

#endif

  extern P_followerController_exp4_T followerController_exp4_P;

#ifdef __cplusplus

}
#endif

/* Block signals (auto storage) */
extern B_followerController_exp4_T followerController_exp4_B;

/* Block states (auto storage) */
extern DW_followerController_exp4_T followerController_exp4_DW;

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
  extern void followerController_exp4_initialize(void);
  extern void followerController_exp4_step(void);
  extern void followerController_exp4_terminate(void);

#ifdef __cplusplus

}
#endif

/* Real-time Model object */
#ifdef __cplusplus

extern "C" {

#endif

  extern RT_MODEL_followerController_e_T *const followerController_exp4_M;

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
 * '<Root>' : 'followerController_exp4'
 * '<S1>'   : 'followerController_exp4/Blank Message Follower1'
 * '<S2>'   : 'followerController_exp4/Blank Message2'
 * '<S3>'   : 'followerController_exp4/Distance between  leader and follower'
 * '<S4>'   : 'followerController_exp4/Follower's positions'
 * '<S5>'   : 'followerController_exp4/Leader's Position'
 * '<S6>'   : 'followerController_exp4/Leader's Velocity'
 * '<S7>'   : 'followerController_exp4/Publish for follower vel'
 * '<S8>'   : 'followerController_exp4/Publish for headway distance experienced by follower'
 * '<S9>'   : 'followerController_exp4/Follower's positions/Enabled Subsystem'
 * '<S10>'  : 'followerController_exp4/Leader's Position/Enabled Subsystem'
 * '<S11>'  : 'followerController_exp4/Leader's Velocity/Enabled Subsystem'
 */
#endif                                 /* RTW_HEADER_followerController_exp4_h_ */
