#include <SFML\System\Vector2.hpp>

#pragma once

namespace sf {

    class Text;
    class Sprite;

    void centerText(Text &text, const Vector2f &center);

    void centerSprite(Sprite &sprite, const Vector2f &center);

}