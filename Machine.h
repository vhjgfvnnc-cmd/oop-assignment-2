#ifndef MACHINE_H
#define MACHINE_H

#include "Memory.h"
#include "RegisterFile.h"
#include "InstructionDecoder.h"
#include "Instruction.h"
#include "ALU.h"
#include <string>

namespace vole {
class Machine {
private:
    Memory memory;
    RegisterFile registers;
    InstructionDecoder decoder;
    int pc;
    bool halted;

public:
    Machine();
    void reset();
    bool loadProgram(const std::string& fileName, int startAddress, std::string& errorMessage);
    void step();
    void run();
    bool isHalted() const;
    int getPC() const;
    const Memory& getMemory() const;
    const RegisterFile& getRegisterFile() const;
};
}

#endif
