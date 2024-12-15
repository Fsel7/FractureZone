#include <mygame.hpp>

namespace sf {

    Text createSimpleText(const std::string &text, const Font &font, const Color &fillColor, const uint32_t charactersize) {
        Text textObj(text, font, charactersize);
        textObj.setFillColor(fillColor);
        return textObj;
    }

    Text createText(const std::string &text, const Vector2f center, const Font &font, const Color &fillColor, const Color &borderColor) {
        Text textObj(text, font, fontSize);
        textObj.setPosition(center);
        textObj.setFillColor(fillColor);
        textObj.setOutlineColor(borderColor);
        return textObj;
    }

    Text createText(const std::string &text, const Vector2f center, const Font &font, const Color &fillColor, const uint32_t charactersize, const Color &borderColor) {
        Text textObj(text, font, charactersize);
        textObj.setPosition(center);
        textObj.setFillColor(fillColor);
        textObj.setOutlineColor(borderColor);
        return textObj;
    }

    Image createConstantImage(const uint32_t dimX, const uint32_t dimY, const Color &color) {
        Image img;
        img.create(dimX, dimY, color);
        return img;
    }

    Sprite createSprite(const Image &image, const Vector2f center) {
        Texture tex;
        tex.loadFromImage(image);
        Sprite sprite(tex);
        sprite.setOrigin({0.5f * image.getSize().x, 0.5f * image.getSize().y});
        sprite.setPosition(center);
        return sprite;
    }

    BlackHole createBlackHole(const Vector2f position, const float gravity) {
        return {position, gravity};
    }

    RectangleShape createRectangle(const float dimX, const float dimY, const Vector2f center, const Color &fillColor, const Color &borderColor) {
        RectangleShape rectangle({dimX, dimY});
        rectangle.setOrigin(Vector2f(0.5f * dimX, 0.5f * dimY));
        rectangle.setPosition(center);
        rectangle.setFillColor(fillColor);
        rectangle.setOutlineColor(borderColor);
        return rectangle;
    }

    CircleShape createCircle(const float radius, const Vector2f center, const Color &fillColor, const Color &borderColor) {
        CircleShape circle(radius);
        circle.setOrigin(Vector2f(radius, radius));
        circle.setPosition(center);
        circle.setFillColor(fillColor);
        circle.setOutlineColor(borderColor);
        return circle;
    }

    CircleEnemy createCircleEnemy(const float speed, const float radius, const Vector2f center, const Color &fillColor, const Color &borderColor) {
        return CircleEnemy(speed, createCircle(radius, center, fillColor, borderColor));
    }

    RectangleEnemy createRectangleEnemy(const float speed, const float dimX, const float dimY, const Vector2f center, const Color &fillColor, const Color &borderColor) {
        return RectangleEnemy(speed, createRectangle(dimX, dimY, center, fillColor, borderColor));
    }


}