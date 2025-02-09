#include <mygame.hpp>

namespace sf {

    template<typename enemy>
    SpawnerUpdate Spawner<enemy>::update(const float deltaTime, const float currentTime) {
        const bool nowActive = currentTime >= m_startTime && currentTime < m_endTime;
        if (!m_active && nowActive) {
            m_active = true;
            return ACTIVE_TEXTURE;
        } else if (m_active && !nowActive) {
            m_active = false;
            return INACTIVE_TEXTURE;
        }
        if (m_active && nowActive) {
            m_timeUntilNextSpawn -= deltaTime;
            if (m_timeUntilNextSpawn <= 0) {
                m_timeUntilNextSpawn = m_delay;
                m_spawnable = true;
            }
        }
        return NO_UPDATE;
    }

    template class Spawner<CircleEnemy>;
    template class Spawner<RectangleEnemy>;

    CircularSpawner::CircularSpawner(const SpawnerData &data, const float minR, const float maxR, const Color color)
            : Spawner(data) {
        m_minRadius   = minR;
        m_maxRadius   = maxR;
        m_color       = color;
    }

    CircleEnemy CircularSpawner::spawn(Sampler& sampler) const {
        const Vector2f offsetCenter = m_position + m_offset * normalized(sampler.next2D());
        const float radius = sampler.next(m_minRadius, m_maxRadius);
        const float speed  = sampler.next(m_enemyMinSpeed, m_enemyMaxSpeed);
        if (m_color == Color::Black)
            return createCircleEnemy(speed, radius, offsetCenter, sampler.nextColor());
        return createCircleEnemy(speed, radius, offsetCenter, m_color);
    }

    RectangularSpawner::RectangularSpawner(const SpawnerData &data, const float minW, const float maxW, const float minH, const float maxH, const Color color)
            : Spawner(data) {
        m_minWidth    = minW;
        m_maxWidth    = maxW;
        m_minHeight   = minH;
        m_maxHeight   = maxH;
        m_color       = color;
    }

    RectangleEnemy RectangularSpawner::spawn(Sampler &sampler) const {
        const Vector2f offsetCenter = m_position + m_offset * normalized(sampler.next2D());
        const float width  = sampler.next(m_minWidth, m_maxWidth);
        const float height = sampler.next(m_minHeight, m_maxHeight);
        const float speed  = sampler.next(m_enemyMinSpeed, m_enemyMaxSpeed);
        if (m_color == Color::Black)
            return createRectangleEnemy(speed, width, height, offsetCenter, sampler.nextColor());
        return createRectangleEnemy(speed, width, height, offsetCenter, m_color);
    }

}
