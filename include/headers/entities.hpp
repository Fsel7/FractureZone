#include <headers/math.hpp>
#include <headers/core.hpp>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#pragma once

namespace sf {

struct BlackHole {
    Vector2f position;
    float gravity;
};

struct Player {

    Shape* shape; 
    float speed;

    int x_vel = 0;
    int y_vel = 0;

    bool wset = false; 
    bool aset = false;
    bool sset = false;
    bool dset = false;

    Player() { shape = nullptr; }
    Player(Shape* shapeZ, float speedZ) : shape(shapeZ), speed(speedZ) {}

    ~Player() { delete shape; }

    void move(float deltatime, FloatRect &bounds) {
        x_vel = dset - aset;
        y_vel = sset - wset;
        shape->move(deltatime * speed * normalized(Vector2i(x_vel, y_vel)));
        
        auto pos = shape->getPosition();
        float newX = std::clamp(pos.x, bounds.left, bounds.left + bounds.width);
        float newY = std::clamp(pos.y, bounds.top, bounds.top + bounds.height);
        shape->setPosition(Vector2f(newX, newY));
    }

    void applyMovement(Vector2f &displacement) {
        shape->move(displacement);
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