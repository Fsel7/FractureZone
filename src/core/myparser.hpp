#include <tinyxml2.h>
#include <headers/game.hpp>

#include <string>

#pragma once

namespace sf {

class XMLParser {

protected:
    std::vector<Vector2f> m_validSpawnerLocations = {};
    tinyxml2::XMLNode* gameRoot = nullptr;
    tinyxml2::XMLNode* sceneRoot = nullptr;
    ref<Game> m_parsedGame = nullptr;
    ref<Player> m_parsedPlayer = nullptr;

    tinyxml2::XMLDocument gameDoc;
    tinyxml2::XMLDocument sceneDoc;

protected:
    const char* removeWhitespace(const char* string);
    const char* removeWhitespace(const std::string &string);
    Vector2f parseVector2f(const char* string);
    Color parseColor(const char* string);

    Shape* parseShape(tinyxml2::XMLElement *shape, const Vector2f position, const Color color = Color::Black);

    void parseGame();
    void parseScene();
    void parseWaves();
    
    bool stringEndsIn(const char* string, const char* ending);

public:
    XMLParser(const char* gamePath);
    
    // Returns false if an error occured
    void execute();
    ref<Game> getGame(){ return m_parsedGame; }
    ref<Player> getPlayer() { return m_parsedPlayer; }


};




}