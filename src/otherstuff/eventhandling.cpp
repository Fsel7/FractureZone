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
            auto button = menu.buttonHit(mouse, MENU_SCREEN);
            if(event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left && button) {
                switch(button->id){
                    case START_ROUND_BUTTON: phase = RESETTING; break;
                    case SETTINGS_BUTTON:    phase = SETTINGS;  break;
                    case QUIT_BUTTON:        phase = CLOSE;     break;
                    default:
                        phase = RESETTING;
                }
                break;
            } 
        }
    }

    void settingsEvents(RenderWindow &window, Game &game, GamePhase &phase, MenuInterface &menu) {
        Event event;
        while(true){
            auto mouse = Mouse::getPosition(window);
            window.waitEvent(event);
            auto button = menu.buttonHit(mouse, SETTINGS_SCREEN);
            if(event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left && button) {
                switch(button->id){
                    case RETURN_TO_MENU_BUTTON: phase = MENU; break;
                    case SET_MAX_FPS_BUTTON: {
                        int input = parseIntInput(window);
                        menu.popUp(window, "Input: " + std::to_string(input));
                        game.setMaxFps(input);
                        break;
                    }
                    default:
                        break;
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
                if (leftMouseOrKey(event)) {
                    keyPresed = true;
                    break;
                }
            }
        }
    }

    int parseIntInput(RenderWindow &window) {
        Event event;
        int result = 0;
        while (true) {
            window.waitEvent(event);
            if(leftMouseOrButton(event, Keyboard::Key::Enter))
                break;
            if(event.type != Event::KeyPressed || event.key.code < 26 || event.key.code > 35)
                continue;
            result = 10 * result + event.key.code - 26;
        }
        return result;
    }

}

