#include <iostream>
#include <fstream>
#include <string>
#include <getPath.cpp>

void printFileContent(const std::string& filePath) {
    std::ifstream file(filePath);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << filePath << std::endl;
    }
}

int main(int argc, char* argv[]) 
{
    std::string projectPath = getPath(argc, argv);
    std::string filePath = projectPath + "\\\\shader\\\\fragment.glsl"; // Specify the path to your file here
    std::cout << "File path: " << filePath << std::endl;
    printFileContent(filePath);


    return 0;
}