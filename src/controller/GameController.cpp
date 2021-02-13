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

        playerHandler.updateTime(dt);

        handlePlayerFric();
        handleInput();;

        world.Step(dt, velocityiIt, posIt);
    
        updateView();
    }
}

void GameController::init() {
    view.getWindow()->setKeyRepeatEnabled(false);
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
    while (view.getWindow()->pollEvent(event)) {

        if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Q)
            running = false; // just closing

        playerHandler.handleEvent(event); // player input
    }
}

void GameController::handlePlayerFric() {
    b2Body* playerbod = model.getPlayer()->getBody();
    
    for (Body platform : *model.getPlatforms()) {
        for (b2ContactEdge* edge = playerbod->GetContactList(); edge; edge = edge->next) {
            if (edge->other == platform.getBody() && edge->contact->IsTouching()) {
                if (playerbod->GetLinearVelocity().x < 0) {
                    playerbod->ApplyLinearImpulseToCenter(b2Vec2(playerGroundForce, 0), true);
                } else if (playerbod->GetLinearVelocity().x > 0) {
                    playerbod->ApplyLinearImpulseToCenter(b2Vec2(-playerGroundForce, 0), true);
                }
            }
            if (edge->other->GetLinearVelocity().y == playerbod->GetLinearVelocity().y) {
                model.getPlayer()->onGround = true;
            } else {
                model.getPlayer()->onGround = false;
            }
        }
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









