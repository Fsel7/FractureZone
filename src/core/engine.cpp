#include <mygame.hpp>

namespace sf {

    GameEngine::GameEngine(Game &gameZ, Player &playerZ, int seedling) : game(gameZ), player(playerZ) {
        sampler.seed(seedling);
        game.setupText();
    }

    void GameEngine::execute() {
        clock.restart();
        while (game.isRunning()) {
            float deltaTime = restartClock();
            float moveDelta = 75 * deltaTime;

            game.addPlayTime(deltaTime);
            game.updateSpawners(sampler, deltaTime);

            for (auto event = Event{}; game.window->pollEvent(event);)
                handleEvent(event, *game.window, player);
            
            player.move(moveDelta, game.getBounds());
            Vector2f gravity = game.blackholes[0].position - player.shape->getPosition();  // Change this to use game.blackholes, see below

            long long multiplier = (long long) exp(7.5f / cbrt(length(gravity))) - 1;  // Change this to use the closest blackhole instead of always sink (or rework entirely ^^)
            game.updateScore(multiplier, deltaTime);

            if(game.lose(player))
                return;

            game.updateView(player);
            game.clear();
            game.draw(player.shape);
            game.draw();
            game.display();

            player.applyMovement(game.blackholes[0].gravity * moveDelta * gravity);   // Change this to use game.blackholes, each vector has to be weighed individually!
            game.updateEnemies(sampler, player, moveDelta);
        }
        game.close();
    }

}