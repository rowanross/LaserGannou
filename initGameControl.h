#ifndef V2THDE_EXAMPLES_INITGAMECONTROL_H
#define V2THDE_EXAMPLES_INITGAMECONTROL_H
#include "hwlib.hpp"
#include "rtos.hpp"
#include "gameParametersControl.h"

class initGameControl {
private:
    hwlib::target::pin_in min = hwlib::target::pin_in(hwlib::target::pins::d8);
    hwlib::target::pin_in plus = hwlib::target::pin_in(hwlib::target::pins::d9);
    hwlib::target::pin_in confirm = hwlib::target::pin_in(hwlib::target::pins::d10);
public:
    initGameControl(
            hwlib::target::pin_in min = hwlib::target::pin_in(hwlib::target::pins::d8),
            hwlib::target::pin_in plus = hwlib::target::pin_in(hwlib::target::pins::d9),
            hwlib::target::pin_in confirm = hwlib::target::pin_in(hwlib::target::pins::d10))
    {}

    int startGame(){
        int playtime = getPlaytime();
        //if(playerNumber != 1){
        //  sendIR........
        //else{
        gameParametersControl parameters;
        int weaponPower = parameters.setWeaponpower();
    }

    int getPlaytime(){
        int playtime = 5;
        scherm(playtime);
        for (;;){
            if(min.read() == 0){
                if(playtime > 1){
                    playtime--;
                }
                scherm(playtime);
            }
            if(plus.read() == 0){
                playtime++;
                scherm(playtime);
            }
            if(confirm.read() == 0){
                break;
            }
        }
        return playtime;
    }

    void scherm(int playtime){
        auto scl     = hwlib::target::pin_oc( hwlib::target::pins::scl );
        auto sda     = hwlib::target::pin_oc( hwlib::target::pins::sda );
        auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda );
        auto oled    = hwlib::glcd_oled( i2c_bus, 0x3c );
        auto font    = hwlib::font_default_8x8();

        auto w1 = hwlib::part(oled, hwlib::xy(0,0), hwlib::xy(128,64));

        auto display = hwlib::terminal_from( w1, font );

        display << "\f" << "Kies de speeltijd"
                << "\n"
                << "\n" << "     - " << playtime << " + "
                << hwlib::flush;
    }
};


#endif //V2THDE_EXAMPLES_INITGAMECONTROL_H
