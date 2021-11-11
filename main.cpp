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
    auto transfer = transferHit();
    auto display = display();
    auto irSend = sendIRMessageControl();
    auto init = InitGameControl(irSend, display);
    auto runGame = RunGameClass(bieper, irSend, display, transfer);
    auto params = Registergame(runGame, display);
    auto receive = receiveIRMessageControl(params);

    rtos::run();
}