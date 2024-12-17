#include <mygame.hpp>

namespace sf {

static constexpr float offsetFac = 4.f/3;

    MultilineText::MultilineText(const Vector2f position, const AlignmentStyle style, const Direction direction) {
        m_style = style;
        m_direction = direction;
        m_position = position;
    }

    void MultilineText::push_back(const Text &text) {
        m_lines.push_back(text);
    }
    
    void MultilineText::setString(const int index, const std::string &text) {
        m_lines[index].setString(text);
        alignText();
    }

    void MultilineText::draw(RenderWindow &window) const {
        for(const auto &text : m_lines)
            window.draw(text);
    }

    void MultilineText::setPosition(Vector2f position) {
        if(m_position == position)
            return;
        move(position - m_position);
        m_position = position;
    }

    void MultilineText::move(Vector2f displacement) {
        for (size_t i = 0; i < m_lines.size(); i++) {
            m_lines[i].move(displacement);
        }
    }

    void MultilineText::alignText() {
        const float lineOffset = offsetFac * m_lines[0].getCharacterSize();
        const size_t size = m_lines.size();
        const float upOffset = m_direction == DOWN ? 0 : - lineOffset * (size - 1);

        switch (m_style){
        case RIGHT:
            for (size_t i = 0; i < size; i++) 
                m_lines[i].setPosition(m_position + Vector2f(-m_lines[i].getGlobalBounds().width, i * lineOffset + upOffset));
            break;

        case CENTER:
            for (size_t i = 0; i < size; i++){
                centerText(m_lines[i], m_position);
                m_lines[i].move(Vector2f(0, i * lineOffset + upOffset));
            }
            break;

        case LEFT: default:
            for (size_t i = 0; i < size; i++) 
                m_lines[i].setPosition(m_position + Vector2f(0, i * lineOffset + upOffset));
            break;
        }

    }

// ----------------------------------------------------------------------------------------

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
        m_buttons[SETTINGS_SCREEN].push_back(createButton(offSet, "Reset Alltime Highscore", RESET_HIGHSCORE_BUTTON));
    }

    Button MenuInterface::createButton(float &offset, const std::string &label, const ButtonId buttonId){
        const RectangleShape buttonBase = createRectangle(m_buttonWidth, m_buttonHeight, Vector2f(windowCenter.x, offset), m_buttonColor, Color::Black);
        Text buttonLabel = createText(label, {0.f, 0.f}, font, Color::White);
        centerText(buttonLabel, buttonBase.getPosition());
        offset += m_buttonOffSet;
        return Button(buttonBase, buttonLabel, buttonId);
    }
    
    PopUpWindow MenuInterface::popUp(const RenderWindow &window, const std::string &text) const {
        RectangleShape popUpBase = createRectangle(1.25f * m_buttonWidth, 1.25f * m_buttonHeight, windowCenter, Color(125,125,200), Color::Black);
        Text popUpLabel = createText(text, {0.f, 0.f}, font, Color::White);
        centerText(popUpLabel, popUpBase.getPosition());
        return PopUpWindow(popUpBase, popUpLabel);
    }

    void MenuInterface::setTitle(const std::string &title) {
        RectangleShape popUpBase = createRectangle(1.5f * m_buttonWidth, m_buttonHeight, Vector2f(windowCenter.x, 0.75f * m_buttonHeight), Color(125,125,150), Color::Black);
        Text popUpLabel = createText(title, {0.f, 0.f}, font, Color::White);
        centerText(popUpLabel, popUpBase.getPosition());
        m_title = PopUpWindow(popUpBase, popUpLabel);
    }

}