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
    }
}

void GameController::init() {
    model = ModelInterface();
    player = model.getPlayer();
    playerHandler = PlayerInputHandler(model.getPlayer());
    initDynBody(player);
    player->getBody()->SetFixedRotation(true);

    player->getBody()->SetUserData(player);


    for (int i = 0; i < model.getPlatforms()->size(); i++) {
        initStatBody(&(model.getPlatforms()->at(i)));   
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

//TODO move to playerctl









