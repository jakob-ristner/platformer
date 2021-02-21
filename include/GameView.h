#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "ModelInterface.h"
#include "MenuView.h"
#include "CoolDownView.h"


class GameView {
    public:
        GameView();
        ~GameView();

        void update();
        void setModel(ModelInterface* model);

        void updatePlatforms();
        void initPlayer();

        MenuView* initMenu();

        bool poll(sf::Event &event);
        void display();

        void setCds(std::vector<std::tuple<std::string, float*, bool*>>* coolDowns);
    private:
        static const int windowWidth = 1920;
        static const int windowHeight = 1080;
        static const int worldScale = 25;

        //charge bar TODO could be moved to playerview
        static const int chargeBarWidth = 400;
        int chargeBarHeight = 20;
        static const int chargeBarY = 900;
        static const int chargeBw = 6;
        sf::RectangleShape chargeBarBorder;
        sf::RectangleShape chargeBarBackground;
        sf::RectangleShape chargeBarFill;
        void initChargeBar();
        void updateChargeBar();

        ModelInterface* model;

        sf::ContextSettings settings = sf::ContextSettings(0, 0, 8);

        sf::RenderWindow window;
        sf::RectangleShape bgFill;
        sf::Clock clock;
        sf::Time deltaTime;
        sf::Event event;

        sf::Vector2f getSize(Body* body);
        sf::Vector2f getOrigin(Body* body);
        sf::Vector2f getPos(Body* body);

        MenuView menu;

        void draw(); 

        // Add to gui view?
        CoolDownView cdView;




        //TODO move below to playerview
        void drawPlayer();
        void updatePlayerPos();
        void drawCastBar(); 
        sf::RectangleShape playerShape;

        //TODO same here
        void drawPlatforms();
        std::vector<sf::RectangleShape> platforms;
};

