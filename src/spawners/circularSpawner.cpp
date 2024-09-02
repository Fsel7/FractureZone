#include <mygame.hpp>

namespace sf {

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

    CircleShape spawn() override{
        Vector2f offsetCenter = m_position + m_offset * normalized(samp->next2D());
        return createCircle(m_radius, offsetCenter, m_color);
    }

};

}
