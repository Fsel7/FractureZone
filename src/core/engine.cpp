#include <mygame.hpp>

namespace sf {

    GameEngine::GameEngine(Game &gameZ, Player &playerZ, int seedling) : game(gameZ), player(playerZ) {
        sampler.seed(seedling);
        game.setupText();
    }

    void GameEngine::execute() {
        // TODO: Add menu and menu phase
        clock.restart();
        game.phase = RUNNING;
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
        game.showEndScreen();
        // TODO: Go back to menu and restart, if chosen
        game.close();
    }

}