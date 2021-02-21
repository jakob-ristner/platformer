#pragma once
#include <iostream>
#include <tuple>
#include <vector>
#include "SFML/Graphics.hpp"


class CoolDownView {
    public:
        CoolDownView(sf::RenderWindow* window);
        CoolDownView();
        ~CoolDownView();

        void draw();
        void set(std::vector<std::tuple<std::string, float*, bool*>>* coolDowns);

    private:    
        int wHeight;
        int wWidth;
        sf::Font font;
        int fontSize = 20;
        int spacing = 10;
        int xPadding = 10;
        int yPadding = 10;
        std::string fontPath = "resources/fonts/pixel.ttf";
        sf::RenderWindow* window;
        std::vector<std::tuple<std::string, float*, bool*>>* coolDowns;

};
