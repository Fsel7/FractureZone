#include <SFML\System\Vector2.hpp>

#pragma once

// Can be used to more easily create standard objects and
// positions the shape's origin at the its centroid for more intuitive usage.

namespace sf {

    class Image;
    class Font;
    class Color;
    class Sprite;
    class Text;
    class CircleShape;
    class RectangleShape;

    Image createConstantImage(const int dimX, const int dimY, const Color &color);

    Sprite createSprite(const Image &image, const Vector2f &center);

    RectangleShape createRectangle(const float dimX, const float dimY, const Vector2f &center, const Color &fillColor);

    CircleShape createCircle(const float radius, const Vector2f &center, const Color &fillColor);

    Text createText(const std::string &text, const Vector2f &center, const Font &font, const Color &fillColor);

    Text createText(const std::string &text, const Vector2f &center, const Font &font, const Color &fillColor, const int charactersize);

}