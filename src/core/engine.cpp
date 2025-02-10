#include <mygame.hpp>

namespace sf {

    GameEngine::GameEngine(const Game &gameZ, const Player &playerZ, const int seedling, const int width, const int height, const std::string &name) :
            player(playerZ),
            game(gameZ),
            window(new RenderWindow(VideoMode(width, height), name, Style::Fullscreen)),
            menu(window->getSize(), gameZ.getFont()) {

        sampler.seed(seedling);
        menu.setTitle(name);
        
        window->setFramerateLimit(144);

        game.setAllTimeHighscore(ini.readHighScore());
        game.window = window;
    }

    void GameEngine::execute() {
        phase = MENU;

        while (phase != CLOSE) {
            switch (phase) {
                case RUNNING:   runPhase();      break;
                case RESETTING: resetPhase();    break;
                case LOST:      lostPhase();     break;
                case MENU:      menuPhase();     break;
                case SETTINGS:  settingsPhase(); break;
                default:        break;
            }
            if (!window->isOpen())
                phase = CLOSE;
        }
        closePhase();
    }

    inline void GameEngine::resetPhase() {
        window->setMouseCursorVisible(false);
        player.reset();
        game.reset();
        phase = RUNNING;
    }

    inline void GameEngine::menuPhase() {
        window->setMouseCursorVisible(true);
        game.resetView();
        window->clear(Color(50, 50, 50));
        menu.draw(*window, MENU_SCREEN);
        window->display();

        menuEvents(*window, game, phase, menu);
    }

    inline void GameEngine::settingsPhase() {
        window->clear(Color(50, 50, 50));
        menu.draw(*window, SETTINGS_SCREEN);
        window->display();

        settingsEvents(*window, game, phase, menu, ini);
    }

    inline void GameEngine::lostPhase() {
        game.showEndScreen();
        sleep(seconds(0.9f));

        lostEvents(*window, phase);
        if (phase != CLOSE)
            phase = MENU;
    }

    inline void GameEngine::closePhase() {
        ini.updateHighScore(game.getSessionHighscore());

        window->close();
    }

    inline void GameEngine::runPhase() {
        window->setMouseCursorVisible(false);
        clock.restart();
        while (phase == RUNNING) {

            if (processEvents(*window, phase, player))
                restartClock();

            if (phase == CLOSE || phase == MENU)
                break;

            game.drawFrame(player);

            const float deltaTime = restartClock();
            game.addTime(deltaTime);
            game.updateSpawners(sampler, deltaTime);
            
            const float moveDelta = 75 * deltaTime;
            player.move(moveDelta, game.getBounds());

            const uint64_t multiplier = game.getMultiplier(player);
            game.updateScore(multiplier, deltaTime);

            if (game.checkLost(player))
                phase = LOST;

            player.applyGravity(game.blackholes, moveDelta, game.getBounds());
            game.updateEnemies(sampler, player, moveDelta);
        }
        game.updateHighscores();
    }

}