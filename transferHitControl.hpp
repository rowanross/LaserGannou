#ifndef TRANSFERHITCONTROL_HPP
#define TRANSFERHITCONTROL_HPP
#include "runGameControl.h"
#include <array>
class transferHit : public rtos::task<>{
public:
    transferHit();
    void transferData(const killedBy kills[9]){
        hwlib::wait_ms(200);
        for (const auto & x : kills){
            hwlib::cout << x.playerID << ","<< x.amount << "\n";
        }
    }
};


#endif