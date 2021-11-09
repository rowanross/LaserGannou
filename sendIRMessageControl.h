#ifndef V2THDE_EXAMPLES_SENDIRMESSAGECONTROL_H
#define V2THDE_EXAMPLES_SENDIRMESSAGECONTROL_H

#include "hwlib.hpp"

class sendIRMessageControl {
private:
    hwlib::target::d2_36kHz led_1 = hwlib::target::d2_36kHz();
public:
    sendIRMessageControl(hwlib::target::d2_36kHz led_1 = hwlib::target::d2_36kHz())
    {}

    void sendMessage(uint16_t message){
        for(unsigned int i = 0; i < 16; i++){
            bool bit = (message & (32768 >> i));
            if(bit){
                sendOne();
            }else{
                sendZero();
            }
        }
    }

    void sendZero(){
        led_1.write(1);
        hwlib::wait_us(800);
        led_1.write(0);
        hwlib::wait_us(1600);
    }

    void sendOne(){
        led_1.write(1);
        hwlib::wait_us(1600);
        led_1.write(0);
        hwlib::wait_us(800);
    }
};


#endif //V2THDE_EXAMPLES_SENDIRMESSAGECONTROL_H