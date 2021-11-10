//
// Created by eriks on 8-11-2021.
//
#include "hwlib.hpp"
#include "rtos.hpp"
#include "display.h"
#include "sendIRMessageControl.h"


#ifndef V2THDE_EXAMPLES_INITGAMECONTROL_H
#define V2THDE_EXAMPLES_INITGAMECONTROL_H


class initGameControl : public rtos::task<> {
private:
    static constexpr int SYSTEMSTARTUP = 1;
    static constexpr int KIESTIMING = 2;
    static constexpr int SENDSTARTSIGNAL= 3;

    rtos::event evt = wait(buttonPressedChannel);

    sendIRMessageControl & sendIRMessage;
    display & scherm;

    rtos::channel<int, 5> buttonPressedChannel = rtos::channel<int, 5>(nullptr);

    void main(){
        namespace target = hwlib::target;
        int status = SYSTEMSTARTUP;

        switch (status) {
            case SYSTEMSTARTUP:
                scherm.showChange();
                if (evt == buttonPressedChannel) {
                    if (buttonPressedChannel.read() != 0) {
                        status = KIESTIMING;
                    }
                }
            case KIESTIMING:
                scherm.showChange();
                scherm.time = 5; // zet timer op 5 min standaard;
                if (evt == buttonPressedChannel) {
                    if (buttonPressedChannel.read() == 1) {
                        scherm.time += 1;
                        scherm.showChange();
                    }
                    if (buttonPressedChannel.read() == 2) {
                        scherm.time -= 1;
                        scherm.showChange();
                    }
                }

                if(evt == buttonPressedChannel && buttonPressedChannel.read() == 4){
                    timer = scherm.time;
                    scherm.showChange();
                    status = SENDSTARTSIGNAL;
                }

                case SENDSTARTSIGNAL:
                sendIRMessage.sendStartSignal(); //stuur start signaal;
                // stuur timer en start zelf timer
        }
    }

public:
    int timer = 0;

    initGameControl(sendIRMessageControl & sendIRMessage, display & scherm) : rtos::task<>("initGameControlTaak"), sendIRMessage(sendIRMessage), scherm(scherm){};

    void buttonPressed(int buttonID){
        buttonPressedChannel.write(buttonID);
    }
};


#endif //V2THDE_EXAMPLES_INITGAMECONTROL_H