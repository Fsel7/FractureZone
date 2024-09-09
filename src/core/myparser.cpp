#include "myparser.hpp"
#include <headers/core.hpp>
#include <headers/objecttransformations.hpp>

#include <limits>

namespace sf {

    XMLParser::XMLParser(const char* gamePath) {
        assert_condition(stringEndsIn(gamePath, ".xml"), "The game path has to point to an .xml file!");

        tinyxml2::XMLError gameError = gameDoc.LoadFile(gamePath);
        assert_condition(gameError == tinyxml2::XML_SUCCESS, "Error loading the game xml");

        gameRoot = gameDoc.FirstChild();

        tinyxml2::XMLElement* sceneElement = gameRoot->FirstChildElement("scene");
        assert_condition(sceneElement != nullptr, "The game xml needs an element containing a path to the scene");

        const char* sceneFileName = sceneElement->Attribute("filename");
        assert_condition(sceneFileName != "", "The scene's filename must not be empty");
        assert_condition(stringEndsIn(sceneFileName, ".xml"), "The scene file has to be of type .xml!");

        auto scenePath = ("resources/" + std::string(sceneFileName)).c_str();

        tinyxml2::XMLError sceneError = sceneDoc.LoadFile(scenePath);
        assert_condition(sceneError == tinyxml2::XML_SUCCESS, "Error loading the game xml");

        sceneRoot = sceneDoc.FirstChild();
    }

    Vector2f XMLParser::parseVector2f(const char* string){
        const char* array = removeWhitespace(string);

        int index = -1; int x = 0; int y = 0;
        while(array[++index] !=',')
            x = 10 * x + array[index] - '0';
        while(++index < (int)strlen(array))
            y = 10 * y + array[index] - '0';

        return {1.f * x, 1.f * y};
    }

    Color XMLParser::parseColor(const char* string, const int opacity){
        const char* array = removeWhitespace(string);

        int index = -1; int x = 0; int y = 0; int z = 0;
        while(array[++index] !=',')
            x = 10 * x + array[index] - '0';
        while(array[++index] !=',')
            y = 10 * y + array[index] - '0';
        while(++index < (int)strlen(array))
            z = 10 * z + array[index] - '0';
            
        return Color(static_cast<Uint8>(x), static_cast<Uint8>(y), static_cast<Uint8>(z), static_cast<Uint8>(opacity));
    }

    const char* XMLParser::removeWhitespace(const char* string) {
        std::string res = "";
        for(size_t i = 0; i < strlen(string); i++){
            char c = string[i];
            if(c != ' ')
                res.push_back(c);
        }
        return res.c_str();
    }

    const char* XMLParser::removeWhitespace(const std::string &string) {
        std::string res = "";
        for(size_t i = 0; i < string.size(); i++){
            char c = string[i];
            if(c != ' ')
                res.push_back(c);
        }
        return res.c_str();
    }

    bool XMLParser::stringEndsIn(const char* string, const char* ending) {
        int lenEnd = strlen(ending);
        if(lenEnd == 0)
            return true;
        
        int lenStr = strlen(string);
        if(lenEnd > lenStr)
            return false;
        for(int i = 0; i<lenEnd; i++)
            if(string[lenStr - 1 - i] != ending[lenEnd - 1 - i])
                return false;
        return true;
    }

    // Delete the pointer after using it!
    Shape* XMLParser::parseShape(tinyxml2::XMLElement *shape, const Vector2f position, const Color color) {
        auto type = shape->Attribute("type");
        if(strcmp(type, "rectangular") == 0){
            float dimX = shape->FloatAttribute("width");
            float dimY = shape->FloatAttribute("height");
            RectangleShape* rect = new RectangleShape({dimX, dimY});
            rect->setOrigin(Vector2f(dimX/2, dimY/2));
            rect->setPosition(position);
            rect->setFillColor(color);
            return rect;
        } else {
            if(strcmp(type, "circular") != 0)
                printf("We only support circles and rectangles but got %s !\n", type);

            float radius = shape->FloatAttribute("radius", 1.f);
            CircleShape* circle = new CircleShape(radius);
            circle->setOrigin(Vector2f(radius, radius));
            circle->setPosition(position);
            circle->setFillColor(color);
            return circle;
        }
    }
    
