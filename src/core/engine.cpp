#include <mygame.hpp>

namespace sf {

    void GameEngine::createEnemies() {
        game.addEnemy(createCircleEnemy(2, 10, {30.f, 500.f},  sampler.nextColor()));
        game.addEnemy(createCircleEnemy(1, 20, {100.f, 300.f}, sampler.nextColor()));
        game.addEnemy(createCircleEnemy(2, 30, {1000.f, 40.f}, sampler.nextColor()));
        game.addEnemy(createCircleEnemy(3, 25, {600.f, 800.f}, sampler.nextColor()));
    }

    void GameEngine::createSpawners() {
        spawner1 = CircularSpawner({&sampler, window_center, 1.f, 20.f, 2.f}, Color::Red, true, 10.f, 15.f);
    }

    GameEngine::GameEngine(int seedling) {
        sampler.seed(seedling);
        font = game.getFont();
        game.setupText();

        player.shape = createCircle(20.f, top_left, Color::Green);
        sink = createBlackHole(window_center, 0.01f);
        game.addBlackHole(sink);
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
            Vector2f gravity = sink.position - player.shape.getPosition();  // Change this to use game.blackholes, see below

            long long multiplier = exp(7.5f / cbrt(length(gravity))) - 1;  // Change this to use the closest blackhole instead of always sink (or rework entirely ^^)
            game.updateScore(multiplier, deltaTime);

            if (game.points < game.minPoints) {
                game.end(POINTS);
                return;
            }
            if (collision(player.shape, game)) {
                game.end(ENEMY);
                return;
            }

            game.clear();
            game.draw(player.shape);
            game.draw();
            game.display();

            player.applyMovement(sink.gravity * moveDelta * gravity);   // Change this to use game.blackholes, each vector has to be weighed individually!
            game.updateEnemies(sampler, player.shape, moveDelta);
            game.addEnemy(spawner1.spawnEnemy());
        }
        game.close();
    }

}