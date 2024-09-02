#include <SFML/Graphics.hpp>
#include <chrono>
#include "eventhandler.cpp"
#include "objecthandler.cpp"
#include "intersectiontester.cpp"
#include "setup.cpp"

int main() {
    using namespace std::chrono;
    using namespace sf;

    if(!runsetup())
        return 1;

    RenderWindow window({window_x, window_y}, "Very Cool Game");
    window.setFramerateLimit(64);
    
    auto windowCenter = window.getView().getCenter();    

    // Timing initialization stuff
    high_resolution_clock::time_point tlast = high_resolution_clock::now();
    high_resolution_clock::time_point tcur = high_resolution_clock::now();
    float playTime = 0;
    float globTime = 0;
    float deltaTime = 0;

    // Some gameplay variables
    long long points = 0;
    long long minPoints = 0;
    const float playerSpeed = 9;

    bool wset, sset, aset, dset;
    wset = sset = aset = dset = false;

    // Used to indicated the player's direction
    float x_vel = 0;
    float y_vel = 0;
    
    // Creation of some objects visible in the game
    CircleShape playerCircle = createCircle(10.f, origin, Color::Green);
    RectangleShape sink = createRectangle(100, 100, windowCenter, Color::Blue);

    Text score    = createText("", origin, myFont, Color::Red);
    Text minScore = createText("", {0.f, score.getCharacterSize() + 10.f}, myFont, Color::Yellow);

    while (window.isOpen()) {

        // Updating the time
        tlast = tcur;
        tcur = high_resolution_clock::now();

        duration<float, std::milli> time_span = tcur - tlast;
        deltaTime = time_span.count() / 1000;
        playTime += deltaTime;
        globTime += deltaTime;

        // Currently only handles keys: WASD and escape
        for (auto event = Event{}; window.pollEvent(event);){
            handleEvent(event, window, &wset, &aset, &sset, &dset);
        }

        // Handling of player movement and 'gravitation' towards the sink in the middle
        x_vel = (dset ? 1.f : 0.f) + (aset ? -1.f : 0.f);
        y_vel = (sset ? 1.f : 0.f) + (wset ? -1.f : 0.f);
        Vector2f movement = {x_vel, y_vel};

        playerCircle.move(playerSpeed * movement.normalized());

        float r = playerCircle.getRadius();
        Vector2f gravity = sink.getPosition() - playerCircle.getPosition();

        // Points calculations
        long long multiplier = exp(7.5f / cbrt(gravity.length())) - 1;
        points += (long long) playTime * multiplier;
        minPoints = (long long) pow(playTime, 3);
        score.setString("Score: " + std::to_string(points) + ", current bonus: " + std::to_string((long long) multiplier));
        minScore.setString("Stay above: " + std::to_string(minPoints));

        // Game-over logic
        if(intersects(playerCircle, sink) || points < minPoints){

            Text gameover("Game over!\nYour points: " + std::to_string(points), myFont, 100);
            FloatRect textRect = gameover.getLocalBounds();
            gameover.setFillColor(Color::Red);
            gameover.setOrigin(textRect.left + 0.5f * textRect.width, textRect.top  + 0.5f * textRect.height);
            gameover.setPosition(windowCenter);

            window.clear();
            window.draw(gameover);
            window.display();
            sleep(sf::seconds(1.f));
            window.close();
            return 0;
        }

        // Drawing all the objects
        window.clear();
        window.draw(sink);
        window.draw(playerCircle);
        window.draw(minScore);
        window.draw(score);
        window.display();

        playerCircle.move(0.01f * gravity);
    }

    window.close();
    return 0;
}


