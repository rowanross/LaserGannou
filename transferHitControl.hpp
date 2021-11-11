#ifndef TRANSFERHITCONTROL_HPP
#define TRANSFERHITCONTROL_HPP

#include "runGameControl.h"
#include "struct.h"

class transferHit : public rtos::task<>{
private:
    rtos::flag transfer;

    killedBy deaths[9];
    void main(){

        for(;;){
            auto evt = wait(transfer);
            if(evt == transfer){
                transferData(deaths);

            }
        }
    }
    void transferData(const killedBy kills[9]){
        hwlib::wait_ms(200);
        for(unsigned int i = 0; i < 9; i++){
            hwlib::cout << kills[i].playerCode << ","<< kills[i].amount << "\n";
        }
    }


public:
    transferHit():
        transfer(this, "transfer")
    {}



    void setTransferFlag(const killedBy kills[9]){
        for(unsigned int i = 0; i < 9; i++){
            deaths[i] = kills[i];
        }
        transfer.set();
    }

};


#endif