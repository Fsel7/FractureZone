#include <mygame.hpp>

#include "myparser.hpp"
#include <tinyxml2.h>

int main() {

    // TODO: Add readable error messages and terminate!
    const char* gamePath = "resources/game.xml";

    sf::XMLParser parser(gamePath);
    parser.execute();
    if(!parser.execute()){
        ;// throw error
    }
    sf::Game* game = parser.getGame();
    sf::Player* player = parser.getPlayer();

    sf::GameEngine engine(game, player, 42);
    engine.execute();

    return 0;
}


