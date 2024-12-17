#include <SimpleIni.h>
#include <filesystem>
#include <headers/core.hpp>

#pragma once

namespace sf {

class IniManager {

private:
    const std::filesystem::path m_iniPath = std::filesystem::path("resources") / "highscores.ini";
    const std::filesystem::path m_savePath = std::filesystem::current_path().parent_path().parent_path().parent_path() / m_iniPath;

    CSimpleIniA m_iniFile;

public:
    IniManager() {
        m_iniFile.SetUnicode();
        const SI_Error loadError = m_iniFile.LoadFile(m_iniPath.string().c_str());
        assert_condition(loadError == SI_OK, "File loading threw an error.");
    }

    uint64_t readHighScore() const {
        const std::string highscore = m_iniFile.GetValue("section", "highscore");

        uint64_t result = 0;
        for(const char character : highscore) {
            const int digit = character - '0';
            assert_condition(digit >= 0 && digit < 10, "The highscore contains non-integer characters!");
            result = 10 * result + digit;
        }
        
        return result;
    }

    void updateHighScore(const uint64_t newHighscore) {
        if (newHighscore < readHighScore())
            return;
        
        const std::string highscoreString = std::to_string(newHighscore);
        const SI_Error rc = m_iniFile.SetValue("section", "highscore", highscoreString.c_str());

        assert_condition(rc >= 0, "There was some error when saving the highscore!");
        m_iniFile.SaveFile(m_savePath.string().c_str());
    }

    void resetHighScore() {
        const SI_Error rc = m_iniFile.SetValue("section", "highscore", "1");
        assert_condition(rc >= 0, "There was some error when resetting the highscore!");

        m_iniFile.SaveFile(m_savePath.string().c_str());
    }

};

}