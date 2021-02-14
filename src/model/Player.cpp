#include "Player.h"
#include <iostream>

Player::Player() {
    width = 1;
    height = 2;
    density = 1;
    friction = 0;
    type = "player";
   
    shape.SetAsBox(width, height);

    startX = 0;
    startY = 0;
}

Player::~Player() {

}

int Player::getJump() {
    return jump;
}

float Player::getSpeed() {
    return speed;
}

float Player::getAcc() {
    return acc;
}

void Player::setCharge(float charge) {
    this->charge = charge;
}

float Player::getCharge() {
    return charge;
}

void Player::collide() {
    collisions++;
}


void Player::unCollide() {
    collisions--;
}

bool Player::getContact() {
    return collisions > 0;
}

void Player::collideStart() {
    collisions++;
}

void Player::collideEnd() {
    collisions--;
}
