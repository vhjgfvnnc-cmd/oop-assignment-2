#pragma once
#include "Instruction.h"
#include <string>
namespace vole {
class InstructionDecoder {
public:
    bool decode(int rawCode, Instruction& instruction) const;
    bool decodeHex(const std::string& text, Instruction& instruction) const;
};
}
