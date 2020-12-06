#pragma once
#include "Player.h"
#include <SFML/Graphics.hpp>

class PlayerInputHandler {
    public:
        PlayerInputHandler(Player* player);
        PlayerInputHandler();
        ~PlayerInputHandler();
        void handleEvent(sf::Event event);
        void updateTime(float dt);
        
    private:
        void playerJump();
        void movePlayer();
        float jumpCounter;
        float jumpDelay = 1;
        bool isMovingRight;
        bool isMovingLeft;


        Player* player;

        b2Vec2 left;
        b2Vec2 right;

        
};

