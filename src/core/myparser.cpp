#include "myparser.hpp"
#include <headers/core.hpp>
#include <headers/objecttransformations.hpp>

#include <limits>

namespace sf {

    XMLParser::XMLParser(const std::filesystem::path &gamePath) {
        assert_condition(stringEndsIn(gamePath.string(), ".xml"), "The game path has to point to an .xml file!");

        const tinyxml2::XMLError gameError = gameDoc.LoadFile(gamePath.string().c_str());
        assert_condition(gameError == tinyxml2::XML_SUCCESS, "Error loading the game xml");

        gameRoot = gameDoc.FirstChild();

        const tinyxml2::XMLElement* sceneElement = gameRoot->FirstChildElement("scene");
        assert_condition(sceneElement != nullptr, "The game xml needs an element containing a path to the scene");

        const char* sceneFileName = sceneElement->Attribute("filename");
        assert_condition(stringEndsIn(sceneFileName, ".xml"), "The scene file has to be of type .xml!");

        const auto scenePath = std::filesystem::path("resources") / sceneFileName;
        const tinyxml2::XMLError sceneError = sceneDoc.LoadFile(scenePath.string().c_str());
        assert_condition(sceneError == tinyxml2::XML_SUCCESS, "Error loading the scene xml");

        sceneRoot = sceneDoc.FirstChild();
    }

    Vector2f XMLParser::parseVector2f(const std::string &string) const {
        const std::string array = removeWhitespace(string);            

        int index = -1; int x = 0; int y = 0;
        while(array[++index] !=',')
            x = 10 * x + array[index] - '0';
        while(++index < static_cast<int>(array.length()))
            y = 10 * y + array[index] - '0';
        return {1.f * x, 1.f * y};
    }

    Color XMLParser::parseColor(const std::string &string, const int opacity) const {
        const std::string array = removeWhitespace(string);

        int index = -1; int x = 0; int y = 0; int z = 0;
        while(array[++index] !=',')
            x = 10 * x + array[index] - '0';
        while(array[++index] !=',')
            y = 10 * y + array[index] - '0';
        while(++index < static_cast<int>(array.length()))
            z = 10 * z + array[index] - '0';
            
        return Color(static_cast<uint8_t>(x), static_cast<uint8_t>(y), static_cast<uint8_t>(z), static_cast<uint8_t>(opacity));
    }

    std::filesystem::path XMLParser::parseFilename(const std::string &attribute, const std::string &fallback, const bool useGameRoot) const {
        const auto attributeNode = useGameRoot ? gameRoot->FirstChildElement(attribute.c_str()) : sceneRoot->FirstChildElement(attribute.c_str());
        if(!attributeNode)
            return std::filesystem::path("resources") / fallback;
        
        const auto filename = attributeNode->Attribute("filename");
        bool validType;
        std::string errorMessage;
        if(stringEndsIn(fallback, ".ttf")) {
            validType = stringEndsIn(filename, ".ttf");
            errorMessage = "The" + attribute + "has to be of type .ttf!";
        } else {
            validType = stringEndsIn(filename, ".jpg") || stringEndsIn(filename, ".png");
            errorMessage = "The" + attribute + "has to be of type .jpg or .png!";
        }
     
        assert_condition(validType, errorMessage.c_str());
        return std::filesystem::path("resources") / filename;
    }

    std::string XMLParser::removeWhitespace(const std::string &string) const {
        std::string res = "";
        for(size_t i = 0; i < string.length(); i++){
            const char c = string[i];
            if(c != ' ')
                res.push_back(c);
        }
        return res;
    }

    bool XMLParser::stringEndsIn(const std::string &string, const std::string &ending) const {
        const size_t lenEnd = ending.length();
        if(lenEnd == 0)
            return true;
        
        const size_t lenStr = string.length();
        if(lenEnd > lenStr)
            return false;
        for(size_t i = 0; i<lenEnd; i++)
            if(string[lenStr - 1 - i] != ending[lenEnd - 1 - i])
                return false;
        return true;
    }

