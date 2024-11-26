#include <mygame.hpp>

namespace sf {

    GameEngine::GameEngine(Game &gameZ, Player &playerZ, int seedling) : game(gameZ), player(playerZ) {
        sampler.seed(seedling);
        game.setupText();
    }

    void GameEngine::execute() {
        phase = RUNNING;

        while(phase != CLOSE) {
            switch (phase) {
                case RUNNING:   runPhase();   break;
                case RESETTING: resetPhase(); break;
                case LOST:      lostPhase();  break;
                case MENU:      menuPhase();  break;
                case CLOSE:     closePhase(); break;
                default:
                    break;
            }
            if (!game.window->isOpen())
                phase = CLOSE;
        }
        game.close();
    }

    inline void GameEngine::resetPhase(){
        game.window->setMouseCursorVisible(false);
        player.reset();
        game.reset();
        phase = RUNNING;
    }

    inline void GameEngine::menuPhase(){
        game.window->setMouseCursorVisible(true);
        game.window->clear();
        game.window->display();
        phase = RESETTING;
    }

    inline void GameEngine::lostPhase(){
        game.showEndScreen();
        clock.restart();
        bool keyPresed = false;
        while(clock.getElapsedTime().asMilliseconds() < 3000 && !keyPresed){
            for (auto event = Event{}; game.window->pollEvent(event);){
                if(event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Key::Escape)){
                    phase = CLOSE;
                    keyPresed = true;
                    break;
                } else if (event.type == Event::KeyPressed) {
                    keyPresed = true;
                    break;
                }
            }
        }
        if(phase != CLOSE)
            phase = MENU;
    }

    inline void GameEngine::closePhase(){
        game.close();
    }

    inline void GameEngine::runPhase(){
        game.window->setMouseCursorVisible(false);
        clock.restart();
        while (phase == RUNNING) {

            if(processEvents(game.window, phase, player))
                restartClock();

            if(phase == CLOSE)
                return;

            game.drawFrame(player);

            float deltaTime = restartClock();
            game.addTime(deltaTime);
            game.updateSpawners(sampler, deltaTime);
            
            float moveDelta = 75 * deltaTime;
            player.move(moveDelta, game.getBounds());

            long long multiplier = game.getMultiplier(player);
            game.updateScore(multiplier, deltaTime);

            if(game.checkLost(player))
                phase = LOST;

            player.applyGravity(game.blackholes, moveDelta, game.getBounds());
            game.updateEnemies(sampler, player, moveDelta);
        }
    }

}