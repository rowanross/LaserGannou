#ifndef V2THDE_EXAMPLES_GAMEPARAMETERSCONTROL_H
#define V2THDE_EXAMPLES_GAMEPARAMETERSCONTROL_H

#include "hwlib.hpp"
#include "rtos.hpp"
#include "runGameControl.h"
#include "display.h"

class gameParametersControl : public rtos::task <>{
private:
    enum state_t {IDLE, WEAPONPOWER, STARTGAME};
    state_t state = IDLE;
    rtos::flag startFlag;
    rtos::channel<int, 5> buttonChannel;

    uint16_t playtime = 0;
    uint16_t playerID = 0;
    int weaponPower = 0;

    runGameControl & runGame;
    display & scherm;

    rtos::channel<int, 5> buttonPressedChannel;
    rtos::flag parametersFlag;

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
                    auto evt = wait(buttonChannel);
                    weaponPower = 1;
                    scherm.setWeaponPower(weaponPower);
                    if(evt == buttonChannel){
                        if(weaponPower> 1){
                            if(buttonChannel.read() == 2){
                                weaponPower--;
                                scherm.setWeaponPower(weaponPower);
                            }
                        }
                        if(weaponPower < 3){
                            if(buttonChannel.read() == 1){
                                weaponPower++;
                                scherm.setWeaponPower(weaponPower);
                            }
                        }
                        if(buttonChannel.read() == 4){
                            scherm.clearDisplay();
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

public:
    gameParametersControl(runGameControl & runGame, display & scherm):
            rtos::task<>("parametersControlTask"),
            startFlag(this, "startFlag"),
            buttonChannel(this, "buttonID"),
            runGame(runGame),
            scherm(scherm)
    {}

    void setParams(uint16_t & playerID_r, uint16_t & playtime_r){
        playerID = playerID_r;
        playtime = playtime_r;
    }

    void buttonPressed(int buttonID){
        buttonPressedChannel.write(buttonID);
    }

    void Start(){startFlag.set();}
};


#endif //V2THDE_EXAMPLES_GAMEPARAMETERSCONTROL_H
