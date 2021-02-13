#pragma once
#include "Player.h"
#include <SFML/Graphics.hpp>

class PlayerInputHandler {
    public:
        PlayerInputHandler(Player* player);
        PlayerInputHandler();
        ~PlayerInputHandler();
        void handleEvent(sf::Event event);
        void update(float dt);
        
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

        
};

