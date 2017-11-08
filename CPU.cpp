///CPU KDIv2.2
//------------
#include <stdio.h>
#include "stack_t.h"
#include <assert.h>

const int MIN_STACK = 2, RamSize = 1024;

struct Cpu_t {
    Stack_t stck;

    StackElem_t ax = 0;
    StackElem_t bx = 0;
    StackElem_t cx = 0;
    StackElem_t dx = 0;
    StackElem_t* ram = new StackElem_t [RamSize] {};

    Stack_t calls;

    Cpu_t ():  stck (), calls () {};
};

#define DEF_CMD(name, compiler_code, cpu_code, disassembler_code)
#define DEF_REG(name, code)

#include "commands.h"

#undef DEF_REG
#undef DEF_CMD

const char* VERSION = "KDIv2.2";

#include "make_buffer.h"

void do_commands                    (int* buffer);

int main ()
{
    FILE* input_file = fopen ("CPU_commands.txt", "rb");
    assert (input_file);

    CHECK_VERSION
    {
        int* buffer = make_buffer (input_file);
        assert (buffer);

        do_commands (buffer);
    }

    fclose (input_file);
    return 0;
}

void cpu_dump (Cpu_t cpu)
{
    FILE* output_file = fopen ("dump.txt", "w");
    assert (output_file);

    fprintf (output_file, "                      CPU DUMP\n\n");

    fprintf (output_file, "    CPU STACK:\n");
    fclose (output_file);

    cpu.stck.Dump ();

    output_file = fopen ("dump.txt", "a");

    fprintf (output_file, "\n    CPU REGISTERS:\nAX = %10f\nBX = %10f\nCX = %10f\nDX = %10f\n\n",
             cpu.ax, cpu.bx, cpu.cx, cpu.dx);

    fprintf (output_file, "    CPU STACK of CALLS:\n");

    fclose (output_file);

    cpu.calls.Dump ();

    output_file = fopen ("dump.txt", "a");

    fprintf (output_file, "\n    CPU RAM:\n");
    for (int i = 0; i < RamSize; i++)
    {
        fprintf (output_file, "[%4d] = %10f\n", i, cpu.ram[i]);
    }

    fclose (output_file);
}

//------------------------------------------------------------
//! Do the commands from buffer
//!
//! @param [in] buffer    pointer on the beginning of commands
//------------------------------------------------------------
void do_commands (int* buffer)
{
    Cpu_t cpu;

    int i = 0;

    while (buffer[i] != 0)
    {
        switch (buffer[i]){
        #define DEF_CMD(name, compiler_code, cpu_code, disassembler_code)\
                    cpu_code
        #define DEF_REG(name, code)

        #include "commands.h"

        #undef DEF_REG
        #undef DEF_CMD
        }
        i++;

    }
}
