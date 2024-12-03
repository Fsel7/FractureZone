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
    START_ROUND_BUTTON,
    SETTINGS_BUTTON,
    QUIT_BUTTON,

    RETURN_TO_MENU_BUTTON,
    SET_MAX_FPS_BUTTON
};

enum MenuScreen {
    MENU_SCREEN,
    SETTINGS_SCREEN,
    SCREEN_COUNT
};

struct PopUpWindow {

protected:
    RectangleShape shape;
    Text label;

    float width;
    float height;
    float minX;
    float minY;

public:
    PopUpWindow(RectangleShape &popUpShape, Text &popUpLabel) :
        shape(popUpShape), label(popUpLabel) {
        width = popUpShape.getSize().x;
        height = popUpShape.getSize().y;
    
        Vector2f center = popUpShape.getPosition();
        minX = center.x - 0.5f * width;
        minY = center.y - 0.5f * height;
    }
    
    void draw(RenderWindow &window) {
        window.draw(shape);
        window.draw(label);
    }
    
};

struct Button : PopUpWindow{

private:


public:
    ButtonId id;

public:
    Button(RectangleShape &buttonShape, Text &buttonLabel, ButtonId buttonId) : PopUpWindow(buttonShape, buttonLabel) {
        id = buttonId;
    }

    /// @brief Checks whether @param position is a point on the button.
    bool contains(Vector2i position){
        return position.x >= minX && position.x <= minX + width &&
               position.y >= minY && position.y <= minY + height;
    }
};

class MenuInterface {

protected:
    std::vector<std::vector<Button>> buttons;

    Font font;
    Vector2f windowCenter;

    float buttonWidth;
    float buttonHeight;
    float buttonOffSet;

    static constexpr float windowScaleX = 0.15f;
    static constexpr float windowScaleY = 0.1f;
    const Color buttonColor = Color(100, 100, 100);

    void createButtons();

    Button createButton(float &offset, const std::string label, ButtonId buttonId);

public:
    MenuInterface() {}

    MenuInterface(Vector2u windowDimensions, Font &buttonsFont) : font(buttonsFont){
        windowCenter = Vector2f(0.5f * windowDimensions.x, 0.5f * windowDimensions.y);

        buttonWidth = windowDimensions.x * windowScaleX;
        buttonHeight = windowDimensions.y * windowScaleY;
        buttonOffSet = 1.5f * buttonHeight;
        
        buttons = std::vector<std::vector<Button>>(SCREEN_COUNT, std::vector<Button>{});
        createButtons();
    }

    /// @brief Returns the clicked button (if any) and assumes no buttons to overlap.
    std::optional<Button> buttonHit(Vector2i position, MenuScreen screenId){
        for(auto &button : buttons[screenId]){
            if(button.contains(position))
                return button;
        }
        return {};
    }

    /// @brief Draws all the buttons and their labels.
    void draw(RenderWindow &window, MenuScreen screenId) {
        for(auto &button : buttons[screenId]) {
            button.draw(window);
        }
    }

    /// @brief Spawns a pop up window, despawning after clicking or after some time.
    void popUp(RenderWindow &window, const std::string text, const int milliseconds = 1500);
};

}