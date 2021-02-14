#include "Player.h"
#include "Box2D.h"
#include <iostream>

class PlayerContactListener : public b2ContactListener {
       void BeginContact(b2Contact* contact) {

           void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
           if (bodyUserData && static_cast<GameObject*>(bodyUserData)->type == "player")
               static_cast<Player*>(bodyUserData)->collide();
                 
           bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
           if (bodyUserData && static_cast<GameObject*>(bodyUserData)->type == "player")
               static_cast<Player*>(bodyUserData)->collide();
       }

       void EndContact(b2Contact* contact) {
           void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
           if (bodyUserData && static_cast<GameObject*>(bodyUserData)->type == "player")
               static_cast<Player*>(bodyUserData)->unCollide();
                 
           bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
           if (bodyUserData && static_cast<GameObject*>(bodyUserData)->type == "player")
               static_cast<Player*>(bodyUserData)->unCollide();
       }
};
