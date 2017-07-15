/*
 * followerController_exp4_private.h
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

#ifndef RTW_HEADER_followerController_exp4_private_h_
#define RTW_HEADER_followerController_exp4_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "followerController_exp4.h"

extern void followerC_EnabledSubsystem_Init(B_EnabledSubsystem_followerCo_T
  *localB, P_EnabledSubsystem_followerCo_T *localP);
extern void followerContro_EnabledSubsystem(boolean_T rtu_Enable, const
  SL_Bus_followerController_exp4_nav_msgs_Odometry *rtu_In1,
  B_EnabledSubsystem_followerCo_T *localB);

#endif                                 /* RTW_HEADER_followerController_exp4_private_h_ */
