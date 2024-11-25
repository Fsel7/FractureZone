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
                case SETTING_UP:
                    setupPhase(); break;
                case LOST:
                    lostPhase(); break;
                case MENU:
                    menuPhase(); break;
                default:
                    break;
            }
        }
        game.close();
    }

    void GameEngine::setupPhase(){

    }

    void GameEngine::menuPhase(){
        
    }

    void GameEngine::lostPhase(){
        game.showEndScreen();
        game.phase = CLOSED;
    }

    void GameEngine::runPhase(){
        clock.restart();
        while (game.phase == RUNNING) {

            game.drawFrame(player);

            float deltaTime = restartClock();
            float moveDelta = 75 * deltaTime;

            game.addPlayTime(deltaTime);
            game.updateSpawners(sampler, deltaTime);

            for (auto event = Event{}; game.window->pollEvent(event);)
                handleEvent(event, *game.window, player);
            
            player.move(moveDelta, game.getBounds());

            long long multiplier = game.getMultiplier(player);
            game.updateScore(multiplier, deltaTime);

            game.checkLost(player);

            player.applyGravity(game.blackholes, moveDelta, game.getBounds());
            game.updateEnemies(sampler, player, moveDelta);
        }
    }

}