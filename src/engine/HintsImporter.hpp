#pragma once

#include <iostream>
#include "../game/Hint.hpp"
#include "ini.hpp"
#include "../game/Species.hpp"

class HintsImporter {
public:
    static std::vector<Hint> Hints(const std::string& filepath, const Species& species);

private:
    static std::vector<std::string> SplitMessage(const std::string& marker, const std::string& message);
    template <typename T>
    static std::vector<Hint>& addToHints(std::vector<Hint>& hints, const std::string& message,
                                         const std::string& marker, const T& value, const std::string& unit = "");
    static std::vector<Hint>& addToHints(std::vector<Hint>& hints, const std::string& message,
                                         const std::string& marker, const std::string& value);

};
