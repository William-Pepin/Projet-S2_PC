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
         bool last_button_trig_left;
         bool last_button_jstick;
         int angle_jstick;
         bool acc;
};

#endif // CONTROLLER_H
