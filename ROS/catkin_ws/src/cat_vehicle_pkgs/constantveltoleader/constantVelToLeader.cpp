/*
 * constantVelToLeader.cpp
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

#include "constantVelToLeader.h"
#include "constantVelToLeader_private.h"
#define constantVelToLe_MessageQueueLen (1)

/* Block states (auto storage) */
DW_constantVelToLeader_T constantVelToLeader_DW;

/* Real-time model */
RT_MODEL_constantVelToLeader_T constantVelToLeader_M_;
RT_MODEL_constantVelToLeader_T *const constantVelToLeader_M =
  &constantVelToLeader_M_;

/* Model step function */
void constantVelToLeader_step(void)
{
  SL_Bus_constantVelToLeader_geometry_msgs_Twist rtb_BusAssignment;

  /* BusAssignment: '<Root>/Bus Assignment' incorporates:
   *  Constant: '<Root>/Connstant Velocity'
   *  Constant: '<Root>/Steering angle'
   *  Constant: '<S1>/Constant'
   */
  rtb_BusAssignment = constantVelToLeader_P.Constant_Value;
  rtb_BusAssignment.Linear.X = constantVelToLeader_P.ConnstantVelocity_Value;
  rtb_BusAssignment.Angular.Z = constantVelToLeader_P.Steeringangle_Value;

  /* Outputs for Atomic SubSystem: '<Root>/Publish for Leader Vel' */
  /* Start for MATLABSystem: '<S2>/SinkBlock' incorporates:
   *  MATLABSystem: '<S2>/SinkBlock'
   */
  Pub_constantVelToLeader_27.publish(&rtb_BusAssignment);

  /* End of Outputs for SubSystem: '<Root>/Publish for Leader Vel' */
}

/* Model initialize function */
void constantVelToLeader_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(constantVelToLeader_M, (NULL));

  /* states (dwork) */
  (void) memset((void *)&constantVelToLeader_DW, 0,
                sizeof(DW_constantVelToLeader_T));

  {
    static const char_T tmp[18] = { '/', 'a', 'z', 'c', 'a', 'r', '_', 's', 'i',
      'm', '/', 'c', 'm', 'd', '_', 'v', 'e', 'l' };

    char_T tmp_0[19];
    int32_T i;

    /* Start for Atomic SubSystem: '<Root>/Publish for Leader Vel' */
    /* Start for MATLABSystem: '<S2>/SinkBlock' */
    constantVelToLeader_DW.obj.isInitialized = 0;
    constantVelToLeader_DW.objisempty = true;
    constantVelToLeader_DW.obj.isInitialized = 1;
    for (i = 0; i < 18; i++) {
      tmp_0[i] = tmp[i];
    }

    tmp_0[18] = '\x00';
    Pub_constantVelToLeader_27.createPublisher(tmp_0,
      constantVelToLe_MessageQueueLen);

    /* End of Start for MATLABSystem: '<S2>/SinkBlock' */
    /* End of Start for SubSystem: '<Root>/Publish for Leader Vel' */
  }
}

/* Model terminate function */
void constantVelToLeader_terminate(void)
{
  /* Terminate for Atomic SubSystem: '<Root>/Publish for Leader Vel' */
  /* Start for MATLABSystem: '<S2>/SinkBlock' incorporates:
   *  Terminate for MATLABSystem: '<S2>/SinkBlock'
   */
  if (constantVelToLeader_DW.obj.isInitialized == 1) {
    constantVelToLeader_DW.obj.isInitialized = 2;
  }

  /* End of Start for MATLABSystem: '<S2>/SinkBlock' */
  /* End of Terminate for SubSystem: '<Root>/Publish for Leader Vel' */
}
