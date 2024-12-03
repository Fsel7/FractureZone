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
                case Keyboard::Key::A: player.aset = true; break;
                case Keyboard::Key::S: player.sset = true; break;
                case Keyboard::Key::D: player.dset = true; break;
                case Keyboard::Key::Up:    player.wset = true; break;
                case Keyboard::Key::Left:  player.aset = true; break;
                case Keyboard::Key::Down:  player.sset = true; break;
                case Keyboard::Key::Right: player.dset = true; break;
                default:
                    break;
            }
        }
        else if (event.type == Event::KeyReleased) {
            switch (event.key.code){
                case Keyboard::Key::W: player.wset = false; break;
                case Keyboard::Key::A: player.aset = false; break;
                case Keyboard::Key::S: player.sset = false; break;               
                case Keyboard::Key::D: player.dset = false; break;
                case Keyboard::Key::Up:    player.wset = false; break;
                case Keyboard::Key::Left:  player.aset = false; break;
                case Keyboard::Key::Down:  player.sset = false; break;
                case Keyboard::Key::Right: player.dset = false; break;
                default:
                    break;
            }
        }
    }

    void awaitUnpause(Window *window, GamePhase &phase, Player &player){
        Event event;
        while (phase == PAUSED) {
            window->waitEvent(event);
            if(isKey(event, Keyboard::Key::P))
                phase = RUNNING;
            else 
                processLiveEvent(event, phase, player);
        }
    }

    void menuEvents(RenderWindow& window, GamePhase &phase, MenuInterface &menu) {
        Event event;
        auto mouse = Mouse::getPosition(window);
        window.waitEvent(event);
        auto button = menu.buttonHit(mouse, MENU_SCREEN);

        if(!button || !isLeftMouse(event))
            return;

        switch(button->id){
            case START_ROUND_BUTTON: phase = RESETTING; break;
            case SETTINGS_BUTTON:    phase = SETTINGS;  break;
            case QUIT_BUTTON:        phase = CLOSE;     break;
            default:                 phase = RESETTING; break;
        }
    }

    void settingsEvents(RenderWindow &window, Game &game, GamePhase &phase, MenuInterface &menu) {
        Event event;
        auto mouse = Mouse::getPosition(window);
        window.waitEvent(event);
        auto button = menu.buttonHit(mouse, SETTINGS_SCREEN);

        if(!button || !isLeftMouse(event))
            return;

        switch(button->id){
            case RETURN_TO_MENU_BUTTON: phase = MENU; break;
            case WINDOW_MODE_BUTTON: game.switchWindowMode(); break;
            case MAX_FPS_BUTTON: {
                int input = fetchNumberInput(window, menu, "New FPS limit: ", 30, 300);
                game.setMaxFps(input);
                break;
            }
            default:
                break;
        }
    }

    void lostEvents(RenderWindow &window, GamePhase &phase) {
        Clock clock;
        while(clock.getElapsedTime().asMilliseconds() < 3000){
            for (auto event = Event{}; window.pollEvent(event);){
                if(event.type == Event::Closed){
                    phase = CLOSE;
                    return;
                }
                if (isLeftMouse(event) || isLetter(event) || isKey(event, Keyboard::Key::Escape)) 
                    return;
            }
        }
    }

    template<typename T>
    T fetchNumberInput(RenderWindow &window, MenuInterface &menu, const std::string &prefix, const T minimum, const T maximum) {
        Event event;
        T result = 0;
        PopUpWindow popUp = menu.popUp(window, prefix + std::to_string(result));
        while (true) {
            popUp.draw(window);
            window.display();

            window.waitEvent(event);
            if(isLeftMouse(event) || isKey(event, Keyboard::Key::Enter))
                break;
            if(isBackSpace(event))
                result /= 10;
            if(isNumber(event))
                result = std::min(maximum, 10 * result + event.key.code - 26);
            popUp.setString(prefix + std::to_string(result));
        }
        result = clamp(result, minimum, maximum);
        return result;
    }

}

