/*
 * followerController_exp4.cpp
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

#include "followerController_exp4.h"
#include "followerController_exp4_private.h"
#define followerControl_MessageQueueLen (1L)

/* Block signals (auto storage) */
B_followerController_exp4_T followerController_exp4_B;

/* Block states (auto storage) */
DW_followerController_exp4_T followerController_exp4_DW;

/* Real-time model */
RT_MODEL_followerController_e_T followerController_exp4_M_;
RT_MODEL_followerController_e_T *const followerController_exp4_M =
  &followerController_exp4_M_;

/*
 * System initialize for enable system:
 *    '<S4>/Enabled Subsystem'
 *    '<S5>/Enabled Subsystem'
 */
void followerC_EnabledSubsystem_Init(B_EnabledSubsystem_followerCo_T *localB,
  P_EnabledSubsystem_followerCo_T *localP)
{
  /* SystemInitialize for Outport: '<S9>/Out1' */
  localB->In1 = localP->Out1_Y0;
}

/*
 * Output and update for enable system:
 *    '<S4>/Enabled Subsystem'
 *    '<S5>/Enabled Subsystem'
 */
void followerContro_EnabledSubsystem(boolean_T rtu_Enable, const
  SL_Bus_followerController_exp4_nav_msgs_Odometry *rtu_In1,
  B_EnabledSubsystem_followerCo_T *localB)
{
  /* Outputs for Enabled SubSystem: '<S4>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S9>/Enable'
   */
  if (rtu_Enable) {
    /* Inport: '<S9>/In1' */
    localB->In1 = *rtu_In1;
  }

  /* End of Outputs for SubSystem: '<S4>/Enabled Subsystem' */
}

