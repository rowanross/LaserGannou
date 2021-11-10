#ifndef V2THDE_EXAMPLES_GAMEPARAMETERSCONTROL_H
#define V2THDE_EXAMPLES_GAMEPARAMETERSCONTROL_H

#include "hwlib.hpp"
#include "rtos.hpp"
#include "runGameControl.h"

class gameParametersControl : public rtos::task <>{
private:
    hwlib::target::pin_in min = hwlib::target::pin_in(hwlib::target::pins::d8);
    hwlib::target::pin_in plus = hwlib::target::pin_in(hwlib::target::pins::d9);
    hwlib::target::pin_in confirm = hwlib::target::pin_in(hwlib::target::pins::d10);

    hwlib::target::pin_oc scl = hwlib::target::pin_oc( hwlib::target::pins::scl );
    hwlib::target::pin_oc sda = hwlib::target::pin_oc( hwlib::target::pins::sda );
    hwlib::i2c_bus_bit_banged_scl_sda i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda );
    hwlib::glcd_oled oled = hwlib::glcd_oled( i2c_bus, 0x3c );

    static constexpr int SYSTEMSTARTUP = 1;
    static constexpr int GETPARAMETERS = 2;
    static constexpr int STARTGAME= 3;

    rtos::flag Startflag;

    uint16_t playtime = 0;
    uint16_t playerID = 0;
    uint16_t weaponPower = 0;

    runGameControl & runGame;

    rtos::channel<buttonID, 5> buttonPressedChannel;
    rtos::flag parametersFlag;

    void main(){
        int state = GETPARAMETERS;
        switch(state) {
            case GETPARAMETERS:{
                auto w2 = hwlib::part(
                        oled,
                        hwlib::xy( 0, 32 ),
                        hwlib::xy( 128, 48));
                auto f1 = hwlib::font_default_8x8();
                auto d2 = hwlib::terminal_from( w2, f1 );
                int power = 1;
                for(;;){
                    if(power > 1){
                        if(min.read() == 0){
                            power--;
                            d2 << "\f"
                               << "     -  " << power << "  +" << hwlib::flush;
                        }
                    }
                    if(power < 3){
                        if(plus.read() == 0){
                            power++;
                            d2 << "\f"
                               << "     -  " << power << "  +" << hwlib::flush;
                        }
                    }
                    if(confirm.read() == 0){
                        break;
                    }
                }
            }

            case STARTGAME:{
                runGame.setParameters();
            }
        }
    }

public:
    gameParametersControl(runGameControl & runGame):
            rtos::task<>("parametersControlTaak"),
            runGame(runGame),
            Startflag(this, "Startflag")
    {}

    void setParams(uint16_t playerID_r, uint16_t playtime_r){
        playerID = playerID_r;
        playtime = playtime_r;
    }

    void buttonPressed(int buttonID){
        buttonPressedChannel.write(buttonID);
    }

    void Start(){Startflag.set();}
};


#endif //V2THDE_EXAMPLES_GAMEPARAMETERSCONTROL_H
