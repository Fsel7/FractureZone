#include <mygame.hpp>

namespace sf {

    GameEngine::GameEngine(Game &gameZ, Player &playerZ, int seedling)
    : game(gameZ), player(playerZ), menu(gameZ.window->getSize(), gameZ.getFont()) {
        sampler.seed(seedling);
        window = game.window;
    }

    void GameEngine::execute() {
        phase = MENU;

        while(phase != CLOSE) {
            switch (phase) {
                case RUNNING:   runPhase();      break;
                case RESETTING: resetPhase();    break;
                case LOST:      lostPhase();     break;
                case MENU:      menuPhase();     break;
                case SETTINGS:  settingsPhase(); break;
                case CLOSE:     closePhase();    break;
                default:        closePhase();
            }
            if (!window->isOpen())
                phase = CLOSE;
        }
        window->close();
    }

    inline void GameEngine::resetPhase(){
        window->setMouseCursorVisible(false);
        player.reset();
        game.reset();
        phase = RUNNING;
    }

    inline void GameEngine::menuPhase(){
        window->setMouseCursorVisible(true);
        game.resetView();
        window->clear(Color(50, 50, 50));
        menu.draw(*window, MENU_SCREEN);
        window->display();

        menuEvents(*window, phase, menu);
    }

    inline void GameEngine::settingsPhase(){
        window->clear(Color(50, 50, 50));
        menu.draw(*window, SETTINGS_SCREEN);
        window->display();

        settingsEvents(*window, game, phase, menu);
    }

    inline void GameEngine::lostPhase(){
        game.showEndScreen();

        lostEvents(*window, phase);
        if(phase != CLOSE)
            phase = MENU;
    }

    inline void GameEngine::closePhase(){
        window->close();
    }

    inline void GameEngine::runPhase(){
        window->setMouseCursorVisible(false);
        clock.restart();
        while (phase == RUNNING) {

            if(processEvents(window, phase, player))
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