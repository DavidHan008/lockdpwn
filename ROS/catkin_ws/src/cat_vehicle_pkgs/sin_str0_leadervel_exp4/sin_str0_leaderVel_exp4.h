/*
 * sin_str0_leaderVel_exp4.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "sin_str0_leaderVel_exp4".
 *
 * Model version              : 1.26
 * Simulink Coder version : 8.10 (R2016a) 10-Feb-2016
 * C++ source code generated on : Wed May 11 15:04:58 2016
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_sin_str0_leaderVel_exp4_h_
#define RTW_HEADER_sin_str0_leaderVel_exp4_h_
#include <math.h>
#include <string.h>
#include <stddef.h>
#ifndef sin_str0_leaderVel_exp4_COMMON_INCLUDES_
# define sin_str0_leaderVel_exp4_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "slros_initialize.h"
#endif                                 /* sin_str0_leaderVel_exp4_COMMON_INCLUDES_ */

#include "sin_str0_leaderVel_exp4_types.h"

/* Shared type includes */
#include "multiword_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  void *SinkBlock_PWORK;               /* '<S2>/SinkBlock' */
  robotics_slros_internal_block_T obj; /* '<S2>/SinkBlock' */
  boolean_T objisempty;                /* '<S2>/SinkBlock' */
} DW_sin_str0_leaderVel_exp4_T;

/* Parameters (auto storage) */
struct P_sin_str0_leaderVel_exp4_T_ {
  SL_Bus_sin_str0_leaderVel_exp4_geometry_msgs_Twist Constant_Value;/* Computed Parameter: Constant_Value
                                                                     * Referenced by: '<S1>/Constant'
                                                                     */
  real_T SineWaveLeaderVelAmplitude1Bias;/* Expression: 5
                                          * Referenced by: '<Root>/Sine Wave Leader Vel Amplitude: 1 Bias: 3 Frequency: 5//2*pi rad//s Phase: 0 '
                                          */
  real_T SineWaveLeaderVelAmplitude1Bi_o;/* Expression: 3
                                          * Referenced by: '<Root>/Sine Wave Leader Vel Amplitude: 1 Bias: 3 Frequency: 5//2*pi rad//s Phase: 0 '
                                          */
  real_T SineWaveLeaderVelAmplitude1Bi_p;/* Expression: 0.7958
                                          * Referenced by: '<Root>/Sine Wave Leader Vel Amplitude: 1 Bias: 3 Frequency: 5//2*pi rad//s Phase: 0 '
                                          */
  real_T SineWaveLeaderVelAmplitude1Bi_e;/* Expression: 0
                                          * Referenced by: '<Root>/Sine Wave Leader Vel Amplitude: 1 Bias: 3 Frequency: 5//2*pi rad//s Phase: 0 '
                                          */
  real_T Steeringangle_Value;          /* Expression: 0.0
                                        * Referenced by: '<Root>/Steering angle'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_sin_str0_leaderVel_ex_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    SimTimeStep simTimeStep;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block parameters (auto storage) */
#ifdef __cplusplus

extern "C" {

#endif

  extern P_sin_str0_leaderVel_exp4_T sin_str0_leaderVel_exp4_P;

#ifdef __cplusplus

}
#endif

/* Block states (auto storage) */
extern DW_sin_str0_leaderVel_exp4_T sin_str0_leaderVel_exp4_DW;

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
  extern void sin_str0_leaderVel_exp4_initialize(void);
  extern void sin_str0_leaderVel_exp4_step(void);
  extern void sin_str0_leaderVel_exp4_terminate(void);

#ifdef __cplusplus

}
#endif

/* Real-time Model object */
#ifdef __cplusplus

extern "C" {

#endif

  extern RT_MODEL_sin_str0_leaderVel_e_T *const sin_str0_leaderVel_exp4_M;

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
 * '<Root>' : 'sin_str0_leaderVel_exp4'
 * '<S1>'   : 'sin_str0_leaderVel_exp4/Blank Message Leader'
 * '<S2>'   : 'sin_str0_leaderVel_exp4/Publish for Leader Vel'
 */
#endif                                 /* RTW_HEADER_sin_str0_leaderVel_exp4_h_ */
