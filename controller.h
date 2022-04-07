#ifndef CONTROLLER_H
#define CONTROLLER_H


class controller
{
public:
    controller();
         int bargraph;
         bool dpad_up;
         bool dpad_down;
         bool dpad_left;
         bool dpad_right;
         bool trig_left;
         bool trig_right;
         bool button_jstick;
         int angle_jstick;
         int acc_x;
         int acc_y;
         int acc_z;
};

#endif // CONTROLLER_H
