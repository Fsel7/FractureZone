#include <mygame.hpp>

namespace sf {

    Text createText(const std::string &text, const Vector2f &center, const Font &font, const Color &fillColor) {
        Text textObj(text, font, fontSize);
        textObj.setPosition(center);
        textObj.setFillColor(fillColor);
        return textObj;
    }

    Text createText(const std::string &text, const Vector2f &center, const Font &font, const Color &fillColor, const int charactersize) {
        Text textObj(text, font, charactersize);
        textObj.setPosition(center);
        textObj.setFillColor(fillColor);
        return textObj;
    }

    Image createConstantImage(const int dimX, const int dimY, const Color &color) {
        Image img;
        img.create(dimX, dimY, color);
        return img;
    }

    Sprite createSprite(const Image &image, const Vector2f &center) {
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

    RectangleShape createRectangle(const float dimX, const float dimY, const Vector2f &center, const Color &fillColor) {
        RectangleShape rectangle({dimX, dimY});
        rectangle.setOrigin(Vector2f(dimX/2, dimY/2));
        rectangle.setPosition(center);
        rectangle.setFillColor(fillColor);
        return rectangle;
    }

    CircleShape createCircle(const float radius, const Vector2f &center, const Color &fillColor) {
        CircleShape circle(radius);
        circle.setOrigin(Vector2f(radius, radius));
        circle.setPosition(center);
        circle.setFillColor(fillColor);
        return circle;
    }

    CircleEnemy createCircleEnemy(const float speed, const float radius, const Vector2f &center, const Color &fillColor) {
        return CircleEnemy(speed, createCircle(radius, center, fillColor));
    }

    RectangleEnemy createRectangleEnemy(const float speed, const float dimX, const float dimY, const Vector2f &center, const Color &fillColor) {
        return RectangleEnemy(speed, createRectangle(dimX, dimY, center, fillColor));
    }


}