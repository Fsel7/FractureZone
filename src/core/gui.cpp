#include <mygame.hpp>

namespace sf {

    MenuInterface::MenuInterface(const Vector2u windowDimensions, const Font &buttonsFont) : font(buttonsFont) {
        windowCenter = Vector2f(0.5f * windowDimensions.x, 0.5f * windowDimensions.y);

        m_buttonWidth = windowDimensions.x * windowScaleX;
        m_buttonHeight = windowDimensions.y * windowScaleY;
        m_buttonOffSet = 1.5f * m_buttonHeight;
        
        m_buttons = std::vector<std::vector<Button>>(SCREEN_COUNT, std::vector<Button>{});
        createButtons();
    }

    void MenuInterface::createButtons(){
        float offSet = 2.f * m_buttonOffSet;

        m_buttons[MENU_SCREEN].push_back(createButton(offSet, "Start Next Round", START_ROUND_BUTTON));
        m_buttons[MENU_SCREEN].push_back(createButton(offSet, "Settings", SETTINGS_BUTTON));
        m_buttons[MENU_SCREEN].push_back(createButton(offSet, "Quit Game", QUIT_BUTTON));

        offSet = 2.f * m_buttonOffSet;

        m_buttons[SETTINGS_SCREEN].push_back(createButton(offSet, "Return To Menu", RETURN_TO_MENU_BUTTON));
        m_buttons[SETTINGS_SCREEN].push_back(createButton(offSet, "Flip Window Mode", WINDOW_MODE_BUTTON));
        m_buttons[SETTINGS_SCREEN].push_back(createButton(offSet, "Set Max FPS", MAX_FPS_BUTTON));
    }

    Button MenuInterface::createButton(float &offset, const std::string label, const ButtonId buttonId){
        const RectangleShape buttonBase = createRectangle(m_buttonWidth, m_buttonHeight, Vector2f(windowCenter.x, offset), m_buttonColor, Color::Black);
        Text buttonLabel = createText(label, {0.f, 0.f}, font, Color::White);
        centerText(buttonLabel, buttonBase.getPosition());
        offset += m_buttonOffSet;
        return Button(buttonBase, buttonLabel, buttonId);
    }
    
    PopUpWindow MenuInterface::popUp(const RenderWindow &window, const std::string text) const {
        RectangleShape popUpBase = createRectangle(1.25f * m_buttonWidth, 1.25f * m_buttonHeight, windowCenter, Color(125,125,200), Color::Black);
        Text popUpLabel = createText(text, {0.f, 0.f}, font, Color::White);
        centerText(popUpLabel, popUpBase.getPosition());
        return PopUpWindow(popUpBase, popUpLabel);
    }

}