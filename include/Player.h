#pragma once
#include "Pos.h"
#include "Body.h"

class Player: public Body {
    public:
        Player();
        ~Player();

        int getJump();
        int getAttCharge();
        float getSpeed();
        float getAcc();
        void setCharge(float charge);
        float getCharge();
        
        bool getContact();
        void collide();
        void unCollide();

        bool onGround = false;

    private:
        int jump = 20;
        float acc = 8; 
        float speed = 8;
        float charge = 0;
        bool contact = false;
        int collisions = 0;

};
