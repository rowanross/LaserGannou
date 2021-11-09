//
// Created by eriks on 8-11-2021.
//
#include "hwlib.hpp"
#include "rtos.hpp"
#include "initGameControl.h"
#include "runGameControl.h"
#include "display.h"

#ifndef V2THDE_EXAMPLES_BUTTONLISTENER_H
#define V2THDE_EXAMPLES_BUTTONLISTENER_H


class ButtonListener : public rtos::task<>{
private:
    hwlib::target::pin_in plusKnop  = hwlib::target::pin_in( hwlib::target::pins::d50 );
    hwlib::target::pin_in minKnop  = hwlib::target::pin_in( hwlib::target::pins::d48 );
    hwlib::target::pin_in menuKnop  = hwlib::target::pin_in( hwlib::target::pins::d46 );
    hwlib::target::pin_in confirmKnop  = hwlib::target::pin_in( hwlib::target::pins::d44 );

    initGameControl & initGame;
    display & scherm;
    runGameControl runGame;

    void main() {
        for (;;) {
            if (!plusKnop.read()) {
                initGame.buttonPressed(1);
                scherm.buttonPressed(1);
                runGame.buttonPressed(1);
            }
            if (!minKnop.read()) {
                initGame.buttonPressed(2);
                scherm.buttonPressed(2);
                runGame.buttonPressed(2);
            }
            if (!menuKnop.read()) {
                initGame.buttonPressed(3);
                scherm.buttonPressed(3);
                runGame.buttonPressed(3);
            }
            if (!confirmKnop.read()) {
                initGame.buttonPressed(4);
                scherm.buttonPressed(4);
                runGame.buttonPressed(4);
            }
            if (!trigger.read()) {
                initGame.buttonPressed(5);
                runGame.buttonPressed(5);

            }
        }
    }

public:

    ButtonListener(initGameControl & initGame, display & scherm  , runGameControl runGame): rtos::task<>("buttonListenerTask"), initGame(initGame), scherm(scherm) , runGame(runGame){}
};


#endif //V2THDE_EXAMPLES_BUTTONLISTENER_H
