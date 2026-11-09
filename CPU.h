#ifndef CPU_H
#define CPU_H

#include <string>
#include "Memory.h"
#include "RegisterFile.h"

namespace vole {

class CPU {
private:
    int opcode, R, S, T, XY;
    Memory* memory;
    RegisterFile* registers;
    int PC;
    std::string IR;
    bool Halted;

public:
    CPU(Memory* mem, RegisterFile* regs);
    
    void fetch();
    bool decode();
    void execute();
    void step();
    bool isHalted();
    void setPC(int address);
    int getPC() const;
    std::string getIR() const;
};

}

#endif