/*
 * humanCarFollowerController.cpp
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

#include "humanCarFollowerController.h"
#include "humanCarFollowerController_private.h"
#define humanCarFollowe_MessageQueueLen (1L)

/* Block signals (auto storage) */
B_humanCarFollowerController_T humanCarFollowerController_B;

/* Block states (auto storage) */
DW_humanCarFollowerController_T humanCarFollowerController_DW;

/* Real-time model */
RT_MODEL_humanCarFollowerCont_T humanCarFollowerController_M_;
RT_MODEL_humanCarFollowerCont_T *const humanCarFollowerController_M =
  &humanCarFollowerController_M_;

/*
 * System initialize for enable system:
 *    '<S3>/Enabled Subsystem'
 *    '<S4>/Enabled Subsystem'
 */
void humanCarF_EnabledSubsystem_Init(B_EnabledSubsystem_humanCarFo_T *localB,
  P_EnabledSubsystem_humanCarFo_T *localP)
{
  /* SystemInitialize for Outport: '<S7>/Out1' */
  localB->In1 = localP->Out1_Y0;
}

/*
 * Output and update for enable system:
 *    '<S3>/Enabled Subsystem'
 *    '<S4>/Enabled Subsystem'
 */
void humanCarFollow_EnabledSubsystem(boolean_T rtu_Enable, const
  SL_Bus_humanCarFollowerController_nav_msgs_Odometry *rtu_In1,
  B_EnabledSubsystem_humanCarFo_T *localB)
{
  /* Outputs for Enabled SubSystem: '<S3>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S7>/Enable'
   */
  if (rtu_Enable) {
    /* Inport: '<S7>/In1' */
    localB->In1 = *rtu_In1;
  }

  /* End of Outputs for SubSystem: '<S3>/Enabled Subsystem' */
}

