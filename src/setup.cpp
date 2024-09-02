#include <SFML/Graphics.hpp>

namespace sf {
size_t window_x = 1200u;
size_t window_y = 900u;

Vector2f origin = {0.f, 0.f};
Font myFont;

bool runsetup(){
    if (!myFont.loadFromFile("fonts/arial.ttf"))
        return false;


    return true;
}


}
