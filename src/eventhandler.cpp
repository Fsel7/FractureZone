#include <SFML/Graphics.hpp>

namespace sf {
    void handleEvent(Event &event, RenderWindow &window, bool *wset, bool *aset, bool *sset, bool *dset){
        if (event.type == Event::Closed)
                window.close();
            else if (event.type == Event::KeyPressed){
                switch (event.key.code){
                    case Keyboard::Key::Escape:
                    {
                        window.close();
                        break;
                    }
                    case Keyboard::Key::W:
                    {
                        *wset = true;
                        break;
                    }
                    case Keyboard::Key::S:
                    {
                        *sset = true;
                        break;
                    }
                    case Keyboard::Key::D:
                    {
                        *dset = true;
                        break;
                    }
                    case Keyboard::Key::A:
                    {
                        *aset = true;
                        break;
                    }
                }
            }
            else if (event.type == Event::KeyReleased) {
                switch (event.key.code){
                    case Keyboard::Key::W:
                    {
                        *wset = false;
                        break;
                    }
                    case Keyboard::Key::S:
                    {
                        *sset = false;
                        break;
                    }
                    case Keyboard::Key::D:
                    {
                        *dset = false;
                        break;
                    }
                    case Keyboard::Key::A:
                    {
                        *aset = false;
                        break;
                    }
                }
            }
    }

}