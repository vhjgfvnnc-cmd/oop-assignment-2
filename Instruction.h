#pragma once
namespace vole {
class Instruction {
private:
    unsigned short raw;
    int opcode;
    int first;
    int second;
    int third;
public:
    Instruction();
    void set(int rawCode, int operation, int a, int b, int c);
    unsigned short getRaw() const;
    int getOpcode() const;
    int getFirst() const;
    int getSecond() const;
    int getThird() const;
};
}