/* Model step function */
void followerController_exp4_step(void)
{
  boolean_T varargout_1;
  real_T rtb_Sqrt;
  real_T rtb_X1X22;
  SL_Bus_followerController_exp4_std_msgs_Float64 rtb_BusAssignment2;

  /* Outputs for Atomic SubSystem: '<Root>/Leader's Velocity' */
  /* Start for MATLABSystem: '<S6>/SourceBlock' incorporates:
   *  Inport: '<S11>/In1'
   *  MATLABSystem: '<S6>/SourceBlock'
   */
  varargout_1 = Sub_followerController_exp4_38.getLatestMessage
    (&followerController_exp4_B.BusAssignment1);

  /* Outputs for Enabled SubSystem: '<S6>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S11>/Enable'
   */
  if (varargout_1) {
    followerController_exp4_B.In1 = followerController_exp4_B.BusAssignment1;
  }

  /* End of Start for MATLABSystem: '<S6>/SourceBlock' */
  /* End of Outputs for SubSystem: '<S6>/Enabled Subsystem' */
  /* End of Outputs for SubSystem: '<Root>/Leader's Velocity' */

  /* Outputs for Atomic SubSystem: '<Root>/Leader's Position' */
  /* Start for MATLABSystem: '<S5>/SourceBlock' incorporates:
   *  MATLABSystem: '<S5>/SourceBlock'
   */
  varargout_1 = Sub_followerController_exp4_40.getLatestMessage
    (&followerController_exp4_B.SourceBlock_o2);

  /* Outputs for Enabled SubSystem: '<S5>/Enabled Subsystem' */
  followerContro_EnabledSubsystem(varargout_1,
    &followerController_exp4_B.SourceBlock_o2,
    &followerController_exp4_B.EnabledSubsystem_f);

  /* End of Outputs for SubSystem: '<S5>/Enabled Subsystem' */

  /* End of Outputs for SubSystem: '<Root>/Leader's Position' */

  /* Outputs for Atomic SubSystem: '<Root>/Follower's positions' */
  /* Start for MATLABSystem: '<S4>/SourceBlock' incorporates:
   *  MATLABSystem: '<S4>/SourceBlock'
   */
  varargout_1 = Sub_followerController_exp4_43.getLatestMessage
    (&followerController_exp4_B.SourceBlock_o2);

  /* Outputs for Enabled SubSystem: '<S4>/Enabled Subsystem' */
  followerContro_EnabledSubsystem(varargout_1,
    &followerController_exp4_B.SourceBlock_o2,
    &followerController_exp4_B.EnabledSubsystem);

  /* End of Outputs for SubSystem: '<S4>/Enabled Subsystem' */

  /* End of Outputs for SubSystem: '<Root>/Follower's positions' */

  /* Sum: '<S3>/X1-X2' */
  rtb_Sqrt =
    followerController_exp4_B.EnabledSubsystem_f.In1.Pose.Pose.Position.X -
    followerController_exp4_B.EnabledSubsystem.In1.Pose.Pose.Position.X;

  /* Product: '<S3>/(X1-X2)^2' */
  rtb_X1X22 = rtb_Sqrt * rtb_Sqrt;

  /* Sum: '<S3>/Y1-Y2' */
  rtb_Sqrt =
    followerController_exp4_B.EnabledSubsystem_f.In1.Pose.Pose.Position.Y -
    followerController_exp4_B.EnabledSubsystem.In1.Pose.Pose.Position.Y;

  /* Sqrt: '<S3>/Sqrt' incorporates:
   *  Product: '<S3>/(Y1-Y2)^2'
   *  Sum: '<S3>/(X1-X2)^2 + (Y1-Y2)^2'
   */
  rtb_Sqrt = sqrt(rtb_Sqrt * rtb_Sqrt + rtb_X1X22);

  /* BusAssignment: '<Root>/Bus Assignment1' incorporates:
   *  Constant: '<Root>/1//30'
   *  Constant: '<Root>/2//3'
   *  Constant: '<Root>/Steering angle'
   *  Constant: '<S1>/Constant'
   *  Product: '<Root>/Product'
   *  Product: '<Root>/Velocity of Follower1'
   *  Sum: '<Root>/FactorB'
   */
  followerController_exp4_B.BusAssignment1 =
    followerController_exp4_P.Constant_Value_l;
  followerController_exp4_B.BusAssignment1.Linear.X = (rtb_Sqrt *
    followerController_exp4_P.u30_Value + followerController_exp4_P.u3_Value) *
    followerController_exp4_B.In1.Linear.X;
  followerController_exp4_B.BusAssignment1.Angular.Z =
    followerController_exp4_P.Steeringangle_Value;

  /* Outputs for Atomic SubSystem: '<Root>/Publish for follower vel' */
  /* Start for MATLABSystem: '<S7>/SinkBlock' incorporates:
   *  MATLABSystem: '<S7>/SinkBlock'
   */
  Pub_followerController_exp4_21.publish
    (&followerController_exp4_B.BusAssignment1);

  /* End of Outputs for SubSystem: '<Root>/Publish for follower vel' */

  /* BusAssignment: '<Root>/Bus Assignment2' */
  rtb_BusAssignment2.Data = rtb_Sqrt;

  /* Outputs for Atomic SubSystem: '<Root>/Publish for headway distance experienced by follower' */
  /* Start for MATLABSystem: '<S8>/SinkBlock' incorporates:
   *  MATLABSystem: '<S8>/SinkBlock'
   */
  Pub_followerController_exp4_61.publish(&rtb_BusAssignment2);

  /* End of Outputs for SubSystem: '<Root>/Publish for headway distance experienced by follower' */
}

