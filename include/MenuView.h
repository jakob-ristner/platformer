#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>

class MenuView {
    public:
        MenuView(sf::RenderWindow* window, sf::Vector2f windowSize);
        MenuView();
        ~MenuView();
        void init();
        void draw();
        int press();

        void cycle(int step);

    private:
        sf::Text button1;
        sf::Text button2;
        sf::Text button3;
        sf::RectangleShape background;
        sf::Font font;
        std::string fontPath = "resources/fonts/pixel.ttf";

        sf::Color selectedColor;
        sf::Color normal;

        sf::Text test;

        std::vector<sf::Text> buttons;

        int normalFontSize = 20;
        int selectedFontSize = 100;
        int selected = 0;
        
        int topButtonY = 400;
        int spacing = 100;

        int windowWidth;
        int windowHeight;


        sf::RenderWindow* window;

        void deselect(sf::Text* text);
        void select(sf::Text* text);
        void resetPosition();

};
