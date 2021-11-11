//
// Created by eriks on 9-11-2021.
//

#include "hwlib.hpp"
#include "rtos.hpp"

#ifndef V2THDE_EXAMPLES_DISPLAY_H
#define V2THDE_EXAMPLES_DISPLAY_H


class display : public rtos::task<>{
private:
    rtos::flag preSpel;
    rtos::flag setTime;
    rtos::flag setPower;
    rtos::flag flush;
    rtos::flag confirm;
    rtos::flag showTime;
    rtos::flag clear;

    int time;
    int weaponpower;
    int restTime;

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

    void preGame(){
        oled.clear();
        d1 << "\f"
           << "press \n any \n button";
        oled.flush();
    }

    void setTiming(int & time){
        oled.clear();
        d4 << "\f"
           << "    Geef uw \n  timing:";
        d5 << "\f"
           << "minuten";
        d6 << "\f"
           << "     -  " << time << "  +";
        oled.flush();
    }

    void setWeaponPower(int & power){
        oled.clear();
        d4 << "\f"
           << "    Geef uw \n  weaponpower:";
        d5 << "\f"
           << "WeaponPower";
        d6 << "\f"
           << "     -  " << power << "  +";
        oled.flush();
    }

    void showConfirm(){
        d4 << "druk aub op de";
        d5 << "confirm knop,";
        d6 << "if(connected met pc)";
    }

    void showChange(){
        oled.flush();
        //update het huidige scherm;
    }

    void ShowTiming(int timeLeft){
        d4  << "\f"
            << " " << timeLeft << " ";
        d5  << " \nseconds left";
        d6  << "\f";

        showChange();
    }

    void clearDisplay(){
        d1 << "\f";
        d4 << "\f";
        d5 << "\f";
        d6 << "\f";

        showChange();

    }



public:

    display():
        rtos::task<>("schermTaak"),
        preSpel(this, "preSpel"),
        setTime(this, "setTime"),
        setPower(this, "setPower"),
        flush(this, "flush"),
        confirm(this, "confirm"),
        showTime(this, "showTime"),
        clear(this, "clear")
    {}

    void main() {
        auto evt = wait(preSpel+setTime+setPower+flush+confirm+showTime+clear);
        for(;;){
            if(evt == preSpel){
                preGame();
            }
            if(evt == setTime){
                setTiming(time);
            }
            if(evt == setPower){
                setWeaponPower(weaponpower);
            }
            if(evt == flush){
                showChange();
            }
            if(evt == confirm){
                showConfirm();
            }
            if(evt == showTime){
                ShowTiming(restTime);
            }
            if(evt == clear){
                clearDisplay();
            }
        }
    }

    void setPreSpelFlag(){
        preSpel.set();
    }

    void setTimeFlag(int & playtime){
        time =  playtime;
        setTime.set();
    }

    void setPowerFlag(int & power){
        weaponpower = power;
        setPower.set();
    }

    void setFlushFlag(){
        flush.set();
    }

    void setConfirmFlag(){
        confirm.set();
    }

    void setShowTimeFlag(int & timeLeft){
        restTime = timeLeft;
        showTime.set();
    }

    void setClearFlag(){
        clear.set();
    }
};


#endif //V2THDE_EXAMPLES_DISPLAY_H
