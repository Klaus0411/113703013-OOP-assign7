#include "UndyneGameObject.h"
#include "gameObject.h"
#include "collider.h"

// UndyneAttack implementation
UndyneAttack::UndyneAttack(Icon icon, Position position, Direction direction, int speed)
: GameObject(icon, position), _speed(speed){
    _dir = direction;
    OBJECT_WIDTH = icon[0].size();
    OBJECT_HEIGHT = icon.size();
}

UndyneAttack::~UndyneAttack() {//will be called if erased from the vector
    ICollider::~ICollider();
    GameObject::~GameObject();
}

void UndyneAttack::update(){
    // default speed is 1 & direction won't chane after spawned
    for (int i = 0; i < _speed; i++) GameObject::update();
}




// UndynePlayer implementation
UndynePlayer::UndynePlayer(Icon icon, Position position, Direction direction, int health)
: GameObject(icon, position), _health(health) {
    _dir = direction;
    OBJECT_WIDTH = icon[0].size();
    OBJECT_HEIGHT = icon.size();
}

void UndynePlayer::update() {
    //shield icon initialization(clearing)
    for(int i = 0; i < _icon[0].size(); i++) _icon[0][i].color = _icon[6][i].color = Color::NOCHANGE;
    for(int i = 0; i < _icon.size(); i++) _icon[i][0].color = _icon[i][6].color = Color::NOCHANGE; 

    //shield icon update
    switch (_dir) {
        case UP:
            for(int i = 0; i < _icon[0].size(); i++) _icon[0][i].color = Color::WHITE; // Clear the top row
            break;
        case LEFT:
            for(int i = 0; i < _icon.size(); i++) _icon[i][0].color = Color::WHITE;
            break;
        case DOWN:
            for(int i = 0; i < _icon[0].size(); i++) _icon[6][i].color = Color::WHITE;
            break;
        case RIGHT:
            for(int i = 0; i < _icon.size(); i++) _icon[i][6].color = Color::WHITE;
            break;
        default:
            break; // No movement        
    }
    if(_health < 5){
        for(int i = 5; i > _health; i--) _icon[5][i].color = Color::BLACK; // Clear the health bar  
    }
}

bool UndynePlayer::intersect(GameObject *other) {
    return (getPosition().x() < other->getPosition().x() + other->getIcon()[0].size() &&
            getPosition().x() + OBJECT_WIDTH > other->getPosition().x() &&
            getPosition().y() < other->getPosition().y() + other->getIcon().size() &&
            getPosition().y() + OBJECT_HEIGHT > other->getPosition().y());
    //also erase the attack in controller.cpp's loop
}

void UndynePlayer::onCollision(GameObject *other) {
    if (intersect(other) && _dir + other->getDirection() != NONE) {
        _health -= 1; // Decrease health of the player
    }
}