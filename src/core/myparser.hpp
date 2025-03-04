#include <tinyxml2.h>
#include <headers/engine.hpp>
#include <headers/game.hpp>

#include <string>
#include <filesystem>

#pragma once

namespace sf {

class XMLParser {

public:
    XMLParser(const std::filesystem::path &gamePath);
    
    // Parses the game and scene
    void execute();
    ref<GameEngine> getGameEngine() { return m_engine; }

private:
    std::vector<Vector2f> m_validSpawnerLocations = {};
    tinyxml2::XMLNode* gameRoot = nullptr;
    tinyxml2::XMLNode* sceneRoot = nullptr;

    Game m_parsedGame;
    Player m_parsedPlayer;
    ref<GameEngine> m_engine = nullptr;

    tinyxml2::XMLDocument gameDoc;
    tinyxml2::XMLDocument sceneDoc;

private:
    std::string removeWhitespace(const std::string &string) const;
    Vector2f parseVector2f(const std::string &string) const;
    Color parseColor(const std::string &string, const int opacity = 255) const;
    std::filesystem::path parseFilename(const std::string &attribute, const std::string &fallback, const bool useGameRoot) const;

    ref<Shape> parseShape(const tinyxml2::XMLElement *shape, const Vector2f position, const Color color = Color::Black) const;

    void parseGame();
    void parseScene();
    void parseWaves();

    void buildEngine();
    
    bool stringEndsIn(const std::string &string, const std::string &ending) const;

};


}