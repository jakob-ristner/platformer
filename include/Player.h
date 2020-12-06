#pragma once
#include "Pos.h"
#include "Body.h"

class Player: public Body {
    public:
        Player();
        ~Player();

        int getJump();
        float getSpeed();
        float getAcc();

        bool onGround = true;
    private:
        int jump;
        float acc; 
        float speed;

};
