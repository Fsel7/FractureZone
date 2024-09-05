#include <mygame.hpp>

namespace sf {

    void centerText(Text &text, const Vector2f &center){
        FloatRect textRect = text.getLocalBounds();
        text.setFillColor(Color::Red);
        text.setOrigin(textRect.left + 0.5f * textRect.width, textRect.top  + 0.5f * textRect.height);
        text.setPosition(center);
    }

}