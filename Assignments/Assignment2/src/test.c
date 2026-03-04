#include "stdio.h"

union wordUnion{
    unsigned char byte[4];
    unsigned short nibble[2];
    unsigned int word;
};

#if 0
struct RegStr{
    unsigned char bit0 : 1;
    unsigned char bit1 : 1;
    unsigned char bit2 : 1;
    unsigned char bit3 : 1;
    unsigned char bit4_7 : 4;
};

union Reg{
    struct RegStr regbits;
    unsigned char wholeReg;
};
#endif



union Reg{
    struct {
        unsigned char bit0 : 1;
        unsigned char bit1 : 1;
        unsigned char bit2 : 1;
        unsigned char bit3 : 1;
        unsigned char bit4_7 : 4;
    } regbits;

    unsigned char wholeReg;
};

int main()
{
    union Reg myRegister = {.wholeReg = 0b11010001};
    printf("bit4_7 = %d, bit3= %d, bit0=%d, reg=%d\n", myRegister.regbits.bit4_7, myRegister.regbits.bit3, myRegister.regbits.bit0, myRegister.wholeReg);
    return 0;
}