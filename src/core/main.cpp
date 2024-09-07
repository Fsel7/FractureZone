#include <mygame.hpp>

#include "myparser.hpp"
#include <tinyxml2.h>

int main() {
    using namespace sf;

    const char* gamePath = "resources/game.xml";

    XMLParser parser(gamePath);
    parser.execute();
    try{
        parser.execute();    
    }catch (...){
        assert_condition(false, "Parsing went wront somewhere!");
    }
    
    auto game = parser.getGame();
    auto player = parser.getPlayer();

    GameEngine engine(*game, *player, 42);
    engine.execute();

    return 0;
}


