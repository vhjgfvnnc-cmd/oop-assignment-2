#include "Memory.h"
#include <iostream>
namespace vole {
Memory::Memory() {
    for (int i = 0; i < 256; i++) cells[i] = 0;
}
unsigned char Memory::read(int address) const {
    if (address < 0 || address >= 256) return 0;
    return cells[address];
}
void Memory::write(int address, unsigned char value) {
    if (address < 0 || address >= 256) return;
    cells[address] = value;
    if (address == 0xFF) std::cout << static_cast<int>(value) << std::endl;
}
bool Memory::loadBytes(int startAddress, const std::vector<unsigned char>& bytes) {
    if (startAddress < 0 || startAddress + static_cast<int>(bytes.size()) > 256) return false;
    for (int i = 0; i < static_cast<int>(bytes.size()); i++) cells[startAddress + i] = bytes[i];
    return true;
}
const unsigned char* Memory::getCells() const { return cells; }
}
