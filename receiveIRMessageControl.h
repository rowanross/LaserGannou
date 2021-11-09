#ifndef V2THDE_EXAMPLES_RECEIVEIRMESSAGECONTROL_H
#define V2THDE_EXAMPLES_RECEIVEIRMESSAGECONTROL_H

#include "hwlib.hpp"

class receiveIRMessageControl {
public:
    receiveIRMessageControl()
    {}

    uint16_t receiveMessage(hwlib::target::pin_in & pin){
        uint16_t data = 0x00;
        for (int i = 0; i < 16; i++) {
            for (;;) {
                int timer = 0;
                if (pin.read() == 0) {
                    timer = hwlib::now_us();
                    while (pin.read() == 0){}
                    timer = (hwlib::now_us() - timer);
                }

                if (timer >= 1200) {
                    data = data | 0x01;
                    if(i < 16){
                        data = data << 1;
                    }
                    break;
                } else if (timer >= 500 && timer < 1200) {
                    if(i < 15){
                        data = data << 1;
                    }
                    break;
                }
            }
        }
        return data;
    }
};


#endif //V2THDE_EXAMPLES_RECEIVEIRMESSAGECONTROL_H