/* Model step function */
void humanCarFollowerController_step(void)
{
  boolean_T varargout_1;
  real_T rtb_VelocityofFollower1;
  real_T rtb_X1X22;

  /* Outputs for Atomic SubSystem: '<Root>/Leader's Velocity' */
  /* Start for MATLABSystem: '<S5>/SourceBlock' incorporates:
   *  Inport: '<S9>/In1'
   *  MATLABSystem: '<S5>/SourceBlock'
   */
  varargout_1 = Sub_humanCarFollowerController_38.getLatestMessage
    (&humanCarFollowerController_B.BusAssignment1);

  /* Outputs for Enabled SubSystem: '<S5>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S9>/Enable'
   */
  if (varargout_1) {
    humanCarFollowerController_B.In1 =
      humanCarFollowerController_B.BusAssignment1;
  }

  /* End of Start for MATLABSystem: '<S5>/SourceBlock' */
  /* End of Outputs for SubSystem: '<S5>/Enabled Subsystem' */
  /* End of Outputs for SubSystem: '<Root>/Leader's Velocity' */

  /* Outputs for Atomic SubSystem: '<Root>/Leader's Position' */
  /* Start for MATLABSystem: '<S4>/SourceBlock' incorporates:
   *  MATLABSystem: '<S4>/SourceBlock'
   */
  varargout_1 = Sub_humanCarFollowerController_40.getLatestMessage
    (&humanCarFollowerController_B.SourceBlock_o2);

  /* Outputs for Enabled SubSystem: '<S4>/Enabled Subsystem' */
  humanCarFollow_EnabledSubsystem(varargout_1,
    &humanCarFollowerController_B.SourceBlock_o2,
    &humanCarFollowerController_B.EnabledSubsystem_f);

  /* End of Outputs for SubSystem: '<S4>/Enabled Subsystem' */

  /* End of Outputs for SubSystem: '<Root>/Leader's Position' */

  /* Outputs for Atomic SubSystem: '<Root>/Follower's positions' */
  /* Start for MATLABSystem: '<S3>/SourceBlock' incorporates:
   *  MATLABSystem: '<S3>/SourceBlock'
   */
  varargout_1 = Sub_humanCarFollowerController_43.getLatestMessage
    (&humanCarFollowerController_B.SourceBlock_o2);

  /* Outputs for Enabled SubSystem: '<S3>/Enabled Subsystem' */
  humanCarFollow_EnabledSubsystem(varargout_1,
    &humanCarFollowerController_B.SourceBlock_o2,
    &humanCarFollowerController_B.EnabledSubsystem);

  /* End of Outputs for SubSystem: '<S3>/Enabled Subsystem' */

  /* End of Outputs for SubSystem: '<Root>/Follower's positions' */

  /* Sum: '<S2>/X1-X2' */
  rtb_VelocityofFollower1 =
    humanCarFollowerController_B.EnabledSubsystem_f.In1.Pose.Pose.Position.X -
    humanCarFollowerController_B.EnabledSubsystem.In1.Pose.Pose.Position.X;

  /* Product: '<S2>/(X1-X2)^2' */
  rtb_X1X22 = rtb_VelocityofFollower1 * rtb_VelocityofFollower1;

  /* Sum: '<S2>/Y1-Y2' */
  rtb_VelocityofFollower1 =
    humanCarFollowerController_B.EnabledSubsystem_f.In1.Pose.Pose.Position.Y -
    humanCarFollowerController_B.EnabledSubsystem.In1.Pose.Pose.Position.Y;

  /* Sqrt: '<S2>/Sqrt' incorporates:
   *  Product: '<S2>/(Y1-Y2)^2'
   *  Sum: '<S2>/(X1-X2)^2 + (Y1-Y2)^2'
   */
  rtb_VelocityofFollower1 = sqrt(rtb_VelocityofFollower1 *
    rtb_VelocityofFollower1 + rtb_X1X22);

  /* BusAssignment: '<Root>/Bus Assignment1' incorporates:
   *  Constant: '<Root>/1//30'
   *  Constant: '<Root>/2//3'
   *  Constant: '<Root>/Steering angle'
   *  Constant: '<S1>/Constant'
   *  Product: '<Root>/Product'
   *  Product: '<Root>/Velocity of Follower1'
   *  Sum: '<Root>/FactorB'
   */
  humanCarFollowerController_B.BusAssignment1 =
    humanCarFollowerController_P.Constant_Value_l;
  humanCarFollowerController_B.BusAssignment1.Linear.X =
    (rtb_VelocityofFollower1 * humanCarFollowerController_P.u30_Value +
     humanCarFollowerController_P.u3_Value) *
    humanCarFollowerController_B.In1.Linear.X;
  humanCarFollowerController_B.BusAssignment1.Angular.Z =
    humanCarFollowerController_P.Steeringangle_Value;

  /* Outputs for Atomic SubSystem: '<Root>/Publish for follower vel' */
  /* Start for MATLABSystem: '<S6>/SinkBlock' incorporates:
   *  MATLABSystem: '<S6>/SinkBlock'
   */
  Pub_humanCarFollowerController_21.publish
    (&humanCarFollowerController_B.BusAssignment1);

  /* End of Outputs for SubSystem: '<Root>/Publish for follower vel' */
}

