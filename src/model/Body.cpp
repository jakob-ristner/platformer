#include "Body.h"

b2Body* Body::getBody() {
    return body;
}

void Body::setBody(b2Body* body) {
    this->body = body;
}

b2Shape* Body::getShape() {
    return &shape;
}

float Body::getStartX() {
    return startX;
}

float Body::getStartY() {
    return startY;
}


float Body::getX() {
    return body->GetPosition().x;
}

float Body::getY() {
    return body->GetPosition().y;
}

float Body::getWidth() {
    return width;
}

float Body::getHeight() {
    return height;
}

float Body::getDensity() {
    return density;
}

float Body::getFriction() {
    return friction;
}
