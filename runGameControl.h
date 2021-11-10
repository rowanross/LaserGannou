#ifndef V2THDE_EXAMPLES_RUNGAMECONTROL_H
#define V2THDE_EXAMPLES_RUNGAMECONTROL_H

#include "hwlib.hpp"
#include "rtos.hpp"
#include "receiveIRMessageControl.h"
#include "sendIRMessageControl.h"
#include "bieperControl.h"
#include "display.h"

struct killedBy {
    unsigned int playerID;
    unsigned int amount = 0;
};


class runGameControl : public rtos::task <>{
private:
    enum state_t {IDLE, COUNTDOWN, NORMAAL, SHOOT, RELOAD, HIT, DEAD, TRANSFER};
    state_t  state = IDLE;
    rtos::pool <int> parametersPool;
    rtos::pool<unsigned long int> countdownPool;
    rtos::flag hitFlag;
    rtos::flag parametersFlag;
    rtos::flag transferFlag;
    rtos::timer countdownTimer;
    rtos::timer revivalTimer;
    rtos::timer reloadTimer;
    rtos::clock gameClock;
    rtos::channel<int, 5> buttonChannel;
    bieperControl & bieper;
    sendIRMessageControl & IR;
    display & scherm;
    killedBy kills[9] = {1,2,3,4,5,6,7,8,9};

    int playerID;
    int playtime;
    int health = 100;
    int weaponPower;
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
                    break;
                }
                case NORMAAL: {
                    auto evt = wait(hitFlag+buttonChannel+gameClock);
                    if(evt == hitFlag){
                        state = HIT;
                        break;
                    }

                    if(evt == buttonChannel){
                        if(buttonChannel.read() == 5){
                                state = SHOOT;
                                break;
                        }
                    }

                    if(evt == gameClock){
                        playtime--;
                        scherm.ShowTiming(playtime);
                        if(playtime == 0){
                            """Stop game, display press accept to transfer deaths"""
                            state = TRANSFER;
                            break;
                        }
                    }
                }
                case SHOOT: {
                    IR.sendMessage(playerID, weaponPower);
                    state = RELOAD;
                    break;
                }
                case RELOAD: {
                    reloadTimer.set(weaponPower);
                    wait(reloadTimer);
                    state = NORMAAL;
                    break;
                }
                case HIT: {
                    bieper.playHitSound();
                    health = health - (parametersPool.read() * 17);
                    if(health <= 0){
                        state = DEAD;
                        break;
                    }
                    state = NORMAAL;
                    break;
                }
                case DEAD: {
                    revivalTimer.set(10);
                    int ID = parametersPool.read();
                    kills[ID-1].playerID = ID;
                    kills[ID-1].amount++;
                    bieper.playDeathSound();
                    wait(revivalTimer);
                    health = 100;
                    state = NORMAAL;
                    break;
                }
                case TRANSFER: {
                    auto evt = wait(transferFlag);
                    if(evt == transferFlag){
                        scherm.clearDisplay();
                        state = IDLE;
                        break;
                    }
                }
            }
        }
    }

public:
    runGameControl(bieperControl & bieper, sendIRMessageControl & IR, display & scherm):
            rtos::task<>("RunGameTask"),
            countdownTimer(this, "countdownTimer"),
            revivalTimer(this, "revivalTimer"),
            reloadTimer(this, "reloadTimer"),
            gameClock(this, 1, "gameClock"),
            parametersPool("parametersPool"),
            buttonChannel(this, "buttonID"),
            parametersFlag(this, "parametersFlag"),
            hitFlag(this, "hitFlag"),
            transferFlag(this, "transferFlag"),
            bieper(bieper),
            IR(IR),
            scherm(scherm)
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
        parametersPool.write(weaponpower);
        parametersPool.write(playerID);
        hitFlag.set();
    }

    void dataTransferred(){
        transferFlag.set();
    }

};


#endif //V2THDE_EXAMPLES_RUNGAMECONTROL_H
