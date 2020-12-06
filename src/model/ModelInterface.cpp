#include "ModelInterface.h"
#include "Platform.h"

ModelInterface::ModelInterface() {
    player = Player();
    platforms.push_back(Platform(10, 0.4, 11, 7));
    platforms.push_back(Platform(10, 0.4, 6, 0));
    platforms.push_back(Platform(8, 0.4, 18, 12));
    platforms.push_back(Platform(8, 0.4, -2, 15));
    platforms.push_back(Platform(7, 0.1, -10, 20));
    platforms.push_back(Platform(50, 0.4, -5, 25));

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
