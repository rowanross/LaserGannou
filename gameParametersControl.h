#ifndef V2THDE_EXAMPLES_GAMEPARAMETERSCONTROL_H
#define V2THDE_EXAMPLES_GAMEPARAMETERSCONTROL_H

#include "hwlib.hpp"
#include "rtos.hpp"
#include "bieperControl.h"
#include "display.h"
#include "runGameControl.h"
class gameParametersControl : public rtos::task <>{
private:
    enum state_t {IDLE, WEAPONPOWER, STARTGAME};
    state_t state = IDLE;
    rtos::flag startFlag;
    rtos::channel<int, 5> buttonPressedChannel;

    uint16_t playtime = 0;
    uint16_t playerID = 0;
    int weaponPower = 0;

    runGameControl & runGame;
    display & scherm;



public:
    gameParametersControl(runGameControl & runGame, display & scherm):
            rtos::task<>(1, "parametersControlTask"),
            startFlag(this, "startFlag"),
            buttonPressedChannel(this, "buttonID"),
            runGame(runGame),
            scherm(scherm){}

    void main(){
        for(;;){
            switch(state) {
                case IDLE: {
                    auto evt = wait(startFlag);
                    if(evt == startFlag){
                        state = WEAPONPOWER;
                    }
                    break;
                }
                case WEAPONPOWER: {
                    auto evt = wait(buttonPressedChannel);
                    weaponPower = 1;
                    scherm.setPowerFlag(weaponPower);
                    if(evt == buttonPressedChannel){
                        if(weaponPower> 1){
                            if(buttonPressedChannel.read() == 2){
                                weaponPower--;
                                scherm.setPowerFlag(weaponPower);
                            }
                        }
                        if(weaponPower < 3){
                            if(buttonPressedChannel.read() == 1){
                                weaponPower++;
                                scherm.setPowerFlag(weaponPower);
                            }
                        }
                        if(buttonPressedChannel.read() == 4){
                            scherm.setClearFlag();
                            hwlib::cout << "yoink";
                            state = STARTGAME;
                            break;
                        }
                    }
                }
                case STARTGAME:{
                    runGame.setParameters(playerID, weaponPower, playtime);
                    state = IDLE;
                    break;
                }
            }
        }
    }

    void setParams(uint16_t & playerID_r, int & playtime_r){
        playerID = playerID_r;
        playtime = playtime_r;
    }

    void buttonPressed(int buttonID){
        buttonPressedChannel.write(buttonID);
    }

    void Start(){startFlag.set();}
};


#endif //V2THDE_EXAMPLES_GAMEPARAMETERSCONTROL_H
