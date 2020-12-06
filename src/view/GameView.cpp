#include "GameView.h"
#include "Platform.h"

GameView::GameView():
    window(sf::VideoMode(windowWidth, windowHeight), "Platformer",
           sf::Style::Close | sf::Style::Fullscreen, settings) 
{
    window.setFramerateLimit(60);
    bgFill.setSize(sf::Vector2f(windowWidth, windowHeight));
    bgFill.setFillColor(sf::Color(28, 28, 28));

}

void GameView::initPlayer() {
    playerShape = sf::RectangleShape(getSize(model->getPlayer()));
    playerShape.setFillColor(sf::Color::Red);
    playerShape.setOrigin(getOrigin(model->getPlayer()));
    drawables.push_back(&playerShape);
}

GameView::~GameView() {}

void GameView::update() {
    updatePlayerPos();
    draw();
}

void GameView::draw() {
    window.draw(bgFill);

    for (auto element : drawables) {
        window.draw(*element);
    }
    drawPlatforms();
    window.display();
}

bool GameView::poll(sf::Event event) {
    return window.pollEvent(event);
}

sf::RenderWindow* GameView::getWindow() {
    return &window;
}

void GameView::setModel(ModelInterface* model) {
    this->model = model;
}

void GameView::updatePlayerPos() {
    playerShape.setPosition(getPos(model->getPlayer()));

    float angle = model->getPlayer()->getBody()->GetAngle() * 180 / M_PI;
    playerShape.setRotation(angle);

}


void GameView::drawPlatforms() {
    for (auto platform : platforms) {
        window.draw(platform);
    }
}


void GameView::updatePlatforms() {
    platforms = {};
    
    for (int i = 0; i < model->getPlatforms()->size(); i++) {
        Body plat = model->getPlatforms()->at(i);
        platforms.push_back(sf::RectangleShape(getSize(&plat)));
        platforms.at(i).setFillColor(sf::Color::Blue);
        platforms.at(i).setPosition(getPos(&plat));
        platforms.at(i).setOrigin(getOrigin(&plat));

    }
}

sf::Vector2f GameView::getSize(Body* body) {
    int scalar = worldScale * 2;
    float width = body->getWidth();
    float height = body->getHeight();
    
    width *= scalar;
    height *= scalar;

    return sf::Vector2f(width, height);
}

sf::Vector2f GameView::getOrigin(Body* body) {
    int scalar = worldScale;
    float width = body->getWidth();
    float height = body->getHeight();

    width *= scalar;
    height *= scalar;

    return sf::Vector2f(width, height);
}

sf::Vector2f GameView::getPos(Body* body) {
    int scalar = worldScale;
    float x = body->getX();
    float y = body->getY();
    
    x *= scalar;
    y *= scalar;

    x += windowWidth / 2;
    y += windowHeight / 2;

    return sf::Vector2f(x, y);
}








