//
// Created by eriks on 8-11-2021.
//
#include "hwlib.hpp"
#include "rtos.hpp"

#ifndef V2THDE_EXAMPLES_INITGAMECONTROL_H
#define V2THDE_EXAMPLES_INITGAMECONTROL_H


class initGameControl {
private:
    const int SYSTEMSTARTUP = 1;
    const int KIESTIMING = 2;
    const int SENDSTARTSIGNAL= 3;


    //sendIRLedControl irLedControl;
    //display display;

public:
    initGameControl(){};
    //void buttonPressed(buttonID:: eButtonID);
    //void buttonReleased(buttonID:: eButtonID);
};


#endif //V2THDE_EXAMPLES_INITGAMECONTROL_H
