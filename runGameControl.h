#ifndef V2THDE_EXAMPLES_RUNGAMECONTROL_H
#define V2THDE_EXAMPLES_RUNGAMECONTROL_H

#include "hwlib.hpp"
#include "rtos.hpp"
#include "receiveIRMessageControl.h"
#include "sendIRMessageControl.h"

struct killedBy {
    unsigned int playerID;
    unsigned int amount;
};


class runGameControl : public rtos::task <>{
private:
    enum state_t {IDLE, COUNTDOWN, NORMAAL, SHOOT, RELOAD, HIT, DEAD};
    state_t  state = IDLE;
    rtos::pool <int> parametersPool;
    rtos::pool<unsigned long int> countdownPool;
    rtos::flag hitFlag;
    rtos::flag parametersFlag;
    rtos::timer countdownTimer;
    rtos::clock gameClock;
    rtos::channel<int, 5> buttonChannel;
    killedBy kills[8];

    int playerID;
    int playtime;
    int health = 100;
    int weaponPower;
    int cooldown = 0;
    unsigned long int countdown = 10;

    void main(){
        for(;;){
            switch(state){
                case IDLE: {
                    auto evt = wait(parametersFlag);
                    if(evt == parametersFlag){
                        state = COUNTDOWN;
                    }
                    break;
                }
                case COUNTDOWN: {
                    playerID = parametersPool.read();
                    weaponPower = parametersPool.read();
                    playtime = parametersPool.read();
                    countdownTimer.set(countdown);
                    wait(countdownTimer);
                    state = NORMAAL;
                }
                case NORMAAL: {
                    if(evt == buttonChannel){
                        if(buttonChannel.read() == 5){
                            if(cooldown <= 0){
                                state = SHOOT;
                                break;
                            }
                        }
                    }

                    if(evt == gameClock){
                        cooldown--;
                        playtime--;
                        if(playtime == 0){
                            """Stop game, display press accept to transfer deaths"""
                            break;
                        }
                        """display.showChange(gameTime);"""
                    }
                }
                case SHOOT: {

                }
            }
        }
    }

public:
    runGameControl():
            rtos::task<>("RunGameTask"),
            countdownTimer(this, "countdownTimer"),
            gameClock(this, 1, "gameClock"),
            parametersPool("parametersPool"),
            buttonChannel(this, "buttonID"),
            parametersFlag(this, "parametersFlag"),
            hitFlag(this, "hitFlag")
    {}

    void setParams(int playerID, int weaponPower, int playtime){
        parametersPool.write(playerID);
        parametersPool.write(weaponPower);
        parametersPool.write(playtime);
        parametersFlag.set();
    }

    void buttonPressed(int buttonID){
        buttonChannel.write(buttonID);
    }

    void hitBy(int playerID, int weaponpower){
        parametersPool.write(playerID);
        parametersPool.write(weaponpower);
        hitFlag.set();
    }

};


#endif //V2THDE_EXAMPLES_RUNGAMECONTROL_H
