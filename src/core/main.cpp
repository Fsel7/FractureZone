#include <mygame.hpp>

#include <tinyxml2.h>

int main() {

    tinyxml2::XMLDocument gameDoc;
    tinyxml2::XMLError gameError = gameDoc.LoadFile("resources/game.xml");
    if (gameError != tinyxml2::XML_SUCCESS) return 1;

    tinyxml2::XMLNode* gameRoot = gameDoc.FirstChild();
    if (gameRoot == nullptr) return 1;

    tinyxml2::XMLNode* mapPath = gameRoot->FirstChildElement("scene");
    if (mapPath == nullptr) return 1;

    // TODO: Read SPAWNER locations from gameDoc

    auto sceneFileName = ("resources/" + std::string(mapPath->FirstChild()->Value())).c_str();
    tinyxml2::XMLDocument sceneDoc;
    tinyxml2::XMLError sceneError = sceneDoc.LoadFile(sceneFileName);
    if (sceneError != tinyxml2::XML_SUCCESS) return 1;

    tinyxml2::XMLNode* sceneRoot = sceneDoc.FirstChild();
    if (sceneRoot == nullptr) return 1;

    sf::GameEngine engine(42);
    engine.execute();

    return 0;
}


