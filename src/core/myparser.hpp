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
    Game* m_parsedGame = nullptr;
    Player* m_parsedPlayer = nullptr;

    tinyxml2::XMLDocument gameDoc;
    tinyxml2::XMLDocument sceneDoc;

protected:
    const char* removeWhitespace(const char* string);
    const char* removeWhitespace(const std::string &string);
    Vector2f parseVector2f(const char* string);
    Color parseColor(const char* string);

    Shape* parseShape(tinyxml2::XMLElement *shape, const Vector2f position, const Color color = Color::Black);

    bool parseGame();
    bool parseScene();
    bool parseWaves();
    
    bool stringEndsIn(const char* string, const char* ending);

public:
    XMLParser(const char* gamePath);

    ~XMLParser() { delete m_parsedGame; delete m_parsedPlayer; }
    
    // Returns false if an error occured
    bool execute();
    Game* getGame(){ return m_parsedGame; }
    Player* getPlayer() { return m_parsedPlayer; }


};




}