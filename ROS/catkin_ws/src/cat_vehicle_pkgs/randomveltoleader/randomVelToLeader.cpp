/*
 * randomVelToLeader.cpp
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

#include "randomVelToLeader.h"
#include "randomVelToLeader_private.h"
#define randomVelToLead_MessageQueueLen (1)

/* Block signals (auto storage) */
B_randomVelToLeader_T randomVelToLeader_B;

/* Block states (auto storage) */
DW_randomVelToLeader_T randomVelToLeader_DW;

/* Real-time model */
RT_MODEL_randomVelToLeader_T randomVelToLeader_M_;
RT_MODEL_randomVelToLeader_T *const randomVelToLeader_M = &randomVelToLeader_M_;
real_T rt_urand_Upu32_Yd_f_pw_snf(uint32_T *u)
{
  uint32_T lo;
  uint32_T hi;

  /* Uniform random number generator (random number between 0 and 1)

     #define IA      16807                      magic multiplier = 7^5
     #define IM      2147483647                 modulus = 2^31-1
     #define IQ      127773                     IM div IA
     #define IR      2836                       IM modulo IA
     #define S       4.656612875245797e-10      reciprocal of 2^31-1
     test = IA * (seed % IQ) - IR * (seed/IQ)
     seed = test < 0 ? (test + IM) : test
     return (seed*S)
   */
  lo = *u % 127773U * 16807U;
  hi = *u / 127773U * 2836U;
  if (lo < hi) {
    *u = 2147483647U - (hi - lo);
  } else {
    *u = lo - hi;
  }

  return (real_T)*u * 4.6566128752457969E-10;
}

real_T rt_nrand_Upu32_Yd_f_pw_snf(uint32_T *u)
{
  real_T y;
  real_T sr;
  real_T si;

  /* Normal (Gaussian) random number generator */
  do {
    sr = 2.0 * rt_urand_Upu32_Yd_f_pw_snf(u) - 1.0;
    si = 2.0 * rt_urand_Upu32_Yd_f_pw_snf(u) - 1.0;
    si = sr * sr + si * si;
  } while (si > 1.0);

  y = sqrt(-2.0 * log(si) / si) * sr;
  return y;
}

