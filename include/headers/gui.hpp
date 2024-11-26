#pragma once

#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Text.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Window.hpp>
#include <vector>
#include <optional>

namespace sf{

/// @brief Encodes the different purposes of a button.
enum ButtonId {
    START_ROUND,
    QUIT
};

struct Button {

private:
    float width;
    float height;
    float minX;
    float minY;

    RectangleShape shape;
    Text label;

public:
    ButtonId id;

public:
    Button(RectangleShape &buttonShape, Text &buttonLabel, ButtonId buttonId) : shape(buttonShape), label(buttonLabel){
        width = buttonShape.getSize().x;
        height = buttonShape.getSize().y;
        id = buttonId;

        Vector2f center = buttonShape.getPosition();
        minX = center.x - 0.5f * width;
        minY = center.y - 0.5f * height;
    }

    /// @brief Checks whether @param position is a point on the button.
    bool contains(Vector2i position){
        return position.x >= minX && position.x <= minX + width &&
               position.y >= minY && position.y <= minY + height;
    }

    /// @brief Draws the button.
    void draw(RenderWindow &window) {
        window.draw(shape);
        window.draw(label);
    }
};

class MenuInterface {

protected:
    std::vector<Button> buttons;

    Font font;
    Vector2f windowCenter;

    float buttonWidth;
    float buttonHeight;
    float buttonOffSet;

    static constexpr float windowScaleX = 0.15f;
    static constexpr float windowScaleY = 0.1f;
    const Color buttonColor = Color(100, 100, 100);

    void createButtons();

    RectangleShape createButtonBase(const float offset);

    Text createButtonLabel(const std::string text, const RectangleShape &button);

public:
    MenuInterface() {}

    MenuInterface(Vector2u windowDimensions, Font &buttonsFont) : font(buttonsFont){
        buttonWidth = windowDimensions.x * windowScaleX;
        buttonHeight = windowDimensions.y * windowScaleY;
        buttonOffSet = 1.5f * buttonHeight;
        windowCenter = Vector2f(0.5f * windowDimensions.x, 0.5f * windowDimensions.y);
        createButtons();
    }

    /// @brief Returns the clicked button (if any) and assumes no buttons to overlap.
    std::optional<Button> buttonHit(Vector2i position){
        for(auto &button : buttons){
            if(button.contains(position))
                return button;
        }
        return {};
    }

    /// @brief Draws all the buttons and their labels.
    void draw(RenderWindow &window) {
        for(auto &button : buttons) {
            button.draw(window);
        }
    }
};


}