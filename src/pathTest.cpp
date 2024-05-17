#include <iostream>
#include <fstream>
#include <string>

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

int main() {
    std::string projectPath = "C:\\\\Users\\\\ADMIN88\\\\Desktop\\\\Files\\\\Project\\\\Shader\\\\opengl\\\\proj\\\\";
    std::string filePath = projectPath + "src\\\\fragment.glsl"; // Specify the path to your file here
    printFileContent(filePath);
    return 0;
}