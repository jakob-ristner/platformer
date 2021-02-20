#include "PlayerInputHandler.h"
#include "Box2D.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>

PlayerInputHandler::PlayerInputHandler(Player* player) {
    this->player = player;
    jumpCounter = 1;

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
                if (dashLeftPressed && !justDashed) {
                    justDashed = true;
                    dashing = true;
                    doDash = true;
                } else {
                    dashLeftPressed = true;
                }
                dashRightPressed = false;
                isMovingRight = false;
                isMovingLeft = true;
                break;

            case sf::Keyboard::Key::D:
                if (dashRightPressed && !justDashed) {
                    justDashed = true;
                    dashing = true;
                    doDash = true;
                } else {
                    dashRightPressed = true;
                }
                dashLeftPressed = false;
                isMovingRight = true;
                isMovingLeft = false;
                break;

            case sf::Keyboard::Key::Space:
                isCharging = true;
                break;
                
            default:
                break;
        }
    } else if (event.type = sf::Event::KeyReleased) {
        handleKeyRelease(event);
    }

}

void PlayerInputHandler::handleKeyRelease(sf::Event event) { // so that keys can be released in menu xd
    switch (event.key.code) {
        case sf::Keyboard::A:
            isMovingLeft = false;
            break;
       
        case sf::Keyboard::D:
            isMovingRight = false;
            break;

        case sf::Keyboard::Key::Space:
            isCharging = false;
            charge = 0;
            break;
    
        default:
            break;
   }
}

void PlayerInputHandler::update(float dt) {
    jumpCounter += dt;

    if (dashRightPressed) {
        dashTimerRight += dt;
        if (dashTimerRight > dashInterval) {
            dashTimerRight = 0;
            dashRightPressed = false;
        }
    }
    if (dashLeftPressed) {
        dashTimerLeft += dt;
        if (dashTimerLeft > dashInterval) {
            dashTimerLeft = 0;
            dashLeftPressed = false;
        }
    }

    if (justDashed) {
        dashCooldowncounter += dt;
        if (dashCooldowncounter >= dashDur && dashing) {
            dashing = false;
            float ys = player->getBody()->GetLinearVelocity().y;
            if (player->getBody()->GetLinearVelocity().x < 0) {
                player->getBody()->SetLinearVelocity(b2Vec2(-postDashSpeed, ys));
            } else {
                player->getBody()->SetLinearVelocity(b2Vec2(postDashSpeed, ys));
            }
        }
        
        if (dashCooldowncounter >= dashCooldown) {
            justDashed = false;
            dashCooldowncounter = 0;
        }
    } 

    if (doDash) {
        dash(dt);
        doDash = false;
    }


    left = b2Vec2(-player->getAcc() * dt * dtConstant, 0);
    right = b2Vec2(player->getAcc() * dt * dtConstant, 0);

    movePlayer();

    if (player->getContact() && player->getBody()->GetLinearVelocity().y == 0) {
        player->onGround = true;
    } else { 
        player->onGround = false;
    }
    if (player->getContact()) {
        if (player->getBody()->GetLinearVelocity().x < 0) {
            player->getBody()->ApplyLinearImpulseToCenter(b2Vec2(2 * dt * dtConstant , 0), true);
        } else if (player->getBody()->GetLinearVelocity().x > 0) {
            player->getBody()->ApplyLinearImpulseToCenter(b2Vec2(-2 * dt * dtConstant, 0), true);
        }
    }
    handleCharge(dt);
}

void PlayerInputHandler::playerJump() {
    float playerVelx = player->getBody()->GetLinearVelocity().x;
    float playerVely = player->getBody()->GetLinearVelocity().y;
    if (player->onGround) {
        player->getBody()->SetLinearVelocity(
                b2Vec2(playerVelx, -player->getJump()));
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


void PlayerInputHandler::handleCharge(float dt) {
    if (isCharging) {
        charge += dt;
    }
    player->setCharge(charge);
}

void PlayerInputHandler::notifyCollide(Body* b1, Body* b2) {
}

void PlayerInputHandler::notifyUncollide(Body* b1, Body* b2) {
}

void PlayerInputHandler::dash(float dt) {
    b2Vec2 dashVec = b2Vec2(-player->getDashForce() * dt * dtConstant, 0);
    if (dashRightPressed) {
        dashRightPressed = false;
        dashVec = b2Vec2(player->getDashForce() * dt * dtConstant, 0);
    } else if (dashLeftPressed) {
        dashLeftPressed = false;
    }


    player->getBody()->ApplyLinearImpulseToCenter(dashVec, true);
}

