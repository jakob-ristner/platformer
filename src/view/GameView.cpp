#include "GameView.h"
#include "Platform.h"

GameView::GameView():
    window(sf::VideoMode(windowWidth, windowHeight), "Platformer",
           sf::Style::Close | sf::Style::Fullscreen, settings) 
{
    window.setFramerateLimit(60);
    bgFill.setSize(sf::Vector2f(windowWidth, windowHeight));
    bgFill.setFillColor(sf::Color(29, 32, 38));

}

void GameView::initPlayer() {
    window.setKeyRepeatEnabled(false);
    playerShape = sf::RectangleShape(getSize(model->getPlayer()));
    playerShape.setFillColor(sf::Color(224, 108, 117));
    playerShape.setOrigin(getOrigin(model->getPlayer()));
    drawables.push_back(&playerShape);

    initChargeBar();
}

GameView::~GameView() {}

void GameView::update() {
    updatePlayerPos();
    updateChargeBar();
    draw();
}

void GameView::draw() {
    window.draw(bgFill);

    for (auto element : drawables) {
        window.draw(*element);
    }

    //testing contact listener
    if (model->getPlayer()->getContact()) {
        playerShape.setFillColor(sf::Color(97, 175, 239));
    } else {
        playerShape.setFillColor(sf::Color(224, 108, 117));
    }

    drawPlatforms();
    window.display();
}

bool GameView::poll(sf::Event &event) {
    return window.pollEvent(event);
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
        platforms.at(i).setFillColor(sf::Color(229, 192, 123));
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

void GameView::initChargeBar() {
    chargeBarBorder.setSize(sf::Vector2f(chargeBarWidth + chargeBw, chargeBarHeight + chargeBw));
    chargeBarBorder.setPosition(
            sf::Vector2f((int) (windowWidth - chargeBarWidth - chargeBw) / 2, chargeBarY - chargeBw / 2));
    chargeBarBorder.setFillColor(sf::Color::White);

    chargeBarBackground.setSize(sf::Vector2f(chargeBarWidth, chargeBarHeight));
    chargeBarBackground.setPosition(sf::Vector2f((int) (windowWidth - chargeBarWidth) / 2, chargeBarY));
    chargeBarBackground.setFillColor(sf::Color(29, 32, 38));

    chargeBarFill.setSize(sf::Vector2f(0, chargeBarHeight));
    chargeBarFill.setPosition(sf::Vector2f((int) (windowWidth - chargeBarWidth) / 2, chargeBarY));
    chargeBarFill.setFillColor(sf::Color(8, 195, 121));

    drawables.push_back(&chargeBarBorder);
    drawables.push_back(&chargeBarBackground);
    drawables.push_back(&chargeBarFill);
}

void GameView::updateChargeBar() {

    if (model->getPlayer()->getCharge() == 0) {
       chargeBarBorder.setSize(sf::Vector2f());
       chargeBarBackground.setSize(sf::Vector2f());
       chargeBarFill.setSize(sf::Vector2f());
    } else {
        initChargeBar();
    }

    int playerCharge = model->getPlayer()->getCharge() * chargeBarWidth;
    int cw = chargeBarWidth;
    int fillWidth = std::min(playerCharge, cw);
    chargeBarFill.setSize(sf::Vector2f(fillWidth, chargeBarHeight));
}









