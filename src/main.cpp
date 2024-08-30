#include <SFML/Graphics.hpp>
#include <chrono>

bool intersects(const sf::CircleShape& circle, const sf::Sprite& sprite);

int main()
{
    size_t window_x = 1200u; size_t window_y = 900u;
    auto window = sf::RenderWindow{ { window_x, window_y }, "Very Cool Game" };
    window.setFramerateLimit(32);


    sf::CircleShape circle(50.f);
    circle.setFillColor(sf::Color::Green);

    sf::Image image;
    image.create(90, 90, sf::Color::Blue);
    sf::Texture tex;
    tex.loadFromImage(image);
    sf::Sprite sink(tex);
    sink.move(window_x/2, window_y/2);

    using namespace std::chrono;
    high_resolution_clock::time_point tlast = high_resolution_clock::now();
    high_resolution_clock::time_point tcur = high_resolution_clock::now();

    double time = 0;
    double deltaTime = 0;
    float x_vel = 0;
    float y_vel = 0;

    bool wset = false;
    bool sset = false;
    bool aset = false;
    bool dset = false;

    while (window.isOpen())
    {
        tlast = tcur;
        tcur = high_resolution_clock::now();
        
        duration<double, std::milli> time_span = tcur - tlast;
        deltaTime = time_span.count()/1000;
        time += deltaTime;
        
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code){
                    case sf::Keyboard::Key::Escape:{
                        window.close();
                        break;
                    }
                    case sf::Keyboard::Key::W:{
                        wset = true;
                        break;
                    }
                    case sf::Keyboard::Key::S:{
                        sset = true;
                        break;
                    }
                    case sf::Keyboard::Key::D:{
                        dset = true;
                        break;
                    }
                    case sf::Keyboard::Key::A:{
                        aset = true;
                        break;
                    }
                }
            } else if (event.type == sf::Event::KeyReleased) {
                switch (event.key.code){
                    case sf::Keyboard::Key::W:{
                        wset = false;
                        break;
                    }
                    case sf::Keyboard::Key::S:{
                        sset = false;
                        break;
                    }
                    case sf::Keyboard::Key::D:{
                        dset = false;
                        break;
                    }
                    case sf::Keyboard::Key::A:{
                        aset = false;
                        break;
                    }
                }
            }
        }

        x_vel = (dset ? 6.f : 0.f) + (aset ? -6.f : 0.f);
        y_vel = (sset ? 6.f : 0.f) + (wset ? -6.f : 0.f);

        circle.move({x_vel, y_vel});

        if(intersects(circle, sink)){
            window.close();
            break;
        }

        window.clear();
        window.draw(sink);
        window.draw(circle);
        window.display();

        auto size = sink.getTextureRect().getSize();
        float r = circle.getRadius();
        sf::Vector2f gravity = sink.getPosition() - circle.getPosition() + sf::Vector2f(0.5f * size.x - r - 0.5f, 0.5f * size.y - r - 0.5f);
        gravity = 0.01f * gravity;

        circle.move(gravity);
    }

    return 0;
}

bool intersects(const sf::CircleShape& circle, const sf::Sprite& sprite) {
    auto size = sprite.getTextureRect().getSize();
    int width  = 0.5f * size.x;
    int height = 0.5f * size.y;
    sf::Vector2f rcenter = sprite.getPosition() + sf::Vector2f(width - 0.5f, height - 0.5f);

    float radius = circle.getRadius();
    auto ccenter = circle.getPosition() + sf::Vector2f(radius, radius);
    
    float dist_x = std::abs(ccenter.x - rcenter.x);
    float dist_y = std::abs(ccenter.y - rcenter.y);

    if (dist_x > (width + radius)) { return false; }
    if (dist_y > (height + radius)) { return false; }

    if (dist_x <= (width)) { return true; } 
    if (dist_y <= (height)) { return true; }

    float cornerDistance_sq = (dist_x - width) * (dist_x - width) + (dist_y - height) * (dist_y - height);

    return (cornerDistance_sq <= (radius * radius));
}
