#include <mygame.hpp>
#include <chrono>

#include "eventhandler.cpp"
#include "objecthandler.cpp"
#include "intersectiontester.cpp"

int main() {
    using namespace std::chrono;
    using namespace sf;

    Player player;
    player.shape = createCircle(20.f, top_left, Color::Green);

    Game game;
    auto myFont = game.myFont;
    
    game.score    = createText("", top_left,                        myFont, Color::Red);
    game.minScore = createText("", top_left    + line_offset,       myFont, Color::Yellow);
    game.gTime    = createText("", bottom_left - line_offset,       myFont, Color::Cyan);
    game.pTime    = createText("", bottom_left - 2.f * line_offset, myFont, Color::Cyan);

    RectangleShape sink = createRectangle(50, 50, window_center, Color::Blue);

    game.addEnemy(createCircle(20, {30, 500.f},    Color::Red));
    game.addEnemy(createCircle(20, {100.f, 300.f}, Color::Red));
    game.addEnemy(createCircle(20, {1000.f, 40.f}, Color::Red));
    game.addEnemy(createCircle(20, {600.f, 800.f}, Color::Red));

    Timer time;

    while (game.isRunning()) {

        time.update();
        game.addPlayTime(time.getDeltaTime());

        for (auto event = Event{}; game.window.pollEvent(event);)
            handleEvent(event, game.window, player);
        
        player.move();
        Vector2f gravity = sink.getPosition() - player.shape.getPosition();

        long long multiplier = exp(7.5f / cbrt(length(gravity))) - 1;
        game.updateScore(multiplier);

        bool hitsEnemy = false;
        for(auto enemy : game.circularEnemies)
            if(intersects(player.shape, enemy)){
                hitsEnemy = true;
                break;
            }

        if(hitsEnemy || intersects(player.shape, sink) || game.points < game.minPoints){
            Text gameover("Game over!\nYour points: " + std::to_string(game.points), myFont, 90);
            centerText(gameover, window_center);

            game.clear();
            game.draw(gameover);
            game.display();
            sleep(sf::seconds(1.5f));
            break;
        }

        game.clear();
        game.draw(sink);
        game.draw(player.shape);
        game.draw();
        game.display();

        player.applyMovement(0.01f * gravity);
    }

    game.close();
    return 0;
}


