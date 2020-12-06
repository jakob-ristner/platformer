#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "ModelInterface.h"


class GameView {
    public:
        GameView();
        ~GameView();

        void update();
        void setModel(ModelInterface* model);

        void updatePlatforms();
        void initPlayer();

        bool poll(sf::Event event);
        sf::RenderWindow* getWindow();
    private:
        static const int windowWidth = 2560;
        static const int windowHeight = 1440;
        static const int worldScale = 20;

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

        void draw(); 

        std::vector<sf::Drawable*> drawables;
        
        //TODO move below to playerview
        void drawPlayer();
        void updatePlayerPos();
        sf::RectangleShape playerShape;

        //TODO same here
        void drawPlatforms();
        std::vector<sf::RectangleShape> platforms;
};
