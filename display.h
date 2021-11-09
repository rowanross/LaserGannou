//
// Created by eriks on 9-11-2021.
//

#include "hwlib.hpp"
#include "rtos.hpp"

#ifndef V2THDE_EXAMPLES_DISPLAY_H
#define V2THDE_EXAMPLES_DISPLAY_H


class display : public rtos::task<>{
private:

    rtos::channel<buttonID, 5> buttonPressedChannel;


    hwlib::target::pin_oc scl = hwlib::target::pin_oc( hwlib::target::pins::scl );
    hwlib::target::pin_oc sda = hwlib::target::pin_oc( hwlib::target::pins::sda );

    int gameState = 0;

    static constexpr const int PRE_GAME = 0;
    static constexpr const int GAME_SETUP = 1;
    static constexpr const int GAME = 2;
    auto oled;

    void main() {
        auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);
        auto oled = hwlib::glcd_oled(i2c_bus, 0x3c);

        auto w1 = hwlib::part(
                oled,
                hwlib::xy(0, 0),
                hwlib::xy(128, 32));
        auto w2 = hwlib::part(
                oled,
                hwlib::xy(0, 32),
                hwlib::xy(128, 32));

        auto f1 = hwlib::font_default_16x16();
        auto d1 = hwlib::terminal_from(w1, f1);

        auto f2 = hwlib::font_default_8x8();
        auto d2 = hwlib::terminal_from(w2, f2);


        switch (gameState){
            case PRE_GAME:
                // als hij net aan gaat dan kan hij hier wat extra gegevens dan wel opvragen dan checken.
                d1 << "\f"
                   << "press \n any \n button";
                if(buttonPressedChannel.read() != 0){
                    showChange();
                    gameState = GAME_SETUP;
                }

            case GAME_SETUP:
                // Momenteel enkel voor het 'opgeven' van de tijd in de int time. Deze zal in gameParameter verder moeten worden verwerkt;
                int time = 5;
                d1 << "\f"
                   << "choose \n timing:";
                d2 << "\f"
                   << "==============\n"
                   << time << "min" "\n"
                   << "==============\n";
                if (buttonPressedChannel.read() == 1) {
                    time++;
                    showChange();
                }
                if (buttonPressedChannel.read() == 2) {
                    time++;
                    showChange();
                }
                if (buttonPressedChannel.read() = 4){
                    d1 << "\f"
                       << "u sure?";
                    d2 << "\f";
                    if (buttonPressedChannel.read() = 4) {
                        gameState = GAME;
                    }else if (buttonPressedChannel.read() = 3){
                        gameState = GAME_SETUP;
                    }
                }
            case GAME:

                // show time
                // show playerNr
                break;
        }

    }


public:
    display(): rtos::task<>("schermTaak"){}

    void buttonPressed(int buttonID){
        buttonPressedChannel.write(buttonID);
    }

    void showChange(){
        for (;;){
            oled.flush();
        }
        //update het huidige scherm;
    }

};


#endif //V2THDE_EXAMPLES_DISPLAY_H
