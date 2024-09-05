#include <SFML/Graphics/CircleShape.hpp>

#pragma once

namespace sf{

class Player {

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

}
