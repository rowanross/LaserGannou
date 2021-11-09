//
// Created by eriks on 8-11-2021.
//

#include "initGameControl.h"
#include "hwlib.hpp"
//include "display"
//include "timer"

void initGameControl(){
    namespace target = hwlib::target;
    int status = SYSTEMSTARTUP;

    switch (status){
    case SYSTEMSTARTUP:
        display.showChange();
        if(buttonPressed(dummyID)){
            status = KIESTIMING;
        }
    case KIESTIMING:
        display.showChange();
        timer = 5; // zet timer op 5 min standaard;
        if(timePlus){
            timer+= 1;
            display.showChange();
        }else if(timeMin){
            display.showChange();
            timer-= 1;
        }
        if(buttonPressed(confirmID)){
            status = SENDSTARTSIGNAL;
        }
    case SENDSTARTSIGNAL:
        irLedControl.sendStartSignal();
        // stuur timer en start zelf timer
    }
}

bool buttonPressed(buttonID:: eButtonID){

}
bool buttonReleased(buttonID:: eButtonID){

}