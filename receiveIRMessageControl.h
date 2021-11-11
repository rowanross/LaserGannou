#ifndef V2THDE_EXAMPLES_RECEIVEIRMESSAGECONTROL_H
#define V2THDE_EXAMPLES_RECEIVEIRMESSAGECONTROL_H

#include "hwlib.hpp"
#include "rtos.hpp"
#include "gameParametersControl.h"

class receiveIRMessageControl : public rtos::task <>{
private:
    hwlib::target::pin_in pin = hwlib::target::pin_in(hwlib::target::pins::d52);
    uint16_t data = 0x00;
    int timer;
    uint8_t playerID;
    uint8_t weaponPower;
    uint8_t playtime;

    gameParametersControl & parameters;




public:
    receiveIRMessageControl(gameParametersControl & parameters): rtos::task<>("receiveIRMessageControlTaak"), parameters(parameters) {}

    void main(){
        enum state_t {IDLE, RECEIVE, STARTGAME};
        state_t state = IDLE;
        for (;;) {
            switch (state) {
                case IDLE: {
                    pin.refresh();
                    if (pin.read() == 0) {
                        state = RECEIVE;
                    }
                    break;
                }

                case RECEIVE: {
                    for (int i = 0; i < 16; i++) {
                        for (;;) {
                            timer = 0;
                            if (pin.read() == 0) {
                                timer = hwlib::now_us();
                                while (pin.read() == 0) {}
                                timer = (hwlib::now_us() - timer);
                            }

                            if (timer >= 1200) {
                                data = data | 0x01;
                                if (i < 16) {
                                    data = data << 1;
                                }
                                break;
                            } else if (timer >= 500 && timer < 1200) {
                                if (i < 15) {
                                    data = data << 1;
                                }
                                break;
                            }
                        }
                    }
                    playerID = (data >> 11) & 0b1111;
                    weaponPower = (data >> 9) & 0b11;
                    playtime = (data >> 4) & 0b11111;
                    state = STARTGAME;
                }

                case STARTGAME: {
                    if(weaponPower == 0b00){
                        parameters.Start();
                    }

                    state = IDLE;
                    break;
                }
            }
        }
    }

//    bool checkSum(uint16_t message) {
//        for (unsigned int i = 1; i < 6; i++) {
//            uint16_t print = (32768 >> i) ^ (32768 >> (i + 5));
//            hwlib::cout << print << hwlib::endl;
//            bool bit = ((32768 >> i) ^ (32768 >> (i + 5)));
//            if (bit != (message & (32768 >> (i + 10)))) {
//                return false;
//            }
//        }
//        return true;
//    }
};

#endif //V2THDE_EXAMPLES_RECEIVEIRMESSAGECONTROL_H
