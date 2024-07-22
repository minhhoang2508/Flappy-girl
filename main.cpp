#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float GRAVITY = 800.0f;
const float JUMP_VELOCITY = -300.0f;
const float PIPE_SPEED = -200.0f;
const float PIPE_SPAWN_INTERVAL = 1.5f;

class Pipe {
public:
    sf::RectangleShape topPipe;
    sf::RectangleShape bottomPipe;

    Pipe(float x, float gapY) {
        topPipe.setSize(sf::Vector2f(80.0f, gapY - 100));
        topPipe.setPosition(x, 0);
        topPipe.setFillColor(sf::Color::Green);

        bottomPipe.setSize(sf::Vector2f(80.0f, WINDOW_HEIGHT - gapY - 100));
        bottomPipe.setPosition(x, gapY + 100);
        bottomPipe.setFillColor(sf::Color::Green);
    }

    void move(float deltaTime) {
        topPipe.move(PIPE_SPEED * deltaTime, 0);
        bottomPipe.move(PIPE_SPEED * deltaTime, 0);
    }

    bool isOffScreen() {
        return topPipe.getPosition().x + topPipe.getSize().x < 0;
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Flappy Girl");
    window.setFramerateLimit(60);

    sf::RectangleShape bird(sf::Vector2f(40.0f, 40.0f));
    bird.setFillColor(sf::Color::Yellow);
    bird.setPosition(200, WINDOW_HEIGHT / 2);

    float birdVelocity = 0;
    bool isGameOver = false;

    vector<Pipe> pipes;
    float timeSinceLastPipe = 0;

    sf::Clock clock;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && !isGameOver) {
                birdVelocity = JUMP_VELOCITY;
            }
        }

        if (!isGameOver) {
            birdVelocity += GRAVITY * deltaTime;
            bird.move(0, birdVelocity * deltaTime);

            if (bird.getPosition().y + bird.getSize().y > WINDOW_HEIGHT || bird.getPosition().y < 0) {
                isGameOver = true;
            }

            timeSinceLastPipe += deltaTime;
            if (timeSinceLastPipe >= PIPE_SPAWN_INTERVAL) {
                float gapY = 100 + rand() % (WINDOW_HEIGHT - 200);
                pipes.push_back(Pipe(WINDOW_WIDTH, gapY));
                timeSinceLastPipe = 0;
            }

            for (auto& pipe : pipes) {
                pipe.move(deltaTime);
                if (bird.getGlobalBounds().intersects(pipe.topPipe.getGlobalBounds()) || bird.getGlobalBounds().intersects(pipe.bottomPipe.getGlobalBounds())) {
                    isGameOver = true;
                }
            }

            pipes.erase(remove_if(pipes.begin(), pipes.end(), [](Pipe& pipe) { return pipe.isOffScreen(); }), pipes.end());
        }

        window.clear(sf::Color::Blue);
        window.draw(bird);

        for (auto& pipe : pipes) {
            window.draw(pipe.topPipe);
            window.draw(pipe.bottomPipe);
        }

        window.display();
    }

    return 0;
}
