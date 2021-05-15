#pragma once

#include <iostream>
#include <memory>
#include "../game/Hint.hpp"
#include "ini.hpp"
#include "../game/Species.hpp"
#include "../maths/probas.hpp"
#include "common.hpp"

struct HintSettings
{
    int xpos;
    int zpos;
    float velocity;
};

class HintsImporter {
public:
    static std::vector< std::shared_ptr<Hint> > Hints(const std::string& filepath, const std::shared_ptr<Species>& species);

    static void setLevel(Difficulty::Level level) { _level = level; }

private:
    static std::vector<std::string> SplitMessage(const std::string& marker, const std::string& message);
    template <typename T>
    static void addToHints(std::vector<std::shared_ptr<Hint> >& hints, const std::string& message,
                                         const std::string& marker, const T& value, const std::string& unit = "");
    static void addToHints(std::vector<std::shared_ptr<Hint> >& hints, const std::string& message,
                                         const std::string& marker, const std::string& value);

    static HintSettings computePositionAndVelocity();

private:
    static Difficulty::Level _level;


};
