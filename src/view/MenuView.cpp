#include "MenuView.h"

MenuView::MenuView(sf::RenderWindow* window, sf::Vector2f windowSize) {
    this->window = window;

    font = sf::Font();
    font.loadFromFile("./font.ttf");

    selectedColor = sf::Color(255, 255, 255);
    normal = sf::Color(50, 50, 50);

    button1 = sf::Text("Quit", font, normalFontSize);
    button2 = sf::Text("Something", font, normalFontSize);
    button3 = sf::Text("Settings", font, normalFontSize);

    buttons.push_back(button1);
    buttons.push_back(button2);
    buttons.push_back(button3);

    background.setFillColor(sf::Color(0, 0, 0, 100));;
    background.setPosition(sf::Vector2f(0, 0));
    background.setSize(windowSize);

    windowWidth = windowSize.x;
    windowHeight = windowSize.y;

    std::cout << "created menuviwe" <<  std::endl;

    int tWidth;
    for (int i = 0; i < buttons.size(); i++) {
        tWidth = buttons.at(i).getLocalBounds().width / 2;
        buttons.at(i).setPosition(sf::Vector2f(windowSize.x / 2 - tWidth, 300 + 100 * i));
        buttons.at(i).setFillColor(sf::Color::White);
    }

    cycle(0);

}

MenuView::MenuView() {

}

MenuView::~MenuView() {

}

void MenuView::init() {
    window->draw(background);
    window->display();
}

void MenuView::draw() {
    window->draw(background);
    resetPosition();
    for (auto bu : buttons) {
        bu.setFont(font);
        window->draw(bu);
    }
}

void MenuView::cycle(int step) {
    selected = (selected + step) % buttons.size();
    for (int i = 0; i < buttons.size(); i++) {  
        deselect(&buttons.at(i));
    }
    std::cout << buttons.size() << std::endl;
    select(&buttons.at(selected));
}

void MenuView::select(sf::Text* text) {
    text->setCharacterSize(selectedFontSize);
    text->setFillColor(selectedColor);
}

void MenuView::deselect(sf::Text* text) {
    text->setCharacterSize(normalFontSize);
    text->setFillColor(normal);
}

void MenuView::resetPosition() {
    int width;
    int height;
    for (int i = 0; i < buttons.size(); i++) {
        buttons.at(i).setFont(font);
        width = buttons.at(i).getGlobalBounds().width;
        height = buttons.at(i).getLocalBounds().height;
        
        buttons.at(i).setPosition(
                sf::Vector2f(windowWidth / 2 - width / 2,
                topButtonY + (i * spacing) - height));
    }
}

