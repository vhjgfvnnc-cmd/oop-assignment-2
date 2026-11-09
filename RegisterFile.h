#pragma once
namespace vole {
class RegisterFile {
private:
    unsigned char registers[16];
public:
    RegisterFile();
    unsigned char get(int index) const;
    bool set(int index, unsigned char value);
    const unsigned char* getAll() const;
};
}
