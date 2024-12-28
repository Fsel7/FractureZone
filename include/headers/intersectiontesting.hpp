#pragma once

namespace sf {

    class CircleShape;
    class RectangleShape;
    class Sprite;

    bool intersects(const CircleShape &player, const RectangleShape &rectangle);

    bool intersects(const CircleShape &player, const CircleShape &circle);

    // bool intersects(const CircleShape &player, const Sprite &sprite);

}