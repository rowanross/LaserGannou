#include "hwlib.hpp"
#include "rtos.hpp"
#include "runGameControl.h"
#include "initGameControl.h"
#include "receiveIRMessageControl.h"
#include "bieperControl.h"
#include "display.h"
#include "ButtonListener.h"
#include "gameParametersControl.h"
#include "sendIRMessageControl.h"
#include "transferHitControl.hpp"


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