/* Model initialize function */
void humanCarFollowerController_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(humanCarFollowerController_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &humanCarFollowerController_B), 0,
                sizeof(B_humanCarFollowerController_T));

  /* states (dwork) */
  (void) memset((void *)&humanCarFollowerController_DW, 0,
                sizeof(DW_humanCarFollowerController_T));

  {
    static const char_T tmp[21] = { '/', 'f', 'o', 'l', 'l', 'o', 'w', 'e', 'r',
      '_', 's', 'i', 'm', '/', 'c', 'm', 'd', '_', 'v', 'e', 'l' };

    static const char_T tmp_0[18] = { '/', 'f', 'o', 'l', 'l', 'o', 'w', 'e',
      'r', '_', 's', 'i', 'm', '/', 'o', 'd', 'o', 'm' };

    static const char_T tmp_1[15] = { '/', 'a', 'z', 'c', 'a', 'r', '_', 's',
      'i', 'm', '/', 'o', 'd', 'o', 'm' };

    static const char_T tmp_2[14] = { '/', 'a', 'z', 'c', 'a', 'r', '_', 's',
      'i', 'm', '/', 'v', 'e', 'l' };

    char_T tmp_3[19];
    char_T tmp_4[16];
    char_T tmp_5[15];
    int16_T i;

    /* Start for Atomic SubSystem: '<Root>/Leader's Velocity' */
    /* Start for MATLABSystem: '<S5>/SourceBlock' */
    humanCarFollowerController_DW.obj.isInitialized = 0L;
    humanCarFollowerController_DW.objisempty_l = true;
    humanCarFollowerController_DW.obj.isInitialized = 1L;
    for (i = 0; i < 14; i++) {
      tmp_5[i] = tmp_2[i];
    }

    tmp_5[14] = '\x00';
    Sub_humanCarFollowerController_38.createSubscriber(tmp_5,
      humanCarFollowe_MessageQueueLen);

    /* End of Start for MATLABSystem: '<S5>/SourceBlock' */
    /* End of Start for SubSystem: '<Root>/Leader's Velocity' */

    /* Start for Atomic SubSystem: '<Root>/Leader's Position' */
    /* Start for MATLABSystem: '<S4>/SourceBlock' */
    humanCarFollowerController_DW.obj_f.isInitialized = 0L;
    humanCarFollowerController_DW.objisempty_h = true;
    humanCarFollowerController_DW.obj_f.isInitialized = 1L;
    for (i = 0; i < 15; i++) {
      tmp_4[i] = tmp_1[i];
    }

    tmp_4[15] = '\x00';
    Sub_humanCarFollowerController_40.createSubscriber(tmp_4,
      humanCarFollowe_MessageQueueLen);

    /* End of Start for MATLABSystem: '<S4>/SourceBlock' */
    /* End of Start for SubSystem: '<Root>/Leader's Position' */

    /* Start for Atomic SubSystem: '<Root>/Follower's positions' */
    /* Start for MATLABSystem: '<S3>/SourceBlock' */
    humanCarFollowerController_DW.obj_ff.isInitialized = 0L;
    humanCarFollowerController_DW.objisempty_a = true;
    humanCarFollowerController_DW.obj_ff.isInitialized = 1L;
    for (i = 0; i < 18; i++) {
      tmp_3[i] = tmp_0[i];
    }

    tmp_3[18] = '\x00';
    Sub_humanCarFollowerController_43.createSubscriber(tmp_3,
      humanCarFollowe_MessageQueueLen);

    /* End of Start for MATLABSystem: '<S3>/SourceBlock' */
    /* End of Start for SubSystem: '<Root>/Follower's positions' */

    /* Start for Atomic SubSystem: '<Root>/Publish for follower vel' */
    /* Start for MATLABSystem: '<S6>/SinkBlock' */
    humanCarFollowerController_DW.obj_m.isInitialized = 0L;
    humanCarFollowerController_DW.objisempty = true;
    humanCarFollowerController_DW.obj_m.isInitialized = 1L;
    for (i = 0; i < 21; i++) {
      humanCarFollowerController_B.cv0[i] = tmp[i];
    }

    humanCarFollowerController_B.cv0[21] = '\x00';
    Pub_humanCarFollowerController_21.createPublisher
      (humanCarFollowerController_B.cv0, humanCarFollowe_MessageQueueLen);

    /* End of Start for MATLABSystem: '<S6>/SinkBlock' */
    /* End of Start for SubSystem: '<Root>/Publish for follower vel' */
  }

  /* SystemInitialize for Atomic SubSystem: '<Root>/Leader's Velocity' */
  /* SystemInitialize for Enabled SubSystem: '<S5>/Enabled Subsystem' */
  /* SystemInitialize for Outport: '<S9>/Out1' */
  humanCarFollowerController_B.In1 = humanCarFollowerController_P.Out1_Y0;

  /* End of SystemInitialize for SubSystem: '<S5>/Enabled Subsystem' */
  /* End of SystemInitialize for SubSystem: '<Root>/Leader's Velocity' */

  /* SystemInitialize for Atomic SubSystem: '<Root>/Leader's Position' */

  /* SystemInitialize for Enabled SubSystem: '<S4>/Enabled Subsystem' */
  humanCarF_EnabledSubsystem_Init
    (&humanCarFollowerController_B.EnabledSubsystem_f,
     (P_EnabledSubsystem_humanCarFo_T *)
     &humanCarFollowerController_P.EnabledSubsystem_f);

  /* End of SystemInitialize for SubSystem: '<S4>/Enabled Subsystem' */

  /* End of SystemInitialize for SubSystem: '<Root>/Leader's Position' */

  /* SystemInitialize for Atomic SubSystem: '<Root>/Follower's positions' */

  /* SystemInitialize for Enabled SubSystem: '<S3>/Enabled Subsystem' */
  humanCarF_EnabledSubsystem_Init(&humanCarFollowerController_B.EnabledSubsystem,
    (P_EnabledSubsystem_humanCarFo_T *)
    &humanCarFollowerController_P.EnabledSubsystem);

  /* End of SystemInitialize for SubSystem: '<S3>/Enabled Subsystem' */

  /* End of SystemInitialize for SubSystem: '<Root>/Follower's positions' */
}

