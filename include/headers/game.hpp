#include <vector>
#include <optional>
#include <headers/sampler.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


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
    Game() : window({window_x, window_y}, "Very Cool Game") {
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

    void draw() {
        for(auto enemy : circularEnemies)
            window.draw(enemy);
        for(auto enemy : rectangularEnemies)
            window.draw(enemy);
        for(auto enemy : spriteEnemies)
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

    ///@param deltatime is given in seconds
    void addPlayTime(const float deltatime);

    void updateScore(const long long multiplier);

    void updateEnemies(Sampler &sampler, CircleShape &player);

};

}