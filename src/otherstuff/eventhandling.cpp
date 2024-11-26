#include <mygame.hpp>

namespace sf {

    bool processEvents(Game &game, Player &player){
        bool wasPaused = false;
        for (auto event = Event{}; game.window->pollEvent(event);)
            processLiveEvent(event, game.phase, player);
        if(game.phase == PAUSED){
            wasPaused = true;
            awaitUnpause(game.window, game.phase, player);
        }
        return wasPaused;       
    }

    void processLiveEvent(Event &event, GamePhase &phase, Player &player) {
        if (event.type == Event::Closed)
            phase = CLOSE;
        else if (event.type == Event::KeyPressed){
            switch (event.key.code){
                case Keyboard::Key::Escape:
                    phase = CLOSE; break;
                case Keyboard::Key::P: phase = PAUSED; break;
                case Keyboard::Key::W: player.wset = true; break;
                case Keyboard::Key::S: player.sset = true; break;
                case Keyboard::Key::D: player.dset = true; break;
                case Keyboard::Key::A: player.aset = true; break;
            }
        }
        else if (event.type == Event::KeyReleased) {
            switch (event.key.code){
                case Keyboard::Key::W: player.wset = false; break;
                case Keyboard::Key::S: player.sset = false; break;
                case Keyboard::Key::D: player.dset = false; break;
                case Keyboard::Key::A: player.aset = false; break;
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
}

