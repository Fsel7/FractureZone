#include <tinyxml2.h>
#include <headers/game.hpp>

#include <string>

#pragma once

namespace sf {

class XMLParser {

private:
    std::vector<Vector2f> m_validSpawnerLocations = {};
    tinyxml2::XMLNode* gameRoot = nullptr;
    tinyxml2::XMLNode* sceneRoot = nullptr;
    ref<Game> m_parsedGame = nullptr;
    ref<Player> m_parsedPlayer = nullptr;

    tinyxml2::XMLDocument gameDoc;
    tinyxml2::XMLDocument sceneDoc;

protected:
    std::string removeWhitespace(const std::string &string);
    Vector2f parseVector2f(const std::string &string);
    Color parseColor(const std::string &string, const int opacity = 255);

    Shape* parseShape(tinyxml2::XMLElement *shape, const Vector2f position, const Color color = Color::Black);

    void parseGame();
    void parseScene();
    void parseWaves();
    
    bool stringEndsIn(const std::string &string, const std::string &ending);

public:
    XMLParser(const char* gamePath);
    
    // Returns false if an error occured
    void execute();
    ref<Game> getGame(){ return m_parsedGame; }
    ref<Player> getPlayer() { return m_parsedPlayer; }


};




}