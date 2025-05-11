// main.cpp
#include "Game.h"

int main() {
    while (true) {
        Game game;
        game.initGame();
        game.run();
    }
    return 0;
}
