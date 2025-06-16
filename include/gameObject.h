#ifndef ELEMENT_H
#define ELEMENT_H

#include "icon.h"
#include "unit.h"
#include <iostream>
#include <vector>
class GameObject {

public:
  GameObject(Icon icon, Position pos = {0, 0});

  virtual ~GameObject();
  virtual void update();
  Icon getIcon() const;
  void setDirection(Direction);
  Vec2 getPosition() const;
  Direction getDirection() const;

protected:
  Direction _dir;
  Vec2 _pos;
  Icon _icon;

  int OBJECT_WIDTH;  
  int OBJECT_HEIGHT; 
};

inline Icon GameObject::getIcon() const { return _icon; }

inline Vec2 GameObject::getPosition() const { return _pos; }
#endif
