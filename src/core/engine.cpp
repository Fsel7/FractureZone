#include <mygame.hpp>

namespace sf {

    GameEngine::GameEngine(Game &gameZ, Player &playerZ, int seedling) : game(gameZ), player(playerZ) {
        sampler.seed(seedling);
        game.setupText();
    }

    void GameEngine::execute() {
        game.phase = RUNNING;
        while(game.phase != CLOSED) {
            switch (game.phase) {
                case RUNNING:
                    runPhase(); break;
                case RESETTING:
                    resetPhase(); break;
                case LOST:
                    lostPhase(); break;
                case MENU:
                    menuPhase(); break;
                default:
                    break;
            }
            if (!game.window->isOpen())
                game.phase = CLOSED;
        }
        game.close();
    }

    void GameEngine::resetPhase(){
        player.reset();
        game.reset();
        game.phase = RUNNING;
    }

    void GameEngine::menuPhase(){
        game.phase = RESETTING;
    }

    void GameEngine::lostPhase(){
        game.showEndScreen();
        game.phase = MENU;
    }

    void GameEngine::runPhase(){
        clock.restart();
        while (game.phase == RUNNING) {

            game.drawFrame(player);

            float deltaTime = restartClock();
            game.addTime(deltaTime);
            game.updateSpawners(sampler, deltaTime);

            for (auto event = Event{}; game.window->pollEvent(event);)
                handleEvent(event, *game.window, player);
            
            if(!game.window->isOpen()){
                game.phase = CLOSED;
                return;
            }
            
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