/* Model initialize function */
void followerController_exp4_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(followerController_exp4_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &followerController_exp4_B), 0,
                sizeof(B_followerController_exp4_T));

  /* states (dwork) */
  (void) memset((void *)&followerController_exp4_DW, 0,
                sizeof(DW_followerController_exp4_T));

  {
    static const char_T tmp[21] = { '/', 'f', 'o', 'l', 'l', 'o', 'w', 'e', 'r',
      '_', 's', 'i', 'm', '/', 'h', 'e', 'a', 'd', 'w', 'a', 'y' };

    static const char_T tmp_0[21] = { '/', 'f', 'o', 'l', 'l', 'o', 'w', 'e',
      'r', '_', 's', 'i', 'm', '/', 'c', 'm', 'd', '_', 'v', 'e', 'l' };

    static const char_T tmp_1[18] = { '/', 'f', 'o', 'l', 'l', 'o', 'w', 'e',
      'r', '_', 's', 'i', 'm', '/', 'o', 'd', 'o', 'm' };

    static const char_T tmp_2[15] = { '/', 'a', 'z', 'c', 'a', 'r', '_', 's',
      'i', 'm', '/', 'o', 'd', 'o', 'm' };

    static const char_T tmp_3[14] = { '/', 'a', 'z', 'c', 'a', 'r', '_', 's',
      'i', 'm', '/', 'v', 'e', 'l' };

    char_T tmp_4[19];
    char_T tmp_5[16];
    char_T tmp_6[15];
    int16_T i;

    /* Start for Atomic SubSystem: '<Root>/Leader's Velocity' */
    /* Start for MATLABSystem: '<S6>/SourceBlock' */
    followerController_exp4_DW.obj.isInitialized = 0L;
    followerController_exp4_DW.objisempty_l = true;
    followerController_exp4_DW.obj.isInitialized = 1L;
    for (i = 0; i < 14; i++) {
      tmp_6[i] = tmp_3[i];
    }

    tmp_6[14] = '\x00';
    Sub_followerController_exp4_38.createSubscriber(tmp_6,
      followerControl_MessageQueueLen);

    /* End of Start for MATLABSystem: '<S6>/SourceBlock' */
    /* End of Start for SubSystem: '<Root>/Leader's Velocity' */

    /* Start for Atomic SubSystem: '<Root>/Leader's Position' */
    /* Start for MATLABSystem: '<S5>/SourceBlock' */
    followerController_exp4_DW.obj_f.isInitialized = 0L;
    followerController_exp4_DW.objisempty_h = true;
    followerController_exp4_DW.obj_f.isInitialized = 1L;
    for (i = 0; i < 15; i++) {
      tmp_5[i] = tmp_2[i];
    }

    tmp_5[15] = '\x00';
    Sub_followerController_exp4_40.createSubscriber(tmp_5,
      followerControl_MessageQueueLen);

    /* End of Start for MATLABSystem: '<S5>/SourceBlock' */
    /* End of Start for SubSystem: '<Root>/Leader's Position' */

    /* Start for Atomic SubSystem: '<Root>/Follower's positions' */
    /* Start for MATLABSystem: '<S4>/SourceBlock' */
    followerController_exp4_DW.obj_ff.isInitialized = 0L;
    followerController_exp4_DW.objisempty_a = true;
    followerController_exp4_DW.obj_ff.isInitialized = 1L;
    for (i = 0; i < 18; i++) {
      tmp_4[i] = tmp_1[i];
    }

    tmp_4[18] = '\x00';
    Sub_followerController_exp4_43.createSubscriber(tmp_4,
      followerControl_MessageQueueLen);

    /* End of Start for MATLABSystem: '<S4>/SourceBlock' */
    /* End of Start for SubSystem: '<Root>/Follower's positions' */

    /* Start for Atomic SubSystem: '<Root>/Publish for follower vel' */
    /* Start for MATLABSystem: '<S7>/SinkBlock' */
    followerController_exp4_DW.obj_m.isInitialized = 0L;
    followerController_exp4_DW.objisempty_m = true;
    followerController_exp4_DW.obj_m.isInitialized = 1L;
    for (i = 0; i < 21; i++) {
      followerController_exp4_B.cv0[i] = tmp_0[i];
    }

    followerController_exp4_B.cv0[21] = '\x00';
    Pub_followerController_exp4_21.createPublisher(followerController_exp4_B.cv0,
      followerControl_MessageQueueLen);

    /* End of Start for MATLABSystem: '<S7>/SinkBlock' */
    /* End of Start for SubSystem: '<Root>/Publish for follower vel' */

    /* Start for Atomic SubSystem: '<Root>/Publish for headway distance experienced by follower' */
    /* Start for MATLABSystem: '<S8>/SinkBlock' */
    followerController_exp4_DW.obj_l.isInitialized = 0L;
    followerController_exp4_DW.objisempty = true;
    followerController_exp4_DW.obj_l.isInitialized = 1L;
    for (i = 0; i < 21; i++) {
      followerController_exp4_B.cv0[i] = tmp[i];
    }

    followerController_exp4_B.cv0[21] = '\x00';
    Pub_followerController_exp4_61.createPublisher(followerController_exp4_B.cv0,
      followerControl_MessageQueueLen);

    /* End of Start for MATLABSystem: '<S8>/SinkBlock' */
    /* End of Start for SubSystem: '<Root>/Publish for headway distance experienced by follower' */
  }

  /* SystemInitialize for Atomic SubSystem: '<Root>/Leader's Velocity' */
  /* SystemInitialize for Enabled SubSystem: '<S6>/Enabled Subsystem' */
  /* SystemInitialize for Outport: '<S11>/Out1' */
  followerController_exp4_B.In1 = followerController_exp4_P.Out1_Y0;

  /* End of SystemInitialize for SubSystem: '<S6>/Enabled Subsystem' */
  /* End of SystemInitialize for SubSystem: '<Root>/Leader's Velocity' */

  /* SystemInitialize for Atomic SubSystem: '<Root>/Leader's Position' */

  /* SystemInitialize for Enabled SubSystem: '<S5>/Enabled Subsystem' */
  followerC_EnabledSubsystem_Init(&followerController_exp4_B.EnabledSubsystem_f,
    (P_EnabledSubsystem_followerCo_T *)
    &followerController_exp4_P.EnabledSubsystem_f);

  /* End of SystemInitialize for SubSystem: '<S5>/Enabled Subsystem' */

  /* End of SystemInitialize for SubSystem: '<Root>/Leader's Position' */

  /* SystemInitialize for Atomic SubSystem: '<Root>/Follower's positions' */

  /* SystemInitialize for Enabled SubSystem: '<S4>/Enabled Subsystem' */
  followerC_EnabledSubsystem_Init(&followerController_exp4_B.EnabledSubsystem,
    (P_EnabledSubsystem_followerCo_T *)
    &followerController_exp4_P.EnabledSubsystem);

  /* End of SystemInitialize for SubSystem: '<S4>/Enabled Subsystem' */

  /* End of SystemInitialize for SubSystem: '<Root>/Follower's positions' */
}

