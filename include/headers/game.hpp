#include <headers/entities.hpp>
#include <headers/spawner.hpp>
#include <headers/gui.hpp>

#include <headers/core.hpp>

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

    Game(const uint32_t window_x, const uint32_t window_y, const std::string &gameName);

    ~Game() { delete window; }

    Font getFont() const { return m_font; }

    uint64_t getHighscore() const { return m_highscore; }

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

    void setMaxFps(const uint16_t maxFps) { m_maxFps = maxFps; window->setFramerateLimit(maxFps); }

    /// @brief To be used after ending a game round.
    void resetView() {
        m_view.setCenter(Vector2f(0.5f * window_x, 0.5f * window_y));
        window->setView(m_view);
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

    /// @brief Resets all enemies, points and the game time.
    void reset();

    /// @brief Checks whether one of the losing conditions is met.
    bool checkLost(const Player &player);

    void showEndScreen();

    void updateHighscore();

    /// @brief Switches between windowed and fullscreen.
    void switchWindowMode();

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
    std::string m_gameName; 
    View m_view;
    Image m_icon;

    uint32_t window_x;
    uint32_t window_y;
    uint16_t m_maxFps = 144;
    bool m_isFullscreen = true;

    Font m_font;
    Color m_outOfBounds = Color(1, 50, 32);

    Sprite m_lostSprite;
    Sprite m_backgroundSprite;
    Texture m_lostTexture;
    Texture m_backgroundTexture;

    Texture m_activeSpawnerTexture;
    Texture m_inactiveSpawnerTexture;

    std::vector<CircularSpawner> m_circleSpawners = {};
    std::vector<RectangularSpawner> m_rectangleSpawners = {};
    std::vector<BonusZone> m_bonusZones = {};

    std::vector<CircleEnemy> m_circularEnemies = {};
    std::vector<RectangleEnemy> m_rectangularEnemies = {};
    std::vector<Sprite> m_spriteEnemies = {};

    Text m_fps;

    MultilineText m_score;
    MultilineText m_time;
    MultilineText m_gameover;

    float m_currentTime = 0;
    float m_totalTime = 0;

    float m_minPoints = 0;
    float m_points = 1;

    uint64_t m_highscore;
};

}