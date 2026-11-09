#ifndef VOLEMACHINE_H
#define VOLEMACHINE_H

#include <string>
#include "Memory.h"
#include "RegisterFile.h"
#include "CPU.h"

namespace vole {

class VoleMachine {
private:
    Memory memory;
    RegisterFile registers;
    CPU cpu;

public:
    VoleMachine();
    bool loadProgram(const std::string& filename, int startAddress);
    void run();
    void step();
    void display();
    bool isHalted();
    void setMemory(int address , int value);
    void setRegister(int registersnum , int value);
};

}

#endif