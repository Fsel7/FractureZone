#include <mygame.hpp>

#include "core/game.cpp"
#include "otherstuff/eventhandler.cpp"
#include "otherstuff/texthandler.cpp"
#include "otherstuff/animationhandler.cpp"
#include "otherstuff/intersectiontester.cpp"
#include "samplers/mt19937.cpp"
#include "spawners/circularSpawner.cpp"

namespace sf {

class GameEngine {

protected:
    MersenneSampler sampler;
    Player player;
    Clock clock;
    Game game;
    Font font;
    RectangleShape sink;
    CircularSpawner spawner1 = CircularSpawner(2.f, 10.f, 5.f, Color::Red, window_center, &sampler);
    
protected:
    /// @brief Restarts the clock and returns the passed time in seconds
    float restartClock() {
        return clock.restart().asSeconds();
    }

    void createEnemies() {
        game.addEnemy(createCircle(20, {30.f, 500.f},  Color::Red));
        game.addEnemy(createCircle(20, {100.f, 300.f}, Color::Red));
        game.addEnemy(createCircle(20, {1000.f, 40.f}, Color::Red));
        game.addEnemy(createCircle(20, {600.f, 800.f}, Color::Red));
    }

public:
    GameEngine(int seedling) {
        sampler.seed(seedling);
        font = game.getFont();
        textSetup(game, font);

        player.shape = createCircle(20.f, top_left, Color::Green);
        sink = createRectangle(50, 50, window_center, Color::Blue);
        game.addEnemy(sink);
        createEnemies(); 
    }

    void execute() {
        spawner1.activate();

        clock.restart();
        while (game.isRunning()) {
            float deltaTime = restartClock();
            spawner1.update(deltaTime);
            game.addPlayTime(deltaTime);

            for (auto event = Event{}; game.window.pollEvent(event);)
                handleEvent(event, game.window, player);
            
            player.move();
            Vector2f gravity = sink.getPosition() - player.shape.getPosition();

            long long multiplier = exp(7.5f / cbrt(length(gravity))) - 1;
            game.updateScore(multiplier);

            if (game.points < game.minPoints || collision(player.shape, game)) {
                Text gameover("Game over!\nYour points: " + std::to_string(game.points), font, 90);
                centerText(gameover, window_center);

                game.clear();
                game.draw(gameover);
                game.display();
                sleep(sf::seconds(1.5f));
                break;
            }

            game.clear();
            game.draw(player.shape);
            game.draw();
            game.display();

            player.applyMovement(0.01f * gravity);
            game.updateEnemies(sampler, player.shape);
            game.addEnemy(spawner1.spawnShape());
        }

    game.close();
    }

};

}