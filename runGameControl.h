#ifndef V2THDE_EXAMPLES_RUNGAMECONTROL_H
#define V2THDE_EXAMPLES_RUNGAMECONTROL_H

#include "hwlib.hpp"
#include "rtos.hpp"
#include "receiveIRMessageControl.h"
#include "sendIRMessageControl.h"

class runGameControl : public rtos::task <>{
private:
    hwlib::target::pin_in trigger = hwlib::target::pin_in(hwlib::target::pins::d8);

public:
    runGameControl(hwlib::target::pin_in trigger = hwlib::target::pin_in(hwlib::target::pins::d8))
    {}

    //void setParameters

    void shoot(){
        //if trigger{
        uint16_t message = 9999;
        sendIRMessageControl sendMessage;
        sendMessage.sendMessage(message);
    }

};


#endif //V2THDE_EXAMPLES_RUNGAMECONTROL_H
