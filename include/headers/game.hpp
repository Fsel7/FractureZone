#include <SFML/Graphics/CircleShape.hpp>
#include <vector>
#include <optional>
#include <headers/math.hpp>
#include <headers/sampler.hpp>

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

class GameInterface {

protected:
    float enemySpeed = 1.f;
    Font font;

public:
    std::vector<CircleShape> circularEnemies = {};
    std::vector<RectangleShape> rectangularEnemies = {};
    std::vector<Sprite> spriteEnemies = {};

    RenderWindow window;

    Text score;
    Text minScore;
    Text pTime;
    Text gTime;

    float playTime = 0;
    float gameTime = 0;

    long long points = 0;
    long long minPoints = 0;
    
public:
    GameInterface() : window({window_x, window_y}, "Very Cool Game") {
        font.loadFromFile("fonts/arial.ttf");      
        window.setFramerateLimit(64);
    }

    Font getFont() { return font; }

    template<typename shape>
    void addEnemy(std::optional<shape> &enemy) {
        if(auto entity = enemy)
            addEnemy(entity.value());
    }

    void addEnemy(CircleShape &enemy) { circularEnemies.push_back(enemy); }
    
    void addEnemy(RectangleShape &enemy) { rectangularEnemies.push_back(enemy); }

    void addEnemy(Sprite &enemy) { spriteEnemies.push_back(enemy); }

    void clear() { window.clear(); }

    void close() { window.close(); }

    void display() { window.display(); }

    bool isRunning() { return window.isOpen(); }

    ///@param deltatime is given in seconds
    virtual void addPlayTime(const float deltatime) = 0;

    virtual void updateScore(const long long multiplier) = 0;

    virtual void updateEnemies(Sampler &sampler, CircleShape &player) = 0;

};

}