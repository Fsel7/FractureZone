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

    void Game::updateEnemies(Sampler &sampler, CircleShape& player, float deltatime) {
        for(auto it = circularEnemies.begin(); it != circularEnemies.end(); it++){
            // Color sampled = sampler.nextColor();
            // Color old = it->getFillColor();
            // Color newColor = Color((Uint8)(sampled.r/4.f + 3*old.r/4.f), (Uint8)(sampled.g/4.f + 3*old.g/4.f), (Uint8)(sampled.b/4.f + 3*old.b/4.f));
            // it->setFillColor(newColor);

            Vector2f toPlayer = player.getPosition() - it->getPosition();
            it->move(deltatime * enemySpeed * normalized(sampler.next2D() + toPlayer));
        }
    }

    void Game::setupText() {
        score    = createText("", top_left,                         font, Color::Red);
        minScore = createText("", top_left    + line_offset,        font, Color::Yellow);
        gTime    = createText("", bottom_left - line_offset,        font, Color::Cyan);
        pTime    = createText("", bottom_left - 2.f * line_offset,  font, Color::Cyan);
        fps      = createText("", top_right   - fps_offset        , font, Color::Green);
    }

    void Game::end(const LoseCondition cause) {
        switch(cause) {
            case POINTS: 
                gameover = Text("Too few points!\nYour points: " + std::to_string((long long) points), font, 90);
                break;
            case ENEMY: 
                gameover = Text("An enemy got you!\nYour points: " + std::to_string((long long) points), font, 90);
                break;
            default:
                gameover = Text("Game over!\nYour points: " + std::to_string((long long) points), font, 90);
        }
        centerText(gameover, window_center);
        clear();
        draw(gameover);
        display();
        sleep(sf::seconds(1.5f));
        close();
    }

}