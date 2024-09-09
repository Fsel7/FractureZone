#pragma once

namespace sf {

    class CircleShape;
    class RectangleShape;
    class Sprite;

    bool intersects(CircleShape* player, const RectangleShape &rectangle);

    bool intersects(CircleShape* player, const CircleShape &circle2);

    bool intersects(CircleShape* player, const Sprite &sprite);

}