#include <headers/entities.hpp>
#include <headers/spawner.hpp>

#include<headers/core.hpp>

#include <vector>

#pragma once

#define window_center Vector2f(0.5f * window_x, 0.5f * window_y)

#define top_left     Vector2f(0.f,            0.f)
#define top_right    Vector2f(1.f * window_x, 0.f)
#define bottom_left  Vector2f(0.f,            1.f * window_y)
#define bottom_right Vector2f(1.f * window_x, 1.f * window_y)

#define fontSize 30
#define line_offset Vector2f(0.f, fontSize + fontSize / 3.f)
#define fps_offset  Vector2f(120.f, 0.f)

namespace sf {

class Game {

protected:
    Font font;
    unsigned int window_x;
    unsigned int window_y;

public:
    std::vector<CircleEnemy> circularEnemies = {};
    std::vector<RectangleEnemy> rectangularEnemies = {};
    std::vector<Sprite> spriteEnemies = {};
    std::vector<BlackHole> blackholes = {};

    std::vector<CircularSpawner> circleSpawners = {};
    std::vector<RectangularSpawner> rectangleSpawners = {};

    RenderWindow* window;

    Text score;
    Text minScore;
    Text pTime;
    Text gTime;
    Text fps;
    Text gameover;

    float playTime = 0;
    float gameTime = 0;

    float points = 1;
    float minPoints = 0;
    
public:

    Game(const unsigned int window_x, const unsigned int window_y, const int maxFrames, const char* gameName, const std::string &fontPath);

    ~Game() { delete window; }

    Font getFont() { return font; }

    template<typename shape>
    void addEnemy(std::optional<shape> &enemy) {
        if(enemy)
            addEnemy(enemy.value());
    }

    void addEnemy(CircleEnemy &enemy) { circularEnemies.push_back(enemy); }
    
    void addEnemy(RectangleEnemy &enemy) { rectangularEnemies.push_back(enemy); }

    void addEnemy(Sprite &enemy) { spriteEnemies.push_back(enemy); }

    void addSpawner(CircularSpawner &spawner) { circleSpawners.push_back(spawner); }

    void addSpawner(RectangularSpawner &spawner) { rectangleSpawners.push_back(spawner); }

    void addBlackHole(BlackHole &blackhole) {blackholes.push_back(blackhole); }

    void clear() { window->clear(); }

    void close() { window->close(); }

    void display() { window->display(); }

    bool isRunning() { return window->isOpen(); }

    void draw() {
        for(auto enemy : rectangularEnemies)
            window->draw(enemy.shape);
        for(auto enemy : circularEnemies)
            window->draw(enemy.shape);
        for(auto enemy : spriteEnemies)
            window->draw(enemy);
        window->draw(score);
        window->draw(minScore);
        window->draw(pTime);
        window->draw(gTime);
        window->draw(fps);
    }

    void draw(Shape* shape) { window->draw(*shape); }
    
    template<typename T>
    void draw(T &obj) {
        window->draw(obj);
    }

    void setupText();

    ///@param deltatime is given in seconds
    void addPlayTime(const float deltatime);

    void updateScore(const long long multiplier, const float deltatime);

    void updateEnemies(Sampler &sampler, const Player &player, const float deltatime);

    void updateSpawners(Sampler& sampler, const float deltaTime);

    void applyGravity(Player &player);

    bool lose(Player &player);

};

}