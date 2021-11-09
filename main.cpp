#include "hwlib.hpp"
#include "rtos.hpp"
#include "runGameControl.h"
//#include "initGameControl.h"
#include "receiveIRMessageControl.h"

int main( void ){
    // wait for the PC console to start
    hwlib::wait_ms( 500 );

    namespace target = hwlib::target;

//    initGameControl initGame;
//    initGame.startGame();

//
//    for(;;){
//        sendOne(led_1);
//        sendZero(led_1);
//        sendOne(led_1);
//        sendZero(led_1);
//        sendOne(led_1);
//        sendZero(led_1);
//        sendOne(led_1);
//        sendZero(led_1);
//        hwlib::wait_ms(500);
//    }
//
//    auto data_pin = target::pin_in( target::pins::d52 );
//
//
//
//    for(;;){
//        hwlib::cout << "START\n";
//        uint16_t data = getData(data_pin);
//        hwlib::cout << data << hwlib::endl;
//        hwlib::cout << "END\n";
//    }

    //rtos::run();
}