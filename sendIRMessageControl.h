#ifndef V2THDE_EXAMPLES_SENDIRMESSAGECONTROL_H
#define V2THDE_EXAMPLES_SENDIRMESSAGECONTROL_H

#include "hwlib.hpp"
#include "rtos.hpp"

class sendIRMessageControl : public rtos::task<> {
private:
    hwlib::target::d2_36kHz led_1 = hwlib::target::d2_36kHz();

    rtos::flag initMessageFlag;
    rtos::flag messageFlag;

    uint16_t message = 0;
    uint8_t playerID = 0;
    uint8_t weaponpower = 0;

    void main(){
        for(;;){

            auto evt = wait(initMessageFlag+messageFlag);

            if(evt == initMessageFlag){
                sendMessage(message);
            }
            if(evt == messageFlag){
                hwlib::cout << "KAK";
                sendMessage(playerID, weaponpower);
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

    void sendMessage(uint16_t Message){

        for(unsigned int i = 0; i < 16; i++){
            bool bit = (Message & (32768 >> i));

            if(bit){
                sendOne();
            }else{
                sendZero();
            }
            hwlib::cout<<"28";
        }
    }

    void sendMessage(uint8_t PlayerID, uint8_t Weaponpower){
        uint16_t Message = (((1 << 4) | PlayerID) << 2 | Weaponpower) << 9;
        for(unsigned int i = 0; i < 16; i++){
            bool bit = (Message & (32768 >> i));
            if(bit){
                sendOne();
            }else{
                sendZero();
            }
        }
    }





public:
    sendIRMessageControl():
        rtos::task<>( 2, "sendIRMessage"),
        initMessageFlag(this, "initMessageFlag"),
        messageFlag(this, "messageFlag")
    {}



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