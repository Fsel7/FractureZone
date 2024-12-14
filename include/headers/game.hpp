#include <headers/entities.hpp>
#include <headers/spawner.hpp>

#include<headers/core.hpp>

#include <vector>

#pragma once

#define fontSize 30

namespace sf {

class Game {
    friend class XMLParser;

public:
    std::vector<BlackHole> blackholes = {};
    RenderWindow* window;

public:
    Game() { window = nullptr; }

    Game(const uint32_t window_x, const uint32_t window_y, const char* gameName, const std::string &fontPath);

    ~Game() { delete window; }

    Font getFont() const { return m_font; }

    FloatRect getBounds() const { return m_backgroundSprite.getGlobalBounds(); }

    template<typename shape>
    void addEnemy(const std::optional<shape> &enemy) { if(enemy) addEnemy(enemy.value()); }

    void addEnemy(const CircleEnemy &enemy) { m_circularEnemies.push_back(enemy); }
    
    void addEnemy(const RectangleEnemy &enemy) { m_rectangularEnemies.push_back(enemy); }

    void addEnemy(const Sprite &enemy) { m_spriteEnemies.push_back(enemy); }

    void addSpawner(const CircularSpawner &spawner) { m_circleSpawners.push_back(spawner); }

    void addSpawner(const RectangularSpawner &spawner) { m_rectangleSpawners.push_back(spawner); }

    void addBlackHole(const BlackHole &blackhole) { blackholes.push_back(blackhole); }

    template<typename T>
    void draw(const T &obj) const { window->draw(obj); }

    void setMaxFps(const uint16_t fps) const {window->setFramerateLimit(fps); }

    void switchWindowMode() {
        window->create(VideoMode(window_x, window_y), m_gameName, m_isFullscreen ? Style::Default :  Style::Fullscreen);
        m_isFullscreen = !m_isFullscreen;
    }

    Vector2f getWindowScale() const {
        const Vector2u curSize = window->getSize();
        return Vector2f(window_x * 1.f / curSize.x , window_y * 1.f / curSize.y);
    }

public:
    uint64_t getMultiplier(const Player &player) const;

    void drawFrame(const Player &player);

    ///@param deltatime is given in seconds
    void addTime(const float deltatime);

    void updateScore(const uint64_t multiplier, const float deltatime);

    void updateEnemies(Sampler &sampler, const Player &player, const float deltatime);

    void updateSpawners(Sampler& sampler, const float deltaTime);

    void applyGravity(Player &player);

    /// @brief To be used after ending a game round.
    void resetView();

    /// @brief Resets all enemies, points and the game time.
    void reset();

    /// @brief Checks whether one of the losing conditions is met.
    bool checkLost(const Player &player);

    void showEndScreen();

private:
    /// @brief Prepares the window during a game round for the new frame.
    void resetGameFrame() { window->clear(m_outOfBounds); window->draw(m_backgroundSprite); }

private:
    /// @brief Initializes all Text objects needed during a game round.
    void setupText();

    /// @brief Checks whether the player collides with any enemies.
    bool collision(const Player &player) const;

    /// @brief Draws the spawners, enemies, player and text
    void draw(const Player &player) const;

    /// @brief Moves the camera to center and adjusts and all UI elements 
    void updateView(const Vector2f center);

private:
    Font m_font;
    Color m_outOfBounds = Color(1, 50, 32);
    View m_view;

    Sprite m_lostSprite;
    Sprite m_backgroundSprite;
    Texture m_lostTexture;
    Texture m_backgroundTexture;

    Texture m_activeSpawnerTexture;
    Texture m_inactiveSpawnerTexture;
    
    uint32_t window_x;
    uint32_t window_y;

    bool m_isFullscreen = true;

    std::string m_gameName;

    std::vector<CircularSpawner> m_circleSpawners = {};
    std::vector<RectangularSpawner> m_rectangleSpawners = {};
    std::vector<BonusZone> m_bonusZones = {};

    std::vector<CircleEnemy> m_circularEnemies = {};
    std::vector<RectangleEnemy> m_rectangularEnemies = {};
    std::vector<Sprite> m_spriteEnemies = {};

    Text m_score;
    Text m_minScore;
    Text m_pTime;
    Text m_gTime;
    Text m_fps;
    Text m_gameover;

    float m_currentTime = 0;
    float m_totalTime = 0;

    float m_points = 1;
    float m_minPoints = 0;
};

}