#include "InstructionDecoder.h"
namespace vole {
namespace {
int hexValue(char ch) {
    if (ch >= '0' && ch <= '9') return ch - '0';
    if (ch >= 'A' && ch <= 'F') return ch - 'A' + 10;
    if (ch >= 'a' && ch <= 'f') return ch - 'a' + 10;
    return -1;
}
}
bool InstructionDecoder::decode(int rawCode, Instruction& instruction) const {
    if (rawCode < 0 || rawCode > 0xFFFF) return false;
    int opcode = (rawCode >> 12) & 0xF;
    int first = (rawCode >> 8) & 0xF;
    int second = (rawCode >> 4) & 0xF;
    int third = rawCode & 0xF;
    if (opcode >= 1 && opcode <= 3) {
        instruction.set(rawCode, opcode, first, second, third);
        return true;
    }
    if (opcode == 4) {
        if (first != 0) return false;
        instruction.set(rawCode, opcode, first, second, third);
        return true;
    }
    if (opcode >= 5 && opcode <= 9) {
        instruction.set(rawCode, opcode, first, second, third);
        return true;
    }
    if (opcode == 10) {
        if (first != 0) return false;
        instruction.set(rawCode, opcode, first, second, third);
        return true;
    }
    if (opcode == 11) {
        instruction.set(rawCode, opcode, first, second, third);
        return true;
    }
    if (rawCode == 0xC000) {
        instruction.set(rawCode, 12, 0, 0, 0);
        return true;
    }
    return false;
}
bool InstructionDecoder::decodeHex(const std::string& text, Instruction& instruction) const {
    if (text.length() != 4) return false;
    int value = 0;
    for (int i = 0; i < 4; i++) {
        int digit = hexValue(text[i]);
        if (digit < 0) return false;
        value = value * 16 + digit;
    }
    return decode(value, instruction);
}
}
