#include <mygame.hpp>
#include <string>

namespace sf {

    #define window_center Vector2f(0.5f * window_x, 0.5f * window_y)

    #define top_left     Vector2f(0.f,            0.f)
    #define top_right    Vector2f(1.f * window_x, 0.f)
    #define bottom_left  Vector2f(0.f,            1.f * window_y)
    #define bottom_right Vector2f(1.f * window_x, 1.f * window_y)

    #define line_offset Vector2f(0.f, fontSize + fontSize / 3.f)
    #define fps_offset  Vector2f(120.f, 0.f)

    Game::Game(const uint32_t width, const uint32_t height, const std::string &gameName)
            : m_gameName(gameName), window_x(width), window_y(height),
              window(new RenderWindow(VideoMode(width, height), gameName, Style::Fullscreen)) {
        setupText();

        m_view.setSize(1.f * window->getSize().x, 1.f * window->getSize().y);
        window->setFramerateLimit(m_maxFps);
    }

    void Game::updateView(const Vector2f center) {
        m_view.setCenter(center);
        window->setView(m_view);

        const Vector2f viewCorner = center - 0.5f * m_view.getSize();
        m_score.setPosition(   top_left                        + viewCorner);
        m_minScore.setPosition(top_left    + line_offset       + viewCorner);
        m_gTime.setPosition(   bottom_left - line_offset       + viewCorner);
        m_pTime.setPosition(   bottom_left - 2.f * line_offset + viewCorner);
        m_fps.setPosition(     top_right   - fps_offset        + viewCorner);
    }

    void Game::draw(const Player &player) const {
        for(const auto &spawner : m_circleSpawners)
            window->draw(spawner.m_spawnerSprite);
        for(const auto &spawner : m_rectangleSpawners)
            window->draw(spawner.m_spawnerSprite);       
        for(const auto &enemy : m_rectangularEnemies)
            window->draw(enemy.shape);
        for(const auto &enemy : m_circularEnemies)
            window->draw(enemy.shape);
        for(const auto &enemy : m_spriteEnemies)
            window->draw(enemy);
        for(const auto &bonus : m_bonusZones){
            window->draw(bonus.rectangle);
            window->draw(bonus.label);
        }
        window->draw(*player.getShape());
        window->draw(m_score);
        window->draw(m_minScore);
        window->draw(m_pTime);
        window->draw(m_gTime);
        window->draw(m_fps);
    }

    void Game::drawFrame(const Player &player) {
        updateView(player.getShape()->getPosition());
        resetGameFrame();
        draw(player);
        window->display();
    }

    void Game::addTime(const float deltatime) {
        m_currentTime += deltatime;
        m_totalTime += deltatime;
        const uint64_t pDigits = static_cast<uint64_t>(1000 * fractionalPart(m_currentTime));
        const uint64_t gDigits = static_cast<uint64_t>(1000 * fractionalPart(m_totalTime));
        m_pTime.setString("Current time: " + std::to_string(static_cast<uint64_t>(m_currentTime)) + "." + std::to_string(pDigits) + "s");
        m_gTime.setString("Total time: "   + std::to_string(static_cast<uint64_t>(m_totalTime  )) + "." + std::to_string(gDigits) + "s");
        m_fps.setString(  "Fps: "          + std::to_string(static_cast<uint16_t>(1 / deltatime)));
    }

    void Game::updateScore(const uint64_t multiplier, const float deltaTime) {
        m_points   += 100 * deltaTime * m_currentTime * multiplier;
        m_minPoints = powf(m_currentTime, 3);
        m_minScore.setString("Stay above: "      + std::to_string(static_cast<uint64_t>(m_minPoints)));
        m_score.setString(   "Score: "           + std::to_string(static_cast<uint64_t>(m_points   )) +
                           ", current bonus: "   + std::to_string(static_cast<uint64_t>(multiplier )));
    }

    void Game::updateEnemies(Sampler &sampler, const Player &player, const float deltatime) {
        for(auto it = m_circularEnemies.begin(); it != m_circularEnemies.end(); it++){
            Vector2f toPlayer = player.getShape()->getPosition() - it->shape.getPosition();
            it->shape.move(deltatime * it->speed * normalized(sampler.next2D() + toPlayer));
        }
        for(auto it = m_rectangularEnemies.begin(); it != m_rectangularEnemies.end(); it++){
            Vector2f toPlayer = player.getShape()->getPosition() - it->shape.getPosition();
            it->shape.move(deltatime * it->speed * normalized(sampler.next2D() + toPlayer));
        }
    }

