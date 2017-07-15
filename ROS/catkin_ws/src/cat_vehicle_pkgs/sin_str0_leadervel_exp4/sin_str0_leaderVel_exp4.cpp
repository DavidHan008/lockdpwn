/*
 * sin_str0_leaderVel_exp4.cpp
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

#include "sin_str0_leaderVel_exp4.h"
#include "sin_str0_leaderVel_exp4_private.h"
#define sin_str0_leader_MessageQueueLen (1)

/* Block states (auto storage) */
DW_sin_str0_leaderVel_exp4_T sin_str0_leaderVel_exp4_DW;

/* Real-time model */
RT_MODEL_sin_str0_leaderVel_e_T sin_str0_leaderVel_exp4_M_;
RT_MODEL_sin_str0_leaderVel_e_T *const sin_str0_leaderVel_exp4_M =
  &sin_str0_leaderVel_exp4_M_;

/* Model step function */
void sin_str0_leaderVel_exp4_step(void)
{
  SL_Bus_sin_str0_leaderVel_exp4_geometry_msgs_Twist rtb_BusAssignment;

  /* BusAssignment: '<Root>/Bus Assignment' incorporates:
   *  Constant: '<Root>/Steering angle'
   *  Constant: '<S1>/Constant'
   *  Sin: '<Root>/Sine Wave Leader Vel Amplitude: 1 Bias: 3 Frequency: 5//2*pi rad//s Phase: 0 '
   */
  rtb_BusAssignment = sin_str0_leaderVel_exp4_P.Constant_Value;
  rtb_BusAssignment.Linear.X = sin
    (sin_str0_leaderVel_exp4_P.SineWaveLeaderVelAmplitude1Bi_p *
     sin_str0_leaderVel_exp4_M->Timing.t[0] +
     sin_str0_leaderVel_exp4_P.SineWaveLeaderVelAmplitude1Bi_e) *
    sin_str0_leaderVel_exp4_P.SineWaveLeaderVelAmplitude1Bias +
    sin_str0_leaderVel_exp4_P.SineWaveLeaderVelAmplitude1Bi_o;
  rtb_BusAssignment.Angular.Z = sin_str0_leaderVel_exp4_P.Steeringangle_Value;

  /* Outputs for Atomic SubSystem: '<Root>/Publish for Leader Vel' */
  /* Start for MATLABSystem: '<S2>/SinkBlock' incorporates:
   *  MATLABSystem: '<S2>/SinkBlock'
   */
  Pub_sin_str0_leaderVel_exp4_27.publish(&rtb_BusAssignment);

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
  if (!(++sin_str0_leaderVel_exp4_M->Timing.clockTick0)) {
    ++sin_str0_leaderVel_exp4_M->Timing.clockTickH0;
  }

  sin_str0_leaderVel_exp4_M->Timing.t[0] =
    sin_str0_leaderVel_exp4_M->Timing.clockTick0 *
    sin_str0_leaderVel_exp4_M->Timing.stepSize0 +
    sin_str0_leaderVel_exp4_M->Timing.clockTickH0 *
    sin_str0_leaderVel_exp4_M->Timing.stepSize0 * 4294967296.0;

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
    sin_str0_leaderVel_exp4_M->Timing.clockTick1++;
    if (!sin_str0_leaderVel_exp4_M->Timing.clockTick1) {
      sin_str0_leaderVel_exp4_M->Timing.clockTickH1++;
    }
  }
}

/* Model initialize function */
void sin_str0_leaderVel_exp4_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)sin_str0_leaderVel_exp4_M, 0,
                sizeof(RT_MODEL_sin_str0_leaderVel_e_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&sin_str0_leaderVel_exp4_M->solverInfo,
                          &sin_str0_leaderVel_exp4_M->Timing.simTimeStep);
    rtsiSetTPtr(&sin_str0_leaderVel_exp4_M->solverInfo, &rtmGetTPtr
                (sin_str0_leaderVel_exp4_M));
    rtsiSetStepSizePtr(&sin_str0_leaderVel_exp4_M->solverInfo,
                       &sin_str0_leaderVel_exp4_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&sin_str0_leaderVel_exp4_M->solverInfo,
                          (&rtmGetErrorStatus(sin_str0_leaderVel_exp4_M)));
    rtsiSetRTModelPtr(&sin_str0_leaderVel_exp4_M->solverInfo,
                      sin_str0_leaderVel_exp4_M);
  }

  rtsiSetSimTimeStep(&sin_str0_leaderVel_exp4_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetSolverName(&sin_str0_leaderVel_exp4_M->solverInfo,"FixedStepDiscrete");
  rtmSetTPtr(sin_str0_leaderVel_exp4_M,
             &sin_str0_leaderVel_exp4_M->Timing.tArray[0]);
  sin_str0_leaderVel_exp4_M->Timing.stepSize0 = 0.2;

  /* states (dwork) */
  (void) memset((void *)&sin_str0_leaderVel_exp4_DW, 0,
                sizeof(DW_sin_str0_leaderVel_exp4_T));

  {
    static const char_T tmp[18] = { '/', 'a', 'z', 'c', 'a', 'r', '_', 's', 'i',
      'm', '/', 'c', 'm', 'd', '_', 'v', 'e', 'l' };

    char_T tmp_0[19];
    int32_T i;

    /* Start for Atomic SubSystem: '<Root>/Publish for Leader Vel' */
    /* Start for MATLABSystem: '<S2>/SinkBlock' */
    sin_str0_leaderVel_exp4_DW.obj.isInitialized = 0;
    sin_str0_leaderVel_exp4_DW.objisempty = true;
    sin_str0_leaderVel_exp4_DW.obj.isInitialized = 1;
    for (i = 0; i < 18; i++) {
      tmp_0[i] = tmp[i];
    }

    tmp_0[18] = '\x00';
    Pub_sin_str0_leaderVel_exp4_27.createPublisher(tmp_0,
      sin_str0_leader_MessageQueueLen);

    /* End of Start for MATLABSystem: '<S2>/SinkBlock' */
    /* End of Start for SubSystem: '<Root>/Publish for Leader Vel' */
  }
}

/* Model terminate function */
void sin_str0_leaderVel_exp4_terminate(void)
{
  /* Terminate for Atomic SubSystem: '<Root>/Publish for Leader Vel' */
  /* Start for MATLABSystem: '<S2>/SinkBlock' incorporates:
   *  Terminate for MATLABSystem: '<S2>/SinkBlock'
   */
  if (sin_str0_leaderVel_exp4_DW.obj.isInitialized == 1) {
    sin_str0_leaderVel_exp4_DW.obj.isInitialized = 2;
  }

  /* End of Start for MATLABSystem: '<S2>/SinkBlock' */
  /* End of Terminate for SubSystem: '<Root>/Publish for Leader Vel' */
}
