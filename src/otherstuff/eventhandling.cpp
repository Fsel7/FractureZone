#include <mygame.hpp>

namespace sf {

    bool processEvents(Window *window, GamePhase &phase, Player &player){
        bool wasPaused = false;
        for (auto event = Event{}; window->pollEvent(event);)
            processLiveEvent(event, phase, player);
        if(phase == PAUSED){
            wasPaused = true;
            awaitUnpause(window, phase, player);
        }
        return wasPaused;       
    }

    void processLiveEvent(Event &event, GamePhase &phase, Player &player) {
        if (event.type == Event::Closed)
            phase = CLOSE;
        else if (event.type == Event::KeyPressed){
            switch (event.key.code){
                case Keyboard::Key::Escape:
                    phase = MENU; break;
                case Keyboard::Key::P: phase = PAUSED; break;
                case Keyboard::Key::W: player.wset = true; break;
                case Keyboard::Key::S: player.sset = true; break;
                case Keyboard::Key::A: player.aset = true; break;
                case Keyboard::Key::D: player.dset = true; break;
                case Keyboard::Key::Up:    player.wset = true; break;
                case Keyboard::Key::Down:  player.sset = true; break;
                case Keyboard::Key::Left:  player.aset = true; break;
                case Keyboard::Key::Right: player.dset = true; break;
            }
        }
        else if (event.type == Event::KeyReleased) {
            switch (event.key.code){
                case Keyboard::Key::W: player.wset = false; break;
                case Keyboard::Key::S: player.sset = false; break;
                case Keyboard::Key::A: player.aset = false; break;
                case Keyboard::Key::D: player.dset = false; break;
                case Keyboard::Key::Up:    player.wset = false; break;
                case Keyboard::Key::Down:  player.sset = false; break;
                case Keyboard::Key::Left:  player.aset = false; break;
                case Keyboard::Key::Right: player.dset = false; break;
            }
        }
    }

    void awaitUnpause(Window *window, GamePhase &phase, Player &player){
        Event event;
        while (phase == PAUSED) {
            window->waitEvent(event);
            if(event.type == Event::KeyPressed && event.key.code == Keyboard::Key::P){
                phase = RUNNING;
            } else {
                processLiveEvent(event, phase, player);
            }
        }
    }

    void menuEvents(RenderWindow& window, GamePhase &phase, MenuInterface &menu) {
        Event event;
        while(true){
            auto mouse = Mouse::getPosition(window);
            window.waitEvent(event);
            auto button = menu.buttonHit(mouse);
            if(event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left && button) {
                switch(button->id){
                    case START_ROUND: phase = RESETTING; break;
                    case QUIT:        phase = CLOSE;     break;
                    default:
                        phase = RESETTING;
                }
                break;
            } 
        }
    }

    void lostEvents(RenderWindow &window, GamePhase &phase) {
        Clock clock;
        bool keyPresed = false;
        while(clock.getElapsedTime().asMilliseconds() < 3000 && !keyPresed){
            for (auto event = Event{}; window.pollEvent(event);){
                if(event.type == Event::Closed){
                    phase = CLOSE;
                    keyPresed = true;
                    break;
                }
                bool letterOrEsc = event.key.code == Keyboard::Key::Escape || event.key.code <= 25;
                bool leftMouse = event.key.code == Mouse::Left;
                if ((event.type == Event::KeyPressed && letterOrEsc) ||
                    (event.type == Event::MouseButtonPressed && leftMouse)) {
                    keyPresed = true;
                    break;
                }
            }
        }
    }
}

