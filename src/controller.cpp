#include <iostream>
#include <ctime>
#include <thread>
#include <unistd.h>
#include <termios.h>
#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>
#include "environment.h"
#include "controller.h"
#include "gameObjectFactory.h"
#include "UndyneGameObject.h"


Controller::Controller(View& view) : _view(view){
    Player = UndyneGameObjectFactory::newUndynePlayer();
    _objs.push_back(Player);
    _objs.push_back(UndyneGameObjectFactory::newUndyneAttack(RIGHT, 1));
    //_objs.push_back(UndyneGameObjectFactory::newUndyneAttack(LEFT, 1));
}

void Controller::run() {
    // initial setup
    std::cin.tie(0);
    std::ios::sync_with_stdio(0);
    configure_terminal();
    auto startTime = std::chrono::steady_clock::now();
    std::chrono::seconds countdown(30); //30 sec per game by default
    std::random_device rd;
    std::mt19937 gen(rd());//for spawning attacks
    std::uniform_int_distribution<> spawnCD(1, 3); // Randomly spawn attacks every 1 to 3 seconds
    std::uniform_int_distribution<> spawnDir(0, 3); // Randomly choose direction for attacks
    auto nextSpawnTime = startTime + std::chrono::seconds(spawnCD(gen)); // Next spawn time

    // init state
    int input = -1;
    clock_t start, end;
    
    // Main loop
    while (true) {
        // Time management
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime);
         std:: cout << "\rTime left: " << std::setw(2) << std::right << countdown.count() - elapsed.count() << " s" << std::flush;
        if (elapsed >= countdown) {
            std::cout << std::endl << "Time's up! You Win!" << std::endl;
            break; // Exit the game loop after 30 seconds
        }
       
        // Randomly spawn attacks
        if(currentTime >= nextSpawnTime) {
            Direction dir; // Randomly choose direction
            switch (spawnDir(gen)) {
                case 0: dir = UP; break;
                case 1: dir = DOWN; break;
                case 2: dir = LEFT; break;
                case 3: dir = RIGHT; break;
                default: dir = NONE; break; // Fallback
            }
            _objs.push_back(UndyneGameObjectFactory::newUndyneAttack(dir, 1));
            nextSpawnTime = currentTime + std::chrono::seconds(spawnCD(gen)); // Set next spawn time
        }

        start = clock();
        // game loop goes here
        input = read_input();

        // ESC to exit program
        if(input==27)break;
        this->handleInput(input);

        _view.resetLatest();
        
        for (size_t i = 0; i < _objs.size(); ++i) {
            _objs[i]->update();
            _view.updateGameObject(_objs[i]);

            // Check for collisions that only check between Player and Attacks
            if (Player->intersect(_objs[i]) && i != 0) {// skip Player itself
                Player->onCollision(_objs[i]);
                _objs.erase(_objs.begin() + i); // Remove the attack from the game(destructor is also called)
                // If Player health is 0, end the game
                //std:: cout << "Collision detected! Player health: " << Player->getHealth() << std::endl;
                if (Player->getHealth() <= 0) {
                    std::cout << std::endl << "Game Over! You have been defeated!" << std::endl;
                    return; // Exit the game loop
                }
            }

            
        }
        //Game end condition
        _view.render();
        end = clock();
        // frame rate normalization
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        if (time_taken > SPF) continue;
        int frameDelay = int((SPF - time_taken) * 100); // 0.01 seconds
        if(frameDelay > 0) std::this_thread::sleep_for(std::chrono::milliseconds(frameDelay)); // frame delay
    }
}



void Controller::handleInput(int keyInput){
    if(keyInput==-1)return;
    
    if(keyInput == 'w' || keyInput == 'W'){
        Player->setDirection(UP);
    }

    if(keyInput == 'a' || keyInput == 'A'){

        Player->setDirection(LEFT);
    }

    if(keyInput == 's' || keyInput == 'S'){

        Player->setDirection(DOWN);
    }

    if(keyInput == 'd' || keyInput == 'D'){

        Player->setDirection(RIGHT);
    }

    if(keyInput == '\t'){
    }
}

void Controller::update(){

}

void reset_terminal() {
    printf("\e[m"); // reset color changes
    printf("\e[?25h"); // show cursor
    fflush(stdout);
    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
}

// terminal initial configuration setup
void configure_terminal() {
    tcgetattr(STDIN_FILENO, &old_termios);
	new_termios = old_termios; // save it to be able to reset on exit
    
    new_termios.c_lflag &= ~(ICANON | ECHO); // turn off echo + non-canonical mode
    new_termios.c_cc[VMIN] = 0;
    new_termios.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

    printf("\e[?25l"); // hide cursor
    std::atexit(reset_terminal);
}


int read_input() {
    fflush(stdout);
   	char buf[4096]; // maximum input buffer
	int n = read(STDIN_FILENO, buf, sizeof(buf));
    return n > 0 ? buf[n - 1] : -1;
}

