//
// Created by eriks on 8-11-2021.
//
#include "hwlib.hpp"
#include "rtos.hpp"
//#include "display"
#include "sendIRMessageControl.h"


#ifndef V2THDE_EXAMPLES_INITGAMECONTROL_H
#define V2THDE_EXAMPLES_INITGAMECONTROL_H


class initGameControl : public rtos::task<> {
private:
    static constexpr int SYSTEMSTARTUP = 1;
    static constexpr int KIESTIMING = 2;
    static constexpr int SENDSTARTSIGNAL= 3;

    sendIRMessageControl & sendIRMessage;

    rtos::channel<buttonID, 5> buttonPressedChannel;

    void main(){
        namespace target = hwlib::target;
        int status = SYSTEMSTARTUP;

        switch (status){
            case SYSTEMSTARTUP:
                display.showChange();
                auto evt = wait(buttonPressedChannel);
                if(evt == buttonPressedChannel){
                    if (buttonPressedChannel.read() != 0) {
                        status = KIESTIMING;
                    }
                }
            case KIESTIMING:
                display.showChange();
                timer = 5; // zet timer op 5 min standaard;
                if(buttonPressedChannel.read() == 1){
                    timer+= 1;
                    display.showChange();
                }else if(buttonPressedChannel.read() == 2){
                    display.showChange();
                    timer-= 1;
                }
                if(buttonPressedChannel.read() == 4){
                    status = SENDSTARTSIGNAL;
                }
            case SENDSTARTSIGNAL:
                sendIRMessage.sendStartSignal(); //stuur start signaal;
                // stuur timer en start zelf timer
        }

    }

public:
    initGameControl(sendIRMessageControl & sendIRMessage) : rtos::task<>("initGameControlTaak"), sendIRMessage(sendIRMessage){

    };

    void buttonPressed(int buttonID){
        buttonPressedChannel.write(buttonID);

    }
};


#endif //V2THDE_EXAMPLES_INITGAMECONTROL_H
