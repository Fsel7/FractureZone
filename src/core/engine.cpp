#include <mygame.hpp>

namespace sf {

    GameEngine::GameEngine(Game &gameZ, Player &playerZ, int seedling) : game(gameZ), player(playerZ) {
        sampler.seed(seedling);
        game.setupText();
    }

    void GameEngine::execute() {
        game.phase = RUNNING;
        while(game.phase != CLOSE) {
            switch (game.phase) {
                case RUNNING:
                    runPhase(); break;
                case RESETTING:
                    resetPhase(); break;
                case LOST:
                    lostPhase(); break;
                case MENU:
                    menuPhase(); break;
                case CLOSE:
                    closePhase(); break;
                default:
                    break;
            }
            if (!game.window->isOpen())
                game.phase = CLOSE;
        }
        game.close();
    }

    inline void GameEngine::resetPhase(){
        game.window->setMouseCursorVisible(false);
        player.reset();
        game.reset();
        game.phase = RUNNING;
    }

    inline void GameEngine::menuPhase(){
        game.window->setMouseCursorVisible(true);
        game.window->clear();
        game.window->display();
        game.phase = RESETTING;
    }

    inline void GameEngine::lostPhase(){
        game.showEndScreen();
        if(game.phase != CLOSE)
            game.phase = MENU;
    }

    inline void GameEngine::closePhase(){
        game.close();
    }

    inline void GameEngine::runPhase(){
        game.window->setMouseCursorVisible(false);
        clock.restart();
        while (game.phase == RUNNING) {

            game.drawFrame(player);

            float deltaTime = restartClock();
            game.addTime(deltaTime);
            game.updateSpawners(sampler, deltaTime);

            for (auto event = Event{}; game.window->pollEvent(event);)
                handleEvent(event, game.phase, player);
            
            if(game.phase == CLOSE)
                return;
            
            float moveDelta = 75 * deltaTime;
            player.move(moveDelta, game.getBounds());

            long long multiplier = game.getMultiplier(player);
            game.updateScore(multiplier, deltaTime);

            if(game.checkLost(player))
                game.phase = LOST;

            player.applyGravity(game.blackholes, moveDelta, game.getBounds());
            game.updateEnemies(sampler, player, moveDelta);
        }
    }

}