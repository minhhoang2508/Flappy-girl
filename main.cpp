#include <SFML/Graphics.hpp>
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
const float PIPE_SPAWN_INTERVAL = 1.5f;

enum GameState { MENU, GAME, GAME_OVER };

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

    bool isOffScreen() {
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

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Flappy Bird");
    window.setFramerateLimit(60);

    
    sf::Texture birdTexture;
    birdTexture.loadFromFile("C:/Users/PC/Desktop/New folder/Project1/picture/ladybird.png");
    sf::Texture pipeTexture;
    pipeTexture.loadFromFile("C:/Users/PC/Desktop/New folder/Project1/picture/pipe.png");
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("C:/Users/PC/Desktop/New folder/Project1/picture/background/day.png");
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

    
    sf::Sprite background(backgroundTexture);
    sf::Sprite bird(birdTexture);
    bird.setScale(0.15f, 0.15f);  
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
    float timeSinceLastPipe = 0;
    int score = 0;

    sf::Clock clock;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (gameState == MENU && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                gameState = GAME;
                isGameOver = false;
                bird.setPosition(200, WINDOW_HEIGHT / 2);
                birdVelocity = 0;
                pipes.clear();
                timeSinceLastPipe = 0;
                score = 0;
            }
            if (gameState == GAME && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && !isGameOver) {
                birdVelocity = JUMP_VELOCITY;
            }
            if (gameState == GAME_OVER && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                gameState = MENU;
            }
        }

        if (gameState == GAME && !isGameOver) {
            birdVelocity += GRAVITY * deltaTime;
            bird.move(0, birdVelocity * deltaTime);

            if (bird.getPosition().y + bird.getGlobalBounds().height >= WINDOW_HEIGHT - ground.getGlobalBounds().height || bird.getPosition().y <= 0) {
                isGameOver = true;
                gameState = GAME_OVER;
            }

            timeSinceLastPipe += deltaTime;
            if (timeSinceLastPipe >= PIPE_SPAWN_INTERVAL) {
                float gapY = 150 + std::rand() % (WINDOW_HEIGHT - 300);
                pipes.push_back(Pipe(WINDOW_WIDTH, gapY, pipeTexture));
                timeSinceLastPipe = 0;
            }

            for (auto& pipe : pipes) {
                pipe.move(deltaTime);
                if (pipe.hasScored(bird)) {
                    score++;
                }
                if (bird.getGlobalBounds().intersects(pipe.topPipe.getGlobalBounds()) || bird.getGlobalBounds().intersects(pipe.bottomPipe.getGlobalBounds())) {
                    isGameOver = true;
                    gameState = GAME_OVER;
                }
            }

            pipes.erase(remove_if(pipes.begin(), pipes.end(), [](Pipe& pipe) { return pipe.isOffScreen(); }), pipes.end());
        }

        window.clear(sf::Color::Blue);
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
            congratulationsText.setPosition(WINDOW_WIDTH / 2, smallImage.getPosition().y + smallImage.getGlobalBounds().height + 20);  
            window.draw(congratulationsText);
        }

        window.display();
    }

    return 0;
}
