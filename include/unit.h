#ifndef UNIT_H
#define UNIT_H
struct Vec2 {
  int e1;
  int e2;
  Vec2(int e1, int e2) : e1(e1), e2(e2) {}
  int &x() { return e1; }
  int &y() { return e2; }
  int &width() { return e1; }
  int &height() { return e2; }
};

using Position = Vec2;
using Size = Vec2;

enum Color { BLACK = 0, RED, GREEN, YELLOW, BLUE, PINK, CYAN, WHITE, NOCHANGE };

enum Direction { RIGHT = -2, DOWN = -1, NONE = 0, UP = 1, LEFT = 2 };

#endif
