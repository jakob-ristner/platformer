#pragma once
#include "Player.h"
#include "Body.h"
#include <vector>

class ModelInterface {
    public:
        ModelInterface();
        ~ModelInterface();

        Player* getPlayer();
        float getPlayerX();
        float getPlayerY();
    
        std::vector<Body>* getPlatforms();

    private:
        std::vector<Body> platforms;
        Player player;
        

};
