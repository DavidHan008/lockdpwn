//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: cmdvel2gazebo.cpp
//
// Code generated for Simulink model 'cmdvel2gazebo'.
//
// Model version                  : 1.29
// Simulink Coder version         : 8.10 (R2016a) 10-Feb-2016
// C/C++ source code generated on : Tue May 10 14:11:14 2016
//
// Target selection: ert.tlc
// Embedded hardware selection: Custom Processor->Custom
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "cmdvel2gazebo.h"
#include "cmdvel2gazebo_private.h"
#define cmdvel2gazebo_MessageQueueLen  (1)

// Block signals (auto storage)
B_cmdvel2gazebo_T cmdvel2gazebo_B;

// Continuous states
X_cmdvel2gazebo_T cmdvel2gazebo_X;

// Block states (auto storage)
DW_cmdvel2gazebo_T cmdvel2gazebo_DW;

// Real-time model
RT_MODEL_cmdvel2gazebo_T cmdvel2gazebo_M_;
RT_MODEL_cmdvel2gazebo_T *const cmdvel2gazebo_M = &cmdvel2gazebo_M_;

//
// This function updates continuous states using the ODE3 fixed-step
// solver algorithm
//
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  // Solver Matrices
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 2;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  // Save the state values at time t in y, we'll use x as ynew.
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  // Assumes that rtsiSetT and ModelOutputs are up-to-date
  // f0 = f(t,y)
  rtsiSetdX(si, f0);
  cmdvel2gazebo_derivatives();

  // f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*));
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  cmdvel2gazebo_step();
  cmdvel2gazebo_derivatives();

  // f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*));
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  cmdvel2gazebo_step();
  cmdvel2gazebo_derivatives();

  // tnew = t + hA(3);
  // ynew = y + f*hB(:,3);
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

