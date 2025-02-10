#include <headers/math.hpp>
#include <headers/core.hpp>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#pragma once

namespace sf {

struct BonusZone : public Drawable {
    RectangleShape rectangle;
    uint64_t multiplier;
    Text label;

    void draw(RenderTarget& target, RenderStates states) const override {
        target.draw(rectangle, states);
        target.draw(label, states);
    }
};

struct BlackHole {
    Vector2f position;
    float gravity;
};

struct Player : public Drawable {

public:
    bool wset = false; 
    bool aset = false;
    bool sset = false;
    bool dset = false;

public:
    Player() { m_shape = nullptr; }

    Player(ref<Shape> &shape, const float speed) : m_shape(shape), m_speed(speed), m_originalPosition(shape->getPosition()) {}

    ~Player() = default;

    ref<Shape> getShape() const { return m_shape; }

    void move(const float deltatime, const FloatRect &bounds) {
        x_vel = dset - aset;
        y_vel = sset - wset;
        moveSelf(deltatime * m_speed * normalized(Vector2i(x_vel, y_vel)), bounds);
    }
    
    void applyGravity(std::vector<BlackHole> &blackholes, const float deltatime, const FloatRect &bounds) {
        Vector2f displacement;
        for (const BlackHole &bh : blackholes) {
            Vector2f gravity = bh.position - m_shape->getPosition();
            displacement += bh.gravity * gravity;
        }
        moveSelf(deltatime * displacement, bounds);
    }

    void reset() {
        wset = aset = sset = dset = false;
        x_vel = y_vel = 0;
        m_shape->setPosition(m_originalPosition);
    }

    void draw(RenderTarget& target, RenderStates states) const override {
        target.draw(*m_shape, states);
    }

private:
    ref<Shape> m_shape;

    int x_vel = 0;
    int y_vel = 0;
    float m_speed;

    Vector2f m_originalPosition;

private:
    void moveSelf(const Vector2f &displacement, const FloatRect &bounds) {
        m_shape->move(displacement);
        const Vector2f pos = m_shape->getPosition();
        const float newX = std::clamp(pos.x, bounds.left, bounds.left + bounds.width);
        const float newY = std::clamp(pos.y, bounds.top, bounds.top + bounds.height);
        m_shape->setPosition(Vector2f(newX, newY));
    }
};

template<typename ObjectShape>
class Enemy {

public:
    float speed;
    ObjectShape shape;

public:
    Enemy(const float speed, const ObjectShape shape) {
        this->speed = speed;
        this->shape = shape;
    }
};


class CircleEnemy : public Enemy<CircleShape> {

public:
    CircleEnemy(const float speed, const CircleShape &circle) : Enemy(speed, circle) {}
};


class RectangleEnemy : public Enemy<RectangleShape> {

public:
    RectangleEnemy(const float speed, const RectangleShape &rectangle) : Enemy(speed, rectangle) {}
};

}