#include <mygame.hpp>

namespace sf {

    GameEngine::GameEngine(Game &gameZ, Player &playerZ, int seedling)
    : game(gameZ), player(playerZ), menu(gameZ.window->getSize(), gameZ.getFont()) {
        sampler.seed(seedling);
        game.setupText();
    }

    void GameEngine::execute() {
        phase = MENU;

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
        game.resetView();
        game.window->setMouseCursorVisible(true);
        game.window->clear(Color(50, 50, 50));
        menu.draw(*game.window);
        game.window->display();

        menuEvents(*game.window, phase, menu);
    }

    inline void GameEngine::lostPhase(){
        game.showEndScreen();

        lostEvents(*game.window, phase);
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

            if(phase == CLOSE || phase == MENU)
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