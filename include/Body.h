#pragma once
#include "Box2D.h"

class Body {
    public:
        b2Body* getBody();
        b2Shape* getShape();
        void setBody(b2Body*);
        

        float getX();
        float getY();
        float getStartX();
        float getStartY();
        float getWidth();
        float getHeight();
        float getDensity();
        float getFriction();


    protected:
        float width;
        float height;
        float density;
        float friction;
        float startX;
        float startY;

        b2PolygonShape shape;

    private:
        b2Body* body;


};
