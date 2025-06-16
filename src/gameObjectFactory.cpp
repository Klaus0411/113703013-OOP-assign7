#include "gameObjectFactory.h"
#include "environment.h"
#include "iconFactory.h"
#include <chrono>
#include <random>
#include <set>
std::random_device rd;
std::mt19937 engine(rd());
std::uniform_int_distribution<int> distX(0, GAME_WINDOW_WIDTH - 4);
std::uniform_int_distribution<int> distY(0, GAME_WINDOW_HEIGHT - 1);

GameObject *SimpleGameObjectFactory::playerGameObject() {

  int x = distX(engine);
  int y = distY(engine);
  return new GameObject(IconFactory::NxMColor(Size(1, 1), RED), Position{x, y});
}
GameObject *SimpleGameObjectFactory::randomGameObject() {
  int x = distX(engine);
  int y = distY(engine);
  return new GameObject(IconFactory::NxMColor(Size(2, 2), BLUE),
                        Position{x, y});
}

UndyneAttack* UndyneGameObjectFactory::newUndyneAttack(Direction direction, int speed) {
  Icon icon;
  int x, y;

  // Set icon and others based on direction
  if(direction == RIGHT || direction == LEFT){
    icon = IconFactory::NxMColor(Size(4, 3), NOCHANGE); // Horizontal attack
    for(int i = 0; i < 4; i++) icon[1][i] = Cell(BLUE, " "); // Set middle row to green
    // Set starting position based on direction
    if(direction == RIGHT){
      x = 0; // Start from the middle of left edge
      y = GAME_WINDOW_HEIGHT / 2 - 1; // Center vertically
      icon[0][2] = icon[2][2] = Cell(BLUE, " "); // Right edge
    }else{ 
      x = GAME_WINDOW_WIDTH - 4; // Start from the middle of right edge
      y = GAME_WINDOW_HEIGHT / 2 - 1; // Center vertically
      icon[0][1] = icon[2][1] = Cell(BLUE, " "); // Left edge
    }
  }else if(direction == UP || direction == DOWN){
    icon = IconFactory::NxMColor(Size(3, 4), NOCHANGE); // Vertical attack
    for(int i = 0; i < 4; i++) icon[i][1] = Cell(GREEN, " "); // Set middle column to blue
    // Set starting position based on direction
    if(direction == UP){
      x = GAME_WINDOW_WIDTH / 2 - 1; // Center horizontally
      y = GAME_WINDOW_HEIGHT - 4; // Start from the bottom edge
      icon[1][0] = icon[1][2] = Cell(GREEN, " "); // Bottom edge
    }else{
      y = 0; // Start from the top edge
      x = GAME_WINDOW_WIDTH / 2 - 1; // Center horizontally
      icon[2][0] = icon[2][2] = Cell(GREEN, " "); // Top edge
    }
  }

  // Set the position based on the calculated x and y
  Position position{x, y};
  //change width, height and position based on direction
  return new UndyneAttack(icon, position, direction, speed);
}

UndynePlayer* UndyneGameObjectFactory::newUndynePlayer() {
  int health = 5; // Default health for the player

  //player icon initialization(as a heart)
  Icon icon = IconFactory::NxMColor(Size(7, 7), NOCHANGE);
  icon[1][2] = icon[1][4] = Cell(RED, " ");
  for(int i = 1; i < 6; i++) icon[2][i] = Cell(RED, " ");
  //center is a heart character as special one
  icon[3][3] = Cell(RED, "♥");
  icon[3][2] = icon[3][4] = Cell(RED, " ");
  icon[4][3] = Cell(RED, " ");
  //HP bar
  for(int i = 1; i < 6; i++) icon[5][i] = Cell(GREEN, " ");

  //shield will be represented in WHITE when game updated

  //position is at the center of the game window
  Position position = {GAME_WINDOW_WIDTH / 2 - 3, GAME_WINDOW_HEIGHT / 2 - 3};
  //direction is set to NONE initially
  Direction direction = NONE;
  return new UndynePlayer(icon, position, direction, health);
}