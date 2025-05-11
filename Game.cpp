// Game.cpp
#include "Game.h"

int getRandomNumber(int a, int b) {
    static bool first = true;
    if (first) { srand(time(NULL)); first = false; }
    return a + rand() % (b - a + 1);
}

Game::Game() : window(VideoMode(WIDTH, HEIGHT), "Forza Horizon 1999") {
    window.setFramerateLimit(60);

    if (!bgMusic.openFromFile("sound/game.wav"))
        cout << "Error loading background music\n";
    else {
        bgMusic.setLoop(true);
        bgMusic.setVolume(100);
        bgMusic.play();
    }

    if (!crashBuffer.loadFromFile("sound/crash.wav"))
        cout << "Error loading crash sound\n";
    else
        crashSound.setBuffer(crashBuffer);

    font.loadFromFile("font/batman.ttf");
    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(10, 10);
}

int Game::showGarage() {
    int selectedCar;
    Texture car1, car2, car3;
    car1.loadFromFile("cars/car.png");
    car2.loadFromFile("cars/racer.png");
    car3.loadFromFile("cars/Jeep.png");

    Sprite s1(car1), s2(car2), s3(car3);
    s1.setPosition(150, 250);
    s2.setPosition(350, 250);
    s3.setPosition(550, 250);

    Text msg("Select Your Car (Press 1 / 2 / 3)", font, 35);
    msg.setFillColor(Color::Yellow);
    msg.setPosition(120, 80);

    Text t1("1", font, 28); t1.setPosition(180, 400);
    Text t2("2", font, 28); t2.setPosition(380, 400);
    Text t3("3", font, 28); t3.setPosition(580, 400);

    while (window.isOpen()) {
        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed)
                window.close();
            if (e.type == Event::KeyPressed) {
                if (e.key.code == Keyboard::Num1) { selectedCar = 1; playerTex = car1; return 1; }
                if (e.key.code == Keyboard::Num2) { selectedCar = 2; playerTex = car2; return 2; }
                if (e.key.code == Keyboard::Num3) { selectedCar = 3; playerTex = car3; return 3; }
            }
        }
        window.clear();
        window.draw(msg);
        window.draw(s1); window.draw(t1);
        window.draw(s2); window.draw(t2);
        window.draw(s3); window.draw(t3);
        window.display();
    }
    return 1;
}

void Game::showGameOver() {
    Texture overTex;
    overTex.loadFromFile("cars/over.png");
    Sprite over(overTex);

    Text scoreTextDisplay("Your Score: " + to_string(score), font, 30);
    scoreTextDisplay.setFillColor(Color::White);
    scoreTextDisplay.setPosition(280, 360);

    Text instruction("Press R to Restart | ESC to Exit", font, 24);
    instruction.setFillColor(Color::Cyan);
    instruction.setPosition(200, 420);

    while (window.isOpen()) {
        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed)
                window.close();
            if (e.type == Event::KeyPressed) {
                if (e.key.code == Keyboard::R) {
                    initGame(true);
                    return;
                }
                if (e.key.code == Keyboard::Escape) exit(0);
            }
        }
        window.clear();
        window.draw(over);
        window.draw(scoreTextDisplay);
        window.draw(instruction);
        window.display();
    }
}

void Game::initGame(bool restart) {
    if (!restart) showGarage();

    player.setTexture(playerTex);
    player.setPosition(WIDTH / 2, HEIGHT + 50); // start below screen

    bgTex.loadFromFile("cars/background.png");
    bg1.setTexture(bgTex);
    bg2.setTexture(bgTex);
    bg1.setPosition(0, 0);
    bg2.setPosition(0, -HEIGHT);

    for (int i = 0; i < 4; ++i) {
        obsTex[i].loadFromFile("cars/obs" + to_string(i + 1) + ".png");
        obs[i].setTexture(obsTex[i]);
        obsX[i] = getRandomNumber(BORDER_LEFT, BORDER_RIGHT);
        obsY[i] = -200 * (i + 1);
        obs[i].setPosition(obsX[i], obsY[i]);
    }

    score = 0;
    speed = PLAYER_SPEED;
    isGameOver = false;
    introDone = false;
    bgMusic.play();
}

void Game::run() {
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        if (!introDone) {
            Vector2f pos = player.getPosition();
            if (pos.y > HEIGHT - 100) {
                player.move(0, -PLAYER_SPEED * dt);
            } else {
                introDone = true;
            }
        } else {
            Vector2f pos = player.getPosition();
            if (Keyboard::isKeyPressed(Keyboard::Left) && pos.x > BORDER_LEFT) player.move(-speed * dt, 0);
            if (Keyboard::isKeyPressed(Keyboard::Right) && pos.x < BORDER_RIGHT) player.move(speed * dt, 0);
            if (Keyboard::isKeyPressed(Keyboard::Up) && pos.y > 0) player.move(0, -speed * dt);
            if (Keyboard::isKeyPressed(Keyboard::Down) && pos.y < HEIGHT - 80) player.move(0, speed * dt);
        }

        float bgSpeed = 100.0f * dt;
        bg1.move(0, bgSpeed);
        bg2.move(0, bgSpeed);
        if (bg1.getPosition().y >= HEIGHT) bg1.setPosition(0, -HEIGHT);
        if (bg2.getPosition().y >= HEIGHT) bg2.setPosition(0, -HEIGHT);

        for (int i = 0; i < 4; ++i) {
            obsY[i] += 250.0f * dt;
            if (obsY[i] > HEIGHT) {
                obsY[i] = -150;
                obsX[i] = getRandomNumber(BORDER_LEFT, BORDER_RIGHT);
                score++;

                if (score % 10 == 0) {
                    speed += 20.0f;
                    cout << "Speed increased to: " << speed << endl;
                }
            }
            obs[i].setPosition(obsX[i], obsY[i]);
        }

        for (int i = 0; i < 4; ++i) {
            if (player.getGlobalBounds().intersects(obs[i].getGlobalBounds())) {
                isGameOver = true;
                bgMusic.stop();
                crashSound.play();
                showGameOver();
                return;
            }
        }

        scoreText.setString("Score: " + to_string(score));

        window.clear();
        window.draw(bg1);
        window.draw(bg2);
        for (int i = 0; i < 4; ++i) window.draw(obs[i]);
        window.draw(player);
        window.draw(scoreText);
        window.display();
    }
}
