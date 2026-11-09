#include "ALU.h"

namespace vole {

unsigned char ALU::addTwoComplement(unsigned char a, unsigned char b) {
    return static_cast<unsigned char>(a + b);
}

unsigned char ALU::addFloatingPoint(unsigned char a, unsigned char b) {
    int s1 = (a >> 7) & 1;
    int e1 = (a >> 4) & 7;
    int m1 = a & 15;

    int s2 = (b >> 7) & 1;
    int e2 = (b >> 4) & 7;
    int m2 = b & 15;

    double val1 = (m1 / 16.0) * (1 << (e1 - 4));
    if (s1) val1 = -val1;

    double val2 = (m2 / 16.0) * (1 << (e2 - 4));
    if (s2) val2 = -val2;

    double sum = val1 + val2;

    int resSign = 0;
    if (sum < 0) {
        resSign = 1;
        sum = -sum;
    }

    if (sum == 0) return 0;

    int exp = 0;
    while (sum >= 1.0 && exp < 7) {
        sum /= 2.0;
        exp++;
    }
    while (sum < 0.5 && exp > 0) {
        sum *= 2.0;
        exp--;
    }

    int mantissa = static_cast<int>(sum * 16.0 + 0.5);
    if (mantissa > 15) mantissa = 15;

    return static_cast<unsigned char>((resSign << 7) | (exp << 4) | mantissa);
}

unsigned char ALU::bitwiseOr(unsigned char a, unsigned char b) {
    return a | b;
}

unsigned char ALU::bitwiseAnd(unsigned char a, unsigned char b) {
    return a & b;
}

unsigned char ALU::bitwiseXor(unsigned char a, unsigned char b) {
    return a ^ b;
}

unsigned char ALU::rotateRight(unsigned char value, int steps) {
    steps %= 8;
    return (value >> steps) | (value << (8 - steps));
}

}
