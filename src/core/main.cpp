#include <mygame.hpp>

#include <tinyxml2.h>

int main() {

    // tinyxml2::XMLDocument gameDoc;
    // tinyxml2::XMLError error = gameDoc.LoadFile("resources/game.xml");

    // if (error != tinyxml2::XML_SUCCESS) return 1;

    // tinyxml2::XMLNode* root = gameDoc.FirstChild();
    // if (root == nullptr) return false;


    sf::GameEngine engine(42);
    engine.execute();

    return 0;
}


