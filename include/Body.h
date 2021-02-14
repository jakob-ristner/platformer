#pragma once
#include "Box2D.h"
#include "GameObject.h"

class Body {
    public:
        b2Body* getBody();
        b2Shape* getShape();
        void setBody(b2Body*);

        void setCollision(bool coll);

        virtual void collideStart() {};
        virtual void collideEnd() {};

        float getX();
        float getY();
        float getStartX();
        float getStartY();
        float getWidth();
        float getHeight();
        float getDensity();
        float getFriction();

        std::string getType();



    protected:
        float width;
        float height;
        float density;
        float friction;
        float startX;
        float startY;

        std::string type;

        b2PolygonShape shape;

    private:
        b2Body* body;


};
