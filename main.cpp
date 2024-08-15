#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

const int WINDOW_WIDTH = 552;
const int WINDOW_HEIGHT = 644;
const float GRAVITY = 800.0f;
const float JUMP_VELOCITY = -300.0f;
const float PIPE_SPEED = -200.0f;
const float PIPE_SPAWN_INTERVAL = 1.6f;
const float APPLE_SCALE_NORMAL = 0.15f;
const float SLOW_MOTION_FACTOR = 0.5f;
const float SLOW_MOTION_DURATION = 5.0f;

enum GameState { MENU, GAME, GAME_OVER, PAUSE };

class Pipe {
public:
    sf::Sprite topPipe;
    sf::Sprite bottomPipe;
    bool scored = false;

    Pipe(float x, float gapY, sf::Texture& pipeTexture) {
        topPipe.setTexture(pipeTexture);
        bottomPipe.setTexture(pipeTexture);
        topPipe.setScale(1, -1);

        topPipe.setPosition(x, gapY - 100);
        bottomPipe.setPosition(x, gapY + 100);
    }

    void move(float deltaTime) {
        topPipe.move(PIPE_SPEED * deltaTime, 0);
        bottomPipe.move(PIPE_SPEED * deltaTime, 0);
    }

    bool isOffScreen() const {
        return topPipe.getPosition().x + topPipe.getGlobalBounds().width < 0;
    }

    bool hasScored(const sf::Sprite& bird) {
        if (!scored && bird.getPosition().x > topPipe.getPosition().x + topPipe.getGlobalBounds().width) {
            scored = true;
            return true;
        }
        return false;
    }
};

class Apple {
public:
    sf::Sprite sprite;
    bool eaten = false;
    float scale = APPLE_SCALE_NORMAL;

    Apple(float x, float y, sf::Texture& appleTexture) {
        sprite.setTexture(appleTexture);
        sprite.setScale(scale, scale);
        sprite.setPosition(x, y);
    }

    void move(float deltaTime) {
        sprite.move(PIPE_SPEED * deltaTime, 0);
    }

    bool isOffScreen() const {
        return sprite.getPosition().x + sprite.getGlobalBounds().width < 0;
    }

    void shrink() {
        eaten = true;
    }
};

class Clock {
public:
    sf::Sprite sprite;
    bool collected = false;

    Clock(float x, float y, sf::Texture& clockTexture) {
        sprite.setTexture(clockTexture);
        sprite.setScale(0.1f, 0.1f);
        sprite.setPosition(x, y);
    }

    void move(float deltaTime) {
        sprite.move(PIPE_SPEED * deltaTime, 0);
    }

