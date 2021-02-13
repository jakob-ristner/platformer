#include "Player.h"
#include "Box2D.h"
#include <iostream>

class PlayerContactListener : public b2ContactListener {
       void BeginContact(b2Contact* contact) {
           //check if fixture A was player
           void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();

           if (bodyUserData && static_cast<GameObject*>(bodyUserData)->type == "player")
                   static_cast<Player*>(bodyUserData)->setContact(true);
                 
           //k if fixture B was player
           bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
           if (bodyUserData && static_cast<GameObject*>(bodyUserData)->type == "player")
                   static_cast<Player*>(bodyUserData)->setContact(true);
       }

       void EndContact(b2Contact* contact) {
              //check if fixture A was player
              void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
           if (bodyUserData && static_cast<GameObject*>(bodyUserData)->type == "player")
                   static_cast<Player*>(bodyUserData)->setContact(false);
                 
              //k if fixture B was player
              bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
           if (bodyUserData && static_cast<GameObject*>(bodyUserData)->type == "player")
                   static_cast<Player*>(bodyUserData)->setContact(false);
       }
};