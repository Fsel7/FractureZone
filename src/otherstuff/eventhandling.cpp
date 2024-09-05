#include <mygame.hpp>

namespace sf {

    void handleEvent(Event &event, RenderWindow &window, Player &player){
        if (event.type == Event::Closed)
            window.close();
        else if (event.type == Event::KeyPressed){
            switch (event.key.code){
                case Keyboard::Key::Escape:
                    window.close();
                    break;
                case Keyboard::Key::W:
                    player.wset = true;
                    break;
                case Keyboard::Key::S:
                    player.sset = true;
                    break;
                case Keyboard::Key::D:
                    player.dset = true;
                    break;
                case Keyboard::Key::A:
                    player.aset = true;
                    break;
            }
        }
        else if (event.type == Event::KeyReleased) {
            switch (event.key.code){
                case Keyboard::Key::W:
                    player.wset = false;
                        break;
                case Keyboard::Key::S:
                    player.sset = false;
                    break;
                case Keyboard::Key::D:
                    player.dset = false;
                    break;
                case Keyboard::Key::A:
                    player.aset = false;
                    break;
            }
        }
    }
}

