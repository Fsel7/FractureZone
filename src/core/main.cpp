#include <mygame.hpp>

#include <tinyxml2.h>

int main() {

    // TODO: Add readable error messages and terminate!

    tinyxml2::XMLDocument gameDoc;
    tinyxml2::XMLError gameError = gameDoc.LoadFile("resources/game.xml");
    if (gameError != tinyxml2::XML_SUCCESS)
        printf("%d", -1);

    tinyxml2::XMLNode* gameRoot = gameDoc.FirstChild();
    if (gameRoot == nullptr)
        printf("%d", -2);

    tinyxml2::XMLElement* mapPath = gameRoot->FirstChildElement("scene");
    if (mapPath == nullptr)
        printf("%d", -3);

    auto sceneFileName = ("resources/" + std::string(mapPath->Attribute("filename"))).c_str();
    tinyxml2::XMLDocument sceneDoc;
    tinyxml2::XMLError sceneError = sceneDoc.LoadFile(sceneFileName);
    if (sceneError != tinyxml2::XML_SUCCESS)
        printf("%d", -4);

    tinyxml2::XMLNode* sceneRoot = sceneDoc.FirstChild();
    if (sceneRoot == nullptr)
        printf("%d", -5);

    std::vector<sf::Vector2f> validSpawnerLocations = {};
    std::vector<sf::BlackHole> blackholes = {};
    auto screen = sceneRoot->FirstChildElement("screen");
    int width = screen->IntAttribute("width");
    int height = screen->IntAttribute("height");

    // TODO: Add a method to read a vector from a char*, see below for implementation

    auto player = sceneRoot->FirstChildElement("player");

    // BlackHole parsing ------------------------------

    auto blackhole = sceneRoot->FirstChildElement("blackhole");
    while(blackhole != nullptr){
        float gravity = blackhole->FloatAttribute("gravity_mult");
        auto pos = blackhole->Attribute("position");
        int index = -1; int x = 0; int y = 0;
        while(pos[++index] !=',')
            x = 10 * x + pos[index] - '0';
        while(++index < strlen(pos))
            y = 10 * y + pos[index] - '0';

        sf::Vector2f position(x, y);
        blackholes.push_back({position, gravity});

        blackhole = blackhole->NextSiblingElement("blackhole");
    }

    // SpawnerLocation parsing ------------------------------

    auto spawnerLoc = sceneRoot->FirstChildElement("spawner_location");
    while(spawnerLoc != nullptr){
        auto pos = spawnerLoc->Attribute("position");

        int index = -1; int x = 0; int y = 0;
        while(pos[++index] !=',')
            x = 10 * x + pos[index] - '0';
        while(++index < strlen(pos))
            y = 10 * y + pos[index] - '0';

        validSpawnerLocations.push_back({1.f * x, 1.f * y});
        spawnerLoc = spawnerLoc->NextSiblingElement("spawner_location");
    }


    // std::vector<sf::Wave> waves = {};
    tinyxml2::XMLNode* wave = gameRoot->FirstChildElement("wave");
    while(wave != nullptr){
        tinyxml2::XMLNode* spawner = wave->FirstChildElement("spawner");
        while(spawner != nullptr){
            // TODO: Read all relevant stats from the spawner here!
            spawner = spawner->NextSiblingElement("spawner");
        }
        wave = wave->NextSiblingElement("wave");
    }

    // sf::GameEngine engine(42);
    // engine.execute();

    return 0;
}


