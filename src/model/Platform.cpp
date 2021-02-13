#include "Platform.h"

Platform::Platform(float width, float height, float x, float y) {
    this->width = width;
    this->height = height;

    startX = x;
    startY = y;
    type = "platform";

    friction = 0;
    shape.SetAsBox(width, height);
}

Platform::Platform() {}

Platform::~Platform() {}
