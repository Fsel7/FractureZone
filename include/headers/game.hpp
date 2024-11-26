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

friend class XMLParser;

private:
    Font font;
    Color outOfBounds = Color(1, 50, 32);
    View view;

    Texture backgroundTexture;
    Sprite backgroundSprite;
    Texture activeSpawnerTexture;
    Texture inactiveSpawnerTexture;
    
    unsigned int window_x;
    unsigned int window_y;

    std::vector<CircularSpawner> circleSpawners = {};
    std::vector<RectangularSpawner> rectangleSpawners = {};
    std::vector<BonusZone> bonusZones = {};

    std::vector<CircleEnemy> circularEnemies = {};
    std::vector<RectangleEnemy> rectangularEnemies = {};
    std::vector<Sprite> spriteEnemies = {};

    Text score;
    Text minScore;
    Text pTime;
    Text gTime;
    Text fps;
    Text gameover;

    float currentTime = 0;
    float totalTime = 0;

    float points = 1;
    float minPoints = 0;

public:
    std::vector<BlackHole> blackholes = {};
    RenderWindow* window;

public:

    Game() {window = nullptr;}

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

    void resetGameFrame() { window->clear(outOfBounds); window->draw(backgroundSprite); }

    void close() { window->close(); }

    FloatRect getBounds(){ return backgroundSprite.getGlobalBounds(); }

    void resetView() {view.setCenter(window_center); window->setView(view);}

    void updateView(const Vector2f center);

    void draw(const Player &player);

    void drawFrame(const Player &player);
    
    template<typename T>
    void draw(T &obj) {
        window->draw(obj);
    }

    void setupText();

    ///@param deltatime is given in seconds
    void addTime(const float deltatime);

    void updateScore(const long long multiplier, const float deltatime);

    void updateEnemies(Sampler &sampler, const Player &player, const float deltatime);

    void updateSpawners(Sampler& sampler, const float deltaTime);

    void applyGravity(Player &player);

    bool checkLost(const Player &player);

    bool collision(const Player &player);

    long long getMultiplier(const Player &player);

    void showEndScreen();

    void reset();

};

}