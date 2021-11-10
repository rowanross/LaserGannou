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

    int gameState = 0;

    static constexpr const int PRE_GAME = 0;
    static constexpr const int SETTIMING = 1;
    static constexpr const int SETWEAPONPOWER = 2;
    static constexpr const int GAME = 3;

    hwlib::target::pin_oc scl = hwlib::target::pin_oc( hwlib::target::pins::scl );
    hwlib::target::pin_oc sda = hwlib::target::pin_oc( hwlib::target::pins::sda );
    hwlib::i2c_bus_bit_banged_scl_sda i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);
    hwlib::glcd_oled oled = hwlib::glcd_oled(i2c_bus, 0x3c);

    hwlib::window_part_t w1 = hwlib::part(
            oled,
            hwlib::xy(0, 0),
            hwlib::xy(128, 32));
    hwlib::window_part_t w4 = hwlib::part(
            oled,
            hwlib::xy( 0, 0 ),
            hwlib::xy( 128, 16));
    hwlib::window_part_t w5 = hwlib::part(
            oled,
            hwlib::xy( 0, 16 ),
            hwlib::xy( 128, 16));
    hwlib::window_part_t w6 = hwlib::part(
            oled,
            hwlib::xy( 0, 32 ),
            hwlib::xy( 128, 16));

    // voor grote texten
    hwlib::font_default_16x16 f1 = hwlib::font_default_16x16();
    hwlib::terminal_from d1 = hwlib::terminal_from(w1, f1);

    //voor +- keuzes
    hwlib::font_default_8x8 f3 = hwlib::font_default_8x8();
    hwlib::terminal_from d4 = hwlib::terminal_from( w4, f3 );
    hwlib::terminal_from d5 = hwlib::terminal_from( w5, f3 );
    hwlib::terminal_from d6 = hwlib::terminal_from( w6, f3 );

    int time = 5;
    int power = 1;


    void main() {



        switch (gameState){
            case PRE_GAME:
                // als hij net aan gaat dan kan hij hier wat extra gegevens dan wel opvragen dan checken.
                d1 << "\f"
                   << "press \n any \n button";
                if(buttonPressedChannel.read() != 0){
                    showChange();
                    gameState = SETTIMING;
                }

            case SETTIMING:
                // Momenteel enkel voor het 'opgeven' van de tijd in de int time. Deze zal in gameParameter verder moeten worden verwerkt;
                d4 << "\f"
                   << "    Geef uw \n  timing:";
                d5 << "\f"
                   << "minuten";
                d6 << "\f"
                   << "     -  " << time << "  +";
                if (buttonPressedChannel.read() == 1) {
                    // timing wordt toegevoegd in initGameControl
                    showChange();
                }
                if (buttonPressedChannel.read() == 2) {
                    //zie bovenstaande comment
                    showChange();
                }
                if (buttonPressedChannel.read() = 4){
                    d1 << "\f"
                       << "u sure?";
                    if (buttonPressedChannel.read() = 4) {
                        gameState = SETWEAPONPOWER;
                    }else if (buttonPressedChannel.read() = 3){
                        gameState = SETTIMING;
                    }
                }


            case SETWEAPONPOWER:
                d4 << "\f"
                   << "    Geef uw \n  weaponpower:";
                d5 << "\f"
                   << "WeaponPower";
                d6 << "\f"
                   << "     -  " << power << "  +";

                if (buttonPressedChannel.read() == 1) {
                    power++;
                    showChange();
                }
                if (buttonPressedChannel.read() == 2) {
                    power++;
                    showChange();
                }
                if (buttonPressedChannel.read() = 4) {
                    d1 << "\f"
                       << "u sure?";
                    if (buttonPressedChannel.read() = 4) {
                        gameState = GAME;
                    } else if (buttonPressedChannel.read() = 3) {
                        gameState = SETWEAPONPOWER;
                    }
                }

                case GAME:

                // show time
                //runGameControl timer ophalen.

                break;
            }
    }



public:

    display(): rtos::task<>("schermTaak"){}


    void ShowTiming(int timeLeft){
        d4  << "\f"
            << " " << timeLeft << " ";
        d5  << " \nseconds left";
        d6  << "\f";

        showChange();
    }

    void buttonPressed(int buttonID){
        buttonPressedChannel.write(buttonID);
    }

    void showChange(){
            oled.flush();
        //update het huidige scherm;
    }

}


#endif //V2THDE_EXAMPLES_DISPLAY_H
