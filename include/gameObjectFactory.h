#include "gameObject.h"
#include "UndyneGameObject.h"

struct SimpleGameObjectFactory {  
    static GameObject* playerGameObject();
    static GameObject* randomGameObject();
};


struct UndyneGameObjectFactory {
    static UndyneAttack* newUndyneAttack(Direction direction, int speed);
    static UndynePlayer* newUndynePlayer();
};