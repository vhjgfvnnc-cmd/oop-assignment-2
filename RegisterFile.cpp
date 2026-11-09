#include "RegisterFile.h"
namespace vole {
RegisterFile::RegisterFile() {
    for (int i = 0; i < 16; i++) registers[i] = 0;
}
unsigned char RegisterFile::get(int index) const {
    if (index < 0 || index >= 16) return 0;
    return registers[index];
}
bool RegisterFile::set(int index, unsigned char value) {
    if (index < 0 || index >= 16) return false;
    registers[index] = value;
    return true;
}
const unsigned char* RegisterFile::getAll() const { return registers; }
}
