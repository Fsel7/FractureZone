#pragma once

#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Text.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Window.hpp>
#include <vector>
#include <optional>

namespace sf {

enum AlignmentStyle{
    LEFT,
    CENTER,
    RIGHT,
};

enum Direction{
    DOWN,
    UP,
};

class MultilineText {

public:
    MultilineText() = default;

    MultilineText(const Vector2f position, const AlignmentStyle style, const Direction direction);

    void push_back(const Text &text);
    
    void setString(const int index, const std::string &text);

    void draw(RenderWindow &window) const;

    void setPosition(Vector2f position);

private:
    void alignText();

    void move(Vector2f displacement);

    std::vector<Text> m_lines = {};
    Vector2f m_position;
    AlignmentStyle m_style;
    Direction m_direction;

};

/// @brief Encodes the different purposes of a button.
enum ButtonId {
    START_ROUND_BUTTON,
    SETTINGS_BUTTON,
    QUIT_BUTTON,

    RETURN_TO_MENU_BUTTON,
    WINDOW_MODE_BUTTON,
    MAX_FPS_BUTTON,
    RESET_HIGHSCORE_BUTTON
};

enum MenuScreen {
    MENU_SCREEN,
    SETTINGS_SCREEN,
    SCREEN_COUNT
};


struct PopUpWindow {

protected:
    RectangleShape m_shape;
    Text m_label;

    float m_width;
    float m_height;
    float m_minX;
    float m_minY;

public:
    PopUpWindow() = default;

    PopUpWindow(const RectangleShape &popUpShape, const Text &popUpLabel)
            : m_shape(popUpShape), m_label(popUpLabel) {

        m_width = popUpShape.getSize().x;
        m_height = popUpShape.getSize().y;
    
        const Vector2f center = popUpShape.getPosition();
        m_minX = center.x - 0.5f * m_width;
        m_minY = center.y - 0.5f * m_height;
    }
    
    void draw(RenderWindow &window) const {
        window.draw(m_shape);
        window.draw(m_label);
    }

    void setString(const std::string &label) {
        m_label.setString(label);
    }
    
};

struct Button : PopUpWindow{
    ButtonId id;

    Button(const RectangleShape &buttonShape, const Text &buttonLabel, const ButtonId buttonId)
            : PopUpWindow(buttonShape, buttonLabel) {
        id = buttonId;
    }

    /// @brief Checks whether @param position is a point on the button.
    bool contains(const Vector2f position) const {
        return position.x >= m_minX && position.x <= m_minX + m_width &&
               position.y >= m_minY && position.y <= m_minY + m_height;
    }
};

class MenuInterface {

public:
    MenuInterface() {}

    MenuInterface(const Vector2u windowDimensions, const Font &buttonsFont);

    /// @brief Returns the clicked button (if any) and assumes no buttons to overlap.
    std::optional<Button> buttonHit(const Vector2f position, const MenuScreen screenId) const {
        for(const auto &button : m_buttons[screenId])
            if(button.contains(position))
                return button;
        return {};
    }

    /// @brief Draws all the buttons and their labels.
    void draw(RenderWindow &window, const MenuScreen screenId) {
        m_title.draw(window);
        for(const auto &button : m_buttons[screenId])
            button.draw(window);
    }

    /// @brief Creates the PopUpWindow responsible for displaying the title in the menu
    void setTitle(const std::string &title);

    /// @brief Spawns a pop up window
    PopUpWindow popUp(const RenderWindow &window, const std::string &text) const;

private:
    Font font;
    PopUpWindow m_title;
    
    Vector2f windowCenter;
    static constexpr float windowScaleX = 0.2f;
    static constexpr float windowScaleY = 0.1f;

    const Color m_buttonColor = Color(100, 100, 100);
    float m_buttonWidth;
    float m_buttonHeight;
    float m_buttonOffSet;

    std::vector<std::vector<Button>> m_buttons;

private:
    void createButtons();

    Button createButton(float &offset, const std::string &label, const ButtonId buttonId);
};

}