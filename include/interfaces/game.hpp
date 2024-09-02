#include <SFML/Graphics/CircleShape.hpp>
#include <vector>

#pragma once

#define window_x 1200u
#define window_y 900u
#define window_center Vector2f(0.5f * window_x, 0.5f * window_y)

#define top_left     Vector2f(0.f,      0.f)
#define top_right    Vector2f(window_x, 0.f)
#define bottom_left  Vector2f(0.f,      window_y)
#define bottom_right Vector2f(window_x, window_y)

#define fontSize 30
#define line_offset Vector2f(0.f, fontSize + 10.f)

namespace sf {

class Game {

private:
    float playTime = 0;
    float gameTime = 0;

public:
    std::vector<CircleShape> circularEnemies = {};
    std::vector<RectangleShape> rectangularEnemies = {};
    std::vector<Sprite> spriteEnemies = {};

    Font myFont;
    RenderWindow window;

    Text score;
    Text minScore;
    Text pTime;
    Text gTime;

    long long points = 0;
    long long minPoints = 0;
    
    Game() : window({window_x, window_y}, "Very Cool Game") {
        myFont.loadFromFile("fonts/arial.ttf");      
        window.setFramerateLimit(64);
    }

    ~Game() = default;

    void addPlayTime(const float deltatime) {
        playTime += deltatime;
        gameTime += deltatime;
        pTime.setString("Play time: " + std::to_string((long long)(1000 * playTime)) + " ms");
        gTime.setString("Game time: " + std::to_string((long long)(1000 * gameTime)) + " ms");
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
        for(auto enemy : circularEnemies)
            window.draw(enemy);
        window.draw(score);
        window.draw(minScore);
        window.draw(pTime);
        window.draw(gTime);
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

    void addEnemy(CircleShape &enemy) {
        circularEnemies.push_back(enemy);
    }
    
    void addEnemy(RectangleShape &enemy) {
        rectangularEnemies.push_back(enemy);
    }

    void addEnemy(Sprite &enemy) {
        spriteEnemies.push_back(enemy);
    }
};

}