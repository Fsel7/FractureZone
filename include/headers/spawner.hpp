#include <SFML/Graphics.hpp>
#include <headers/sampler.hpp>
#include <headers/objectfactory.hpp>
#include <optional>

#pragma once

namespace sf {

template<typename shape>
class Spawner{

protected:
    bool active = false;
    bool spawnable = false;
    
    float timeUntilNextSpawn;
    float m_delay;
    Vector2f m_position;
    Sampler* samp;

protected:
    virtual shape spawn() = 0;

public:
    /// @param delay required in seconds
    Spawner(float delay, Vector2f position, Sampler* sampler)  {
        m_delay = delay;
        m_position = position;
        timeUntilNextSpawn = delay;
        samp = sampler;
    }

    std::optional<shape> spawnShape() {
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

class CircularSpawner : public Spawner<CircleShape> {

protected:
    float m_radius;
    float m_offset;
    Color m_color;

public:
    CircularSpawner(float delay, float radius, float offset, const Color &color, Vector2f position, Sampler *sampler) : Spawner(delay, position, sampler){
        m_radius = radius;
        m_offset = offset;
        m_color  = color;
    }

    CircleShape spawn() override {
        Vector2f offsetCenter = m_position + m_offset * normalized(samp->next2D());
        return createCircle(m_radius, offsetCenter, m_color);
    }

};

}

 
 