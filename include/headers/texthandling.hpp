#include <SFML\System\Vector2.hpp>

#pragma once

namespace sf {

    class Game;
    class Font;
    class Text;

    void textSetup(Game &game, Font &font);

    void centerText(Text &text, const Vector2f &center);

}