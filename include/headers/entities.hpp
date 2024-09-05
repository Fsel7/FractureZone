#include <headers/math.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#pragma once

namespace sf {

struct BlackHole {
    Vector2f position;
    float gravity;
};

struct Player {
    CircleShape shape; 
    const float speed = 9;
    float x_vel = 0;
    float y_vel = 0;

    bool wset = false; 
    bool aset = false;
    bool sset = false;
    bool dset = false;

    void move(float deltatime) {
        x_vel = (dset ? 1.f : 0.f) + (aset ? -1.f : 0.f);
        y_vel = (sset ? 1.f : 0.f) + (wset ? -1.f : 0.f);
        shape.move(deltatime * speed * normalized(Vector2f(x_vel, y_vel)));
    }

    void applyMovement(Vector2f &displacement) {
        shape.move(displacement);
    }
};

template<typename obj_shape>
class Enemy {

public:
    float speed;
    obj_shape shape;

public:
    Enemy(float speed, obj_shape shape){
        this->speed = speed;
        this->shape = shape;
    }
};


class CircleEnemy : public Enemy<CircleShape> {

public:
    CircleEnemy(float speed, CircleShape circle) : Enemy(speed, circle) {}
};


class RectangleEnemy : public Enemy<RectangleShape> {

public:
    RectangleEnemy(float speed, RectangleShape rectangle) : Enemy(speed, rectangle) {}
};


}