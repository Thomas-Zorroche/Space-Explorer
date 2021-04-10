#include "HintsImporter.hpp"

std::vector<Hint> HintsImporter::Hints(const std::string& filepath) {
    std::vector<Hint> hints;

    mINI::INIFile file(filepath);
    mINI::INIStructure ini;
    file.read(ini);

    int temperature = 10;
    bool water = true;

    for (auto& category :ini)
    {
        if (category.first == "temperature")
            addToHints(hints, category.second.get("hint1"), "%f", temperature, "°C");
        if (category.first == "water")
            addToHints(hints, category.second.get("hint1"), "%b", (water) ? std::string("") : "not");
    }
    return hints;
}

std::vector<std::string> HintsImporter::SplitMessage(const std::string& marker, const std::string& message) {
    std::size_t marker_pos = message.find(marker);
    std::string beginning = message.substr(0, marker_pos);
    std::string end = message.substr(marker_pos + 3, message.length() - marker_pos);
    return { beginning, end };
}

template <typename T>
std::vector<Hint>& HintsImporter::addToHints(std::vector<Hint>& hints, const std::string& message,
                                             const std::string& marker, const T& value, const std::string& unit)
{
    std::vector<std::string> parts_of_message = SplitMessage(marker, message);
    std::string composed_message = parts_of_message.at(0);
    composed_message += std::to_string(value) + unit + " " + parts_of_message.at(1);
    hints.emplace_back(TransformLayout(glm::vec3(0), glm::vec3(0)), composed_message);
    std::cout << composed_message << std::endl;
    return hints;
}

std::vector<Hint>& HintsImporter::addToHints(std::vector<Hint>& hints, const std::string& message,
                                             const std::string& marker, const std::string & value)
{
    std::vector<std::string> parts_of_message = SplitMessage(marker, message);
    std::string composed_message = parts_of_message.at(0);
    composed_message += value + parts_of_message.at(1);
    hints.emplace_back(TransformLayout(glm::vec3(0), glm::vec3(0)), composed_message);
    std::cout << composed_message << std::endl;
    return hints;
}
