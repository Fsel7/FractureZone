#include <SFML/Graphics/CircleShape.hpp>

#pragma once


struct Player {

    sf::CircleShape shape; 
    const float speed = 9;
    float x_vel = 0;
    float y_vel = 0;

    bool wset = false; 
    bool aset = false;
    bool sset = false;
    bool dset = false;
};
