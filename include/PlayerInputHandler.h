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
        
        float fricConstant = 60;

        
};

