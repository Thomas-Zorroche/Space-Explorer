#include "HintsImporter.hpp"
#include "maths/probas.hpp"


Difficulty::Level HintsImporter::_level = Difficulty::Easy;


std::vector< std::shared_ptr<Hint> > HintsImporter::Hints(const std::string& filepath, const std::shared_ptr<Species>& species) {
    std::vector<std::shared_ptr<Hint> > hints;

    mINI::INIFile file(filepath);
    mINI::INIStructure ini;
    file.read(ini);

    const auto& caracs = species->planetSettings();
    std::string hi; // hint_index

    for (auto& category :ini)
    {
        hi = std::to_string(probas::discreteUniformDistribution(1, 3));
        if (category.first == "temperature")
            addToHints(hints, category.second.get("hint" + hi), "%f", caracs.temperature(), "°C");
        if (category.first == "telluric")
            addToHints(hints, category.second.get("hint" + hi), "%b", caracs.telluric() ? std::string("") : "not");
        if (category.first == "water")
            addToHints(hints, category.second.get("hint" + hi), "%b", caracs.hasWater() ? std::string("") : "not");
        if (category.first == "atmosphere")
            addToHints(hints, category.second.get("hint" + hi), "%b", caracs.atmosphere() ? std::string("") : "not");
        if (category.first == "magnetosphere")
            addToHints(hints, category.second.get("hint" + hi), "%b", caracs.magnetosphere() ? std::string("") : "not");
        if (category.first == "radioactivity")
            addToHints(hints, category.second.get("hint" + hi), "%f", caracs.radioactivityLevel(), "Gy");
    }
    return hints;
}

std::vector<std::string> HintsImporter::SplitMessage(const std::string& marker, const std::string& message) {
    std::size_t marker_pos = message.find(marker);
    std::string beginning = message.substr(0, marker_pos - 1);
    std::string end;
    if (marker_pos + 2 > message.size() - 1)
        end = message.substr(marker_pos + 2, message.length() - marker_pos);
    else
        end = message.substr(marker_pos + 3, message.length() - marker_pos);
    return { beginning, end };
}

template <typename T>
void HintsImporter::addToHints(std::vector<std::shared_ptr<Hint> >& hints, const std::string& message,
                                             const std::string& marker, const T& value, const std::string& unit)
{
    std::vector<std::string> parts_of_message = SplitMessage(marker, message);
    std::string composed_message = parts_of_message.at(0);
    composed_message += " " + std::to_string(value) + unit + " " + parts_of_message.at(1);

    HintSettings settings = computePositionAndVelocity();

    hints.emplace_back(std::make_shared<Hint> (TransformLayout(glm::vec3(settings.xpos, 0, settings.zpos), glm::vec3(0)), composed_message, settings.velocity) );
    std::cout << composed_message << std::endl;
}

void HintsImporter::addToHints(std::vector<std::shared_ptr<Hint> >& hints, const std::string& message,
                                             const std::string& marker, const std::string & value)
{
    std::vector<std::string> parts_of_message = SplitMessage(marker, message);
    std::string composed_message = parts_of_message.at(0);
    composed_message += " " + value + ((value.empty()) ? "" : " ") + parts_of_message.at(1);

    HintSettings settings = computePositionAndVelocity();

    hints.emplace_back(std::make_shared<Hint>(TransformLayout(glm::vec3(settings.xpos, 0, settings.zpos), glm::vec3(0)), composed_message, settings.velocity));
    std::cout << composed_message << std::endl;
}

HintSettings HintsImporter::computePositionAndVelocity()
{
    // Random position
    int xpos = probas::continuousUniformDistribution(100, 400);
    int zpos = probas::continuousUniformDistribution(100, 400);

    // Random velocity
    float velocity = 3;

    switch (_level)
    {
    case Difficulty::Easy:
        velocity += probas::simulateBinomialProb(50, 0.2);
        break;
    case Difficulty::Medium:
        velocity += probas::simulateBinomialProb(50, 0.5);
        break;
    case Difficulty::Hard:
        velocity += probas::simulateBinomialProb(50, 0.8);
        break;
    }  

    return { xpos, zpos, velocity };
}

