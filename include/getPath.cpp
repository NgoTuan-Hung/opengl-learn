#include <iostream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

static std::string getPath(int argc, char* argv[])
{
    if (argc < 1) {
        std::cerr << "Error: No command-line arguments provided." << std::endl;
        return "";
    }

    // Extracting the directory part from the full path of the executable
    fs::path exePath = fs::path(argv[0]);
    fs::path directoryPath = exePath.parent_path();

    // Convert path to string
    std::string pathString = directoryPath.string();

    // Format the path in the "drive:\\abc\\xyz" format
    std::string formattedPath = "";
    for (char &c : pathString) {
        if (c == '\\') {
            formattedPath += "\\\\";
        } else {
            formattedPath += c;
        }
    }

    return formattedPath;
}
