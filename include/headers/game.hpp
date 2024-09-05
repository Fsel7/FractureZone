#include <vector>
#include <optional>
#include <headers/sampler.hpp>
#include <SFML/Graphics/Font.hpp>
#include <headers/entities.hpp>
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
#define line_offset Vector2f(0.f, fontSize + fontSize / 3.f)
#define fps_offset  Vector2f(120.f, 0.f)

namespace sf {

enum LoseCondition {
    ENEMY,
    POINTS,
};

class BlackHole;
class Player;

class Game {

protected:
    int framerateLimit = 144;
    Font font;

public:
    std::vector<CircleEnemy> circularEnemies = {};
    std::vector<RectangleEnemy> rectangularEnemies = {};
    std::vector<Sprite> spriteEnemies = {};
    std::vector<BlackHole> blackholes = {};

    RenderWindow window;

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
    Game() : window({window_x, window_y}, "Very Cool Game") {
        font.loadFromFile("resources/arial.ttf");      
        window.setFramerateLimit(framerateLimit);
        setupText();
    }

    Font getFont() { return font; }

    template<typename shape>
    void addEnemy(std::optional<shape> &enemy) {
        if(auto entity = enemy)
            addEnemy(entity.value());
    }

    void addEnemy(CircleEnemy &enemy) { circularEnemies.push_back(enemy); }
    
    void addEnemy(RectangleEnemy &enemy) { rectangularEnemies.push_back(enemy); }

    void addEnemy(Sprite &enemy) { spriteEnemies.push_back(enemy); }

    void addBlackHole(BlackHole &blackhole) {blackholes.push_back(blackhole); }

    void clear() { window.clear(); }

    void close() { window.close(); }

    void display() { window.display(); }

    bool isRunning() { return window.isOpen(); }

    void draw() {
        for(auto enemy : rectangularEnemies)
            window.draw(enemy.shape);
        for(auto enemy : circularEnemies)
            window.draw(enemy.shape);
        for(auto enemy : spriteEnemies)
            window.draw(enemy);
        window.draw(score);
        window.draw(minScore);
        window.draw(pTime);
        window.draw(gTime);
        window.draw(fps);
    }

    template<typename T>
    void draw(T &obj) {
        window.draw(obj);
    }

    void end(const LoseCondition cause);

    void setupText();

    ///@param deltatime is given in seconds
    void addPlayTime(const float deltatime);

    void updateScore(const long long multiplier, const float deltatime);

    void updateEnemies(Sampler &sampler, CircleShape &player, const float deltatime);

    void applyGravity(Player &player);

};

}