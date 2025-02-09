#include <SFML/Graphics.hpp>
#include <headers/sampler.hpp>
#include <headers/objectfactory.hpp>
#include <optional>

#pragma once

namespace sf {

enum SpawnerUpdate{
    NO_UPDATE,
    ACTIVE_TEXTURE,
    INACTIVE_TEXTURE
};

struct SpawnerData {
    Vector2f position;
    float delay;
    float offset;
    float minSpeed;
    float maxSpeed;
    float startTime;
    float endTime;
};

template<typename enemy>
class Spawner {

public:
    Sprite m_spawnerSprite;

public:
    Spawner() = default;
    virtual ~Spawner() = default;

    /// @note SpawnerData::delay required in seconds.
    Spawner(const SpawnerData &data) {
        m_position = data.position;
        m_offset = data.offset;
        m_delay = data.delay;
        m_timeUntilNextSpawn = m_delay;
        m_enemyMinSpeed = data.minSpeed;
        m_enemyMaxSpeed = data.maxSpeed;
        m_startTime = data.startTime;
        m_endTime = data.endTime;
    }

    bool isActive() { return m_active; }

    /// @brief deltaTime and currentTime required in seconds.
    SpawnerUpdate update(const float deltaTime, const float currentTime);

    /// @brief Spawns an enemy if the spawner is still active and currently not on cooldown.
    std::optional<enemy> spawnEnemy(Sampler& sampler) {
        if (!m_spawnable)
            return {};
        m_spawnable = false;
        return spawn(sampler);
    }

protected:
    bool m_active = false;
    bool m_spawnable = false;

    float m_startTime;
    float m_endTime;

    float m_offset;
    float m_delay;
    float m_enemyMinSpeed;
    float m_enemyMaxSpeed;
    float m_timeUntilNextSpawn;

    Vector2f m_position;
    
protected:
    virtual enemy spawn(Sampler& sampler) const = 0;
};

//------------------- CircularSpawner --------------------

class CircularSpawner : public Spawner<CircleEnemy> {

public:
    CircularSpawner() = default;
    CircularSpawner(const SpawnerData &data, const float minRadius, const float maxRadius, const Color color = Color::Black);
    ~CircularSpawner() = default;

protected:
    Color m_color;
    float m_minRadius;
    float m_maxRadius;

protected:
    CircleEnemy spawn(Sampler& sampler) const override;
};

//------------------- RectangularSpawner --------------------

class RectangularSpawner : public Spawner<RectangleEnemy> {

public:
    RectangularSpawner() = default;
    RectangularSpawner(const SpawnerData &data, const float minWidth, const float maxWidth, const float minHeight, const float maxHeight, const Color color = Color::Black);
    ~RectangularSpawner() = default;

protected:
    Color m_color;
    float m_minWidth;
    float m_maxWidth;
    float m_minHeight;
    float m_maxHeight;

protected:
    RectangleEnemy spawn(Sampler& sampler) const override;
    
};

}

 
 