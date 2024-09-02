#include <SFML/Graphics.hpp>

#pragma once

// Can be used to more easily create standard objects and
// positions the shape's origin at the its centroid for more intuitive usage.

namespace sf {

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

Text createText(const std::string &text, const Vector2f &center, const Font &font, const Color &fillColor) {
    Text textObj(text, font);
    textObj.setPosition(center);
    textObj.setFillColor(fillColor);
    return textObj;
}

}