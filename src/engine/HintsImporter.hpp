#pragma once

#include "../game/Hint.hpp"

class HintsImporter {
public:
    static std::vector<Hint> Hints(const std::string& filepath);

private:
    static std::vector<std::string> SplitMessage(const std::string& marker, const std::string& message);

};
