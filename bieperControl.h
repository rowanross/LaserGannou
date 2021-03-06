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
    static constexpr char hitSound[] = "hit:d=4,o=5,b=500:a,16p,a";       // gr kyrill
    static constexpr char deathSound[] = "dood:d=4,o=5,b=40:16g6,16e6,16g";     // gr kyrill

    //zet de juiste pin neer;
    hwlib::target::pin_out lsp = hwlib::target::pin_out( hwlib::target::pins::d7 );
    note_player_gpio p = note_player_gpio( lsp );

    rtos::flag playHit;
    rtos::flag playDeath;

    void playHitSound(){
        //aan te roepen vanuit bijv. rungGameControl bij iedere hit;
        rtttl_play( p, hitSound);
    }

    void playDeathSound(){
        //aan te roepen vanuit bijv. runGameContol bij iedere keer dat je dood gaat.
        rtttl_play( p, deathSound);
    }



public:
<<<<<<< HEAD
    bieperControl(): rtos::task<>( "bieperControlTaak"),
=======
    bieperControl(): rtos::task<>(4, "bieperControlTaak"),
>>>>>>> 02d7de1592c584de8c407a9539bc5f8791becba6
        playHit(this, "playHit"),
        playDeath(this, "playDeath")
        {}

    void main(){
        for(;;){
            auto evt = wait(playHit+playDeath);
            if(evt == playHit){
                playHitSound();
                break;
            }
            if(evt == playDeath){
                playDeathSound();
                break;
            }
        }
    }

    void setPlayHitFlag(){
        playHit.set();
    }

    void setPlayDeathFlag(){
        playDeath.set();
    }
};


#endif //V2THDE_EXAMPLES_BIEPERCONTROL_H