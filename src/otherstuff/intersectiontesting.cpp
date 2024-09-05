#include <mygame.hpp>

namespace sf {

    bool intersects(const CircleShape &circle, const RectangleShape &rectangle){
        auto size = rectangle.getSize();
        float width = 0.5f * size.x;
        float height = 0.5f * size.y;
        Vector2f rcenter = rectangle.getPosition();

        float radius = circle.getRadius();
        auto ccenter = circle.getPosition();

        float dist_x = std::abs(ccenter.x - rcenter.x);
        float dist_y = std::abs(ccenter.y - rcenter.y);

        if (dist_x > width + radius || dist_y > height + radius)
            return false;

        if (dist_x <= width || dist_y <= height)
            return true;

        float cornerDistance_sq = (dist_x - width) * (dist_x - width) + (dist_y - height) * (dist_y - height);

        return (cornerDistance_sq <= radius * radius);
    }

    bool intersects(const CircleShape &circle1, const CircleShape &circle2){
        return length(circle1.getPosition() - circle2.getPosition()) <= circle1.getRadius() + circle2.getRadius();
    }

    bool intersects(const CircleShape &circle, const Sprite &sprite){
        // TODO: Implement me!
        return false;
    }

    bool collision(CircleShape &player, Game &game){
        bool hitsEnemy = false;
        for(auto enemy : game.circularEnemies)
            if(intersects(player, enemy.shape))
                return true;
        for(auto enemy : game.rectangularEnemies)
            if(intersects(player, enemy.shape))
                return true;
        for(auto enemy : game.spriteEnemies)
            if(intersects(player, enemy))
                return true;
        return false;
    }

}