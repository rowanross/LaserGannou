//
// Created by eriks on 8-11-2021.
//

#include "hwlib.hpp"
#include "rtos.hpp"

#include "note_player_gpio.hpp"
#include "rtttl_player.hpp"


#ifndef V2THDE_EXAMPLES_BIEPERCONTROL_H
#define V2THDE_EXAMPLES_BIEPERCONTROL_H


class bieperControl : public rtos::task<>{
private:
    //stuur de bieper aan
    static constexpr char hitSound[] = "SOS:d=4,o=5,b=60:a,p,a,p,a,p,2a.,p,2a.,p,2a.,p,a,p,a,p,a";       // te veranderen!
    static constexpr char deathSound[] = "dood:d=4,o=5,b=40:16g6,16e6,16g,2p";                          // idk van kyrill gekregen

    //zet de juiste pin neer;
    hwlib::target::pin_out lsp = hwlib::target::pin_out( hwlib::target::pins::d7 );
    note_player_gpio p = note_player_gpio( lsp );

    void main(){
        //idk moest dit maken volgens CLION aangezien klasse abstract is.
    }
public:
    bieperControl(): rtos::task<>("bieperControlTaak"){}

    void playHitSound(){
        //aan te roepen vanuit bijv. rungGameControl bij iedere hit;
        rtttl_play( p, hitSound);
    }

    void playDeathSound(){
        //aan te roepen vanuit bijv. runGameContol bij iedere keer dat je dood gaat.
        rtttl_play( p, deathSound);
    }
};


#endif //V2THDE_EXAMPLES_BIEPERCONTROL_H