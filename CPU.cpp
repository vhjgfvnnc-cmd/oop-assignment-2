#include "CPU.h"
#include "ALU.h"
#include <iostream>
using namespace std;

namespace vole {

string static byteToHex(int value) {
    
    string digits = "0123456789ABCDEF";
    string result = "";
    result += digits[value / 16];
    result += digits[value % 16];
    return result;

}

int static hexToInt(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    return c - 'A' + 10;
}

CPU::CPU(Memory* mem, RegisterFile* regs) {
    memory = mem ;
    registers = regs ;
    PC = 0 ;
    IR = "0000";
    Halted = false ;
}

void CPU::fetch() {
     int first  = memory->read(PC) ;
     int second = memory->read(PC+1) ;
     IR = byteToHex(first) + byteToHex(second);
     PC += 2;
}


bool CPU::decode() {
    opcode = hexToInt(IR[0]);
    R = hexToInt(IR[1]);
    S = hexToInt(IR[2]);
    T = hexToInt(IR[3]);
    XY = hexToInt(IR[2]) * 16 + hexToInt(IR[3]);

    
    if (opcode < 1 || opcode > 12) return false;
    if (opcode == 4  && R != 0) return false;   // 1
    if (opcode == 10 && S != 0) return false;   // 2
    if (opcode == 12 && IR != "C000") return false;   // 3

    return true;
}

void CPU::setPC(int address) {
    PC = address ;
    Halted = false;
}

bool CPU::isHalted() {
    return Halted ;
}

void CPU::execute() {
    switch (opcode) {

        case 1:
            registers->set(R, memory->read(XY));
            break;

        case 2:
            registers->set(R, XY);
            break;

        case 3:
            memory->write(XY, registers->get(R));
            break;

        case 4:
            registers->set(T, registers->get(S));
            break;

        case 5:
            registers->set(R,
                registers->get(S) + registers->get(T));
            break;

        case 6:
             registers->set(R, ALU::addFloatingPoint(
            registers->get(S),
            registers->get(T)
             ));
             break;

        case 7:
             registers->set(R, registers->get(S) | registers->get(T));
             break;

        case 8:
            registers->set(R, registers->get(S) & registers->get(T));
            break;

        case 9:
            registers->set(R, registers->get(S) ^ registers->get(T));
            break; 
        
        case 10: {
            int shift = T % 8;
            unsigned char value = registers->get(R);

            registers->set(R, (value >> shift) | (value << (8 - shift)));
            break;
        }

        case 11:
            if (registers->get(R) == registers->get(0))
                PC = XY;
            break;

        case 12:
            Halted = true;
            break;
    }
}


void CPU::step() {
    if (Halted == true) return;      

    fetch();                 

    if (!decode() == true ) {            
        cout << "Invalid instruction: " << IR << endl;
        Halted = true;
        return;
    }

    execute();               
}

int CPU::getPC() const {
    return PC;
}

string CPU::getIR() const {
    return IR;
}

}