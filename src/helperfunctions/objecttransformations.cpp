#include <mygame.hpp>

namespace sf {

    void centerText(Text &text, const Vector2f &center){
        const FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + 0.5f * textRect.width, textRect.top  + 0.5f * textRect.height);
        text.setPosition(center);
    }

    void centerSprite(Sprite &sprite, const Vector2f &center){
        const FloatRect textRect = sprite.getLocalBounds();
        sprite.setOrigin(textRect.left + 0.5f * textRect.width, textRect.top  + 0.5f * textRect.height);
        sprite.setPosition(center);
    }

}