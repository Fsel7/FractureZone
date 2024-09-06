#include <mygame.hpp>

namespace sf {

    CircularSpawner::CircularSpawner(const SpawnerData &data, const Color &color, bool randomColor, float minR, float maxR) : Spawner(data) {
        m_minRadius   = minR;
        m_maxRadius   = maxR;
        m_color       = color,
        m_randomColor = randomColor;
    }

    CircleEnemy CircularSpawner::spawn() {
        Vector2f offsetCenter = m_position + m_offset * normalized(sampler->next2D());
        float radius = sampler->next(m_minRadius, m_maxRadius);
        float speed  = sampler->next(m_enemyMinSpeed, m_enemyMaxSpeed);
        if (m_randomColor)
            return createCircleEnemy(speed, radius, offsetCenter, sampler->nextColor());
        return createCircleEnemy(speed, radius, offsetCenter, m_color);
    }

    RectangularSpawner::RectangularSpawner(const SpawnerData &data, const Color &color, bool randomColor, float minW, float maxW, float minH, float maxH) : Spawner(data) {
        m_minWidth    = minW;
        m_maxWidth    = maxW;
        m_minHeight   = minH;
        m_maxHeight   = maxH;
        m_color       = color,
        m_randomColor = randomColor;
    }

    RectangleEnemy RectangularSpawner::spawn() {
        Vector2f offsetCenter = m_position + m_offset * normalized(sampler->next2D());
        float width  = sampler->next(m_minWidth, m_maxWidth);
        float height = sampler->next(m_minHeight, m_maxHeight);
        float speed  = sampler->next(m_enemyMinSpeed, m_enemyMaxSpeed);
        if (m_randomColor)
            return createRectangleEnemy(speed, width, height, offsetCenter, sampler->nextColor());
        return createRectangleEnemy(speed, width, height, offsetCenter, m_color);
    }

}
