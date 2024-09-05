#include <mygame.hpp>

namespace sf {

    void GameEngine::createEnemies() {
        game.addEnemy(createCircle(20, {30.f, 500.f},  Color::Red));
        game.addEnemy(createCircle(20, {100.f, 300.f}, Color::Red));
        game.addEnemy(createCircle(20, {1000.f, 40.f}, Color::Red));
        game.addEnemy(createCircle(20, {600.f, 800.f}, Color::Red));
    }

    void GameEngine::createSpawners() {
        spawner1 = CircularSpawner(1.f, 10.f, 5.f, Color::Red, window_center, &sampler, true);
    }

    GameEngine::GameEngine(int seedling) {
        sampler.seed(seedling);
        font = game.getFont();
        game.setupText();

        player.shape = createCircle(20.f, top_left, Color::Green);
        sink = createRectangle(5, 5, window_center, Color::Red);
        game.addEnemy(sink);
        createEnemies();
        createSpawners();
    }

    void GameEngine::execute() {
        spawner1.activate();

        clock.restart();
        while (game.isRunning()) {
            float deltaTime = restartClock();
            float moveDelta = 75 * deltaTime;
            spawner1.update(deltaTime);
            game.addPlayTime(deltaTime);

            for (auto event = Event{}; game.window.pollEvent(event);)
                handleEvent(event, game.window, player);
            
            player.move(moveDelta);
            Vector2f gravity = sink.getPosition() - player.shape.getPosition();

            long long multiplier = exp(7.5f / cbrt(length(gravity))) - 1;
            game.updateScore(multiplier);

            if (game.points < game.minPoints || collision(player.shape, game)) {
                game.end();
                return;
            }

            game.clear();
            game.draw(player.shape);
            game.draw();
            game.display();

            player.applyMovement(0.01f * moveDelta * gravity);
            game.updateEnemies(sampler, player.shape, moveDelta);
            game.addEnemy(spawner1.spawnShape());
        }
        game.close();
    }

}