    void Game::setupText() {
        m_gameover = createText("", window_center,                    m_font, Color::Red,  90);
        m_score    = createText("", top_left,                         m_font, Color::Red     );
        m_minScore = createText("", top_left    + line_offset,        m_font, Color::Yellow  );
        m_gTime    = createText("", bottom_left - line_offset,        m_font, Color::Cyan    );
        m_pTime    = createText("", bottom_left - 2.f * line_offset,  m_font, Color::Cyan    );
        m_fps      = createText("", top_right   - fps_offset,         m_font, Color::Green   );
    }

    void Game::updateSpawners(Sampler& sampler, const float deltaTime) {
        for(auto &spawner : m_circleSpawners) {
            switch (spawner.update(deltaTime, m_currentTime)) {
                case ACTIVE_TEXTURE:
                    spawner.m_spawnerSprite.setTexture(m_activeSpawnerTexture); break;
                case INACTIVE_TEXTURE:
                    spawner.m_spawnerSprite.setTexture(m_inactiveSpawnerTexture); break;
                default:
                    break;
            }                
            addEnemy(spawner.spawnEnemy(sampler));
        }
        for(auto &spawner : m_rectangleSpawners) {
            switch (spawner.update(deltaTime, m_currentTime)) {
                case ACTIVE_TEXTURE:
                    spawner.m_spawnerSprite.setTexture(m_activeSpawnerTexture); break;
                case INACTIVE_TEXTURE:
                    spawner.m_spawnerSprite.setTexture(m_inactiveSpawnerTexture); break;
                default:
                    break;
            }   
            addEnemy(spawner.spawnEnemy(sampler));
        }
    }

    bool Game::checkLost(const Player &player) {
        if (m_points < m_minPoints)
            m_gameover.setString("Too few points!\nYour points: "   + std::to_string(static_cast<uint64_t>(m_points)));
        else if (collision(player))
            m_gameover.setString("An enemy got you!\nYour points: " + std::to_string(static_cast<uint64_t>(m_points)));
        else return false;
        return true;
    }

    void Game::showEndScreen() {
        window->clear();
        centerSprite(m_lostSprite, m_view.getCenter());
        window->draw(m_lostSprite);

        centerText(m_gameover, m_view.getCenter());
        m_gameover.move(0, 0.25f * window_y);
        draw(m_gameover);
        
        window->display();
    }

    bool Game::collision(const Player &player) const {
        for(const auto &enemy : m_circularEnemies)
            if(intersects(dynamic_cast<CircleShape*>(player.getShape()), enemy.shape))
                return true;
        for(const auto &enemy : m_rectangularEnemies)
            if(intersects(dynamic_cast<CircleShape*>(player.getShape()), enemy.shape))
                return true;
        for(const auto &enemy : m_spriteEnemies)
            if(intersects(dynamic_cast<CircleShape*>(player.getShape()), enemy))
                return true;
        return false;
    }

    uint64_t Game::getMultiplier(const Player &player) const {
        uint64_t res = 1;
        for(const auto &bonus : m_bonusZones)
            if(bonus.rectangle.getGlobalBounds().contains(player.getShape()->getPosition()))
                res *= bonus.multiplier;
        return res;
    }

    void Game::resetView() {
        m_view.setCenter(window_center);
        window->setView(m_view);
    }

    void Game::reset() {
        m_circularEnemies.clear();
        m_rectangularEnemies.clear();
        m_spriteEnemies.clear();
        m_currentTime = 0;
        m_points = 1;
        m_minPoints = 0;
    }

    void Game::switchWindowMode() {
        const auto fullscreen = m_isFullscreen ? Style::Default : Style::Fullscreen;
        window->create(VideoMode(window_x, window_y), m_gameName, fullscreen);
        window->setIcon(m_icon.getSize().x, m_icon.getSize().y, m_icon.getPixelsPtr());
        window->setFramerateLimit(m_maxFps);
        m_isFullscreen = !m_isFullscreen;
    }

}