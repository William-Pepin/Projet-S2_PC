#include "controller.h"

controller::controller()
{
    bargraph = false;
    dpad_up = false;
    dpad_down = false;
    dpad_left = false;
    dpad_right = false;
    trig_left = false;
    trig_right = false;
    button_jstick = false;
    last_button_trig_left = false;
    last_button_jstick = false;
    angle_jstick = 0;
    acc = false;
}
