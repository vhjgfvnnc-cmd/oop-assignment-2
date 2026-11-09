#pragma once
#include "InstructionDecoder.h"
#include "Memory.h"
#include <string>
namespace vole {
class ProgramLoader {
private:
    const InstructionDecoder& decoder;
public:
    ProgramLoader(const InstructionDecoder& instructionDecoder);
    bool loadFromFile(const std::string& fileName, int startAddress, Memory& memory, std::string& errorMessage) const;
};
}
