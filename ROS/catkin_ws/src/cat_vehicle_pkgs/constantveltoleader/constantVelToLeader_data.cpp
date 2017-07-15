/*
 * constantVelToLeader_data.cpp
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

/* Block parameters (auto storage) */
P_constantVelToLeader_T constantVelToLeader_P = {
  {
    {
      0.0,                             /* X */
      0.0,                             /* Y */
      0.0                              /* Z */
    },                                 /* Linear */

    {
      0.0,                             /* X */
      0.0,                             /* Y */
      0.0                              /* Z */
    }                                  /* Angular */
  },                                   /* Computed Parameter: Constant_Value
                                        * Referenced by: '<S1>/Constant'
                                        */
  5.0,                                 /* Expression: 5.0
                                        * Referenced by: '<Root>/Connstant Velocity'
                                        */
  0.0                                  /* Expression: 0.0
                                        * Referenced by: '<Root>/Steering angle'
                                        */
};
