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
        handleInput();
        playerHandler.update(dt);
        world.Step(dt, velocityiIt, posIt);
        updateCooldowns();
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

    playerHandler.setCds(&coolDowns);

    view.setModel(&model);
    view.setCds(&coolDowns);

    view.initPlayer();
    view.updatePlatforms();

    world.SetContactListener(&clistener);

}
                                                                            
void GameController::handleInput() {
    // can be used to call seperate methods instead
    while (view.poll(event)) {

        if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Q)
            running = false; // just closing

        if (event.key.code  == sf::Keyboard::P) {
            enterMenu();
        }

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

//TODO move to menucontroller
void GameController::enterMenu() {
    MenuView* menu = view.initMenu();
    inMenu = true;
    while (inMenu) {
        while (view.poll(event)) {
            playerHandler.handleKeyRelease(event);
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        inMenu = false;
                        break;

                    case sf::Keyboard::W:
                        menu->cycle(-1);
                        break;
                    
                    case sf::Keyboard::S:
                        menu->cycle(1);
                        break;

                    case sf::Keyboard::Enter:
                        pressMenuButton(menu);
                        break;

                }
            }
        }
        dt = clock.restart().asMilliseconds() / 1000.0f;
        updateView();
        menu->draw();
        view.display();
    }      
}


void GameController::pressMenuButton(MenuView* menu) {
    // 0 : quit
    // 1 : nothing
    // 2 : nothing
    
    switch(menu->press()) { 
        case 0:
            running = false;
            inMenu = false;
            break;
    }

}

void GameController::updateCooldowns() {
    std::vector<std::tuple<std::string, float*, bool*>> keep;
    for (auto cd : coolDowns) {
        if (*std::get<2>(cd)) {
            keep.push_back(cd);
        }
    }
    coolDowns = keep;
}








