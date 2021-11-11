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
    static constexpr int IDLE = 4;

    uint16_t message = 0;
    int playtime = 5;
    uint16_t playerID = 0;
    uint16_t weaponPower = 0;
    gameParametersControl & parameters;
    rtos::flag startFlag;
    rtos::channel<int, 5> buttonChannel;

    sendIRMessageControl & sendIRMessage;
    display & scherm;


    void main(){
        start();
        int status = IDLE;

        switch (status) {
            for (;;) {
                case IDLE: {
                    auto evt = wait(startFlag);
                    if(evt == startFlag){
                        status = SYSTEMSTARTUP;
                        break;
                    }
                }
                case SYSTEMSTARTUP: {
                    scherm.preGame();
                    auto evt = wait(buttonChannel);
                    if (evt == buttonChannel) {
                        if (buttonChannel.read() != 0) {
                            status = KIESTIMING;
                            break;
                        }
                    }
                }

                case KIESTIMING: {
                    auto evt = wait(buttonChannel);
                    if(evt == buttonChannel){
                        int button = buttonChannel.read();
                        scherm.setTiming(playtime);
                        if (button == 1) {
                            playtime++;
                            scherm.setTiming(playtime);
                        }else if (button == 2) {
                            playtime--;
                            scherm.setTiming(playtime);
                        }
                        if (button == 4) {
                            status = SENDSTARTSIGNAL;
                            break;
                        }
                    }
                }

                case SENDSTARTSIGNAL: {
                    for (;;) {
                        auto evt = wait(buttonChannel);
                        if(evt == buttonChannel){
                            playerID++;
                            message = (((((1 << 4) | playerID) << 2 | weaponPower) << 5) | playtime) << 4;
                            sendIRMessage.sendMessage(message); //stuur start signaal
                            if (buttonChannel.read() == 4) {
                                playerID = 0;
                                parameters.setParams(playerID, playtime);
                                status = IDLE;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }



public:
    initGameControl(sendIRMessageControl & sendIRMessage, display & scherm):
        rtos::task<>("initGameControlTaak"),
        buttonChannel(this, "buttonID"),
        startFlag(this, "startFlag"),
        sendIRMessage(sendIRMessage),
        scherm(scherm)
    {}

    void buttonPressed(int buttonID){
        buttonChannel.write(buttonID);
    }

    void start(){
        startFlag.set();
    }


};


#endif //V2THDE_EXAMPLES_INITGAMECONTROL_H