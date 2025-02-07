#include "entity.h"

void Entity::print(){
    std::cout << _x << "," << _y << std::endl;
    std::cout << "Entity" << std::endl;
}

void Player::print(){
    std::cout << _name << std::endl;
    std::cout << "Player" << std::endl;
}

void printEntity(Entity* e){ 
    e->print();
}

void printClassName(Printable* p){
    p->getClassName();
}