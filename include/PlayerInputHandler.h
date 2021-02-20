#pragma once
#include "Player.h"
#include "CollisionObserver.h"
#include <SFML/Graphics.hpp>

class PlayerInputHandler : public CollisionObserver {
    public:
        PlayerInputHandler(Player* player);
        PlayerInputHandler();
        ~PlayerInputHandler();
        void handleEvent(sf::Event event);
        void update(float dt);

        void notifyCollide(Body* b1, Body* b2);
        void notifyUncollide(Body* b1, Body* b2);

        void handleKeyRelease(sf::Event event);
        
    private:

        void playerJump();
        void movePlayer();
        void handleCharge(float dt);
        float jumpCounter;
        bool isMovingRight;
        bool isMovingLeft;

        bool isCharging = false;
        float charge = 0;

        Player* player;

        b2Vec2 left;
        b2Vec2 right;
        
        float dtConstant = 60;


        // Dashing
        void dash(float dt);
        float dashInterval = 0.5;
        float dashCooldown = 0.8;
        float dashDur = 0.2;
        float dashCooldowncounter = 0;
        int postDashSpeed = 5;
        bool dashRightPressed = false;
        bool justDashed = false;
        bool doDash = false;
        bool dashing = false;
        bool dashLeftPressed = false;
        float dashTimerRight = 0;
        float dashTimerLeft = 0;
        
};