    ref<Shape> XMLParser::parseShape(const tinyxml2::XMLElement *shape, const Vector2f position, const Color color) const {
        const auto type = shape->Attribute("type");
        if(strcmp(type, "rectangular") == 0){
            const float dimX = shape->FloatAttribute("width");
            const float dimY = shape->FloatAttribute("height");
            return std::make_shared<RectangleShape>(createRectangle(dimX, dimY, position, color));
        } else {
            if(strcmp(type, "circular") != 0)
                printf("We only support circles and rectangles but got %s !\n", type);

            const float radius = shape->FloatAttribute("radius", 1.f);
            return std::make_shared<CircleShape>(createCircle(radius, position, color));
        }
    }
    
    void XMLParser::parseGame() {
        const auto window      = gameRoot->FirstChildElement("window");
        const auto windowName  = window->Attribute("name");
        const int width        = window->IntAttribute("width");
        const int height       = window->IntAttribute("height");

        m_parsedGame.reset(new Game(width, height, windowName));

        const auto fontName = parseFilename("font", "arial.ttf", true);
        m_parsedGame->m_font.loadFromFile(fontName.string());

        const auto iconPath(parseFilename("icon", "defaultGameIcon.png", true));
        const bool loadIcon = m_parsedGame->m_icon.loadFromFile(iconPath.string());
        assert_condition(loadIcon, "Could not load the window icon!");

        const auto iconSize = m_parsedGame->m_icon.getSize();
        m_parsedGame->window->setIcon(iconSize.x, iconSize.y, m_parsedGame->m_icon.getPixelsPtr());

        // Get lose screen
        const auto loseScreenPath(parseFilename("loseScreen", "defaultGameOver.png", true));
        m_parsedGame->m_lostTexture.loadFromFile(loseScreenPath.string());

        const float scaleX = 1.f * width  /  m_parsedGame->m_lostTexture.getSize().x;
        const float scaleY = 1.f * height /  m_parsedGame->m_lostTexture.getSize().y;

        m_parsedGame->m_lostSprite.setTexture(m_parsedGame->m_lostTexture);
        m_parsedGame->m_lostSprite.setScale(scaleX, scaleY);
    }

