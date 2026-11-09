#include "ProgramLoader.h"
#include <cctype>
#include <fstream>
#include <vector>
namespace vole {
namespace {
int hexValue(char ch) {
    if (ch >= '0' && ch <= '9') return ch - '0';
    if (ch >= 'A' && ch <= 'F') return ch - 'A' + 10;
    if (ch >= 'a' && ch <= 'f') return ch - 'a' + 10;
    return -1;
}
}
ProgramLoader::ProgramLoader(const InstructionDecoder& instructionDecoder) : decoder(instructionDecoder) {}
bool ProgramLoader::loadFromFile(const std::string& fileName, int startAddress, Memory& memory, std::string& errorMessage) const {
    if (startAddress < 0 || startAddress >= 0xFF || startAddress % 2 != 0) {
        errorMessage = "Start address must be even and less than FF.";
        return false;
    }
    std::ifstream input(fileName);
    if (!input) {
        errorMessage = "Could not open the program file.";
        return false;
    }
    std::vector<unsigned char> bytes;
    std::string line;
    int lineNumber = 0;
    while (std::getline(input, line)) {
        lineNumber++;
        int start = 0;
        while (start < static_cast<int>(line.length()) && std::isspace(static_cast<unsigned char>(line[start]))) start++;
        if (start == static_cast<int>(line.length()) || line[start] == ';') continue;
        if (start + 4 > static_cast<int>(line.length())) {
            errorMessage = "Invalid instruction on line " + std::to_string(lineNumber) + ".";
            return false;
        }
        int rawCode = 0;
        for (int i = 0; i < 4; i++) {
            int digit = hexValue(line[start + i]);
            if (digit < 0) {
                errorMessage = "Invalid instruction on line " + std::to_string(lineNumber) + ".";
                return false;
            }
            rawCode = rawCode * 16 + digit;
        }
        Instruction instruction;
        if (!decoder.decode(rawCode, instruction)) {
            errorMessage = "Invalid instruction on line " + std::to_string(lineNumber) + ".";
            return false;
        }
        bytes.push_back(static_cast<unsigned char>((rawCode >> 8) & 0xFF));
        bytes.push_back(static_cast<unsigned char>(rawCode & 0xFF));
    }
    if (bytes.empty()) {
        errorMessage = "The program contains no instructions.";
        return false;
    }
    if (!memory.loadBytes(startAddress, bytes)) {
        errorMessage = "The program does not fit in memory.";
        return false;
    }
    errorMessage = "";
    return true;
}
}