/* Model terminate function */
void followerController_exp4_terminate(void)
{
  /* Terminate for Atomic SubSystem: '<Root>/Leader's Velocity' */
  /* Start for MATLABSystem: '<S6>/SourceBlock' incorporates:
   *  Terminate for MATLABSystem: '<S6>/SourceBlock'
   */
  if (followerController_exp4_DW.obj.isInitialized == 1L) {
    followerController_exp4_DW.obj.isInitialized = 2L;
  }

  /* End of Start for MATLABSystem: '<S6>/SourceBlock' */
  /* End of Terminate for SubSystem: '<Root>/Leader's Velocity' */

  /* Terminate for Atomic SubSystem: '<Root>/Leader's Position' */
  /* Start for MATLABSystem: '<S5>/SourceBlock' incorporates:
   *  Terminate for MATLABSystem: '<S5>/SourceBlock'
   */
  if (followerController_exp4_DW.obj_f.isInitialized == 1L) {
    followerController_exp4_DW.obj_f.isInitialized = 2L;
  }

  /* End of Start for MATLABSystem: '<S5>/SourceBlock' */
  /* End of Terminate for SubSystem: '<Root>/Leader's Position' */

  /* Terminate for Atomic SubSystem: '<Root>/Follower's positions' */
  /* Start for MATLABSystem: '<S4>/SourceBlock' incorporates:
   *  Terminate for MATLABSystem: '<S4>/SourceBlock'
   */
  if (followerController_exp4_DW.obj_ff.isInitialized == 1L) {
    followerController_exp4_DW.obj_ff.isInitialized = 2L;
  }

  /* End of Start for MATLABSystem: '<S4>/SourceBlock' */
  /* End of Terminate for SubSystem: '<Root>/Follower's positions' */

  /* Terminate for Atomic SubSystem: '<Root>/Publish for follower vel' */
  /* Start for MATLABSystem: '<S7>/SinkBlock' incorporates:
   *  Terminate for MATLABSystem: '<S7>/SinkBlock'
   */
  if (followerController_exp4_DW.obj_m.isInitialized == 1L) {
    followerController_exp4_DW.obj_m.isInitialized = 2L;
  }

  /* End of Start for MATLABSystem: '<S7>/SinkBlock' */
  /* End of Terminate for SubSystem: '<Root>/Publish for follower vel' */

  /* Terminate for Atomic SubSystem: '<Root>/Publish for headway distance experienced by follower' */
  /* Start for MATLABSystem: '<S8>/SinkBlock' incorporates:
   *  Terminate for MATLABSystem: '<S8>/SinkBlock'
   */
  if (followerController_exp4_DW.obj_l.isInitialized == 1L) {
    followerController_exp4_DW.obj_l.isInitialized = 2L;
  }

  /* End of Start for MATLABSystem: '<S8>/SinkBlock' */
  /* End of Terminate for SubSystem: '<Root>/Publish for headway distance experienced by follower' */
}
