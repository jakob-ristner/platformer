#include "GameController.h"
#include <iostream>
#include "PlayerInputHandler.h"

GameController::GameController() {
}

GameController::~GameController() {}

void GameController::updateModel(float dt) {
}

void GameController::updateView() {
    view.update();
}

void GameController::run() {
    running = true;
    init();
    while (running) {
        dt = clock.restart().asMilliseconds() / 1000.0f;
        playerHandler.update(dt);
        handleInput();;
        world.Step(dt, velocityiIt, posIt);
        updateView();
        view.display();
    }
}

void GameController::init() {
    model = ModelInterface();
    player = model.getPlayer();
    playerHandler = PlayerInputHandler(model.getPlayer());
    PlayerContactListener::addObserver(&playerHandler);
    initDynBody(player);
    player->getBody()->SetFixedRotation(true);

    player->getBody()->SetUserData(player);


    for (int i = 0; i < model.getPlatforms()->size(); i++) {
        initStatBody(&(model.getPlatforms()->at(i)));   
        model.getPlatforms()->at(i).getBody()->SetUserData(&model.getPlatforms()->at(i));
    }

    view.setModel(&model);
    view.initPlayer();
    view.updatePlatforms();

    world.SetContactListener(&clistener);

}

void GameController::handleInput() {
    // can be used to call seperate methods instead
    while (view.poll(event)) {

        if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Q)
            running = false; // just closing

        if (event.key.code  == sf::Keyboard::P)
            enterMenu();

        playerHandler.handleEvent(event); // player input
    }
}

void GameController::initDynBody(Body* body) {
    b2BodyDef bodyDef;
    bodyDef.position.Set(body->getStartX(), body->getStartY());
    bodyDef.type = b2_dynamicBody;
    b2Body* b2body = world.CreateBody(&bodyDef);

    b2FixtureDef fixDef;

    fixDef.shape = body->getShape();
    fixDef.density = body->getDensity();
    fixDef.friction = body->getFriction();

    body->setBody(b2body);
    body->getBody()->CreateFixture(&fixDef);
}

void GameController::initStatBody(Body* body) {
    b2BodyDef bodyDef;
    bodyDef.position.Set(body->getStartX(), body->getStartY());
    bodyDef.type = b2_staticBody;
    b2Body* b2body = world.CreateBody(&bodyDef);

    b2FixtureDef fixDef;

    fixDef.shape = body->getShape();
    fixDef.friction = body->getFriction();

    body->setBody(b2body);
    body->getBody()->CreateFixture(&fixDef);
}

void GameController::enterMenu() {
    MenuView* menu = view.initMenu();
    bool inMenu = true;
    while (inMenu) {
        while (view.poll(event)) {
            if (event.key.code == sf::Keyboard::Escape) {
                inMenu = false; // just closing
                break;
            } else if (event.key.code == sf::Keyboard::W) {
                menu->cycle(-1);
            } else if (event.key.code == sf::Keyboard::S) {
                menu->cycle(1);
            }
        }
        updateView();
        menu->draw();
        view.display();
    }      
}

//TODO move to playerctl









