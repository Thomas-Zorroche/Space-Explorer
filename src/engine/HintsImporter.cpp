#include "HintsImporter.hpp"
#include <fstream>
#include <iostream>

std::vector<Hint> HintsImporter::Hints(const std::string &filepath) {
    std::vector<Hint> hints;

    std::ifstream stream(filepath);
    std::string line;

    int temperature = 10;
    std::string type = "rocheuse";

    while(getline(stream, line)){

        if(line.find("%f") != std::string::npos){
            std::vector<std::string> parts_of_message = SplitMessage("%f", line);
            std::string message = parts_of_message.at(0) + std::to_string(temperature) + "°C" + parts_of_message.at(1);
            hints.push_back(Hint(TransformLayout(glm::vec3(0), glm::vec3(0)), message));
            std::cout << message << std::endl;
        }

        if(line.find("%v") != std::string::npos) {
            std::vector<std::string> parts_of_message = SplitMessage("%v", line);
            std::string message = parts_of_message.at(0) + type + parts_of_message.at(1);
            hints.push_back(Hint(TransformLayout(glm::vec3(0), glm::vec3(0)), message));
            std::cout << message << std::endl;
        }
    }

    return hints;
}

std::vector<std::string> HintsImporter::SplitMessage(const std::string &marker, const std::string &message) {
    std::size_t marker_pos = message.find(marker);
    std::string beginning = message.substr(0, marker_pos);
    std::string end = message.substr(marker_pos + 2, message.length() - marker_pos);
    return { beginning, end };
}