    bool isOffScreen() const {
        return sprite.getPosition().x + sprite.getGlobalBounds().width < 0;
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Flappy Girl");
    window.setFramerateLimit(60);

    sf::Texture birdTexture;
    birdTexture.loadFromFile("C:/Users/PC/Desktop/New folder/Project1/picture/ladybird.png");
    sf::Texture pipeTexture;
    pipeTexture.loadFromFile("C:/Users/PC/Desktop/New folder/Project1/picture/treetrunk.png");
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("C:/Users/PC/Desktop/New folder/Project1/picture/background/night.png");
    sf::Texture startTexture;
    startTexture.loadFromFile("C:/Users/PC/Desktop/New folder/Project1/picture/start.png");
    sf::Texture logoTexture;
    logoTexture.loadFromFile("C:/Users/PC/Desktop/New folder/Project1/picture/logo1.png");
    sf::Texture groundTexture;
    groundTexture.loadFromFile("C:/Users/PC/Desktop/New folder/Project1/picture/ground.png");
    sf::Texture gameOverTexture;
    gameOverTexture.loadFromFile("C:/Users/PC/Desktop/New folder/Project1/picture/gameover.png");
    sf::Texture smallImageTexture;
    smallImageTexture.loadFromFile("C:/Users/PC/Desktop/New folder/Project1/picture/ladybird.png");
    sf::Texture pauseTexture;
    pauseTexture.loadFromFile("C:/Users/PC/Desktop/New folder/Project1/picture/pause.png");
    sf::Texture replayTexture;
    replayTexture.loadFromFile("C:/Users/PC/Desktop/New folder/Project1/picture/replay.png");
    sf::Texture appleTexture;
    appleTexture.loadFromFile("C:/Users/PC/Desktop/New folder/Project1/picture/apple.png");
    sf::Texture clockTexture;
    clockTexture.loadFromFile("C:/Users/PC/Desktop/New folder/Project1/picture/clock.png");

    sf::SoundBuffer flapBuffer;
    flapBuffer.loadFromFile("C:/Users/PC/Desktop/New folder/Project1/sound/flap.wav");
    sf::SoundBuffer scoreBuffer;
    scoreBuffer.loadFromFile("C:/Users/PC/Desktop/New folder/Project1/sound/score.wav");
    sf::SoundBuffer hitBuffer;
    hitBuffer.loadFromFile("C:/Users/PC/Desktop/New folder/Project1/sound/hit.wav");

    sf::Sound flapSound(flapBuffer);
    sf::Sound scoreSound(scoreBuffer);
    sf::Sound hitSound(hitBuffer);

    sf::Sprite background(backgroundTexture);
    sf::Sprite bird(birdTexture);
    bird.setScale(0.12f, 0.12f);
    bird.setPosition(200, WINDOW_HEIGHT / 2);

    sf::Sprite startButton(startTexture);
    startButton.setPosition(WINDOW_WIDTH / 2 - startButton.getGlobalBounds().width / 2, WINDOW_HEIGHT / 2 + 50);

    sf::Sprite logo(logoTexture);
    logo.setScale(0.4f, 0.4f);
    logo.setPosition(WINDOW_WIDTH / 2 - logo.getGlobalBounds().width / 2, WINDOW_HEIGHT / 2 - startButton.getGlobalBounds().height - 50);

    sf::Sprite ground(groundTexture);
    ground.setPosition(0, WINDOW_HEIGHT - ground.getGlobalBounds().height);

    sf::Sprite gameOver(gameOverTexture);
    gameOver.setPosition(WINDOW_WIDTH / 2 - gameOver.getGlobalBounds().width / 2, 50);

    sf::Sprite smallImage(smallImageTexture);
    smallImage.setScale(0.3f, 0.3f);
    smallImage.setPosition(WINDOW_WIDTH / 2 - smallImage.getGlobalBounds().width / 2, WINDOW_HEIGHT / 2 - smallImage.getGlobalBounds().height / 2 - 50);

    sf::Sprite pauseImage(pauseTexture);
    pauseImage.setScale(4.0f, 4.0f);
    pauseImage.setPosition(WINDOW_WIDTH / 2 - pauseImage.getGlobalBounds().width / 2, WINDOW_HEIGHT / 2 - pauseImage.getGlobalBounds().height / 2);

    sf::Sprite replayButton(replayTexture);
    replayButton.setScale(1.0f, 1.0f);
    replayButton.setPosition(WINDOW_WIDTH / 2 - replayButton.getGlobalBounds().width / 2, WINDOW_HEIGHT / 2 + 200);

    sf::Font font;
    font.loadFromFile("C:/Users/PC/Desktop/New folder/Project1/font/04B_19__.ttf");

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(50);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(WINDOW_WIDTH / 2, 50);

    sf::Text congratulationsText;
    congratulationsText.setFont(font);
    congratulationsText.setCharacterSize(30);
    congratulationsText.setFillColor(sf::Color::White);

    float birdVelocity = 0;
    bool isGameOver = false;
    GameState gameState = MENU;

    std::vector<Pipe> pipes;
    std::vector<Apple> apples;
    std::vector<Clock> clocks;
    float timeSinceLastPipe = 0;
    float timeSinceLastApple = 0;
    float timeSinceLastClock = 0;
    int score = 0;
    int shrinkEndScore = -1;
    bool isSlowMotion = false;
    int slowMotionEndScore = -1;

    sf::Clock clock;

    sf::View view(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));

