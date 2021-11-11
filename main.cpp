#include "hwlib.hpp"
#include "rtos.hpp"
#include "bieperControl.h"
#include "transferHitControl.hpp"
#include "display.h"
<<<<<<< HEAD
=======
#include "ButtonListener.h"
#include "gameParametersControl.h"
>>>>>>> 02d7de1592c584de8c407a9539bc5f8791becba6
#include "sendIRMessageControl.h"
#include "runGameControl.h"
#include "gameParametersControl.h"
#include "initGameControl.h"
#include "ButtonListener.h"
#include "receiveIRMessageControl.h"


int main( void ){
    hwlib::wait_ms(500);
    auto bieper = bieperControl();
    auto transfer = transferHit();
    auto scherm = display();
    auto irSend = sendIRMessageControl();
    auto runGame = runGameControl(bieper, irSend, scherm, transfer);
    auto params = gameParametersControl(runGame, scherm);
    auto init = initGameControl(irSend, scherm, params);
    auto button = ButtonListener(init, runGame, params);
    auto receive = receiveIRMessageControl(params);
    rtos::run();
}