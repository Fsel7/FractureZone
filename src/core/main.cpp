#include <mygame.hpp>

#include "myparser.hpp"
#include <tinyxml2.h>

int main() {
    const std::filesystem::path gamePath = std::filesystem::path("resources") / "game.xml";

    sf::XMLParser parser(gamePath);
    try {
        parser.execute();    
    } catch (...) {
        assert_condition(false, "Parsing went wront somewhere!");
    }
    
    auto game = parser.getGame();
    auto player = parser.getPlayer();

    sf::GameEngine engine(*game, *player, 42);
    engine.execute();

    return 0;
}


