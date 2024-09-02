#include <game.hpp>
#include <chrono>

#include "eventhandler.cpp"
#include "objecthandler.cpp"
#include "intersectiontester.cpp"

#define origin {0.f, 0.f}
#define window_x 1200u
#define window_y 900u

struct Game {
public:
    sf::Font myFont;
    sf::RenderWindow window;

    long long points = 0;
    long long minPoints = 0;

    float playTime = 0;
    float globTime = 0;
    
    Game() : window({window_x, window_y}, "Very Cool Game") {
        myFont.loadFromFile("fonts/arial.ttf");      
        window.setFramerateLimit(64);
    }

    ~Game() = default;
};

int main() {
    using namespace std::chrono;
    using namespace sf;

    Game game;
    Player player;
    player.shape = createCircle(20.f, origin, Color::Green);

    auto myFont = game.myFont;
    auto windowCenter = game.window.getView().getCenter();

    // Timing initialization stuff
    high_resolution_clock::time_point tlast = high_resolution_clock::now();
    high_resolution_clock::time_point tcur = high_resolution_clock::now();
    float deltaTime = 0;
    
    // Creation of some objects visible in the game
    RectangleShape sink = createRectangle(50, 50, windowCenter, Color::Blue);
    Text score    = createText("", origin, myFont, Color::Red);
    Text minScore = createText("", {0.f, score.getCharacterSize() + 10.f}, myFont, Color::Yellow);

    while (game.window.isOpen()) {

        // Updating the time
        tlast = tcur;
        tcur = high_resolution_clock::now();

        duration<float, std::milli> time_span = tcur - tlast;
        deltaTime = time_span.count() / 1000;
        game.playTime += deltaTime;
        game.globTime += deltaTime;

        // Currently only handles keys: WASD and escape
        for (auto event = Event{}; game.window.pollEvent(event);){
            handleEvent(event, game.window, player);
        }

        // Handling of player movement and 'gravitation' towards the sink in the middle
        player.x_vel = (player.dset ? 1.f : 0.f) + (player.aset ? -1.f : 0.f);
        player.y_vel = (player.sset ? 1.f : 0.f) + (player.wset ? -1.f : 0.f);
        player.shape.move(player.speed * normalized(Vector2f(player.x_vel, player.y_vel)));
        Vector2f gravity = sink.getPosition() - player.shape.getPosition();

        // Points calculations
        long long multiplier = exp(7.5f / cbrt(length(gravity))) - 1;
        game.points   += (long long) game.playTime * multiplier;
        game.minPoints = (long long) pow(game.playTime, 3);
        score.setString("Score: " + std::to_string(game.points) + ", current bonus: " + std::to_string((long long) multiplier));
        minScore.setString("Stay above: " + std::to_string(game.minPoints));

        // Game-over logic
        if(intersects(player.shape, sink) || game.points < game.minPoints){

            Text gameover("Game over!\nYour points: " + std::to_string(game.points), myFont, 100);
            centerText(gameover, windowCenter);

            game.window.clear();
            game.window.draw(gameover);
            game.window.display();
            sleep(sf::seconds(1.f));
            break;
        }

        // Drawing all the objects
        game.window.clear();
        game.window.draw(sink);
        game.window.draw(player.shape);
        game.window.draw(minScore);
        game.window.draw(score);
        game.window.display();

        player.shape.move(0.01f * gravity);
    }

    game.window.close();
    return 0;
}


