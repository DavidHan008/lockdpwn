/*
 * randomVelToLeader.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "randomVelToLeader".
 *
 * Model version              : 1.21
 * Simulink Coder version : 8.10 (R2016a) 10-Feb-2016
 * C++ source code generated on : Sun May  8 12:47:32 2016
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_randomVelToLeader_h_
#define RTW_HEADER_randomVelToLeader_h_
#include <math.h>
#include <string.h>
#include <stddef.h>
#ifndef randomVelToLeader_COMMON_INCLUDES_
# define randomVelToLeader_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "slros_initialize.h"
#endif                                 /* randomVelToLeader_COMMON_INCLUDES_ */

#include "randomVelToLeader_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

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

/* Block signals (auto storage) */
typedef struct {
  real_T MinMax;                       /* '<S3>/MinMax' */
} B_randomVelToLeader_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T NextOutput;                   /* '<S4>/White Noise' */
  void *SinkBlock_PWORK;               /* '<S2>/SinkBlock' */
  uint32_T RandSeed;                   /* '<S4>/White Noise' */
  robotics_slros_internal_block_T obj; /* '<S2>/SinkBlock' */
  boolean_T objisempty;                /* '<S2>/SinkBlock' */
} DW_randomVelToLeader_T;

/* Parameters (auto storage) */
struct P_randomVelToLeader_T_ {
  SL_Bus_randomVelToLeader_geometry_msgs_Twist Constant_Value;/* Computed Parameter: Constant_Value
                                                               * Referenced by: '<S1>/Constant'
                                                               */
  real_T WhiteNoise_Mean;              /* Expression: 0
                                        * Referenced by: '<S4>/White Noise'
                                        */
  real_T WhiteNoise_StdDev;            /* Computed Parameter: WhiteNoise_StdDev
                                        * Referenced by: '<S4>/White Noise'
                                        */
  real_T WhiteNoise_Seed;              /* Expression: seed
                                        * Referenced by: '<S4>/White Noise'
                                        */
  real_T Output_Gain;                  /* Expression: [sqrt(Cov)]/[sqrt(Ts)]
                                        * Referenced by: '<S4>/Output'
                                        */
  real_T Constant_Value_p;             /* Expression: 4
                                        * Referenced by: '<S3>/Constant'
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
struct tag_RTM_randomVelToLeader_T {
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

  extern P_randomVelToLeader_T randomVelToLeader_P;

#ifdef __cplusplus

}
#endif

/* Block signals (auto storage) */
extern B_randomVelToLeader_T randomVelToLeader_B;

/* Block states (auto storage) */
extern DW_randomVelToLeader_T randomVelToLeader_DW;

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
  extern void randomVelToLeader_initialize(void);
  extern void randomVelToLeader_step(void);
  extern void randomVelToLeader_terminate(void);

#ifdef __cplusplus

}
#endif

/* Real-time Model object */
#ifdef __cplusplus

extern "C" {

#endif

  extern RT_MODEL_randomVelToLeader_T *const randomVelToLeader_M;

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
 * '<Root>' : 'randomVelToLeader'
 * '<S1>'   : 'randomVelToLeader/Blank Message Leader'
 * '<S2>'   : 'randomVelToLeader/Publish for Leader Vel'
 * '<S3>'   : 'randomVelToLeader/Velocity of Leader'
 * '<S4>'   : 'randomVelToLeader/Velocity of Leader/Band-Limited White Noise1'
 */
#endif                                 /* RTW_HEADER_randomVelToLeader_h_ */
