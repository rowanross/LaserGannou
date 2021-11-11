#include "hwlib.hpp"
#include "rtos.hpp"
#include "runGameControl.h"
#include "initGameControl.h"
#include "receiveIRMessageControl.h"
#include "bieperControl.h"
#include "display.h"
#include "gameParametersControl.h"
#include "sendIRMessageControl.h"
#include "transferHitControl.hpp"


int main( void ){
    hwlib::wait_ms(500);
    auto bieper = bieperControl();
    (void) bieper;
    auto transfer = transferHit();
    (void) transfer;
    auto scherm = display();
    (void) scherm;
    auto irSend = sendIRMessageControl();
    (void) irSend;
    auto runGame = runGameControl(bieper, irSend, scherm, transfer);
    (void) runGame;
    auto params = gameParametersControl(runGame, scherm);
    (void) params;
    auto init = initGameControl(irSend, scherm, params);
    (void) init;
    auto receive = receiveIRMessageControl(params);
    (void) receive;
    rtos::run();
}