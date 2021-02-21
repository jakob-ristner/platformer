#include "CoolDownView.h"

CoolDownView::CoolDownView(sf::RenderWindow* window) {
    this->window = window;
    wWidth = window->getSize().x;
    wHeight = window->getSize().y;
    font = sf::Font();
    font.loadFromFile(fontPath);
}

CoolDownView::CoolDownView() {} 
CoolDownView::~CoolDownView() {}

void CoolDownView::draw() {
    sf::Text text = sf::Text("", font, fontSize);
    std::string cText;
    float cTime;

    for (auto cd : *coolDowns) {
        cText = std::get<0>(cd);
        cTime = *std::get<1>(cd);
        //std::cout << cText << " : " << cTime << std::endl; 
    }

    for (int i = 0; i  < coolDowns->size(); i++) {
        std::tuple<std::string, float*, bool*> cd = (*coolDowns).at(i);
        cTime = *std::get<1>(cd);
        cText = std::get<0>(cd).append(" : ").append(std::to_string(cTime));
        text.setString(cText);
        text.setPosition(sf::Vector2f(xPadding, yPadding + i * spacing));

        window->draw(text);
    }

    

}

void CoolDownView::set(std::vector<std::tuple<std::string, float*, bool*>>* coolDowns) {
    this->coolDowns = coolDowns;
}

    
