#include <SFML/Graphics.hpp>
#include <headers/sampler.hpp>
#include <headers/objectfactory.hpp>
#include <optional>

#pragma once

namespace sf {

struct SpawnerData {
    Sampler* sampler;
    Vector2f position;
    float delay;
    float offset;
    float minSpeed;
    float maxSpeed;
};

template<typename enemy>
class Spawner{

protected:
    bool active = false;
    bool spawnable = false;

    float m_offset;
    float m_delay;
    float m_enemyMinSpeed;
    float m_enemyMaxSpeed;
    float timeUntilNextSpawn;

    Vector2f m_position;
    Sampler* sampler;

protected:
    virtual enemy spawn() = 0;

public:

    Spawner(){}

    /// @param delay required in seconds
    Spawner(const SpawnerData &data)  {
        sampler = data.sampler;
        m_position = data.position;
        m_offset = data.offset;
        m_delay = data.delay;
        m_enemyMinSpeed = data.minSpeed;
        m_enemyMaxSpeed = data.maxSpeed;
        timeUntilNextSpawn = m_delay;
    }

    std::optional<enemy> spawnEnemy() {
        if(spawnable){
            spawnable = false;
            return spawn();
        }
        return {};
    }

    void activate() { active = true; }

    void deactivate() { active = false; }

    /// @param deltaTime required in seconds
    void update(float deltaTime){
        if(active)
            timeUntilNextSpawn -= deltaTime;
        if(timeUntilNextSpawn <= 0){
            timeUntilNextSpawn = m_delay;
            spawnable = true;
        }
    }

};

//------------------- CircularSpawner --------------------

class CircularSpawner : public Spawner<CircleEnemy> {

protected:
    bool m_randomColor = false;
    Color m_color;
    float m_minRadius;
    float m_maxRadius;

protected:
    CircleEnemy spawn() override;

public:
    CircularSpawner(){}
    CircularSpawner(const SpawnerData &data, const Color &color, bool randomColor, float minRadius, float maxRadius);
};

//------------------- RectangularSpawner --------------------

class RectangularSpawner : public Spawner<RectangleEnemy> {

protected:
    bool m_randomColor = false;
    Color m_color;
    float m_minWidth;
    float m_maxWidth;
    float m_minHeight;
    float m_maxHeight;

protected:
    RectangleEnemy spawn() override;

public:
    RectangularSpawner(){}
    RectangularSpawner(const SpawnerData &data, const Color &color, bool randomColor, float minWidth, float maxWidth, float minHeight, float maxHeight);
    
};

}

 
 