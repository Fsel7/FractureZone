#pragma once

namespace sf {

    class CircleShape;
    class RectangleShape;
    class Sprite;

    bool intersects(CircleShape* player, const RectangleShape &rectangle);

    bool intersects(CircleShape* player, const CircleShape &circle);

    bool intersects(CircleShape* player, const Sprite &sprite);

}