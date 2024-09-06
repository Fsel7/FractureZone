#include <mygame.hpp>

namespace sf {

    CircularSpawner::CircularSpawner(const SpawnerData &data, float minR, float maxR, Color color) : Spawner(data) {
        m_minRadius   = minR;
        m_maxRadius   = maxR;
        m_color       = color;
    }

    CircleEnemy CircularSpawner::spawn() {
        Vector2f offsetCenter = m_position + m_offset * normalized(sampler->next2D());
        float radius = sampler->next(m_minRadius, m_maxRadius);
        float speed  = sampler->next(m_enemyMinSpeed, m_enemyMaxSpeed);
        if (m_color == Color::Black)
            return createCircleEnemy(speed, radius, offsetCenter, sampler->nextColor());
        return createCircleEnemy(speed, radius, offsetCenter, m_color);
    }

    RectangularSpawner::RectangularSpawner(const SpawnerData &data, float minW, float maxW, float minH, float maxH, Color color) : Spawner(data) {
        m_minWidth    = minW;
        m_maxWidth    = maxW;
        m_minHeight   = minH;
        m_maxHeight   = maxH;
        m_color       = color;
    }

    RectangleEnemy RectangularSpawner::spawn() {
        Vector2f offsetCenter = m_position + m_offset * normalized(sampler->next2D());
        float width  = sampler->next(m_minWidth, m_maxWidth);
        float height = sampler->next(m_minHeight, m_maxHeight);
        float speed  = sampler->next(m_enemyMinSpeed, m_enemyMaxSpeed);
        if (m_color == Color::Black)
            return createRectangleEnemy(speed, width, height, offsetCenter, sampler->nextColor());
        return createRectangleEnemy(speed, width, height, offsetCenter, m_color);
    }

}
