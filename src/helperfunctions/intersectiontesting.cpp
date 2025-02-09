#include <mygame.hpp>

namespace sf {

    bool intersects(const CircleShape &player, const RectangleShape &rectangle) {
        auto size = rectangle.getSize();
        float width = 0.5f * size.x;
        float height = 0.5f * size.y;
        Vector2f rcenter = rectangle.getPosition();

        float radius = player.getRadius();
        auto ccenter = player.getPosition();

        float dist_x = std::abs(ccenter.x - rcenter.x);
        float dist_y = std::abs(ccenter.y - rcenter.y);

        if (dist_x > width + radius || dist_y > height + radius)
            return false;

        if (dist_x <= width || dist_y <= height)
            return true;

        float cornerDistance_sq = (dist_x - width) * (dist_x - width) + (dist_y - height) * (dist_y - height);

        return (cornerDistance_sq <= radius * radius);
    }

    bool intersects(const CircleShape &player, const CircleShape &circle) {
        return length(player.getPosition() - circle.getPosition()) <= player.getRadius() + circle.getRadius();
    }

    // bool intersects(const CircleShape &player, const Sprite &sprite) {
    //     // TODO: Implement me!
    //     return false;
    // }

}