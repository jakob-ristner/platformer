#include "PlayerInputHandler.h"
#include "Box2D.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>

PlayerInputHandler::PlayerInputHandler(Player* player) {
    this->player = player;
    jumpCounter = 1;
    left = b2Vec2(-player->getAcc(), 0);
    right = b2Vec2(player->getAcc(), 0);

    isMovingRight = false;
    isMovingLeft = false;
}

PlayerInputHandler::PlayerInputHandler() {}

PlayerInputHandler::~PlayerInputHandler(){}

void PlayerInputHandler::handleEvent(sf::Event event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::Key::W:
                playerJump();
                break;
            case sf::Keyboard::Key::A:
                isMovingRight = false;
                isMovingLeft = true;
                break;

            case sf::Keyboard::Key::D:
                isMovingRight = true;
                isMovingLeft = false;
                break;
                
            default:
                break;
        }
    } else if (event.type = sf::Event::KeyReleased) {
        switch (event.key.code) {
            case sf::Keyboard::A:
                isMovingLeft = false;
                break;
            
            case sf::Keyboard::D:
                isMovingRight = false;
         
            default:
                break;
        }
    }

}

void PlayerInputHandler::updateTime(float dt) {
    jumpCounter += dt;
    movePlayer();
}

void PlayerInputHandler::playerJump() {
    float playerVelx = player->getBody()->GetLinearVelocity().x;
    float playerVely = player->getBody()->GetLinearVelocity().y;
    if (jumpCounter >= jumpDelay && player->onGround) {
        player->getBody()->SetLinearVelocity(b2Vec2(playerVelx, -player->getJump()));
        jumpCounter = 0;
    }
}

void PlayerInputHandler::movePlayer() {

    float playerVelx = player->getBody()->GetLinearVelocity().x;

    if (playerVelx > -player->getSpeed() && isMovingLeft) {
        player->getBody()->ApplyLinearImpulseToCenter(left, true);

    } else if (playerVelx < player->getSpeed() && isMovingRight) {
        player->getBody()->ApplyLinearImpulseToCenter(right, true);
    }
}
