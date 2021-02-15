#include "GameView.h"
#include "Player.h"
#include "Body.h"
#include "ModelInterface.h"
#include "../lib/Box2D.h"
#include <SFML/Graphics.hpp>
#include "PlayerInputHandler.h"
#include "PlayerContactListener.cpp"

class GameController {
    public:
        GameController();
        ~GameController();

        void updateModel(float dt);
        void updateView();

        void run();

    private: 
        void init();
        void initDynBody(Body* body);
        void initStatBody(Body* body);

        void handlePlayerFric(); 

        //Input
        void enterMenu();
        void handleInput();
        void pressMenuButton(MenuView* menu);

        bool running;
        bool inMenu;
        GameView view;
        
        Player* player;
        void playerJump();
        const float playerGroundForce = 2;

        ModelInterface model;
       
        sf::Clock clock;
        sf::Time deltaTime;
        sf::Event event;
        float dt;

        void beginPlayerContact();
        void endPlayerContact();
        bool playerCol = false;
        PlayerContactListener clistener;


        static const int velocityiIt = 6;
        static const int posIt = 2;
        static const int g = 30;

        b2Vec2 gravity = b2Vec2(0.0f, g);
        b2World world = b2World(gravity);

        PlayerInputHandler playerHandler;

        

};
