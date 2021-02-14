#include "Player.h"
#include "Box2D.h"
#include "CollisionObserver.h"
#include <iostream>
#include <vector>


class PlayerContactListener : public b2ContactListener {

    public:

    static void addObserver(CollisionObserver* observer) {
        observers.push_back(observer);
    }


    private:

    static inline std::vector<CollisionObserver*> observers;

    static void notifyObserversColl(Body* b1, Body* b2) {
        for (auto obs : observers)
            obs->notifyCollide(b1, b2);
    }

    static void notifyObserversUnColl(Body* b1, Body* b2) {
        for (auto obs : observers)
            obs->notifyUncollide(b1, b2);
    }

    void BeginContact(b2Contact* contact) {
        void* bodyDataA = contact->GetFixtureA()->GetBody()->GetUserData();
        void* bodyDataB = contact->GetFixtureB()->GetBody()->GetUserData();
        if (bodyDataA && bodyDataB) {
            Body* b1 = static_cast<Body*>(bodyDataA);
            Body* b2 = static_cast<Body*>(bodyDataB);
            b1->collideStart();
            b2->collideStart();
            PlayerContactListener::notifyObserversColl(b1, b2);
        }
    }

    void EndContact(b2Contact* contact) {
        void* bodyDataA = contact->GetFixtureA()->GetBody()->GetUserData();
        void* bodyDataB = contact->GetFixtureB()->GetBody()->GetUserData();
        if (bodyDataA && bodyDataB) {
            Body* b1 = static_cast<Body*>(bodyDataA);
            Body* b2 = static_cast<Body*>(bodyDataB);
            b1->collideEnd();
            b2->collideEnd();
            PlayerContactListener::notifyObserversUnColl(b1, b2);
        }
    }
};
