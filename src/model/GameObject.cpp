#include "GameObject.h"


GameObject::GameObject(std::string type) {this->type = type;}
GameObject::GameObject() {type = "";}
GameObject::~GameObject(){}

bool GameObject::checkType(std::string otype) {
    if (type == otype)
        return true;
    return false;
}
