//
// Created by eriks on 8-11-2021.
//
#include "hwlib.hpp"
#include "rtos.hpp"
#include "initGameControl.h"

#ifndef V2THDE_EXAMPLES_BUTTONLISTENER_H
#define V2THDE_EXAMPLES_BUTTONLISTENER_H


class ButtonListener : public rtos::task<>{
private:
    hwlib::target::pin_in plusKnop  = hwlib::target::pin_in( hwlib::target::pins::d50 );
    hwlib::target::pin_in minKnop  = hwlib::target::pin_in( hwlib::target::pins::d48 );
    hwlib::target::pin_in menuKnop  = hwlib::target::pin_in( hwlib::target::pins::d46 );
    hwlib::target::pin_in confirmKnop  = hwlib::target::pin_in( hwlib::target::pins::d44 );
    hwlib::target::pin_in trigger  = hwlib::target::pin_in( hwlib::target::pins::d42 );
    initGameControl & initGame;

    void main(){
        for(;;) {
            if (!plusKnop.read()) {
                initGame.buttonPressed(1);
                runGameControl.buttonPressed(1);
            }
            if (!minKnop.read()){
                initGame.buttonPressed(2);
                runGameControl.buttonPressed(2);
            }
            if(!menuKnop.read()){
                initGame.buttonPressed(3);
                runGameControl.buttonPressed(3);
            }
            if(!confirmKnop.read()){
                initGame.buttonPressed(4);
                runGameControl.buttonPressed(4);
            }
            if(!trigger.read()){
                initGame.buttonPressed(5);
                runGameControl.buttonPressed(5);
            }
        }
    }

public:
    ButtonListener(initGameControl & initGame): rtos::task<>("buttonListenerTask"), initGame(initGame){

    }

};


#endif //V2THDE_EXAMPLES_BUTTONLISTENER_H
