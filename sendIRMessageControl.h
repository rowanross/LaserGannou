#ifndef V2THDE_EXAMPLES_SENDIRMESSAGECONTROL_H
#define V2THDE_EXAMPLES_SENDIRMESSAGECONTROL_H

#include "hwlib.hpp"
#include "rtos.hpp"

class sendIRMessageControl : public rtos::task<> {
private:
    hwlib::target::d2_36kHz led_1 = hwlib::target::d2_36kHz();

    rtos::flag initMessageFlag;
    rtos::flag messageFlag;

    uint16_t message;
    uint8_t playerID;
    uint8_t weaponpower;



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

    void sendMessage(uint8_t playerID, uint8_t weaponpower){
        uint16_t message = (((1 << 4) | playerID) << 2 | weaponpower) << 9;
        for(unsigned int i = 0; i < 16; i++){
            bool bit = (message & (32768 >> i));
            if(bit){
                sendOne();
            }else{
                sendZero();
            }
        }
    }





public:
    sendIRMessageControl():
        rtos::task<>("sendIRMessage"),
        initMessageFlag(this, "initMessageFlag"),
        messageFlag(this, "messageFlag")
    {}

    void main(){
        auto evt = wait(initMessageFlag+messageFlag);
        for(;;){
            if(evt == initMessageFlag){
                sendMessage(message);
            }
            if(evt == messageFlag){
                sendMessage(playerID, weaponpower);
            }
        }
    }

    void setInitMessageFlag(uint16_t bericht){
        message = bericht;
        initMessageFlag.set();
    }

    void setMessageFlag(uint8_t ID, uint8_t power){
        playerID = ID;
        weaponpower = power;
        messageFlag.set();
    }


};


#endif //V2THDE_EXAMPLES_SENDIRMESSAGECONTROL_H