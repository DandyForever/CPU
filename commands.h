///MAKER OF COMMANDS OF COMPILER
//------------------------------

#include "enums.h"

#define COMMAND(name)\
        if (strcmp (command, #name) == 0)

#define REGISTER(name)\
        if (strcmp (register_name, #name) == 0)\
            return name;\
        else

#define SIMPLE_COMMAND(name)\
        COMMAND(name)\
        buffer[(*index)++] = name;\
    else

#define JUMP_COMMAND(name)\
        COMMAND(name)\
    {\
        char* label = (char*) calloc (LABEL_SIZE, sizeof (*label));\
        assert (label);\
\
        fscanf (input_file, " :%s", label);\
\
        buffer[(*index)++] = name;\
\
        int point = -1;\
        assert (&point);\
\
        for (int i = 0; i < num_of_labels; i++)\
        {\
            if (strcmp (label, labels[i].label) == 0)\
                point = labels[i].index;\
        }\
\
        buffer[(*index)++] = point;\
    }\
\
    else\

#define REGISTER_NAME\
        char* register_name = (char*) calloc (REGISTER_SZ, sizeof (*register_name));\
        assert (register_name);\
\
        int number = -1;\
        assert (&number);\
\
        fscanf (input_file, " %[ABCDX] %n", register_name, &number);

#define NOT_WRONG_COMMAND\
        if (number == -1)\
            {\
                printf ("WRONG COMMAND: '%s'\n", command);\
                assert (0);\
            }\
            else

#define STACK_SMALL\
        if (cpu.stck.Size () < MIN_STACK)\
            {\
                printf ("Can't compare 2 elements, stack size < 2\n");\
                cpu_dump (cpu);\
                assert (0);\
            }\
            else

#define BAD_JUMPING\
        if (buffer[i + 1] == -1)\
            {\
                printf ("Bad jumping\n");\
                cpu_dump (cpu);\
                assert (0);\
            }\
        else

#define EMPTY_STACK\
        if (cpu.stck.Empty ())\
            {\
                printf ("Stack is empty\n");\
                cpu_dump (cpu);\
                assert (0);\
            }\
            else

#define UNCKNOWN_REGISTER\
            default:\
                printf ("UNCKNOWN REGISTER\n");\
                assert(0);


#define JUMP_IF(name, cmp)\
        case name:\
            STACK_SMALL\
            {\
                StackElem_t value1 = cpu.stck.Pop ();\
                StackElem_t value2 = cpu.stck.Pop ();\
\
                assert (&value1);\
                assert (&value2);\
\
                if (cmp)\
                    BAD_JUMPING\
                    i = buffer[i + 1] - 1;\
\
                else\
                    i++;\
            }\
\
            break;

#define REG_PUSH(name, name_cpu)\
                case name:\
                    cpu.stck.Push (name_cpu);\
\
                    break;

#define REG_POP(name, name_cpu)\
                case name:\
                    name_cpu = cpu.stck.Pop ();\
\
                    break;

#define RAM_PUSH(name, name_cpu)\
                case name:\
                cpu.stck.Push (cpu.ram[(int) name_cpu]);\
\
                break;

#define RAM_POP(name, name_cpu)\
                case name:\
                    cpu.ram[(int) name_cpu] = cpu.stck.Pop ();\
\
                    break;

#define OPERATIONS(name, operation)\
        case name:\
            STACK_SMALL\
            {\
                StackElem_t value1 = cpu.stck.Pop ();\
                StackElem_t value2 = cpu.stck.Pop ();\
\
                assert (&value1);\
                assert (&value2);\
\
                cpu.stck.Push (value2 operation value1);\
            }\
\
            break;

#define MATH(name, name_cpu)\
            case name_cpu:\
            {StackElem_t value = cpu.stck.Pop ();\
            assert (&value);\
\
            cpu.stck.Push (name (value));\
\
            break;}

#define REGISTER_CPU(name, function)\
            case name:\
                {\
		fprintf (output_file, #function);\
                fprintf (output_file, " ");\
                fprintf (output_file, #name);\
                fprintf (output_file, "\n");\
\
                break;}

#define REGISTER_RAM_CPU(name_r, function)\
            case name_r:\
                fprintf (output_file, #function);\
                fprintf (output_file, " [");\
                fprintf (output_file, #name_r);\
                fprintf (output_file, "]\n");\
\
                break;

#define JUMP_COMMAND_DIS(name)\
            case name:\
                i++;\
                fprintf (output_file, #name);\
                fprintf (output_file, " :%d\n", buffer[i]);\
\
                break;

#define SIMPLE_COMMAND_DIS(name_c)\
            case name_c:\
                fprintf (output_file, #name_c);\
                fprintf (output_file, "\n");\
                \
                break;

/*enum commands {
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
    AX = 100,
    BX = 200,
    CX = 300,
    DX = 400
};

enum pushtypes {
    VAL = 101,
    REG = 202,
    RAM = 303,
    REGRAM = 404
};*/


DEF_CMD(PUSH, COMMAND(PUSH)
    {
        //REGISTER_NAME
        char* register_name = (char*) calloc (REGISTER_SZ, sizeof (*register_name));
        assert (register_name);

        int number = -1;
        assert (&number);

        getc (input_file);

        fscanf (input_file, "[%[ABCDX]]%n", register_name, &number);

        if (number != -1)
        {
            buffer[(*index)++] = PUSH;
            buffer[(*index)++] = REGRAM;
            buffer[(*index)++] = tell_register (register_name);
        }

        else
        {
            fscanf (input_file, "%[ABCDX]%n", register_name, &number);

            if (number == -1)
            {
                double value = 0;
                assert (&value);

                fscanf (input_file, "%lf%n", &value, &number);
                NOT_WRONG_COMMAND

                if (getc (input_file) != ']')
                {

                    buffer[(*index)++] = PUSH;
                    buffer[(*index)++] = VAL;
                    buffer[(*index)++] = value;
                }
                else
                {
                    buffer[(*index)++] = PUSH;
                    buffer[(*index)++] = RAM;
                    buffer[(*index)++] = (int)value;
                }
            }
            else
            {
                buffer[(*index)++] = PUSH;
                buffer[(*index)++] = REG;
                buffer[(*index)++] = tell_register (register_name);
            }
        }
        free (register_name);
    }

    else,
        case PUSH:
            i++;

            switch ((int) buffer[i]) {
            case VAL:
                cpu.stck.Push (buffer[i + 1]);

                break;
            case REG:
                switch ((int) buffer[i + 1]) {

                REG_PUSH(AX, cpu.ax)
                REG_PUSH(BX, cpu.bx)
                REG_PUSH(CX, cpu.cx)
                REG_PUSH(DX, cpu.dx)
                UNCKNOWN_REGISTER}

                break;
            case RAM:
                if (buffer[i + 1] >= RamSize)
                {
                    printf ("WRONG ADDRESS OF RAM [%d]", (int) buffer[i + 1]);
                    assert (0);
                }
                else
                    cpu.stck.Push (cpu.ram[(int) buffer[i + 1]]);

                break;

            case REGRAM:
                switch ((int) buffer[i + 1]) {

                RAM_PUSH(AX, cpu.ax)
                RAM_PUSH(BX, cpu.bx)
                RAM_PUSH(CX, cpu.cx)
                RAM_PUSH(DX, cpu.dx)
                UNCKNOWN_REGISTER
                }

                break;
            }
            i++;
            break;,

            case PUSH:
            i++;
            switch (buffer[i])
            {
            case VAL:
                i++;
                fprintf (output_file, "PUSH %d\n", buffer[i]);

                break;
            case REG:
                i++;
                switch (buffer[i])
                {
                REGISTER_CPU(AX, PUSH)
                REGISTER_CPU(BX, PUSH)
                REGISTER_CPU(CX, PUSH)
                REGISTER_CPU(DX, PUSH)
                UNCKNOWN_REGISTER
                }
                break;
            case RAM:
                i++;
                fprintf (output_file, "PUSH [%d]\n", buffer[i]);
		
		break;
            
            case REGRAM:
                i++;
                switch (buffer[i])
                {
                    REGISTER_RAM_CPU(AX, PUSH)
                    REGISTER_RAM_CPU(BX, PUSH)
                    REGISTER_RAM_CPU(CX, PUSH)
                    REGISTER_RAM_CPU(DX, PUSH)
                    UNCKNOWN_REGISTER
                }

                break;}
            break;)

DEF_CMD(POP, COMMAND(POP)
    {
        char* register_name = (char*) calloc (REGISTER_SZ, sizeof (*register_name));
        assert (register_name);

        int number = -1;
        assert (&number);
        getc (input_file);

        fscanf (input_file, "[%[ABCDX]]%n", register_name, &number);

        if (number != -1)
        {
            buffer[(*index)++] = POP;
            buffer[(*index)++] = REGRAM;
            buffer[(*index)++] = tell_register (register_name);
        }
        else
        {
            fscanf (input_file, "%[ABCDX]%n", register_name, &number);

            if (number == -1)
            {
                int value = 0;
                assert (&value);

                fscanf (input_file, "%d]%n", &value, &number);

                NOT_WRONG_COMMAND

                buffer[(*index)++] = POP;
                buffer[(*index)++] = RAM;
                buffer[(*index)++] = value;
            }
            else
            {
                buffer[(*index)++] = POP;
                buffer[(*index)++] = REG;
                buffer[(*index)++] = tell_register (register_name);
            }
        }
        free (register_name);
    }

    else,
        case POP:
            i++;
            EMPTY_STACK
            switch ((int) buffer[i])
            {
            case REG:
                {
                    switch ((int) buffer[i + 1]){

                    REG_POP(AX, cpu.ax)
                    REG_POP(BX, cpu.bx)
                    REG_POP(CX, cpu.cx)
                    REG_POP(DX, cpu.dx)
                    UNCKNOWN_REGISTER;
                    }
                    break;
                }
            case RAM:
                {
                    if (buffer[i + 1] >= RamSize)
                    {
                        printf ("WRONG ADDRESS OF RAM [%d]", (int) buffer[i + 1]);
                        assert (0);
                    }
                    else
                        cpu.ram[(int) buffer[i + 1]] = cpu.stck.Pop ();

                    break;
                }

            case REGRAM:
                {
                    switch ((int) buffer[i + 1]){

                    RAM_POP(AX, cpu.ax)
                    RAM_POP(BX, cpu.bx)
                    RAM_POP(CX, cpu.cx)
                    RAM_POP(DX, cpu.dx)
                    UNCKNOWN_REGISTER;
                    }
                    break;
                }
            }
            i++;

            break;,

            case POP:
            i++;
            switch (buffer[i])
            {
            case REG:
                switch (buffer[i + 1])
                {
                REGISTER_CPU(AX, POP)
                REGISTER_CPU(BX, POP)
                REGISTER_CPU(CX, POP)
                REGISTER_CPU(DX, POP)
                UNCKNOWN_REGISTER
                }

                break;
            case RAM:
                {
                fprintf (output_file, "POP [%d]\n", buffer[i + 1]);
                }

                break;

            case REGRAM:
                switch (buffer[i + 1])
                {
                REGISTER_RAM_CPU(AX, POP)
                REGISTER_RAM_CPU(BX, POP)
                REGISTER_RAM_CPU(CX, POP)
                REGISTER_RAM_CPU(DX, POP)
                UNCKNOWN_REGISTER
                }

                break;
            }
            i++;

            break;)

DEF_CMD(ADD, SIMPLE_COMMAND(ADD), OPERATIONS(ADD, +), SIMPLE_COMMAND_DIS(ADD))
DEF_CMD(SUB, SIMPLE_COMMAND(SUB), OPERATIONS(SUB, -), SIMPLE_COMMAND_DIS(SUB))
DEF_CMD(MUL, SIMPLE_COMMAND(MUL), OPERATIONS(MUL, *), SIMPLE_COMMAND_DIS(MUL))
DEF_CMD(DIV, SIMPLE_COMMAND(DIV), OPERATIONS(DIV, /), SIMPLE_COMMAND_DIS(DIV))

DEF_CMD(OUT, SIMPLE_COMMAND(OUT), case OUT:
            EMPTY_STACK
            {
                printf ("%g\n", cpu.stck.Pop ());
            }

            break;,

                                                     SIMPLE_COMMAND_DIS(OUT))

DEF_CMD(END, SIMPLE_COMMAND(END), , )
DEF_CMD(IN,  SIMPLE_COMMAND(IN), case IN:
            {StackElem_t value = 0;
            assert (&value);

            scanf ("%lf", &value);

            cpu.stck.Push (value);

            break;},

                                                      SIMPLE_COMMAND_DIS(IN))

DEF_CMD(SQRT, SIMPLE_COMMAND(SQRT), MATH(sqrt, SQRT), SIMPLE_COMMAND_DIS(SQRT))
DEF_CMD(SIN,  SIMPLE_COMMAND(SIN),  MATH(sin, SIN),   SIMPLE_COMMAND_DIS(SIN))
DEF_CMD(COS,  SIMPLE_COMMAND(COS),  MATH(cos, COS),   SIMPLE_COMMAND_DIS(COS))

DEF_CMD(REV, SIMPLE_COMMAND(REV), case REV:
            i = (int) cpu.calls.Pop ();
            break;,
                                                      SIMPLE_COMMAND_DIS(REV))

DEF_CMD(JE,  JUMP_COMMAND(JE),  JUMP_IF(JE,                       abs (value1 - value2) < EPS),   JUMP_COMMAND_DIS(JE))
DEF_CMD(JNE, JUMP_COMMAND(JNE), JUMP_IF(JNE,                    !(abs (value1 - value2) < EPS)),  JUMP_COMMAND_DIS(JNE))
DEF_CMD(JA,  JUMP_COMMAND(JA),  JUMP_IF(JA,  value2 > value1 && !(abs (value1 - value2) < EPS)),  JUMP_COMMAND_DIS(JA))
DEF_CMD(JAE, JUMP_COMMAND(JAE), JUMP_IF(JAE, value2 > value1 ||   abs (value1 - value2) < EPS),   JUMP_COMMAND_DIS(JAE))
DEF_CMD(JB,  JUMP_COMMAND(JB),  JUMP_IF(JB,  value2 < value1 && !(abs (value1 - value2) < EPS)),  JUMP_COMMAND_DIS(JB))
DEF_CMD(JBE, JUMP_COMMAND(JBE), JUMP_IF(JBE, value2 < value1 ||   abs (value1 - value2) < EPS),   JUMP_COMMAND_DIS(JBE))
DEF_CMD(JMP, JUMP_COMMAND(JMP), case JMP:
            BAD_JUMPING
            i = buffer[i + 1] - 1;

            break;,

                                                                                                  JUMP_COMMAND_DIS(JMP))

DEF_CMD(CALL, JUMP_COMMAND(CALL), case CALL:
            BAD_JUMPING
            {cpu.calls.Push (i + 1);

            i = buffer[i + 1] - 1;}

            break;,

                                                                                                  JUMP_COMMAND_DIS(CALL))

DEF_REG(AX, REGISTER(AX))
DEF_REG(BX, REGISTER(BX))
DEF_REG(CX, REGISTER(CX))
DEF_REG(DX, REGISTER(DX))

#undef MATH
#undef OPERATIONS
#undef REG_POP
#undef REG_PUSH
#undef JUMP_IF
#undef UNCKNOWN_REGISTER
#undef EMPTY_STACK
#undef BAD_JUMPING
#undef STACK_SMALL
#undef NOT_WRONG_COMMAND
#undef REGISTER_NAME
#undef JUMP_COMMAND
#undef SIMPLE_COMMAND
#undef REGISTER
#undef COMMAND
