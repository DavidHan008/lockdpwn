/*
 * sinVelToLeader_data.cpp
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

/* Block parameters (auto storage) */
P_sinVelToLeader_T sinVelToLeader_P = {
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
  5.0,                                 /* Expression: 5
                                        * Referenced by: '<S3>/Sine Wave azcar Vel Comp2'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S3>/Sine Wave azcar Vel Comp2'
                                        */
  2.0,                                 /* Expression: 2
                                        * Referenced by: '<S3>/Sine Wave azcar Vel Comp2'
                                        */
  0.3,                                 /* Expression: 0.3
                                        * Referenced by: '<S3>/Sine Wave azcar Vel Comp2'
                                        */
  5.0,                                 /* Expression: 5
                                        * Referenced by: '<S3>/Sine Wave azcar Vel Comp1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S3>/Sine Wave azcar Vel Comp1'
                                        */
  3.0,                                 /* Expression: 3
                                        * Referenced by: '<S3>/Sine Wave azcar Vel Comp1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S3>/Sine Wave azcar Vel Comp1'
                                        */
  0.0                                  /* Expression: 0.0
                                        * Referenced by: '<Root>/Steering angle'
                                        */
};
