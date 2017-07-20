#include <project3/purePursuit.h>

#define _RAD2DEG 180 / M_PI
#define _DEG2RAD M_PI / 180

purePursuit::purePursuit(){

}

control purePursuit::get_control(point x_robot, point x_goal){

    double re_th = M_PI/2 - x_robot.th;

    double tr_X = (x_goal.x-x_robot.x)*cos(re_th)-(x_goal.y-x_robot.y)*sin(re_th);

    double tr_Y = (x_goal.x-x_robot.x)*sin(re_th)+(x_goal.y-x_robot.y)*cos(re_th);
    double R = 0.0;

    double l = sqrt((pow((x_goal.x - x_robot.x),2)) + (pow((x_goal.y - x_robot.y),2)));

    R = 2.0*(tr_X/(l*l));

    ctrl.v = 0.15 * l;
    ctrl.w =  R * ctrl.v * l * 2;

    if(ctrl.v > 0.59)    ctrl.v = 0.59;
    if(ctrl.v < 0.17)    ctrl.v = 0.17;
    if(ctrl.w > 300*_DEG2RAD)    ctrl.w = 300*_DEG2RAD;
    if(ctrl.w < -300*_DEG2RAD)    ctrl.w = -300*_DEG2RAD;
    if(tr_Y/tr_X < 1.3 && tr_Y/tr_X > -1.3)
    {
        ctrl.v = 0.01;
        if(ctrl.w > 0.3) ctrl.w = 0.3;
        if(ctrl.w < -0.3) ctrl.w = -0.3;
    }

    if(tr_Y < 0) ctrl.v = 0.01;
    //if(x_goal.th-x_robot.th > M_PI/3) ctrl.v = 0.1;

    return ctrl;
}
