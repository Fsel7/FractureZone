#pragma once

namespace sf {

    class Game;
    class Shape;
    class CircleShape;
    class RectangleShape;
    class Sprite;

    bool intersects(CircleShape* player, const RectangleShape &rectangle);

    bool intersects(CircleShape* player, const CircleShape &circle2);

    bool intersects(CircleShape* player, const Sprite &sprite);

    bool collision(Player &player, const Game &game);

}