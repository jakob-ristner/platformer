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
        void setCds(std::vector<std::tuple<std::string, float*, bool*>>* coolDowns);

        
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

        std::vector<std::tuple<std::string, float*, bool*>>* coolDowns;

        // Dashing
        void dash(float dt);
        float dashInterval = 0.2;
        float dashCooldown = 2;
        float dashDur = 0.25;
        float dashCooldowncounter = dashCooldown;
        int postDashSpeed = 8;
        bool dashRightPressed = false;
        bool justDashed = false;
        bool doDash = false;
        bool dashing = false;
        bool dashLeftPressed = false;
        float dashTimerRight = 0;
        float dashTimerLeft = 0;
        
};

