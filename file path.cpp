#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

void countFileContent(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file) {
        std::cerr << "Error: File not found." << std::endl;
        return;
    }

    int numLines = 0, numWords = 0, numChars = 0;
    std::string line;

    while (std::getline(file, line)) {
        numLines++;
        numChars += line.length();
        
        std::istringstream stream(line);
        std::string word;
        while (stream >> word) {
            numWords++;
        }
    }

    std::cout << "Lines: " << numLines << std::endl;
    std::cout << "Words: " << numWords << std::endl;
    std::cout << "Characters: " << numChars << std::endl;
}

int main() {
    std::string filePath;
    std::cout << "Enter the file path: ";
    std::cin >> filePath;
    countFileContent(filePath);
    return 0;
}