    void XMLParser::parseGame() {
        auto window = gameRoot->FirstChildElement("window");
        auto windowName = window->Attribute("name");
        int width = window->IntAttribute("width");
        int height = window->IntAttribute("height");

        int maxFps = gameRoot->FirstChildElement("maxFps")->IntAttribute("value");

        auto fontName = gameRoot->FirstChildElement("font")->Attribute("filename");
        assert_condition(stringEndsIn(fontName, ".ttf"), "The font should point to an .ttf file!");

        auto fontPath = "resources/" + std::string(fontName);

        m_parsedGame.reset(new Game(width, height, maxFps, windowName, fontPath));
    }

    void XMLParser::parseWaves() {
        tinyxml2::XMLNode* wave = gameRoot->FirstChildElement("wave");
        while(wave != nullptr){
            auto spawner = wave->FirstChildElement("spawner");
            while(spawner != nullptr){
                unsigned int location = (unsigned) spawner->IntAttribute("location");
                assert_condition(location < m_validSpawnerLocations.size(), "A spawner references an invalid spawn location");
                Vector2f pos = m_validSpawnerLocations[location];

                auto offset = spawner->FloatAttribute("offset");
                auto delay = spawner->FloatAttribute("delay");
                auto start = spawner->FloatAttribute("start", 0.f);
                auto end = spawner->FloatAttribute("end", std::numeric_limits<float>::max());
                Color color = Color::Black;
                if(spawner->Attribute("color") != nullptr)
                    color = parseColor(spawner->Attribute("color"));

                auto enemy = spawner->FirstChildElement("enemy");
                auto minSpeed = enemy->FloatAttribute("minspeed");
                auto maxSpeed = enemy->FloatAttribute("maxspeed");
                assert_condition(maxSpeed >= minSpeed, "The minimum speed cannot be greater than the maximum speed!");
                assert_condition(minSpeed > 0,  "The minimum speed should be bigger than 0!");

                SpawnerData data = {pos, delay, offset, minSpeed, maxSpeed, start, end};
                auto shape = enemy->FirstChildElement("shape");
                auto type = shape->Attribute("type");
                Sprite spawnerSprite(m_parsedGame->inactiveSpawnerTexture);
                centerSprite(spawnerSprite, pos);
                if(strcmp(type, "rectangular") == 0) {
                    auto minW = shape->FloatAttribute("minw", 10.f);
                    auto maxW = shape->FloatAttribute("maxw", 10.f);
                    auto minH = shape->FloatAttribute("minh", 10.f);
                    auto maxH = shape->FloatAttribute("maxh", 10.f);
                    auto spawn = RectangularSpawner(data, minW, maxW, minH, maxH, color);
                    spawn.m_spawnerSprite = spawnerSprite;
                    m_parsedGame->addSpawner(spawn);
                } else {
                    if(strcmp(type, "circular") != 0)
                        printf("We only support circles and rectangles but got %s !\n", type);
                    auto minR = shape->FloatAttribute("minr", 10.f);
                    auto maxR = shape->FloatAttribute("maxr", 10.f);
                    auto spawn = CircularSpawner(data, minR, maxR, color);
                    spawn.m_spawnerSprite = spawnerSprite;
                    m_parsedGame->addSpawner(spawn);
                }
                spawner = spawner->NextSiblingElement("spawner");

            }
            wave = wave->NextSiblingElement("wave");
            
        }
    }

