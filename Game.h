// Game.h
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace sf;
using namespace std;

const int WIDTH = 800, HEIGHT = 600;
const int BORDER_LEFT = 140, BORDER_RIGHT = 660;
const float PLAYER_SPEED = 200.0f;

int getRandomNumber(int a, int b);

class Game {
private:
    RenderWindow window;
    Font font;
    Texture playerTex;
    Sprite player;
    Texture bgTex;
    Sprite bg1, bg2;
    Texture obsTex[4];
    Sprite obs[4];
    float obsX[4], obsY[4];
    float speed;
    Clock clock;
    int score;
    Text scoreText;
    bool isGameOver;

    Music bgMusic;
    SoundBuffer crashBuffer;
    Sound crashSound;

    bool introDone;

public:
    Game();
    int showGarage();
    void showGameOver();
    void initGame(bool restart = false);
    void run();
};

#endif // GAME_H
