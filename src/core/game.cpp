#include <mygame.hpp>
#include <string>

namespace sf {

    void Game::addPlayTime(const float deltatime) {
        playTime += deltatime;
        gameTime += deltatime;
        long long pDigits = (long long)(1000 * fractionalPart(playTime));
        long long gDigits = (long long)(1000 * fractionalPart(gameTime));
        pTime.setString("Play time: " + std::to_string((long long)playTime) + "." + std::to_string(pDigits) + "s");
        gTime.setString("Game time: " + std::to_string((long long)gameTime) + "." + std::to_string(gDigits) + "s");
        fps.setString("Fps: " + std::to_string((int) (1 / deltatime)));
    }

    void Game::updateScore(const long long multiplier, const float deltaTime) {
        points   += 100 * deltaTime * playTime * multiplier;
        minPoints = pow(playTime, 3);
        score.setString("Score: " + std::to_string((long long) points) + ", current bonus: " + std::to_string((long long) multiplier));
        minScore.setString("Stay above: " + std::to_string((long long) minPoints));
    }

    void Game::updateEnemies(Sampler &sampler, Player& player, float deltatime) {
        for(auto it = circularEnemies.begin(); it != circularEnemies.end(); it++){
            Vector2f toPlayer = player.shape.getPosition() - it->shape.getPosition();
            it->shape.move(deltatime * it->speed * normalized(sampler.next2D() + toPlayer));
        }
    }

    void Game::setupText() {
        score    = createText("", top_left,                         font, Color::Red);
        minScore = createText("", top_left    + line_offset,        font, Color::Yellow);
        gTime    = createText("", bottom_left - line_offset,        font, Color::Cyan);
        pTime    = createText("", bottom_left - 2.f * line_offset,  font, Color::Cyan);
        fps      = createText("", top_right   - fps_offset,         font, Color::Green);
    }

    void Game::updateSpawners(const float deltaTime) {
        for(auto spawner : circleSpawners) {
            spawner.update(deltaTime, playTime);
            addEnemy(spawner.spawnEnemy());
        }
        for(auto spawner : rectangleSpawners) {
            spawner.update(deltaTime, playTime);
            addEnemy(spawner.spawnEnemy());
        }
    }

    bool Game::lose(Player &player) {
        if (points < minPoints)
            gameover = Text("Too few points!\nYour points: " + std::to_string((long long) points), font, 90);
        else if (collision(player.shape, *this))
            gameover = Text("An enemy got you!\nYour points: " + std::to_string((long long) points), font, 90);
        else return false;

        centerText(gameover, window_center);
        clear();
        draw(gameover);
        display();
        sleep(sf::seconds(1.5f));
        close();
        return true;
    }

}