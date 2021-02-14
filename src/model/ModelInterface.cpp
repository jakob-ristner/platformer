#include "ModelInterface.h"
#include <iostream>
#include "Platform.h"

ModelInterface::ModelInterface() {
    player = Player();
    //platforms.push_back(Platform(width, height, x, y));
    platforms.push_back(Platform(10, 0.4, -15, 10));
    platforms.push_back(Platform(10, 0.4, -30, 15));
    platforms.push_back(Platform(10, 0.4, 18, 12));
    platforms.push_back(Platform(10, 0.4, -2, 15));
    platforms.push_back(Platform(40, 0.4, -2, 20));
}

ModelInterface::~ModelInterface() {}

Player* ModelInterface::getPlayer() {
    return &player;
}

float ModelInterface::getPlayerX() {
    return player.getBody()->GetPosition().x;
}

float ModelInterface::getPlayerY() {
    return player.getBody()->GetPosition().y;
}

std::vector<Body>* ModelInterface::getPlatforms() {
    return &platforms;
}