// Model step function
void cmdvel2gazebo_step(void)
{
  if (rtmIsMajorTimeStep(cmdvel2gazebo_M)) {
    // set solver stop time
    if (!(cmdvel2gazebo_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&cmdvel2gazebo_M->solverInfo,
                            ((cmdvel2gazebo_M->Timing.clockTickH0 + 1) *
        cmdvel2gazebo_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&cmdvel2gazebo_M->solverInfo,
                            ((cmdvel2gazebo_M->Timing.clockTick0 + 1) *
        cmdvel2gazebo_M->Timing.stepSize0 + cmdvel2gazebo_M->Timing.clockTickH0 *
        cmdvel2gazebo_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    // end MajorTimeStep

  // Update absolute time of base rate at minor time step
  if (rtmIsMinorTimeStep(cmdvel2gazebo_M)) {
    cmdvel2gazebo_M->Timing.t[0] = rtsiGetT(&cmdvel2gazebo_M->solverInfo);
  }

  {
    real_T *lastU;
    boolean_T timedOut;
    SL_Bus_cmdvel2gazebo_std_msgs_Float64 rtb_BusAssignment;
    SL_Bus_cmdvel2gazebo_std_msgs_Float64 rtb_BusAssignment1;
    real_T rtb_Fcn3;
    SL_Bus_cmdvel2gazebo_std_msgs_Float64 rtb_BusAssignment2;
    SL_Bus_cmdvel2gazebo_std_msgs_Float64 rtb_BusAssignment3;
    boolean_T rtb_SourceBlock_o1;
    real_T rtb_Derivative;
    if (rtmIsMajorTimeStep(cmdvel2gazebo_M)) {
      // Outputs for Atomic SubSystem: '<Root>/Subscribe'
      // Start for MATLABSystem: '<S10>/SourceBlock' incorporates:
      //   Inport: '<S13>/In1'
      //   MATLABSystem: '<S10>/SourceBlock'

      rtb_SourceBlock_o1 = Sub_cmdvel2gazebo_3.getLatestMessage
        (&cmdvel2gazebo_B.varargout_2);

      // Outputs for Enabled SubSystem: '<S10>/Enabled Subsystem' incorporates:
      //   EnablePort: '<S13>/Enable'

      if (rtb_SourceBlock_o1) {
        cmdvel2gazebo_B.In1 = cmdvel2gazebo_B.varargout_2;
      }

      // End of Start for MATLABSystem: '<S10>/SourceBlock'
      // End of Outputs for SubSystem: '<S10>/Enabled Subsystem'
      // End of Outputs for SubSystem: '<Root>/Subscribe'

      // BusAssignment: '<Root>/Bus Assignment' incorporates:
      //   Fcn: '<Root>/Fcn'

      rtb_BusAssignment.Data = cmdvel2gazebo_B.In1.Angular.Z;

      // Outputs for Atomic SubSystem: '<Root>/Publish'
      // Start for MATLABSystem: '<S6>/SinkBlock' incorporates:
      //   MATLABSystem: '<S6>/SinkBlock'

      Pub_cmdvel2gazebo_9.publish(&rtb_BusAssignment);

      // End of Outputs for SubSystem: '<Root>/Publish'

      // BusAssignment: '<Root>/Bus Assignment1' incorporates:
      //   Fcn: '<Root>/Fcn1'

      rtb_BusAssignment1.Data = cmdvel2gazebo_B.In1.Angular.Z;

      // Outputs for Atomic SubSystem: '<Root>/Publish1'
      // Start for MATLABSystem: '<S7>/SinkBlock' incorporates:
      //   MATLABSystem: '<S7>/SinkBlock'

      Pub_cmdvel2gazebo_18.publish(&rtb_BusAssignment1);

      // End of Outputs for SubSystem: '<Root>/Publish1'

      // Outputs for Atomic SubSystem: '<Root>/Dead Man's Switch'
      // MATLAB Function: '<S5>/timeout set to 0 output'
      // MATLAB Function 'Dead Man\'s Switch/timeout set to 0 output': '<S12>:1' 
      // '<S12>:1:4' timedOut=true;
      timedOut = true;

      // '<S12>:1:5' if isempty(sinceLastMsg)
      if (!cmdvel2gazebo_DW.sinceLastMsg_not_empty) {
        // '<S12>:1:6' sinceLastMsg=(timeout/stepSize)+1;
        cmdvel2gazebo_DW.sinceLastMsg = cmdvel2gazebo_P.DeadMansSwitch_timeout /
          cmdvel2gazebo_P.DeadMansSwitch_stepSize + 1.0;
        cmdvel2gazebo_DW.sinceLastMsg_not_empty = true;
      }

      // '<S12>:1:9' safeValue=0;
      cmdvel2gazebo_B.safeValue = 0.0;

      //  if no new message
      //  after timeout, we output 0
      // '<S12>:1:12' if( isNew == true )
      if (rtb_SourceBlock_o1) {
        // '<S12>:1:13' sinceLastMsg = 0;
        cmdvel2gazebo_DW.sinceLastMsg = 0.0;
      } else {
        // '<S12>:1:14' else
        // '<S12>:1:15' sinceLastMsg = sinceLastMsg+1;
        cmdvel2gazebo_DW.sinceLastMsg++;
      }

      //  Note: we require step size as an input here, and depend on our
      //  system being executed at a regular rate, or bad things will happen
      // '<S12>:1:20' if( sinceLastMsg < timeout/stepSize )
      if (cmdvel2gazebo_DW.sinceLastMsg < cmdvel2gazebo_P.DeadMansSwitch_timeout
          / cmdvel2gazebo_P.DeadMansSwitch_stepSize) {
        // '<S12>:1:21' timedOut = false;
        timedOut = false;
      }

      // '<S12>:1:24' if( timedOut == false )
      if (!timedOut) {
        // '<S12>:1:25' safeValue = value;
        cmdvel2gazebo_B.safeValue = cmdvel2gazebo_B.In1.Linear.X;
      }

      // End of MATLAB Function: '<S5>/timeout set to 0 output'
      // End of Outputs for SubSystem: '<Root>/Dead Man's Switch'
    }

    // TransferFcn: '<S11>/Transfer Fcn1'
    rtb_Fcn3 = cmdvel2gazebo_P.TransferFcn1_C *
      cmdvel2gazebo_X.TransferFcn1_CSTATE;

    // Derivative: '<S11>/Derivative'
    if ((cmdvel2gazebo_DW.TimeStampA >= cmdvel2gazebo_M->Timing.t[0]) &&
        (cmdvel2gazebo_DW.TimeStampB >= cmdvel2gazebo_M->Timing.t[0])) {
      rtb_Derivative = 0.0;
    } else {
      rtb_Derivative = cmdvel2gazebo_DW.TimeStampA;
      lastU = &cmdvel2gazebo_DW.LastUAtTimeA;
      if (cmdvel2gazebo_DW.TimeStampA < cmdvel2gazebo_DW.TimeStampB) {
        if (cmdvel2gazebo_DW.TimeStampB < cmdvel2gazebo_M->Timing.t[0]) {
          rtb_Derivative = cmdvel2gazebo_DW.TimeStampB;
          lastU = &cmdvel2gazebo_DW.LastUAtTimeB;
        }
      } else {
        if (cmdvel2gazebo_DW.TimeStampA >= cmdvel2gazebo_M->Timing.t[0]) {
          rtb_Derivative = cmdvel2gazebo_DW.TimeStampB;
          lastU = &cmdvel2gazebo_DW.LastUAtTimeB;
        }
      }

      rtb_Derivative = (cmdvel2gazebo_B.safeValue - *lastU) /
        (cmdvel2gazebo_M->Timing.t[0] - rtb_Derivative);
    }

    // End of Derivative: '<S11>/Derivative'

    // Switch: '<S11>/Switch' incorporates:
    //   TransferFcn: '<S11>/Transfer Fcn2'

    if (!(rtb_Derivative > cmdvel2gazebo_P.Switch_Threshold)) {
      rtb_Fcn3 = cmdvel2gazebo_P.TransferFcn2_C *
        cmdvel2gazebo_X.TransferFcn2_CSTATE;
    }

    // End of Switch: '<S11>/Switch'

    // Gain: '<Root>/Gazebo Multiplier'
    rtb_Fcn3 *= cmdvel2gazebo_P.GazeboMultiplier_Gain;

    // BusAssignment: '<Root>/Bus Assignment2' incorporates:
    //   Fcn: '<Root>/Fcn2'

    rtb_BusAssignment2.Data = rtb_Fcn3;

    // Outputs for Atomic SubSystem: '<Root>/Publish2'
    // Start for MATLABSystem: '<S8>/SinkBlock' incorporates:
    //   MATLABSystem: '<S8>/SinkBlock'

    Pub_cmdvel2gazebo_24.publish(&rtb_BusAssignment2);

    // End of Outputs for SubSystem: '<Root>/Publish2'

    // BusAssignment: '<Root>/Bus Assignment3'
    rtb_BusAssignment3.Data = rtb_Fcn3;

    // Outputs for Atomic SubSystem: '<Root>/Publish3'
    // Start for MATLABSystem: '<S9>/SinkBlock' incorporates:
    //   MATLABSystem: '<S9>/SinkBlock'

    Pub_cmdvel2gazebo_25.publish(&rtb_BusAssignment3);

    // End of Outputs for SubSystem: '<Root>/Publish3'
  }

  if (rtmIsMajorTimeStep(cmdvel2gazebo_M)) {
    real_T *lastU;

    // Update for Derivative: '<S11>/Derivative'
    if (cmdvel2gazebo_DW.TimeStampA == (rtInf)) {
      cmdvel2gazebo_DW.TimeStampA = cmdvel2gazebo_M->Timing.t[0];
      lastU = &cmdvel2gazebo_DW.LastUAtTimeA;
    } else if (cmdvel2gazebo_DW.TimeStampB == (rtInf)) {
      cmdvel2gazebo_DW.TimeStampB = cmdvel2gazebo_M->Timing.t[0];
      lastU = &cmdvel2gazebo_DW.LastUAtTimeB;
    } else if (cmdvel2gazebo_DW.TimeStampA < cmdvel2gazebo_DW.TimeStampB) {
      cmdvel2gazebo_DW.TimeStampA = cmdvel2gazebo_M->Timing.t[0];
      lastU = &cmdvel2gazebo_DW.LastUAtTimeA;
    } else {
      cmdvel2gazebo_DW.TimeStampB = cmdvel2gazebo_M->Timing.t[0];
      lastU = &cmdvel2gazebo_DW.LastUAtTimeB;
    }

    *lastU = cmdvel2gazebo_B.safeValue;

    // End of Update for Derivative: '<S11>/Derivative'
  }                                    // end MajorTimeStep

  if (rtmIsMajorTimeStep(cmdvel2gazebo_M)) {
    rt_ertODEUpdateContinuousStates(&cmdvel2gazebo_M->solverInfo);

    // Update absolute time for base rate
    // The "clockTick0" counts the number of times the code of this task has
    //  been executed. The absolute time is the multiplication of "clockTick0"
    //  and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
    //  overflow during the application lifespan selected.
    //  Timer of this task consists of two 32 bit unsigned integers.
    //  The two integers represent the low bits Timing.clockTick0 and the high bits
    //  Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.

    if (!(++cmdvel2gazebo_M->Timing.clockTick0)) {
      ++cmdvel2gazebo_M->Timing.clockTickH0;
    }

    cmdvel2gazebo_M->Timing.t[0] = rtsiGetSolverStopTime
      (&cmdvel2gazebo_M->solverInfo);

    {
      // Update absolute timer for sample time: [0.02s, 0.0s]
      // The "clockTick1" counts the number of times the code of this task has
      //  been executed. The resolution of this integer timer is 0.02, which is the step size
      //  of the task. Size of "clockTick1" ensures timer will not overflow during the
      //  application lifespan selected.
      //  Timer of this task consists of two 32 bit unsigned integers.
      //  The two integers represent the low bits Timing.clockTick1 and the high bits
      //  Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.

      cmdvel2gazebo_M->Timing.clockTick1++;
      if (!cmdvel2gazebo_M->Timing.clockTick1) {
        cmdvel2gazebo_M->Timing.clockTickH1++;
      }
    }
  }                                    // end MajorTimeStep
}

// Derivatives for root system: '<Root>'
void cmdvel2gazebo_derivatives(void)
{
  XDot_cmdvel2gazebo_T *_rtXdot;
  _rtXdot = ((XDot_cmdvel2gazebo_T *) cmdvel2gazebo_M->ModelData.derivs);

  // Derivatives for TransferFcn: '<S11>/Transfer Fcn1'
  _rtXdot->TransferFcn1_CSTATE = 0.0;
  _rtXdot->TransferFcn1_CSTATE += cmdvel2gazebo_P.TransferFcn1_A *
    cmdvel2gazebo_X.TransferFcn1_CSTATE;
  _rtXdot->TransferFcn1_CSTATE += cmdvel2gazebo_B.safeValue;

  // Derivatives for TransferFcn: '<S11>/Transfer Fcn2'
  _rtXdot->TransferFcn2_CSTATE = 0.0;
  _rtXdot->TransferFcn2_CSTATE += cmdvel2gazebo_P.TransferFcn2_A *
    cmdvel2gazebo_X.TransferFcn2_CSTATE;
  _rtXdot->TransferFcn2_CSTATE += cmdvel2gazebo_B.safeValue;
}

// Model initialize function
void cmdvel2gazebo_initialize(void)
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));

  // initialize real-time model
  (void) memset((void *)cmdvel2gazebo_M, 0,
                sizeof(RT_MODEL_cmdvel2gazebo_T));

  {
    // Setup solver object
    rtsiSetSimTimeStepPtr(&cmdvel2gazebo_M->solverInfo,
                          &cmdvel2gazebo_M->Timing.simTimeStep);
    rtsiSetTPtr(&cmdvel2gazebo_M->solverInfo, &rtmGetTPtr(cmdvel2gazebo_M));
    rtsiSetStepSizePtr(&cmdvel2gazebo_M->solverInfo,
                       &cmdvel2gazebo_M->Timing.stepSize0);
    rtsiSetdXPtr(&cmdvel2gazebo_M->solverInfo,
                 &cmdvel2gazebo_M->ModelData.derivs);
    rtsiSetContStatesPtr(&cmdvel2gazebo_M->solverInfo, (real_T **)
                         &cmdvel2gazebo_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&cmdvel2gazebo_M->solverInfo,
      &cmdvel2gazebo_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&cmdvel2gazebo_M->solverInfo,
      &cmdvel2gazebo_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&cmdvel2gazebo_M->solverInfo,
      &cmdvel2gazebo_M->ModelData.periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&cmdvel2gazebo_M->solverInfo,
      &cmdvel2gazebo_M->ModelData.periodicContStateRanges);
    rtsiSetErrorStatusPtr(&cmdvel2gazebo_M->solverInfo, (&rtmGetErrorStatus
      (cmdvel2gazebo_M)));
    rtsiSetRTModelPtr(&cmdvel2gazebo_M->solverInfo, cmdvel2gazebo_M);
  }

  rtsiSetSimTimeStep(&cmdvel2gazebo_M->solverInfo, MAJOR_TIME_STEP);
  cmdvel2gazebo_M->ModelData.intgData.y = cmdvel2gazebo_M->ModelData.odeY;
  cmdvel2gazebo_M->ModelData.intgData.f[0] = cmdvel2gazebo_M->ModelData.odeF[0];
  cmdvel2gazebo_M->ModelData.intgData.f[1] = cmdvel2gazebo_M->ModelData.odeF[1];
  cmdvel2gazebo_M->ModelData.intgData.f[2] = cmdvel2gazebo_M->ModelData.odeF[2];
  cmdvel2gazebo_M->ModelData.contStates = ((X_cmdvel2gazebo_T *)
    &cmdvel2gazebo_X);
  rtsiSetSolverData(&cmdvel2gazebo_M->solverInfo, (void *)
                    &cmdvel2gazebo_M->ModelData.intgData);
  rtsiSetSolverName(&cmdvel2gazebo_M->solverInfo,"ode3");
  rtmSetTPtr(cmdvel2gazebo_M, &cmdvel2gazebo_M->Timing.tArray[0]);
  cmdvel2gazebo_M->Timing.stepSize0 = 0.02;

  // block I/O
  (void) memset(((void *) &cmdvel2gazebo_B), 0,
                sizeof(B_cmdvel2gazebo_T));

  // states (continuous)
  {
    (void) memset((void *)&cmdvel2gazebo_X, 0,
                  sizeof(X_cmdvel2gazebo_T));
  }

  // states (dwork)
  (void) memset((void *)&cmdvel2gazebo_DW, 0,
                sizeof(DW_cmdvel2gazebo_T));

  {
    static const char_T tmp[45] = { '/', 'a', 'z', 'c', 'a', 'r', '_', 's', 'i',
      'm', '/', 'j', 'o', 'i', 'n', 't', '2', '_', 'v', 'e', 'l', 'o', 'c', 'i',
      't', 'y', '_', 'c', 'o', 'n', 't', 'r', 'o', 'l', 'l', 'e', 'r', '/', 'c',
      'o', 'm', 'm', 'a', 'n', 'd' };

    static const char_T tmp_0[45] = { '/', 'a', 'z', 'c', 'a', 'r', '_', 's',
      'i', 'm', '/', 'j', 'o', 'i', 'n', 't', '1', '_', 'v', 'e', 'l', 'o', 'c',
      'i', 't', 'y', '_', 'c', 'o', 'n', 't', 'r', 'o', 'l', 'l', 'e', 'r', '/',
      'c', 'o', 'm', 'm', 'a', 'n', 'd' };

    static const char_T tmp_1[59] = { '/', 'a', 'z', 'c', 'a', 'r', '_', 's',
      'i', 'm', '/', 'f', 'r', 'o', 'n', 't', '_', 'r', 'i', 'g', 'h', 't', '_',
      's', 't', 'e', 'e', 'r', 'i', 'n', 'g', '_', 'p', 'o', 's', 'i', 't', 'i',
      'o', 'n', '_', 'c', 'o', 'n', 't', 'r', 'o', 'l', 'l', 'e', 'r', '/', 'c',
      'o', 'm', 'm', 'a', 'n', 'd' };

    static const char_T tmp_2[58] = { '/', 'a', 'z', 'c', 'a', 'r', '_', 's',
      'i', 'm', '/', 'f', 'r', 'o', 'n', 't', '_', 'l', 'e', 'f', 't', '_', 's',
      't', 'e', 'e', 'r', 'i', 'n', 'g', '_', 'p', 'o', 's', 'i', 't', 'i', 'o',
      'n', '_', 'c', 'o', 'n', 't', 'r', 'o', 'l', 'l', 'e', 'r', '/', 'c', 'o',
      'm', 'm', 'a', 'n', 'd' };

    static const char_T tmp_3[18] = { '/', 'a', 'z', 'c', 'a', 'r', '_', 's',
      'i', 'm', '/', 'c', 'm', 'd', '_', 'v', 'e', 'l' };

    char_T tmp_4[19];
    int32_T i;

    // Start for Atomic SubSystem: '<Root>/Subscribe'
    // Start for MATLABSystem: '<S10>/SourceBlock'
    cmdvel2gazebo_DW.obj_d.isInitialized = 0;
    cmdvel2gazebo_DW.obj_d.isInitialized = 1;
    for (i = 0; i < 18; i++) {
      tmp_4[i] = tmp_3[i];
    }

    tmp_4[18] = '\x00';
    Sub_cmdvel2gazebo_3.createSubscriber(tmp_4, cmdvel2gazebo_MessageQueueLen);

    // End of Start for MATLABSystem: '<S10>/SourceBlock'
    // End of Start for SubSystem: '<Root>/Subscribe'

    // Start for Atomic SubSystem: '<Root>/Publish'
    // Start for MATLABSystem: '<S6>/SinkBlock'
    cmdvel2gazebo_DW.obj_n.isInitialized = 0;
    cmdvel2gazebo_DW.obj_n.isInitialized = 1;
    for (i = 0; i < 58; i++) {
      cmdvel2gazebo_B.cv1[i] = tmp_2[i];
    }

    cmdvel2gazebo_B.cv1[58] = '\x00';
    Pub_cmdvel2gazebo_9.createPublisher(cmdvel2gazebo_B.cv1,
      cmdvel2gazebo_MessageQueueLen);

    // End of Start for MATLABSystem: '<S6>/SinkBlock'
    // End of Start for SubSystem: '<Root>/Publish'

    // Start for Atomic SubSystem: '<Root>/Publish1'
    // Start for MATLABSystem: '<S7>/SinkBlock'
    cmdvel2gazebo_DW.obj_l.isInitialized = 0;
    cmdvel2gazebo_DW.obj_l.isInitialized = 1;
    for (i = 0; i < 59; i++) {
      cmdvel2gazebo_B.cv0[i] = tmp_1[i];
    }

    cmdvel2gazebo_B.cv0[59] = '\x00';
    Pub_cmdvel2gazebo_18.createPublisher(cmdvel2gazebo_B.cv0,
      cmdvel2gazebo_MessageQueueLen);

    // End of Start for MATLABSystem: '<S7>/SinkBlock'
    // End of Start for SubSystem: '<Root>/Publish1'

    // Start for Atomic SubSystem: '<Root>/Publish2'
    // Start for MATLABSystem: '<S8>/SinkBlock'
    cmdvel2gazebo_DW.obj_m.isInitialized = 0;
    cmdvel2gazebo_DW.obj_m.isInitialized = 1;
    for (i = 0; i < 45; i++) {
      cmdvel2gazebo_B.cv2[i] = tmp_0[i];
    }

    cmdvel2gazebo_B.cv2[45] = '\x00';
    Pub_cmdvel2gazebo_24.createPublisher(cmdvel2gazebo_B.cv2,
      cmdvel2gazebo_MessageQueueLen);

    // End of Start for MATLABSystem: '<S8>/SinkBlock'
    // End of Start for SubSystem: '<Root>/Publish2'

    // Start for Atomic SubSystem: '<Root>/Publish3'
    // Start for MATLABSystem: '<S9>/SinkBlock'
    cmdvel2gazebo_DW.obj.isInitialized = 0;
    cmdvel2gazebo_DW.obj.isInitialized = 1;
    for (i = 0; i < 45; i++) {
      cmdvel2gazebo_B.cv2[i] = tmp[i];
    }

    cmdvel2gazebo_B.cv2[45] = '\x00';
    Pub_cmdvel2gazebo_25.createPublisher(cmdvel2gazebo_B.cv2,
      cmdvel2gazebo_MessageQueueLen);

    // End of Start for MATLABSystem: '<S9>/SinkBlock'
    // End of Start for SubSystem: '<Root>/Publish3'

    // InitializeConditions for TransferFcn: '<S11>/Transfer Fcn1'
    cmdvel2gazebo_X.TransferFcn1_CSTATE = 0.0;

    // InitializeConditions for Derivative: '<S11>/Derivative'
    cmdvel2gazebo_DW.TimeStampA = (rtInf);
    cmdvel2gazebo_DW.TimeStampB = (rtInf);

    // InitializeConditions for TransferFcn: '<S11>/Transfer Fcn2'
    cmdvel2gazebo_X.TransferFcn2_CSTATE = 0.0;

    // SystemInitialize for Atomic SubSystem: '<Root>/Subscribe'
    // SystemInitialize for Enabled SubSystem: '<S10>/Enabled Subsystem'
    // SystemInitialize for Outport: '<S13>/Out1'
    cmdvel2gazebo_B.In1 = cmdvel2gazebo_P.Out1_Y0;

    // End of SystemInitialize for SubSystem: '<S10>/Enabled Subsystem'
    // End of SystemInitialize for SubSystem: '<Root>/Subscribe'

    // SystemInitialize for Atomic SubSystem: '<Root>/Dead Man's Switch'
    // SystemInitialize for MATLAB Function: '<S5>/timeout set to 0 output'
    cmdvel2gazebo_DW.sinceLastMsg_not_empty = false;

    // End of SystemInitialize for SubSystem: '<Root>/Dead Man's Switch'
  }
}

// Model terminate function
void cmdvel2gazebo_terminate(void)
{
  // Terminate for Atomic SubSystem: '<Root>/Subscribe'
  // Start for MATLABSystem: '<S10>/SourceBlock' incorporates:
  //   Terminate for MATLABSystem: '<S10>/SourceBlock'

  if (cmdvel2gazebo_DW.obj_d.isInitialized == 1) {
    cmdvel2gazebo_DW.obj_d.isInitialized = 2;
  }

  // End of Start for MATLABSystem: '<S10>/SourceBlock'
  // End of Terminate for SubSystem: '<Root>/Subscribe'

  // Terminate for Atomic SubSystem: '<Root>/Publish'
  // Start for MATLABSystem: '<S6>/SinkBlock' incorporates:
  //   Terminate for MATLABSystem: '<S6>/SinkBlock'

  if (cmdvel2gazebo_DW.obj_n.isInitialized == 1) {
    cmdvel2gazebo_DW.obj_n.isInitialized = 2;
  }

  // End of Start for MATLABSystem: '<S6>/SinkBlock'
  // End of Terminate for SubSystem: '<Root>/Publish'

  // Terminate for Atomic SubSystem: '<Root>/Publish1'
  // Start for MATLABSystem: '<S7>/SinkBlock' incorporates:
  //   Terminate for MATLABSystem: '<S7>/SinkBlock'

  if (cmdvel2gazebo_DW.obj_l.isInitialized == 1) {
    cmdvel2gazebo_DW.obj_l.isInitialized = 2;
  }

  // End of Start for MATLABSystem: '<S7>/SinkBlock'
  // End of Terminate for SubSystem: '<Root>/Publish1'

  // Terminate for Atomic SubSystem: '<Root>/Publish2'
  // Start for MATLABSystem: '<S8>/SinkBlock' incorporates:
  //   Terminate for MATLABSystem: '<S8>/SinkBlock'

  if (cmdvel2gazebo_DW.obj_m.isInitialized == 1) {
    cmdvel2gazebo_DW.obj_m.isInitialized = 2;
  }

  // End of Start for MATLABSystem: '<S8>/SinkBlock'
  // End of Terminate for SubSystem: '<Root>/Publish2'

  // Terminate for Atomic SubSystem: '<Root>/Publish3'
  // Start for MATLABSystem: '<S9>/SinkBlock' incorporates:
  //   Terminate for MATLABSystem: '<S9>/SinkBlock'

  if (cmdvel2gazebo_DW.obj.isInitialized == 1) {
    cmdvel2gazebo_DW.obj.isInitialized = 2;
  }

  // End of Start for MATLABSystem: '<S9>/SinkBlock'
  // End of Terminate for SubSystem: '<Root>/Publish3'
}

//
// File trailer for generated code.
//
// [EOF]
//
