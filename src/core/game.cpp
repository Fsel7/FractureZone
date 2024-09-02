#include <headers/game.hpp>
#include <string>

namespace sf {

class Game : public GameInterface {

public:
    Game() : GameInterface() {}

    template<typename T>
    void draw(T &obj) { window.draw(obj); }

    void draw() {
        for(auto enemy : circularEnemies)
            window.draw(enemy);
        for(auto enemy : rectangularEnemies)
            window.draw(enemy);
        for(auto enemy : spriteEnemies)
            window.draw(enemy);
        window.draw(score);
        window.draw(minScore);
        window.draw(pTime);
        window.draw(gTime);
    }

    void addPlayTime(const float deltatime) override {
        playTime += deltatime;
        gameTime += deltatime;
        long long pDigits = (long long)(1000 * fractionalPart(playTime));
        long long gDigits = (long long)(1000 * fractionalPart(gameTime));
        pTime.setString("Play time: " + std::to_string((long long)playTime) + "." + std::to_string(pDigits) + "s");
        gTime.setString("Game time: " + std::to_string((long long)gameTime) + "." + std::to_string(gDigits) + "s");
    }

    void updateScore(const long long multiplier) override {
        points   += (long long) (playTime + 1) * multiplier;
        minPoints = (long long) pow(playTime + 1, 3);
        score.setString("Score: " + std::to_string(points) + ", current bonus: " + std::to_string((long long) multiplier));
        minScore.setString("Stay above: " + std::to_string(minPoints));
    }

    void updateEnemies(Sampler &sampler) override {
        for(auto enemy : circularEnemies){
            enemy.setFillColor(sampler.nextColor());
            enemy.move({10.f, 10.f});
        }
        for(auto enemy : rectangularEnemies){
            enemy.setFillColor(sampler.nextColor());
            enemy.move({10.f, 10.f});
        }
        for(auto enemy : spriteEnemies){
            enemy.move(sampler.next2D());
        }
    }

};

}