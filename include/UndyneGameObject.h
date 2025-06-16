#ifndef UNDYNE_H
#define UNDYNE_H

#include "collider.h"
#include "gameObject.h"
#include "unit.h"


class UndyneAttack : public GameObject, public ICollider {
public:
friend class UndynePlayer; // Allow UndynePlayer to access private members
    UndyneAttack(Icon icon, Position position, Direction direction, int speed);
    ~UndyneAttack() override;
    void update();
private:
    // For Attack: movement direction; 
    int _speed; // Speed of Attacks, default is 1
};

class UndynePlayer : public GameObject, public ICollider {
public:
    UndynePlayer(Icon icon, Position position, Direction direction, int health);
    void update() override;
    void onCollision(GameObject *other);
    bool intersect(GameObject *other);
    int getHealth() const { return _health; } // Getter for health

private:
    // For Player: direction is the way the player faces
    int _health; // Health of Player
};
#endif