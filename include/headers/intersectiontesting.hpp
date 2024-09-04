#pragma once

namespace sf {

    class Game;
    class CircleShape;
    class RectangleShape;
    class Sprite;

    bool intersects(const CircleShape &circle, const RectangleShape &rectangle);

    bool intersects(const CircleShape &circle1, const CircleShape &circle2);

    bool intersects(const CircleShape &circle, const Sprite &sprite);

    bool collision(CircleShape &player, Game &game);

}