/* Model step function */
void randomVelToLeader_step(void)
{
  SL_Bus_randomVelToLeader_geometry_msgs_Twist rtb_BusAssignment;
  real_T u0;

  /* Gain: '<S4>/Output' incorporates:
   *  RandomNumber: '<S4>/White Noise'
   */
  u0 = randomVelToLeader_P.Output_Gain * randomVelToLeader_DW.NextOutput;

  /* MinMax: '<S3>/MinMax' incorporates:
   *  Constant: '<S3>/Constant'
   */
  if ((u0 <= randomVelToLeader_P.Constant_Value_p) || rtIsNaN
      (randomVelToLeader_P.Constant_Value_p)) {
    randomVelToLeader_B.MinMax = u0;
  } else {
    randomVelToLeader_B.MinMax = randomVelToLeader_P.Constant_Value_p;
  }

  /* End of MinMax: '<S3>/MinMax' */

  /* BusAssignment: '<Root>/Bus Assignment' incorporates:
   *  Abs: '<S3>/Abs'
   *  Constant: '<Root>/Steering angle'
   *  Constant: '<S1>/Constant'
   *  Sin: '<S3>/Sine Wave azcar Vel Comp1'
   *  Sum: '<S3>/Add'
   */
  rtb_BusAssignment = randomVelToLeader_P.Constant_Value;
  rtb_BusAssignment.Linear.X = fabs(sin
    (randomVelToLeader_P.SineWaveazcarVelComp1_Freq *
     randomVelToLeader_M->Timing.t[0] +
     randomVelToLeader_P.SineWaveazcarVelComp1_Phase) *
    randomVelToLeader_P.SineWaveazcarVelComp1_Amp +
    randomVelToLeader_P.SineWaveazcarVelComp1_Bias) + randomVelToLeader_B.MinMax;
  rtb_BusAssignment.Angular.Z = randomVelToLeader_P.Steeringangle_Value;

  /* Outputs for Atomic SubSystem: '<Root>/Publish for Leader Vel' */
  /* Start for MATLABSystem: '<S2>/SinkBlock' incorporates:
   *  MATLABSystem: '<S2>/SinkBlock'
   */
  Pub_randomVelToLeader_27.publish(&rtb_BusAssignment);

  /* End of Outputs for SubSystem: '<Root>/Publish for Leader Vel' */

  /* Update for RandomNumber: '<S4>/White Noise' */
  randomVelToLeader_DW.NextOutput = rt_nrand_Upu32_Yd_f_pw_snf
    (&randomVelToLeader_DW.RandSeed) * randomVelToLeader_P.WhiteNoise_StdDev +
    randomVelToLeader_P.WhiteNoise_Mean;

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++randomVelToLeader_M->Timing.clockTick0)) {
    ++randomVelToLeader_M->Timing.clockTickH0;
  }

  randomVelToLeader_M->Timing.t[0] = randomVelToLeader_M->Timing.clockTick0 *
    randomVelToLeader_M->Timing.stepSize0 +
    randomVelToLeader_M->Timing.clockTickH0 *
    randomVelToLeader_M->Timing.stepSize0 * 4294967296.0;

  {
    /* Update absolute timer for sample time: [0.1s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.1, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    randomVelToLeader_M->Timing.clockTick1++;
    if (!randomVelToLeader_M->Timing.clockTick1) {
      randomVelToLeader_M->Timing.clockTickH1++;
    }
  }
}

/* Model initialize function */
void randomVelToLeader_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)randomVelToLeader_M, 0,
                sizeof(RT_MODEL_randomVelToLeader_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&randomVelToLeader_M->solverInfo,
                          &randomVelToLeader_M->Timing.simTimeStep);
    rtsiSetTPtr(&randomVelToLeader_M->solverInfo, &rtmGetTPtr
                (randomVelToLeader_M));
    rtsiSetStepSizePtr(&randomVelToLeader_M->solverInfo,
                       &randomVelToLeader_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&randomVelToLeader_M->solverInfo, (&rtmGetErrorStatus
      (randomVelToLeader_M)));
    rtsiSetRTModelPtr(&randomVelToLeader_M->solverInfo, randomVelToLeader_M);
  }

  rtsiSetSimTimeStep(&randomVelToLeader_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetSolverName(&randomVelToLeader_M->solverInfo,"FixedStepDiscrete");
  rtmSetTPtr(randomVelToLeader_M, &randomVelToLeader_M->Timing.tArray[0]);
  randomVelToLeader_M->Timing.stepSize0 = 0.1;

  /* block I/O */
  (void) memset(((void *) &randomVelToLeader_B), 0,
                sizeof(B_randomVelToLeader_T));

  /* states (dwork) */
  (void) memset((void *)&randomVelToLeader_DW, 0,
                sizeof(DW_randomVelToLeader_T));

  {
    static const char_T tmp[18] = { '/', 'a', 'z', 'c', 'a', 'r', '_', 's', 'i',
      'm', '/', 'c', 'm', 'd', '_', 'v', 'e', 'l' };

    char_T tmp_0[19];
    int32_T i;

    /* Start for Atomic SubSystem: '<Root>/Publish for Leader Vel' */
    /* Start for MATLABSystem: '<S2>/SinkBlock' */
    randomVelToLeader_DW.obj.isInitialized = 0;
    randomVelToLeader_DW.objisempty = true;
    randomVelToLeader_DW.obj.isInitialized = 1;
    for (i = 0; i < 18; i++) {
      tmp_0[i] = tmp[i];
    }

    tmp_0[18] = '\x00';
    Pub_randomVelToLeader_27.createPublisher(tmp_0,
      randomVelToLead_MessageQueueLen);

    /* End of Start for MATLABSystem: '<S2>/SinkBlock' */
    /* End of Start for SubSystem: '<Root>/Publish for Leader Vel' */
  }

  {
    uint32_T tseed;
    int32_T r;
    int32_T t;
    real_T tmp;

    /* InitializeConditions for RandomNumber: '<S4>/White Noise' */
    tmp = floor(randomVelToLeader_P.WhiteNoise_Seed);
    if (rtIsNaN(tmp) || rtIsInf(tmp)) {
      tmp = 0.0;
    } else {
      tmp = fmod(tmp, 4.294967296E+9);
    }

    tseed = tmp < 0.0 ? (uint32_T)-(int32_T)(uint32_T)-tmp : (uint32_T)tmp;
    r = (int32_T)(tseed >> 16U);
    t = (int32_T)(tseed & 32768U);
    tseed = ((((tseed - ((uint32_T)r << 16U)) + t) << 16U) + t) + r;
    if (tseed < 1U) {
      tseed = 1144108930U;
    } else {
      if (tseed > 2147483646U) {
        tseed = 2147483646U;
      }
    }

    randomVelToLeader_DW.RandSeed = tseed;
    randomVelToLeader_DW.NextOutput = rt_nrand_Upu32_Yd_f_pw_snf
      (&randomVelToLeader_DW.RandSeed) * randomVelToLeader_P.WhiteNoise_StdDev +
      randomVelToLeader_P.WhiteNoise_Mean;

    /* End of InitializeConditions for RandomNumber: '<S4>/White Noise' */
  }
}

/* Model terminate function */
void randomVelToLeader_terminate(void)
{
  /* Terminate for Atomic SubSystem: '<Root>/Publish for Leader Vel' */
  /* Start for MATLABSystem: '<S2>/SinkBlock' incorporates:
   *  Terminate for MATLABSystem: '<S2>/SinkBlock'
   */
  if (randomVelToLeader_DW.obj.isInitialized == 1) {
    randomVelToLeader_DW.obj.isInitialized = 2;
  }

  /* End of Start for MATLABSystem: '<S2>/SinkBlock' */
  /* End of Terminate for SubSystem: '<Root>/Publish for Leader Vel' */
}
