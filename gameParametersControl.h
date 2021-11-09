#ifndef V2THDE_EXAMPLES_GAMEPARAMETERSCONTROL_H
#define V2THDE_EXAMPLES_GAMEPARAMETERSCONTROL_H

#include "hwlib.hpp"

class gameParametersControl {
private:
    hwlib::target::pin_in min = hwlib::target::pin_in(hwlib::target::pins::d8);
    hwlib::target::pin_in plus = hwlib::target::pin_in(hwlib::target::pins::d9);
    hwlib::target::pin_in confirm = hwlib::target::pin_in(hwlib::target::pins::d10);
public:
    gameParametersControl(
            hwlib::target::pin_in min = hwlib::target::pin_in(hwlib::target::pins::d8),
            hwlib::target::pin_in plus = hwlib::target::pin_in(hwlib::target::pins::d9),
            hwlib::target::pin_in confirm = hwlib::target::pin_in(hwlib::target::pins::d10))
    {}



    void powerDisplay(int &power){
        auto scl     = hwlib::target::pin_oc( hwlib::target::pins::scl );
        auto sda     = hwlib::target::pin_oc( hwlib::target::pins::sda );
        auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda );
        auto oled    = hwlib::glcd_oled( i2c_bus, 0x3c );
        auto w1 = hwlib::part(
                oled,
                hwlib::xy( 0, 0 ),
                hwlib::xy( 128, 16));
        auto w2 = hwlib::part(
                oled,
                hwlib::xy( 0, 16 ),
                hwlib::xy( 128, 32));
        auto w3 = hwlib::part(
                oled,
                hwlib::xy( 0, 32 ),
                hwlib::xy( 128, 48));

        auto f1 = hwlib::font_default_8x8();
        auto d1 = hwlib::terminal_from( w1, f1 );
        auto d2 = hwlib::terminal_from( w2, f1 );
        auto d3 = hwlib::terminal_from( w3, f1 );
        d1 << "\f"
           << "    Geef uw \n  weaponpower:" << hwlib::flush;
        d2 << "\f"
           << "" << hwlib::flush;
        d3 << "\f"
           << "     -  " << power << "  +" << hwlib::flush;

    }

    int setWeaponpower(){
        int power = 1;
        for(;;){
            if(power > 1){
                if(min.read() == 0){
                    power--;
                    powerDisplay(power);
                }
            }
            if(power < 3){
                if(plus.read() == 0){
                    power++;
                    powerDisplay(power);
                }
            }
            if(confirm.read() == 0){
                break;
            }
        }
        return power;
    }
};


#endif //V2THDE_EXAMPLES_GAMEPARAMETERSCONTROL_H
