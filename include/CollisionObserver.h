#include "Body.h"
#pragma once

class CollisionObserver {
    public:
        CollisionObserver();
        ~CollisionObserver();
        virtual void notifyCollide(Body* b1, Body* b2);
        virtual void notifyUncollide(Body* b1, Body* b2);

};

                                                                            

