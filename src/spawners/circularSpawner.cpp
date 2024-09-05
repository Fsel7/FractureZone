#include <mygame.hpp>

namespace sf {

    CircularSpawner::CircularSpawner(float delay, float radius, float offset, const Color &color, Vector2f position, Sampler *sampler, bool randomColor = false)
        : Spawner(delay, position, sampler) {
        m_randomColor = randomColor;
        m_radius      = radius;
        m_offset      = offset;
        m_color       = color;
    }

    CircleShape CircularSpawner::spawn() {
        Vector2f offsetCenter = m_position + m_offset * normalized(sampler->next2D());
        if (m_randomColor)
            return createCircle(m_radius, offsetCenter, sampler->nextColor());
        return createCircle(m_radius, offsetCenter, m_color);
    }

}
