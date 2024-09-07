#pragma once

namespace sf {

    struct Player;

    class Event;
    class RenderWindow;
    

    void handleEvent(Event &event, RenderWindow &window, Player &player);

}