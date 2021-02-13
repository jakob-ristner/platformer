#include <iostream>

class GameObject {
    public:
        GameObject(std::string type);
        GameObject();
        ~GameObject();
        std::string type;
};
