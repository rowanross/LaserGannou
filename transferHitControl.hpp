#ifndef TRANSFERHITCONTROL_HPP
#define TRANSFERHITCONTROL_HPP

#include "runGameControl.h"
#include "struct.h"

class transferHit : public rtos::task<>{
private:
    void main(){}
public:
    transferHit();
    void transferData(const killedBy kills[9]){
        hwlib::wait_ms(200);
        for(unsigned int i = 0; i < 9; i++){
            hwlib::cout << kills[i].playerCode << ","<< kills[i].amount << "\n";
        }
//        for (const killedBy & x : kills){
//            hwlib::cout << x.playerCode << ","<< x.amount << "\n";
//        }
    }
};


#endif