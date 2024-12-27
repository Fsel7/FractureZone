#include <mygame.hpp>

#include <string>

namespace sf {

    #define window_center Vector2f(0.5f * window_x, 0.5f * window_y)

    #define top_left     Vector2f(0.f,            0.f)
    #define top_right    Vector2f(1.f * window_x, 0.f)
    #define bottom_left  Vector2f(0.f,            1.f * window_y)
    #define bottom_right Vector2f(1.f * window_x, 1.f * window_y)

    #define line_offset  Vector2f(0.f, fontSize + fontSize / 3.f)
    #define fps_offset   Vector2f(120.f, 0.f)

    Game::Game(const uint32_t width, const uint32_t height, const std::string &gameName)
            : window(new RenderWindow(VideoMode(width, height), gameName, Style::Fullscreen)),
            m_gameName(gameName), window_x(width), window_y(height) {
        setupText();

        m_view.setSize(1.f * window->getSize().x, 1.f * window->getSize().y);
        window->setFramerateLimit(m_maxFps);
    }

    void Game::updateView(const Vector2f center) {
        m_view.setCenter(center);
        window->setView(m_view);

        const Vector2f viewCorner = center - 0.5f * m_view.getSize();

        m_score.setPosition(top_left                  + viewCorner);
        m_time.setPosition( bottom_left - line_offset + viewCorner);
        m_fps.setPosition(  top_right   - fps_offset  + viewCorner);
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

        window->draw(m_fps);
        m_score.draw(*window);
        m_time.draw(*window);
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
        m_time.setString(0, "Current time: " + std::to_string(static_cast<uint64_t>(m_currentTime)) + "." + std::to_string(pDigits) + "s");
        m_time.setString(1, "Total time: "   + std::to_string(static_cast<uint64_t>(m_totalTime  )) + "." + std::to_string(gDigits) + "s");
        m_fps.setString(    "Fps: "          + std::to_string(static_cast<uint16_t>(1 / deltatime)));
    }

    void Game::updateScore(const uint64_t multiplier, const float deltaTime) {
        m_points   += 100 * deltaTime * m_currentTime * multiplier;
        m_minPoints = powf(m_currentTime, 3);
        
        m_score.setString(0, "Score: "         + std::to_string(static_cast<uint64_t>(m_points   )) +
                           ", current bonus: " + std::to_string(static_cast<uint64_t>(multiplier )));
        m_score.setString(1, "Stay above: "    + std::to_string(static_cast<uint64_t>(m_minPoints)));
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
        /// The set strings are irrelevant, as they will be overriden later!
        /// This is part of a rewrite and still a pretty bad solution as the order matters!
        /// If I find the time, I will probably swap to enums instead (see: buttons).
        m_fps = createText("fps", top_right - fps_offset, m_font, Color::Green);

        m_score    = MultilineText(top_left,                  LEFT,    DOWN);
        m_time     = MultilineText(bottom_left - line_offset, LEFT,    UP  );
        m_gameover = MultilineText(window_center,             CENTER,  DOWN);

        m_score.push_back(createSimpleText("score",    m_font, Color::Red, 30));
        m_score.push_back(createSimpleText("minScore", m_font, Color::Yellow, 30));

        m_time.push_back(createSimpleText("pTime", m_font, Color::Cyan, 30));
        m_time.push_back(createSimpleText("gTime", m_font, Color::Cyan, 30));

        Color lost(0, 183, 239);

        m_gameover.push_back(createSimpleText("losingCondition",   m_font, Color::Red, 50));
        m_gameover.push_back(createSimpleText("yourPoints",        m_font, lost,       50));
        m_gameover.push_back(createSimpleText("highscore",         m_font, lost,       50));
        m_gameover.push_back(createSimpleText("alltime highscore", m_font, lost,       50));
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
        if (m_points < m_minPoints){
            m_gameover.setString(0, "Too few points!");
            m_gameover.setString(1, "Your points: " + std::to_string(static_cast<uint64_t>(m_points)));
        }
        else if (collision(player)) {
            m_gameover.setString(0, "An enemy got you!");
            m_gameover.setString(1, "Your points: " + std::to_string(static_cast<uint64_t>(m_points)));
        }
        else return false;
        return true;
    }

    void Game::showEndScreen() {
        window->clear();
        centerSprite(m_lostSprite, m_view.getCenter());
        window->draw(m_lostSprite);

        m_gameover.setPosition(m_view.getCenter() + Vector2f(0, 0.25f * m_view.getSize().y));
        m_gameover.draw(*window);
        
        window->display();
    }

    bool Game::collision(const Player &player) const {
        CircleShape* shape = dynamic_cast<CircleShape*>(player.getShape().get());
        assert_condition(shape != nullptr, "We only handle CircleShapes this far!");

        for(const auto &enemy : m_circularEnemies)
            if(intersects(*shape, enemy.shape))
                return true;
        for(const auto &enemy : m_rectangularEnemies)
            if(intersects(*shape, enemy.shape))
                return true;
        for(const auto &enemy : m_spriteEnemies)
            if(intersects(*shape, enemy))
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

    void Game::updateHighscores() {
        const auto prevHigh = m_highscore;
        m_highscore = std::max(m_highscore, static_cast<uint64_t>(m_points));
        
        std::string sessionHighscore;
        if (prevHigh < m_highscore)
            sessionHighscore = "You beat your session's highscore of " + std::to_string(prevHigh) + "! ";
        else
            sessionHighscore = "Your session's highscore of " + std::to_string(prevHigh) + " still stands!";
        m_gameover.setString(2, sessionHighscore);

        std::string alltimeHighscore;
        if (m_alltimeHighscore < m_highscore)
            alltimeHighscore = "You beat your all time highscore of " + std::to_string(m_alltimeHighscore) + "! ";
        else
            alltimeHighscore = "Your all time highscore of " + std::to_string(m_alltimeHighscore) + " still stands!";
        m_gameover.setString(3, alltimeHighscore);

        m_alltimeHighscore = std::max(m_alltimeHighscore, m_highscore);
    }

}