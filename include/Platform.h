#pragma once
#include "Body.h"



class Platform: public Body {
    public:
        Platform(float w, float h, float x, float y);
        Platform();
        ~Platform();
        
};
