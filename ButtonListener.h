//
// Created by eriks on 8-11-2021.
//
#include "hwlib.hpp"
#include "rtos.hpp"
#include "initGameControl.h"
#include "runGameControl.h"
#include "gameParametersControl.h"

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

    runGameControl & runGame;
    gameParametersControl & gameParam;



public:

    ButtonListener(initGameControl & initGame, runGameControl & runGame, gameParametersControl & gameParam):
<<<<<<< HEAD
        rtos::task<>( 4, "buttonListenerTask"),
=======
        rtos::task<>(2, "buttonListenerTask"),
>>>>>>> 02d7de1592c584de8c407a9539bc5f8791becba6
        initGame(initGame),
        runGame(runGame),
        gameParam(gameParam)
    {}
    void main() {
        for (;;) {
            if (plusKnop.read() == 0) {

                while (plusKnop.read() == 0){}
                hwlib::cout << "1" ;
                initGame.buttonPressed(1);
                runGame.buttonPressed(1);
                gameParam.buttonPressed(1);

            }
            if (minKnop.read()== 0) {
                while (minKnop.read() == 0){}
                hwlib::cout << "2" ;
                initGame.buttonPressed(2);
                runGame.buttonPressed(2);
                gameParam.buttonPressed(2);

            }
            if (menuKnop.read()== 0) {
                while (menuKnop.read() == 0){}
                hwlib::cout << "3" ;
                initGame.buttonPressed(3);
                runGame.buttonPressed(3);
                gameParam.buttonPressed(3);

            }
            if (confirmKnop.read()== 0) {
                while (confirmKnop.read() == 0){}
                hwlib::cout << "4" ;
                initGame.buttonPressed(4);
                runGame.buttonPressed(4);
                gameParam.buttonPressed(4);

            }
            if (trigger.read()== 0) {
                while (trigger.read() == 0){}
                hwlib::cout << "5" ;
                initGame.buttonPressed(5);
                runGame.buttonPressed(5);
                gameParam.buttonPressed(5);

            }
        }
    }
};


#endif //V2THDE_EXAMPLES_BUTTONLISTENER_H