/* Model terminate function */
void humanCarFollowerController_terminate(void)
{
  /* Terminate for Atomic SubSystem: '<Root>/Leader's Velocity' */
  /* Start for MATLABSystem: '<S5>/SourceBlock' incorporates:
   *  Terminate for MATLABSystem: '<S5>/SourceBlock'
   */
  if (humanCarFollowerController_DW.obj.isInitialized == 1L) {
    humanCarFollowerController_DW.obj.isInitialized = 2L;
  }

  /* End of Start for MATLABSystem: '<S5>/SourceBlock' */
  /* End of Terminate for SubSystem: '<Root>/Leader's Velocity' */

  /* Terminate for Atomic SubSystem: '<Root>/Leader's Position' */
  /* Start for MATLABSystem: '<S4>/SourceBlock' incorporates:
   *  Terminate for MATLABSystem: '<S4>/SourceBlock'
   */
  if (humanCarFollowerController_DW.obj_f.isInitialized == 1L) {
    humanCarFollowerController_DW.obj_f.isInitialized = 2L;
  }

  /* End of Start for MATLABSystem: '<S4>/SourceBlock' */
  /* End of Terminate for SubSystem: '<Root>/Leader's Position' */

  /* Terminate for Atomic SubSystem: '<Root>/Follower's positions' */
  /* Start for MATLABSystem: '<S3>/SourceBlock' incorporates:
   *  Terminate for MATLABSystem: '<S3>/SourceBlock'
   */
  if (humanCarFollowerController_DW.obj_ff.isInitialized == 1L) {
    humanCarFollowerController_DW.obj_ff.isInitialized = 2L;
  }

  /* End of Start for MATLABSystem: '<S3>/SourceBlock' */
  /* End of Terminate for SubSystem: '<Root>/Follower's positions' */

  /* Terminate for Atomic SubSystem: '<Root>/Publish for follower vel' */
  /* Start for MATLABSystem: '<S6>/SinkBlock' incorporates:
   *  Terminate for MATLABSystem: '<S6>/SinkBlock'
   */
  if (humanCarFollowerController_DW.obj_m.isInitialized == 1L) {
    humanCarFollowerController_DW.obj_m.isInitialized = 2L;
  }

  /* End of Start for MATLABSystem: '<S6>/SinkBlock' */
  /* End of Terminate for SubSystem: '<Root>/Publish for follower vel' */
}