    void XMLParser::parseWaves() const {
        tinyxml2::XMLNode* wave = gameRoot->FirstChildElement("wave");
        while(wave != nullptr){
            auto spawner = wave->FirstChildElement("spawner");
            while(spawner != nullptr){
                const uint32_t location = static_cast<uint32_t>(spawner->IntAttribute("location"));
                assert_condition(location < m_validSpawnerLocations.size(), "A spawner references an invalid spawn location");
                const Vector2f pos = m_validSpawnerLocations[location];

                const auto offset = spawner->FloatAttribute("offset");
                const auto delay  = spawner->FloatAttribute("delay");
                const auto start  = spawner->FloatAttribute("start", 0.f);
                const auto end    = spawner->FloatAttribute("end", std::numeric_limits<float>::max());
                Color color(Color::Black);
                if(spawner->Attribute("color") != nullptr)
                    color = parseColor(spawner->Attribute("color"));

                const auto enemy    = spawner->FirstChildElement("enemy");
                const auto minSpeed = enemy->FloatAttribute("minspeed");
                const auto maxSpeed = enemy->FloatAttribute("maxspeed");
                assert_condition(maxSpeed >= minSpeed, "The minimum speed cannot be greater than the maximum speed!");
                assert_condition(minSpeed > 0,  "The minimum speed should be bigger than 0!");

                const SpawnerData data = {pos, delay, offset, minSpeed, maxSpeed, start, end};
                const auto shape = enemy->FirstChildElement("shape");
                const auto type = shape->Attribute("type");
                Sprite spawnerSprite(m_parsedGame->m_inactiveSpawnerTexture);
                centerSprite(spawnerSprite, pos);
                if(strcmp(type, "rectangular") == 0) {
                    const auto minW = shape->FloatAttribute("minw", 10.f);
                    const auto maxW = shape->FloatAttribute("maxw", 10.f);
                    const auto minH = shape->FloatAttribute("minh", 10.f);
                    const auto maxH = shape->FloatAttribute("maxh", 10.f);
                    auto spawn = RectangularSpawner(data, minW, maxW, minH, maxH, color);
                    spawn.m_spawnerSprite = spawnerSprite;
                    m_parsedGame->addSpawner(spawn);
                } else {
                    if(strcmp(type, "circular") != 0)
                        printf("We only support circles and rectangles but got %s !\n", type);
                    const auto minR = shape->FloatAttribute("minr", 10.f);
                    const auto maxR = shape->FloatAttribute("maxr", 10.f);
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
        const auto map = sceneRoot->FirstChildElement("map");
        const auto width = map->IntAttribute("width");
        const auto height = map->IntAttribute("height");
        
        // Get Background
        const auto backgroundPath(parseFilename("background", "defaultBackground.png", false));
        m_parsedGame->m_backgroundTexture.loadFromFile(backgroundPath.string());

        const float scaleX = 1.f * width  /  m_parsedGame->m_backgroundTexture.getSize().x;
        const float scaleY = 1.f * height /  m_parsedGame->m_backgroundTexture.getSize().y;

        m_parsedGame->m_backgroundSprite.setTexture(m_parsedGame->m_backgroundTexture);
        m_parsedGame->m_backgroundSprite.setScale(scaleX, scaleY);
        
        // Parse player
        const auto player = sceneRoot->FirstChildElement("player");
        const auto speed = player->FloatAttribute("speed");

        const auto pos = parseVector2f(player->Attribute("position"));
        const auto color = parseColor(player->Attribute("color"));
        const auto shape = player->FirstChildElement("shape");
        ref<Shape> playerShape = parseShape(shape, pos, color);
        m_parsedPlayer.reset(new Player(playerShape, speed));

        // Parse blackholes
        auto blackhole = sceneRoot->FirstChildElement("blackhole");
        while(blackhole != nullptr){
            const float gravity = blackhole->FloatAttribute("gravity_mult");
            const auto pos = blackhole->Attribute("position");
            
            m_parsedGame->addBlackHole(BlackHole{parseVector2f(pos), gravity});
            blackhole = blackhole->NextSiblingElement("blackhole");
        }

        // Parse spawners
        const auto actSpawnerFileName   = parseFilename("active_spawner",   "defaultActiveSpawner.png",   false);
        const auto inactSpawnerFileName = parseFilename("inactive_spawner", "defaultInactiveSpawner.png", false);

        m_parsedGame->m_activeSpawnerTexture.loadFromFile(actSpawnerFileName.string());
        m_parsedGame->m_inactiveSpawnerTexture.loadFromFile(inactSpawnerFileName.string());

        auto spawnerLoc = sceneRoot->FirstChildElement("spawner_location");
        while(spawnerLoc != nullptr){
            const auto pos = spawnerLoc->Attribute("position");

            m_validSpawnerLocations.push_back(parseVector2f(pos));
            spawnerLoc = spawnerLoc->NextSiblingElement("spawner_location");
        }

        // Parse bonus zones
        auto bonusZone = sceneRoot->FirstChildElement("bonus_zone");
        while(bonusZone != nullptr){
            const auto width = bonusZone->IntAttribute("width");
            const auto height = bonusZone->IntAttribute("height");
            const auto center = parseVector2f(bonusZone->Attribute("center"));
            const auto opacity = bonusZone->IntAttribute("opacity");
            const auto multiplier = bonusZone->IntAttribute("multiplier");
            auto color = parseColor(bonusZone->Attribute("color"), opacity);
            const RectangleShape rectangle = createRectangle(1.f * width, 1.f * height, center, color);
            
            color.a = 255;
            Text label = createText("x" + std::to_string(multiplier), rectangle.getPosition(), m_parsedGame->m_font, color, 20);
            centerText(label, rectangle.getPosition());
            
            BonusZone bonus;
            bonus.multiplier = multiplier;
            bonus.rectangle = rectangle;
            bonus.label = label;
            m_parsedGame->m_bonusZones.push_back(bonus);
            bonusZone = bonusZone->NextSiblingElement("bonus_zone");
        }
    }

    void XMLParser::execute() {
        parseGame();
        parseScene();
        parseWaves();
    }
}