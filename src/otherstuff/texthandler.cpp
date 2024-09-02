#include <mygame.hpp>

namespace sf {

    void textSetup(Game &game, Font &font) {
        game.score    = createText("", top_left,                        font, Color::Red);
        game.minScore = createText("", top_left    + line_offset,       font, Color::Yellow);
        game.gTime    = createText("", bottom_left - line_offset,       font, Color::Cyan);
        game.pTime    = createText("", bottom_left - 2.f * line_offset, font, Color::Cyan);
    }

    void centerText(Text &text, const Vector2f &center){
        FloatRect textRect = text.getLocalBounds();
        text.setFillColor(Color::Red);
        text.setOrigin(textRect.left + 0.5f * textRect.width, textRect.top  + 0.5f * textRect.height);
        text.setPosition(center);
    }

}