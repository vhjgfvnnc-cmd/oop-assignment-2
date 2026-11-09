#pragma once
#include <vector>
namespace vole {
class Memory {
private:
    unsigned char cells[256];
public:
    Memory();
    unsigned char read(int address) const;
    void write(int address, unsigned char value);
    bool loadBytes(int startAddress, const std::vector<unsigned char>& bytes);
    const unsigned char* getCells() const;
};
}