    void XMLParser::parseScene() {
        // Get Map size
        auto map = sceneRoot->FirstChildElement("map");
        int width = map->IntAttribute("width");
        int height = map->IntAttribute("height");
        
        // Get Background
        std::string backgroundPath;
        auto background = sceneRoot->FirstChildElement("background");
        
        if(background == nullptr)
            backgroundPath = "resources/defaultBackground.jpg";
        else {
            auto bgFileName = background->Attribute("filename");
            bool validType = stringEndsIn(bgFileName, ".jpg") || stringEndsIn(bgFileName, ".png");
            assert_condition(validType, "The background has to be of type .jpg or .png!");
            backgroundPath = "resources/" + std::string(bgFileName);
        }

        m_parsedGame->backgroundTexture.loadFromFile(backgroundPath);

        float scaleX = (float) width /  m_parsedGame->backgroundTexture.getSize().x;
        float scaleY = (float) height /  m_parsedGame->backgroundTexture.getSize().y;

        m_parsedGame->backgroundSprite.setTexture(m_parsedGame->backgroundTexture);
        m_parsedGame->backgroundSprite.setScale(scaleX, scaleY);
        
        // Parse player
        auto player = sceneRoot->FirstChildElement("player");

        auto speed = player->FloatAttribute("speed");

        auto pos = parseVector2f(player->Attribute("position"));
        auto color = parseColor(player->Attribute("color"));
        auto shape = player->FirstChildElement("shape");
        Shape* playerShape = parseShape(shape, pos, color);

        m_parsedPlayer.reset(new Player(playerShape, speed));

        // Parse blackholes
        auto blackhole = sceneRoot->FirstChildElement("blackhole");
        while(blackhole != nullptr){
            float gravity = blackhole->FloatAttribute("gravity_mult");
            auto pos = blackhole->Attribute("position");
            
            m_parsedGame->addBlackHole(BlackHole{parseVector2f(pos), gravity});
            blackhole = blackhole->NextSiblingElement("blackhole");
        }

        // Parse spawners
        auto actSpawnerFileName = sceneRoot->FirstChildElement("active_spawner")->Attribute("filename");
        auto inactSpawnerFileName = sceneRoot->FirstChildElement("inactive_spawner")->Attribute("filename");
        bool validType = (stringEndsIn(inactSpawnerFileName, ".jpg") || stringEndsIn(inactSpawnerFileName, ".png"))
                      && (stringEndsIn(actSpawnerFileName, ".jpg")   || stringEndsIn(actSpawnerFileName, ".png"));
        assert_condition(validType, "The spawner textures have to be of type .jpg or .png!");
        m_parsedGame->activeSpawnerTexture.loadFromFile("resources/" + std::string(actSpawnerFileName));
        m_parsedGame->inactiveSpawnerTexture.loadFromFile("resources/" + std::string(inactSpawnerFileName));

        auto spawnerLoc = sceneRoot->FirstChildElement("spawner_location");
        while(spawnerLoc != nullptr){
            auto pos = spawnerLoc->Attribute("position");

            m_validSpawnerLocations.push_back(parseVector2f(pos));
            spawnerLoc = spawnerLoc->NextSiblingElement("spawner_location");
        }

        // Parse bonus zones
        auto bonusZone = sceneRoot->FirstChildElement("bonus_zone");
        while(bonusZone != nullptr){
            auto width = bonusZone->IntAttribute("width");
            auto height = bonusZone->IntAttribute("height");
            auto center = parseVector2f(bonusZone->Attribute("center"));
            auto opacity = bonusZone->IntAttribute("opacity");
            auto color = parseColor(bonusZone->Attribute("color"), opacity);
            auto multiplier = bonusZone->IntAttribute("multiplier");

            RectangleShape rectangle = createRectangle(1.f * width, 1.f * height, center, color);
            color.a = 255;
            Text label = createText("x" + std::to_string(multiplier), rectangle.getPosition(), m_parsedGame->font, color, 20);
            centerText(label, rectangle.getPosition());
            
            BonusZone bonus;
            bonus.multiplier = multiplier;
            bonus.rectangle = rectangle;
            bonus.label = label;
            m_parsedGame->bonusZones.push_back(bonus);
            bonusZone = bonusZone->NextSiblingElement("bonus_zone");
        }
    }

    void XMLParser::execute() {
        parseGame();
        parseScene();
        parseWaves();
    }
}