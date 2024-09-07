#include <mygame.hpp>

namespace sf {

    void GameEngine::createEnemies() {
        game.addEnemy(createCircleEnemy(2, 10, {30.f, 500.f},  sampler.nextColor()));
        game.addEnemy(createCircleEnemy(1, 20, {100.f, 300.f}, sampler.nextColor()));
        game.addEnemy(createCircleEnemy(2, 30, {1000.f, 40.f}, sampler.nextColor()));
        game.addEnemy(createCircleEnemy(3, 25, {600.f, 800.f}, sampler.nextColor()));
    }

    GameEngine::GameEngine(Game &gameZ, Player &playerZ, int seedling) : game(gameZ), player(playerZ) {
        sampler.seed(seedling);
        game.setupText();
        createEnemies();
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
            
            player.move(moveDelta);
            Vector2f gravity = game.blackholes[0].position - player.shape->getPosition();  // Change this to use game.blackholes, see below

            long long multiplier = (long long) exp(7.5f / cbrt(length(gravity))) - 1;  // Change this to use the closest blackhole instead of always sink (or rework entirely ^^)
            game.updateScore(multiplier, deltaTime);

            if(game.lose(player))
                return;

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