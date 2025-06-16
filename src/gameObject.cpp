#include "gameObject.h"
#include "environment.h"


GameObject::GameObject(Icon icon, Position pos) : _icon(icon), _pos(pos) {
  _dir = NONE;
}
GameObject::~GameObject() {}

void GameObject::update() {
  if (_dir == UP && _pos.y() != 0) {
    _pos.y()--;
  } else if (_dir == LEFT && _pos.x() != 0) {

    _pos.x()--;
  } else if (_dir == DOWN && _pos.y() < GAME_WINDOW_HEIGHT - 1) {

    _pos.y()++;
  } else if (_dir == RIGHT && _pos.x() < GAME_WINDOW_WIDTH - 1) {

    _pos.x()++;
  }

}

void GameObject::setDirection(Direction dir) { _dir = dir; }
Direction GameObject::getDirection() const { return _dir; }


