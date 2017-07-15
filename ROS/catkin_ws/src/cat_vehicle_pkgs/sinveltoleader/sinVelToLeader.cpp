/*
 * sinVelToLeader.cpp
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

#include "sinVelToLeader.h"
#include "sinVelToLeader_private.h"
#define sinVelToLeader_MessageQueueLen (1)

/* Block states (auto storage) */
DW_sinVelToLeader_T sinVelToLeader_DW;

/* Real-time model */
RT_MODEL_sinVelToLeader_T sinVelToLeader_M_;
RT_MODEL_sinVelToLeader_T *const sinVelToLeader_M = &sinVelToLeader_M_;

/* Model step function */
void sinVelToLeader_step(void)
{
  SL_Bus_sinVelToLeader_geometry_msgs_Twist rtb_BusAssignment;

  /* BusAssignment: '<Root>/Bus Assignment' incorporates:
   *  Abs: '<S3>/Abs'
   *  Constant: '<Root>/Steering angle'
   *  Constant: '<S1>/Constant'
   *  Sin: '<S3>/Sine Wave azcar Vel Comp1'
   *  Sin: '<S3>/Sine Wave azcar Vel Comp2'
   *  Sum: '<S3>/Add'
   */
  rtb_BusAssignment = sinVelToLeader_P.Constant_Value;
  rtb_BusAssignment.Linear.X = (sin(sinVelToLeader_P.SineWaveazcarVelComp2_Freq *
    sinVelToLeader_M->Timing.t[0] + sinVelToLeader_P.SineWaveazcarVelComp2_Phase)
    * sinVelToLeader_P.SineWaveazcarVelComp2_Amp +
    sinVelToLeader_P.SineWaveazcarVelComp2_Bias) + fabs(sin
    (sinVelToLeader_P.SineWaveazcarVelComp1_Freq * sinVelToLeader_M->Timing.t[0]
     + sinVelToLeader_P.SineWaveazcarVelComp1_Phase) *
    sinVelToLeader_P.SineWaveazcarVelComp1_Amp +
    sinVelToLeader_P.SineWaveazcarVelComp1_Bias);
  rtb_BusAssignment.Angular.Z = sinVelToLeader_P.Steeringangle_Value;

  /* Outputs for Atomic SubSystem: '<Root>/Publish for Leader Vel' */
  /* Start for MATLABSystem: '<S2>/SinkBlock' incorporates:
   *  MATLABSystem: '<S2>/SinkBlock'
   */
  Pub_sinVelToLeader_27.publish(&rtb_BusAssignment);

  /* End of Outputs for SubSystem: '<Root>/Publish for Leader Vel' */

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++sinVelToLeader_M->Timing.clockTick0)) {
    ++sinVelToLeader_M->Timing.clockTickH0;
  }

  sinVelToLeader_M->Timing.t[0] = sinVelToLeader_M->Timing.clockTick0 *
    sinVelToLeader_M->Timing.stepSize0 + sinVelToLeader_M->Timing.clockTickH0 *
    sinVelToLeader_M->Timing.stepSize0 * 4294967296.0;

  {
    /* Update absolute timer for sample time: [0.2s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.2, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    sinVelToLeader_M->Timing.clockTick1++;
    if (!sinVelToLeader_M->Timing.clockTick1) {
      sinVelToLeader_M->Timing.clockTickH1++;
    }
  }
}

/* Model initialize function */
void sinVelToLeader_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)sinVelToLeader_M, 0,
                sizeof(RT_MODEL_sinVelToLeader_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&sinVelToLeader_M->solverInfo,
                          &sinVelToLeader_M->Timing.simTimeStep);
    rtsiSetTPtr(&sinVelToLeader_M->solverInfo, &rtmGetTPtr(sinVelToLeader_M));
    rtsiSetStepSizePtr(&sinVelToLeader_M->solverInfo,
                       &sinVelToLeader_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&sinVelToLeader_M->solverInfo, (&rtmGetErrorStatus
      (sinVelToLeader_M)));
    rtsiSetRTModelPtr(&sinVelToLeader_M->solverInfo, sinVelToLeader_M);
  }

  rtsiSetSimTimeStep(&sinVelToLeader_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetSolverName(&sinVelToLeader_M->solverInfo,"FixedStepDiscrete");
  rtmSetTPtr(sinVelToLeader_M, &sinVelToLeader_M->Timing.tArray[0]);
  sinVelToLeader_M->Timing.stepSize0 = 0.2;

  /* states (dwork) */
  (void) memset((void *)&sinVelToLeader_DW, 0,
                sizeof(DW_sinVelToLeader_T));

  {
    static const char_T tmp[18] = { '/', 'a', 'z', 'c', 'a', 'r', '_', 's', 'i',
      'm', '/', 'c', 'm', 'd', '_', 'v', 'e', 'l' };

    char_T tmp_0[19];
    int32_T i;

    /* Start for Atomic SubSystem: '<Root>/Publish for Leader Vel' */
    /* Start for MATLABSystem: '<S2>/SinkBlock' */
    sinVelToLeader_DW.obj.isInitialized = 0;
    sinVelToLeader_DW.objisempty = true;
    sinVelToLeader_DW.obj.isInitialized = 1;
    for (i = 0; i < 18; i++) {
      tmp_0[i] = tmp[i];
    }

    tmp_0[18] = '\x00';
    Pub_sinVelToLeader_27.createPublisher(tmp_0, sinVelToLeader_MessageQueueLen);

    /* End of Start for MATLABSystem: '<S2>/SinkBlock' */
    /* End of Start for SubSystem: '<Root>/Publish for Leader Vel' */
  }
}

/* Model terminate function */
void sinVelToLeader_terminate(void)
{
  /* Terminate for Atomic SubSystem: '<Root>/Publish for Leader Vel' */
  /* Start for MATLABSystem: '<S2>/SinkBlock' incorporates:
   *  Terminate for MATLABSystem: '<S2>/SinkBlock'
   */
  if (sinVelToLeader_DW.obj.isInitialized == 1) {
    sinVelToLeader_DW.obj.isInitialized = 2;
  }

  /* End of Start for MATLABSystem: '<S2>/SinkBlock' */
  /* End of Terminate for SubSystem: '<Root>/Publish for Leader Vel' */
}
