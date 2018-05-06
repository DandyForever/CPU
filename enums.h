///ENUMS USED IN COMPILER, CPU and DISASSEMBLER
//---------------------------------------------
enum commands {
    END   =  0,
    PUSH  =  1,
    ADD   =  2,
    SUB   =  3,
    MUL   =  4,
    DIV   =  5,
    OUT   =  6,
    IN    =  7,
    SQRT  =  8,
    SIN   =  9,
    COS   = 10,
    POP   = 11,
    JMP   = 12,
    JE    = 13,
    JNE   = 14,
    JA    = 15,
    JAE   = 16,
    JB    = 17,
    JBE   = 18,
    CALL  = 19,
    REV   = 20
};

enum registers {
    AX = 0,
    BX = 3,
    CX = 1,
    DX = 2
};

enum pushtypes {
    VAL = 1,
    REG = 2,
    RAM = 3,
    REGRAM = 4
};
