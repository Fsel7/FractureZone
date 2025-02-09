#include <tinyxml2.h>
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
    ref<Game> getGame() { return m_parsedGame; }
    ref<Player> getPlayer() { return m_parsedPlayer; }

private:
    std::vector<Vector2f> m_validSpawnerLocations = {};
    tinyxml2::XMLNode* gameRoot = nullptr;
    tinyxml2::XMLNode* sceneRoot = nullptr;
    ref<Game> m_parsedGame = nullptr;
    ref<Player> m_parsedPlayer = nullptr;

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
    void parseWaves() const;
    
    bool stringEndsIn(const std::string &string, const std::string &ending) const;

};


}