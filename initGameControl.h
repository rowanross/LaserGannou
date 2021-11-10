//
// Created by eriks on 8-11-2021.
//
#include "hwlib.hpp"
#include "rtos.hpp"
#include "display.h"
#include "sendIRMessageControl.h"
#include "gameParametersControl.h"

#ifndef V2THDE_EXAMPLES_INITGAMECONTROL_H
#define V2THDE_EXAMPLES_INITGAMECONTROL_H


class initGameControl : public rtos::task<> {
private:
    static constexpr int SYSTEMSTARTUP = 1;
    static constexpr int KIESTIMING = 2;
    static constexpr int SENDSTARTSIGNAL= 3;

    uint16_t message = 0;
    uint16_t playtime = 5;
    uint16_t playerID = 0;
    uint16_t weaponPower = 0;
    gameParametersControl & parameters;
    rtos::channel<int, 5> buttonChannel;

    sendIRMessageControl & sendIRMessage;
    display & scherm;


    void main(){
        namespace target = hwlib::target;
        int status = SYSTEMSTARTUP;

        switch (status) {
            case SYSTEMSTARTUP:
                scherm.showChange();
                auto evt = wait(buttonChannel);
                if (evt == buttonChannel) {
                    if (buttonChannel.read() != 0) {
                        status = KIESTIMING;
                    }
                }


            case KIESTIMING:
                scherm.showChange();
                if (buttonChannel.read() == 1) {
                    playtime++;
                    scherm.showChange();
                } else if (buttonChannel.read() == 2) {
                    scherm.showChange();
                    playtime--;
                }
                if (buttonChannel.read() == 4) {
                    status = SENDSTARTSIGNAL;
                }


            case SENDSTARTSIGNAL:
                for (;;) {
                    playerID++;
                    message = (((((1 << 4) | playerID) << 2 | weaponPower) << 5) | playtime) << 4;
                    sendIRMessage.sendMessage(message); //stuur start signaal
                    if (buttonChannel.read() == 4) {
                        parameters.setParams(0x00, playtime);
                        break;
                    }
                }
        }
    }



public:
    initGameControl(sendIRMessageControl & sendIRMessage, display & scherm):
        rtos::task<>("initGameControlTaak"),
        buttonChannel(this, "buttonID"),
        sendIRMessage(sendIRMessage),
        scherm(scherm)
    {}

    void buttonPressed(int buttonID){
        buttonPressedChannel.write(buttonID);
    }


};


#endif //V2THDE_EXAMPLES_INITGAMECONTROL_H