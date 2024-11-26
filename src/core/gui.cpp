#include <mygame.hpp>

namespace sf {

    void MenuInterface::createButtons(){
        float offSet = 2.f * buttonOffSet;
        Color buttonColor = Color(100, 100, 100);
        
        RectangleShape button1 = createButtonBase(offSet);
        Text label1 = createButtonLabel("Start Next Round", button1);
        buttons.push_back(Button(button1, label1, ButtonId::START_ROUND));

        offSet += buttonOffSet;

        RectangleShape button2 = createButtonBase(offSet);
        Text label2 = createButtonLabel("Quit Game", button2);
        buttons.push_back(Button(button2, label2, ButtonId::QUIT));
    }

    RectangleShape MenuInterface::createButtonBase(const float offset) {
        return createRectangle(buttonWidth, buttonHeight, Vector2f(windowCenter.x, offset), buttonColor, Color::Black);
    }

    Text MenuInterface::createButtonLabel(const std::string text, const RectangleShape &button) {
        Text label = createText(text, {0.f, 0.f}, font, Color::White);
        centerText(label, button.getPosition());
        return label;
    }

}