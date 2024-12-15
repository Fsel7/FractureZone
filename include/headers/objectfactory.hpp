#include <SFML\System\Vector2.hpp>

#pragma once

// Can be used to more easily create standard objects and
// positions the shape's origin at the its centroid for more intuitive usage.

namespace sf {

    struct BlackHole;
    
    class Image;
    class Font;
    class Color;
    class Sprite;
    class Text;
    class CircleShape;
    class CircleEnemy;
    class RectangleShape;
    class RectangleEnemy;

    Text createSimpleText(const std::string &text, const Font &font, const Color &fillColor, const uint32_t charactersize);
    Text createText(const std::string &text, const Vector2f center, const Font &font, const Color &fillColor, const Color &borderColor = Color::Transparent);
    Text createText(const std::string &text, const Vector2f center, const Font &font, const Color &fillColor, const uint32_t charactersize, const Color &borderColor = Color::Transparent);

    Image createConstantImage(const uint32_t dimX, const uint32_t dimY, const Color &color);

    Sprite createSprite(const Image &image, const Vector2f center);

    BlackHole createBlackHole(const Vector2f position, const float gravity);

    RectangleShape createRectangle(const float dimX, const float dimY, const Vector2f center, const Color &fillColor, const Color &borderColor = Color::Transparent);
    RectangleEnemy createRectangleEnemy(const float speed, const float dimX, const float dimY, const Vector2f center, const Color &fillColor, const Color &borderColor = Color::Transparent);

    CircleShape createCircle(const float radius, const Vector2f center, const Color &fillColor, const Color &borderColor = Color::Transparent);
    CircleEnemy createCircleEnemy(const float speed, const float radius, const Vector2f center, const Color &fillColor, const Color &borderColor = Color::Transparent);



}