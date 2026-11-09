#ifndef ALU_H
#define ALU_H

namespace vole {
class ALU {
public:
    static unsigned char addTwoComplement(unsigned char a, unsigned char b);
    static unsigned char addFloatingPoint(unsigned char a, unsigned char b);
    static unsigned char bitwiseOr(unsigned char a, unsigned char b);
    static unsigned char bitwiseAnd(unsigned char a, unsigned char b);
    static unsigned char bitwiseXor(unsigned char a, unsigned char b);
    static unsigned char rotateRight(unsigned char value, int steps);
};
}

#endif
