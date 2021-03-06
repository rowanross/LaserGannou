#ifndef V2THDE_EXAMPLES_RUNGAMECONTROL_H
#define V2THDE_EXAMPLES_RUNGAMECONTROL_H

#include "hwlib.hpp"
#include "rtos.hpp"
#include "receiveIRMessageControl.h"
#include "sendIRMessageControl.h"
#include "transferHitControl.hpp"
#include "bieperControl.h"
#include "display.h"
#include "struct.h"

<<<<<<< HEAD
=======
//struct killedBy {
//    unsigned int playerCode = 0;
//    unsigned int amount = 0;
//};

>>>>>>> 02d7de1592c584de8c407a9539bc5f8791becba6
class runGameControl : public rtos::task<>{
private:
    enum state_t {IDLE, COUNTDOWN, NORMAAL, SHOOT, RELOAD, HIT, DEAD, TRANSFER};
    state_t state = IDLE;
    rtos::pool <int> parametersPool;
    rtos::flag hitFlag;
    rtos::flag parametersFlag;
    rtos::timer countdownTimer;
    rtos::timer revivalTimer;
    rtos::timer reloadTimer;
    rtos::clock gameClock;
    rtos::channel<int, 5> buttonChannel;
    bieperControl & bieper;
    sendIRMessageControl & IR;
    display & scherm;
    transferHit & transfer;
    killedBy player_1, player_2, player_3, player_4, player_5, player_6, player_7, player_8, player_9;
    killedBy kills[9] = {player_1,player_2,player_3,player_4,player_5,player_6,player_7,player_8,player_9};

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
                        scherm.setShowTimeFlag(playtime);
                        if(playtime == 0){
                            scherm.setConfirmFlag();
                            state = TRANSFER;
                            break;
                        }
                    }
                }
                case SHOOT: {
                    IR.setMessageFlag(playerID, weaponPower);
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
                    bieper.setPlayHitFlag();
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
                    kills[ID-1].playerCode = ID;
                    kills[ID-1].amount++;
                    bieper.setPlayDeathFlag();
                    wait(revivalTimer);
                    health = 100;
                    state = NORMAAL;
                    break;
                }
                case TRANSFER: {
                    auto evt = wait(buttonChannel);
                    if(evt == buttonChannel){
                        if(buttonChannel.read() == 4){
                            transfer.setTransferFlag(kills);
                            scherm.setClearFlag();
                            state = IDLE;
                            break;
                        }
                    }
                }
            }
        }
    }


public:
    runGameControl(bieperControl & bieper, sendIRMessageControl & IR, display & scherm, transferHit & transfer):
<<<<<<< HEAD
            rtos::task<>( "RunGameTask"),
=======
            rtos::task<>(9, "RunGameTask"),
>>>>>>> 02d7de1592c584de8c407a9539bc5f8791becba6
            parametersPool("parametersPool"),
            hitFlag(this, "hitFlag"),
            parametersFlag(this, "parametersFlag"),
            countdownTimer(this, "countdownTimer"),
            revivalTimer(this, "revivalTimer"),
            reloadTimer(this, "reloadTimer"),
            gameClock(this, 1, "gameClock"),
            buttonChannel(this, "buttonID"),
            bieper(bieper),
            IR(IR),
            scherm(scherm),
            transfer(transfer)
    {}



    void setParameters(int playerID, int weaponPower, int playtime){
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

};


#endif //V2THDE_EXAMPLES_RUNGAMECONTROL_H