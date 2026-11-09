#include "Instruction.h"
namespace vole {
Instruction::Instruction() : raw(0), opcode(0), first(0), second(0), third(0) {}
void Instruction::set(int rawCode, int operation, int a, int b, int c) {
    raw = static_cast<unsigned short>(rawCode);
    opcode = operation;
    first = a;
    second = b;
    third = c;
}
unsigned short Instruction::getRaw() const { return raw; }
int Instruction::getOpcode() const { return opcode; }
int Instruction::getFirst() const { return first; }
int Instruction::getSecond() const { return second; }
int Instruction::getThird() const { return third; }
}
