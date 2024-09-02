#include <mygame.hpp>
#include <chrono>

#include "eventhandler.cpp"
#include "objecthandler.cpp"
#include "intersectiontester.cpp"

int main() {
    using namespace std::chrono;
    using namespace sf;

    Player player;
    player.shape = createCircle(20.f, origin, Color::Green);

    Game game;
    auto myFont = game.myFont;
    auto windowCenter = game.window.getView().getCenter();
    
    game.score    = createText("", origin, myFont, Color::Red);
    game.minScore = createText("", {0.f, game.score.getCharacterSize() + 10.f}, myFont, Color::Yellow);

    RectangleShape sink = createRectangle(50, 50, windowCenter, Color::Blue);

    high_resolution_clock::time_point tlast = high_resolution_clock::now();
    high_resolution_clock::time_point tcur = high_resolution_clock::now();

    while (game.isRunning()) {

        tlast = tcur;
        tcur = high_resolution_clock::now();

        duration<float, std::milli> time_span = tcur - tlast;
        float deltaTime = time_span.count() / 1000;
        game.addPlayTime(deltaTime);

        for (auto event = Event{}; game.window.pollEvent(event);)
            handleEvent(event, game.window, player);
        
        player.move();
        Vector2f gravity = sink.getPosition() - player.shape.getPosition();

        long long multiplier = exp(7.5f / cbrt(length(gravity))) - 1;
        game.updateScore(multiplier);

        if(intersects(player.shape, sink) || game.points < game.minPoints){

            Text gameover("Game over!\nYour points: " + std::to_string(game.points), myFont, 100);
            centerText(gameover, windowCenter);

            game.clear();
            game.draw(gameover);
            game.display();
            sleep(sf::seconds(1.f));
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


