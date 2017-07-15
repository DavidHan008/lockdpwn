/*
 * sinVelToLeader.h
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

#ifndef RTW_HEADER_sinVelToLeader_h_
#define RTW_HEADER_sinVelToLeader_h_
#include <math.h>
#include <string.h>
#include <stddef.h>
#ifndef sinVelToLeader_COMMON_INCLUDES_
# define sinVelToLeader_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "slros_initialize.h"
#endif                                 /* sinVelToLeader_COMMON_INCLUDES_ */

#include "sinVelToLeader_types.h"

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
} DW_sinVelToLeader_T;

/* Parameters (auto storage) */
struct P_sinVelToLeader_T_ {
  SL_Bus_sinVelToLeader_geometry_msgs_Twist Constant_Value;/* Computed Parameter: Constant_Value
                                                            * Referenced by: '<S1>/Constant'
                                                            */
  real_T SineWaveazcarVelComp2_Amp;    /* Expression: 5
                                        * Referenced by: '<S3>/Sine Wave azcar Vel Comp2'
                                        */
  real_T SineWaveazcarVelComp2_Bias;   /* Expression: 0
                                        * Referenced by: '<S3>/Sine Wave azcar Vel Comp2'
                                        */
  real_T SineWaveazcarVelComp2_Freq;   /* Expression: 2
                                        * Referenced by: '<S3>/Sine Wave azcar Vel Comp2'
                                        */
  real_T SineWaveazcarVelComp2_Phase;  /* Expression: 0.3
                                        * Referenced by: '<S3>/Sine Wave azcar Vel Comp2'
                                        */
  real_T SineWaveazcarVelComp1_Amp;    /* Expression: 5
                                        * Referenced by: '<S3>/Sine Wave azcar Vel Comp1'
                                        */
  real_T SineWaveazcarVelComp1_Bias;   /* Expression: 0
                                        * Referenced by: '<S3>/Sine Wave azcar Vel Comp1'
                                        */
  real_T SineWaveazcarVelComp1_Freq;   /* Expression: 3
                                        * Referenced by: '<S3>/Sine Wave azcar Vel Comp1'
                                        */
  real_T SineWaveazcarVelComp1_Phase;  /* Expression: 0
                                        * Referenced by: '<S3>/Sine Wave azcar Vel Comp1'
                                        */
  real_T Steeringangle_Value;          /* Expression: 0.0
                                        * Referenced by: '<Root>/Steering angle'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_sinVelToLeader_T {
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

  extern P_sinVelToLeader_T sinVelToLeader_P;

#ifdef __cplusplus

}
#endif

/* Block states (auto storage) */
extern DW_sinVelToLeader_T sinVelToLeader_DW;

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
  extern void sinVelToLeader_initialize(void);
  extern void sinVelToLeader_step(void);
  extern void sinVelToLeader_terminate(void);

#ifdef __cplusplus

}
#endif

/* Real-time Model object */
#ifdef __cplusplus

extern "C" {

#endif

  extern RT_MODEL_sinVelToLeader_T *const sinVelToLeader_M;

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
 * '<Root>' : 'sinVelToLeader'
 * '<S1>'   : 'sinVelToLeader/Blank Message Leader'
 * '<S2>'   : 'sinVelToLeader/Publish for Leader Vel'
 * '<S3>'   : 'sinVelToLeader/Velocity of Leader'
 */
#endif                                 /* RTW_HEADER_sinVelToLeader_h_ */
