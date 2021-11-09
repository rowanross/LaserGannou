#ifndef TRANSFERHITCONTROL_HPP
#define TRANSFERHITCONTROL_HPP

#include <array>
class transferHit : public rtos::task<>{
private:
    bool nextGame;
    void main(){
        enum state_t {BUSY, FINISHED}
        state_t state = BUSY;
        rtos::flag acceptButton;

        for (;;){
            switch(state){
                case BUSY: {
                    if (gameTime == 0){
                        state = FINISHED;
                    }
                    break;
                }

                case FINISHED:{
                    auto evt = wait(acceptButton);
                    if(evt == acceptButton){
                        hwlib::wait_ms(200);
                        for (std::array & x : a){
                            hwlib::cout << playernr << ","<< hits << "\n";
                        }

                        state = BUSY;

                    }
                    break;
                }
            }
        }
    }

public:
    transferHit():
        rtos::task<>("TransferHit"),
        acceptButton(this, "acceptButton")
    {}

};


#endif