    std::srand(std::time(nullptr));

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        if (isSlowMotion) {
            deltaTime *= SLOW_MOTION_FACTOR;
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::Resized) {
                float aspectRatio = float(WINDOW_WIDTH) / float(WINDOW_HEIGHT);
                float newAspectRatio = float(event.size.width) / float(event.size.height);

                if (newAspectRatio > aspectRatio) {
                    float newWidth = aspectRatio * event.size.height;
                    view.setViewport(sf::FloatRect((event.size.width - newWidth) / (2.0f * event.size.width), 0.0f, newWidth / event.size.width, 1.0f));
                }
                else {
                    float newHeight = event.size.width / aspectRatio;
                    view.setViewport(sf::FloatRect(0.0f, (event.size.height - newHeight) / (2.0f * event.size.height), 1.0f, newHeight / event.size.height));
                }

                window.setView(view);
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                if (gameState == GAME) {
                    gameState = PAUSE;
                }
                else if (gameState == PAUSE) {
                    gameState = GAME;
                }
            }
            if (gameState == MENU && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

                if (startButton.getGlobalBounds().contains(worldPos)) {
                    gameState = GAME;
                    bird.setPosition(200, WINDOW_HEIGHT / 2);
                    bird.setScale(0.12f, 0.12f);
                    birdVelocity = 0;
                    pipes.clear();
                    apples.clear();
                    clocks.clear();
                    timeSinceLastPipe = 0;
                    timeSinceLastApple = 0;
                    timeSinceLastClock = 0;
                    score = 0;
                    shrinkEndScore = -1;
                    isSlowMotion = false;
                    slowMotionEndScore = -1;
                    isGameOver = false;
                }
            }
            if (gameState == GAME && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && !isGameOver) {
                birdVelocity = JUMP_VELOCITY;
                flapSound.play();
            }
            if (gameState == GAME_OVER && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

                if (replayButton.getGlobalBounds().contains(worldPos)) {
                    gameState = MENU;
                }
            }
        }

        if (gameState == GAME) {
            birdVelocity += GRAVITY * deltaTime;
            bird.move(0, birdVelocity * deltaTime);

            if (bird.getPosition().y + bird.getGlobalBounds().height >= WINDOW_HEIGHT - ground.getGlobalBounds().height || bird.getPosition().y <= 0) {
                isGameOver = true;
                gameState = GAME_OVER;
                hitSound.play();
            }

            timeSinceLastPipe += deltaTime;
            if (timeSinceLastPipe >= PIPE_SPAWN_INTERVAL) {
                float gapY = 150 + std::rand() % (WINDOW_HEIGHT - 300);
                pipes.emplace_back(WINDOW_WIDTH, gapY, pipeTexture);
                timeSinceLastPipe = 0;

                bool spawnApple = (shrinkEndScore == -1 && std::rand() % 10 == 0);
                bool spawnClock = (!spawnApple && std::rand() % 10 == 0);

                if (spawnApple) {
                    float appleY = gapY;
                    float appleX = WINDOW_WIDTH + (pipes.back().bottomPipe.getGlobalBounds().width / 3.5f);
                    apples.emplace_back(appleX, appleY, appleTexture);
                }
                else if (spawnClock) {
                    float clockY = gapY;
                    float clockX = WINDOW_WIDTH + (pipes.back().bottomPipe.getGlobalBounds().width / 3.5f);
                    clocks.emplace_back(clockX, clockY, clockTexture);
                }
            }

            for (auto& pipe : pipes) {
                pipe.move(deltaTime);
                if (pipe.hasScored(bird)) {
                    score++;
                    scoreSound.play();
                }
                if (bird.getGlobalBounds().intersects(pipe.topPipe.getGlobalBounds()) || bird.getGlobalBounds().intersects(pipe.bottomPipe.getGlobalBounds())) {
                    isGameOver = true;
                    gameState = GAME_OVER;
                    hitSound.play();
                }
            }

            pipes.erase(std::remove_if(pipes.begin(), pipes.end(), [](const Pipe& pipe) { return pipe.isOffScreen(); }), pipes.end());

            for (auto& apple : apples) {
                apple.move(deltaTime);
                if (!apple.eaten && bird.getGlobalBounds().intersects(apple.sprite.getGlobalBounds())) {
                    apple.eaten = true;
                    apple.shrink();
                    shrinkEndScore = score + 10;
                }
            }

            apples.erase(std::remove_if(apples.begin(), apples.end(), [](const Apple& apple) { return apple.eaten || apple.isOffScreen(); }), apples.end());

            for (auto& clock : clocks) {
                clock.move(deltaTime);
                if (!clock.collected && bird.getGlobalBounds().intersects(clock.sprite.getGlobalBounds())) {
                    clock.collected = true;
                    isSlowMotion = true;
                    slowMotionEndScore = score + 5;
                }
            }

            clocks.erase(std::remove_if(clocks.begin(), clocks.end(), [](const Clock& clock) { return clock.collected || clock.isOffScreen(); }), clocks.end());

            if (shrinkEndScore != -1 && score >= shrinkEndScore) {
                bird.setScale(0.12f, 0.12f);
                shrinkEndScore = -1;
            }
            else if (shrinkEndScore != -1) {
                bird.setScale(0.06f, 0.06f);
            }

            if (isSlowMotion && score >= slowMotionEndScore) {
                isSlowMotion = false;
                slowMotionEndScore = -1;
            }
        }

        window.clear(sf::Color(150, 150, 150));

        window.draw(background);

        if (gameState == MENU) {
            window.draw(startButton);
            window.draw(logo);
        }
        else if (gameState == GAME) {
            window.draw(bird);
            for (auto& pipe : pipes) {
                window.draw(pipe.topPipe);
                window.draw(pipe.bottomPipe);
            }
            for (auto& apple : apples) {
                window.draw(apple.sprite);
            }
            for (auto& clock : clocks) {
                window.draw(clock.sprite);
            }
            window.draw(ground);

            scoreText.setString(to_string(score));
            scoreText.setOrigin(scoreText.getGlobalBounds().width / 2, scoreText.getGlobalBounds().height / 2);
            window.draw(scoreText);
        }
        else if (gameState == GAME_OVER) {
            window.draw(gameOver);
            window.draw(smallImage);

            congratulationsText.setString("Congratulations, you've scored " + to_string(score));
            congratulationsText.setOrigin(congratulationsText.getGlobalBounds().width / 2, congratulationsText.getGlobalBounds().height / 2);
            congratulationsText.setPosition(WINDOW_WIDTH / 2, smallImage.getPosition().y + smallImage.getGlobalBounds().height + 70);
            window.draw(congratulationsText);
            window.draw(replayButton);
        }
        else if (gameState == PAUSE) {
            window.draw(pauseImage);
        }

        window.display();
    }

    return 0;
}
