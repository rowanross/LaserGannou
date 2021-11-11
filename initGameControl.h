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
    enum state_t {SYSTEMSTARTUP, KIESTIMING, SENDSTARTSIGNAL, IDLE};
    state_t state = IDLE;
    
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
        for (;;) {
            switch (state) {

                case IDLE: {

                    auto evt = wait(startFlag);
                    if(evt == startFlag){
                        state = SYSTEMSTARTUP;
                        break;
                    }
                }
                case SYSTEMSTARTUP: {
                    scherm.setPreSpelFlag();
                    auto evt = wait(buttonChannel);
                    if (evt == buttonChannel) {
                        if (buttonChannel.read() != 0) {
                            state = KIESTIMING;
                            break;
                        }
                    }
                }

                case KIESTIMING: {
                    auto evt = wait(buttonChannel);
                    if(evt == buttonChannel){
                        for (;;){
                            int button = buttonChannel.read();
                            scherm.setTimeFlag(playtime);
                            if (button == 1) {
                                playtime++;
                                scherm.setTimeFlag(playtime);
                            }else if (button == 2) {
                                playtime--;
                                scherm.setTimeFlag(playtime);
                            }
                            if (button == 4) {
                                state = SENDSTARTSIGNAL;
                                break;
                            }
                        }

                    }
                }

                case SENDSTARTSIGNAL: {
                    for (;;) {
                        auto evt = wait(buttonChannel);

                        if(evt == buttonChannel){

                            playerID++;
                            message = (((((1 << 4) | playerID) << 2 | weaponPower) << 5) | playtime) << 4;
                            sendIRMessage.setInitMessageFlag(message); //stuur start signaal
                            if (buttonChannel.read() == 4) {
                                hwlib::cout << "pls werk";
                                playerID = 0;
                                parameters.setParams(playerID, playtime);
                                state = IDLE;
                                parameters.Start();
                                break;
                            }
                        }
                    }
                }
            }
        }
    }




public:
    initGameControl(sendIRMessageControl & sendIRMessage, display & scherm, gameParametersControl & parameters):
        rtos::task<>(0, "initGameControlTaak"),
        parameters(parameters),
        startFlag(this, "startFlag"),
        buttonChannel(this, "buttonID"),
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