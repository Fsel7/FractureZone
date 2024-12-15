#include <mygame.hpp>

#include <SimpleIni.h>
#include <filesystem>

namespace sf {

    GameEngine::GameEngine(const Game &gameZ, const Player &playerZ, const int seedling) :
            game(gameZ), player(playerZ), menu(gameZ.window->getSize(), gameZ.getFont()) {
        sampler.seed(seedling);
        window = game.window;
    }

    void GameEngine::execute() {
        phase = MENU;

        while(phase != CLOSE) {
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

    inline void GameEngine::resetPhase(){
        window->setMouseCursorVisible(false);
        player.reset();
        game.reset();
        phase = RUNNING;
    }

    inline void GameEngine::menuPhase(){
        window->setMouseCursorVisible(true);
        game.resetView();
        window->clear(Color(50, 50, 50));
        menu.draw(*window, MENU_SCREEN);
        window->display();

        menuEvents(*window, game, phase, menu);
    }

    inline void GameEngine::settingsPhase(){
        window->clear(Color(50, 50, 50));
        menu.draw(*window, SETTINGS_SCREEN);
        window->display();

        settingsEvents(*window, game, phase, menu);
    }

    inline void GameEngine::lostPhase(){
        game.showEndScreen();
        sleep(seconds(0.5f));

        lostEvents(*window, phase);
        if(phase != CLOSE)
            phase = MENU;
    }

    inline void GameEngine::closePhase(){
        const auto iniPath = std::filesystem::path("resources/") / "highscores.ini";
        const auto savePath = std::filesystem::current_path().parent_path().parent_path().parent_path() / iniPath;

        CSimpleIniA ini;
        ini.SetUnicode();
        ini.LoadFile(iniPath.string().c_str());

        const std::string newHighscore = std::to_string(game.getHighscore());
        const SI_Error rc = ini.SetValue("section", "highscore", newHighscore.c_str());

        assert_condition(game.getHighscore() >= 1 && rc >= 0, "There was some error when saving the highscore!");

        ini.SaveFile(savePath.string().c_str());


        window->close();
    }

    inline void GameEngine::runPhase(){
        window->setMouseCursorVisible(false);
        clock.restart();
        while (phase == RUNNING) {

            if(processEvents(*window, phase, player))
                restartClock();

            if(phase == CLOSE || phase == MENU)
                break;

            game.drawFrame(player);

            const float deltaTime = restartClock();
            game.addTime(deltaTime);
            game.updateSpawners(sampler, deltaTime);
            
            const float moveDelta = 75 * deltaTime;
            player.move(moveDelta, game.getBounds());

            const uint64_t multiplier = game.getMultiplier(player);
            game.updateScore(multiplier, deltaTime);

            if(game.checkLost(player))
                phase = LOST;

            player.applyGravity(game.blackholes, moveDelta, game.getBounds());
            game.updateEnemies(sampler, player, moveDelta);
        }
        game.updateHighscore();
    }

}