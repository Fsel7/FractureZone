#include <SFML/Graphics/CircleShape.hpp>

#pragma once

#define origin {0.f, 0.f}
#define window_x 1200u
#define window_y 900u

namespace sf {

struct Game {
public:
    Font myFont;
    RenderWindow window;

    Text score;
    Text minScore;

    long long points = 0;
    long long minPoints = 0;

    float playTime = 0;
    float globTime = 0;
    
    Game() : window({window_x, window_y}, "Very Cool Game") {
        myFont.loadFromFile("fonts/arial.ttf");      
        window.setFramerateLimit(64);
    }

    ~Game() = default;

    void addPlayTime(const float deltatime) {
        playTime += deltatime;
        globTime += deltatime;
    }

    void updateScore(const long long multiplier) {
        points   += (long long) playTime * multiplier;
        minPoints = (long long) pow(playTime, 3);
        score.setString("Score: " + std::to_string(points) + ", current bonus: " + std::to_string((long long) multiplier));
        minScore.setString("Stay above: " + std::to_string(minPoints));
    }

    void clear() {
        window.clear();
    }

    void close() {
        window.close();
    }

    void draw() {
        window.draw(score);
        window.draw(minScore);
    }

    template<typename T>
    void draw(T &obj) {
        window.draw(obj);
    }

    void display() {
        window.display();
    }

    bool isRunning() {
        return window.isOpen();
    }
};

}