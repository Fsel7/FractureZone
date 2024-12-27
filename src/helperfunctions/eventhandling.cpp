#include <mygame.hpp>

namespace sf {

    inline bool isLeftMouse(const Event &event) {
        return event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left;
    }

    inline bool isKey(const Event &event, const Keyboard::Key key) {
        return event.type == Event::KeyPressed && event.key.code == key;
    }

    inline bool isBackSpace(const Event &event) {
        return event.type == Event::KeyPressed && (event.key.code == Keyboard::Key::BackSpace || event.key.code == Keyboard::Key::Backspace);
    }

    inline bool isNumber(const Event &event) {
        return event.type == Event::KeyPressed && event.key.code >= 26 && event.key.code <= 35;
    }

    inline bool isLetter(const Event &event) {
        return event.type == Event::KeyPressed && event.key.code <= 25;
    }

    inline Vector2f getMousePos(const Game &game) {
        const Vector2i mouse = Mouse::getPosition(*game.window);
        const Vector2f scale = game.getWindowScale();
        return Vector2f(scale.x * mouse.x, scale.y * mouse.y);
    }

    template<typename T>
    T fetchNumberInput(RenderWindow &window, const MenuInterface &menu, const std::string &prefix, const T minimum, const T maximum) {
        Event event;
        T result = 0;
        PopUpWindow popUp = menu.popUp(prefix + std::to_string(result));
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
        result = std::clamp(result, minimum, maximum);
        return result;
    }

    bool processEvents(RenderWindow &window, GamePhase &phase, Player &player){
        bool wasPaused = false;
        for (auto event = Event{}; window.pollEvent(event);)
            processLiveEvent(event, phase, player);
        if(phase == PAUSED){
            wasPaused = true;
            awaitUnpause(window, phase, player);
        }
        return wasPaused;       
    }

    void processLiveEvent(const Event &event, GamePhase &phase, Player &player) {
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

    void awaitUnpause(RenderWindow &window, GamePhase &phase, Player &player){
        Event event;
        while (phase == PAUSED) {
            window.waitEvent(event);
            if(isKey(event, Keyboard::Key::P))
                phase = RUNNING;
            else 
                processLiveEvent(event, phase, player);
        }
    }

    void menuEvents(RenderWindow& window, const Game &game, GamePhase &phase, const MenuInterface &menu) {
        Event event;
        window.waitEvent(event);
        if (event.type == Event::Closed) {
            phase = CLOSE;
            return;
        }

        auto button = menu.buttonHit(getMousePos(game), MENU_SCREEN);
        if(!button || !isLeftMouse(event))
            return;

        switch(button->id){
            case START_ROUND_BUTTON: phase = RESETTING; break;
            case SETTINGS_BUTTON:    phase = SETTINGS;  break;
            case QUIT_BUTTON:        phase = CLOSE;     break;
            default:                 phase = RESETTING; break;
        }
    }

    void settingsEvents(RenderWindow &window, Game &game, GamePhase &phase, const MenuInterface &menu, IniManager &ini) {
        Event event;
        window.waitEvent(event);
        if (event.type == Event::Closed) {
            phase = CLOSE;
            return;
        }

        auto button = menu.buttonHit(getMousePos(game), SETTINGS_SCREEN);
        if(!button || !isLeftMouse(event))
            return;

        switch(button->id){
            case RETURN_TO_MENU_BUTTON: phase = MENU; break;
            case WINDOW_MODE_BUTTON: game.switchWindowMode(); break;
            case MAX_FPS_BUTTON: {
                const int input = fetchNumberInput(window, menu, "New FPS limit: ", 30, 300);
                game.setMaxFps(input);
                break;
            }
            case RESET_HIGHSCORE_BUTTON: {
                ini.resetHighScore();
                game.setAllTimeHighscore(1);
                break;
            }
            default:
                break;
        }
    }

    void lostEvents(RenderWindow &window, GamePhase &phase) {
        Event event;
        Clock clock;
        while(clock.getElapsedTime().asMilliseconds() < 8000){
            if(!window.pollEvent(event))
                continue;
            if(event.type == Event::Closed){
                phase = CLOSE;
                return;
            }
            if (isLeftMouse(event) || isLetter(event) || isKey(event, Keyboard::Key::Escape)) 
                return;
        }
    }

}

