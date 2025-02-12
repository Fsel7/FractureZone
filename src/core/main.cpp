#include <mygame.hpp>

#include "myparser.hpp"
#include <tinyxml2.h>

int main() {
    const auto gamePath = std::filesystem::path("resources") / "game.xml";
    
    sf::XMLParser parser(gamePath);

    // Try-catch currently redundant, as no exceptions are thrown - in case of errors,
    // the program immediately terminates due to asserts!
    try {
        parser.execute();    
    } catch (...) {
        std::cout << "Parsing went wront somewhere!";
        abort();
    }
    
    auto engine = parser.getGameEngine();
    engine->execute();

    return 0;
}