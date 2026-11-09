#include "Machine.h"
#include "ProgramLoader.h"
#include <iostream>

namespace vole {

Machine::Machine() : pc(0), halted(false) {}

void Machine::reset() {
    memory = Memory();
    registers = RegisterFile();
    pc = 0;
    halted = false;
}

bool Machine::loadProgram(const std::string& fileName, int startAddress, std::string& errorMessage) {
    ProgramLoader loader(decoder);
    pc = startAddress;
    return loader.loadFromFile(fileName, startAddress, memory, errorMessage);
}

void Machine::step() {
    if (halted) return;

    if (pc < 0 || pc >= 255) {
        halted = true;
        return;
    }

    unsigned char high = memory.read(pc);
    unsigned char low = memory.read(pc + 1);
    int rawCode = (high << 8) | low;

    pc += 2;

    Instruction instr;
    if (!decoder.decode(rawCode, instr)) {
        return;
    }

    int op = instr.getOpcode();
    int r = instr.getFirst();
    int xy = (instr.getSecond() << 4) | instr.getThird();
    int s = instr.getSecond();
    int t = instr.getThird();

    switch (op) {
        case 1:
            registers.set(r, memory.read(xy));
            break;
        case 2:
            registers.set(r, static_cast<unsigned char>(xy));
            break;
        case 3:
            memory.write(xy, registers.get(r));
            if (xy == 0xFF) {
                std::cout << static_cast<int>(registers.get(r)) << std::endl;
            }
            break;
        case 4:
            registers.set(t, registers.get(s));
            break;
        case 5:
            registers.set(r, ALU::addTwoComplement(registers.get(s), registers.get(t)));
            break;
        case 6:
            registers.set(r, ALU::addFloatingPoint(registers.get(s), registers.get(t)));
            break;
        case 7:
            registers.set(r, ALU::bitwiseOr(registers.get(s), registers.get(t)));
            break;
        case 8:
            registers.set(r, ALU::bitwiseAnd(registers.get(s), registers.get(t)));
            break;
        case 9:
            registers.set(r, ALU::bitwiseXor(registers.get(s), registers.get(t)));
            break;
        case 10:
            registers.set(r, ALU::rotateRight(registers.get(r), t));
            break;
        case 11:
            if (registers.get(r) == registers.get(0)) {
                pc = xy;
            }
            break;
        case 12:
            halted = true;
            break;
        default:
            break;
    }
}

void Machine::run() {
    while (!halted) {
        step();
    }
}

bool Machine::isHalted() const {
    return halted;
}

int Machine::getPC() const {
    return pc;
}

const Memory& Machine::getMemory() const {
    return memory;
}

const RegisterFile& Machine::getRegisterFile() const {
    return registers;
}

}
