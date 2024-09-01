#include <SFML/Graphics.hpp>
#include <chrono>

bool intersects(const sf::CircleShape &circle, const sf::Sprite &sprite);

int main()
{
    using namespace std::chrono;
    using namespace sf;

    high_resolution_clock::time_point tlast = high_resolution_clock::now();
    high_resolution_clock::time_point tcur = high_resolution_clock::now();

    float playTime = 0;
    float globTime = 0;
    float deltaTime = 0;
    long long points = 0;
    long long minPoints = 0;
    float x_vel = 0;
    float y_vel = 0;

    const float speed = 9;

    bool wset = false;
    bool sset = false;
    bool aset = false;
    bool dset = false;

    size_t window_x = 1200u;
    size_t window_y = 900u;
    auto window = RenderWindow{{window_x, window_y}, "Very Cool Game"};
    window.setFramerateLimit(32);

    CircleShape circle(10.f);
    circle.setFillColor(Color::Green);

    Image image;
    image.create(10, 10, Color::Blue);
    Texture tex;
    tex.loadFromImage(image);
    Sprite sink(tex);
    sink.move(0.5f * window_x, 0.5f * window_y);

    Font myFont;
    if (!myFont.loadFromFile("fonts/arial.ttf")){
        window.close();
        return 0;
    }

    Text score;
    score.setFont(myFont);
    score.setFillColor(Color::Red);
    score.setStyle(Text::Regular);

    Text minScore;
    minScore.setFont(myFont);
    minScore.setFillColor(Color::Yellow);
    minScore.setStyle(Text::Regular);
    minScore.move({0.f, score.getCharacterSize() + 10.f});

    while (window.isOpen())
    {
        auto windowCenter = window.getView().getCenter();
        tlast = tcur;
        tcur = high_resolution_clock::now();

        duration<float, std::milli> time_span = tcur - tlast;
        deltaTime = time_span.count() / 1000;
        playTime += deltaTime;
        globTime += deltaTime;

        for (auto event = Event{}; window.pollEvent(event);){
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == Event::KeyPressed){
                switch (event.key.code){
                    case Keyboard::Key::Escape:
                    {
                        window.close();
                        break;
                    }
                    case Keyboard::Key::W:
                    {
                        wset = true;
                        break;
                    }
                    case Keyboard::Key::S:
                    {
                        sset = true;
                        break;
                    }
                    case Keyboard::Key::D:
                    {
                        dset = true;
                        break;
                    }
                    case Keyboard::Key::A:
                    {
                        aset = true;
                        break;
                    }
                }
            }
            else if (event.type == Event::KeyReleased) {
                switch (event.key.code){
                    case Keyboard::Key::W:
                    {
                        wset = false;
                        break;
                    }
                    case Keyboard::Key::S:
                    {
                        sset = false;
                        break;
                    }
                    case Keyboard::Key::D:
                    {
                        dset = false;
                        break;
                    }
                    case Keyboard::Key::A:
                    {
                        aset = false;
                        break;
                    }
                }
            }
        }

        x_vel = (dset ? 1.f : 0.f) + (aset ? -1.f : 0.f);
        y_vel = (sset ? 1.f : 0.f) + (wset ? -1.f : 0.f);
        Vector2f movement = {x_vel, y_vel};

        circle.move(speed * movement.normalized());

        auto size = sink.getTextureRect().getSize();
        float r = circle.getRadius();
        Vector2f gravity = sink.getPosition() - circle.getPosition() + Vector2f(0.5f * size.x - r - 0.5f, 0.5f * size.y - r - 0.5f);

        long long multiplier = exp(7.5f / cbrt(gravity.length()));
        points += (long long) playTime * multiplier;
        minPoints = (long long) pow(playTime, 3);
        score.setString("Score: " + std::to_string(points) + ", current bonus: " + std::to_string((long long) multiplier));
        minScore.setString("Stay above: " + std::to_string(minPoints));

        if(intersects(circle, sink) || points < minPoints){

            Text gameover("Game over!\nYour points: " + std::to_string(points), myFont, 100);
            FloatRect textRect = gameover.getLocalBounds();
            gameover.setFillColor(Color::Red);
            gameover.setOrigin(textRect.left + 0.5f * textRect.width, textRect.top  + 0.5f * textRect.height);
            gameover.setPosition(windowCenter);

            window.clear();
            window.draw(gameover);
            window.display();
            sleep(sf::seconds(3.f));
            break;
        }

        window.clear();
        window.draw(sink);
        window.draw(circle);
        window.draw(minScore);
        window.draw(score);
        window.display();

        circle.move(0.01f * gravity);
    }

    window.close();
    return 0;
}

bool intersects(const sf::CircleShape &circle, const sf::Sprite &sprite)
{
    auto size = sprite.getTextureRect().getSize();
    float width = 0.5f * size.x;
    float height = 0.5f * size.y;
    sf::Vector2f rcenter = sprite.getPosition() + sf::Vector2f(width - 0.5f, height - 0.5f);

    float radius = circle.getRadius();
    auto ccenter = circle.getPosition() + sf::Vector2f(radius, radius);

    float dist_x = std::abs(ccenter.x - rcenter.x);
    float dist_y = std::abs(ccenter.y - rcenter.y);

    if (dist_x > width + radius)
        return false;

    if (dist_y > height + radius)
        return false;

    if (dist_x <= width)
        return true;

    if (dist_y <= height)
        return true;

    float cornerDistance_sq = (dist_x - width) * (dist_x - width) + (dist_y - height) * (dist_y - height);

    return (cornerDistance_sq <= radius * radius);
}
