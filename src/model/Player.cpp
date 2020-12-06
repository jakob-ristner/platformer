#include "Player.h"
#include <iostream>

Player::Player() {
    width = 1;
    height = 2;
    density = 1;
    friction = 0;

    jump = 15;
    acc = 4;
    speed = 8;
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


