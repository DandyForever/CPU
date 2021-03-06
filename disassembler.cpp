///DISASSEMBLER FOR CPU KDIv2.2
//------------------------------
#include <stdio.h>
#include <iostream>
#include <assert.h>
#include <set>
#include <cstdlib>
#include <string.h>

#define DEF_CMD(name, compiler_code, cpu_code, disassembler_code)
#define DEF_REG(name, code)

#include "commands.h"

#undef DEF_REG
#undef DEF_CMD

const char* VERSION = "KDIv2.2";

#include "make_buffer.h"

std::set < int > labels_numbers (int* buffer);
void make_command_file (int* buffer, const std::set < int > labels);

int main ()
{
    FILE* input_file = fopen ("CPU_commands.txt", "rb");
    assert (input_file);

    CHECK_VERSION
    {
        int* buffer = make_buffer (input_file);
        assert (buffer);

//for (int i = 1; i < 50; i++)
//printf("%d\n", buffer[i]);

        std::set < int > labels = labels_numbers (buffer);
        assert (&labels);

        make_command_file (buffer, labels);

	free (buffer);
    }
    return 0;
}

std::set < int > labels_numbers (int* buffer)
{
    int i = 0;
    assert (&i);

    std::set < int > labels;
    assert (&labels);

    while (buffer[i] != 0)
    {
        if (buffer[i] == PUSH || buffer[i] == POP)
            i += 3;
        else if (buffer[i] == JE || buffer[i] == JNE || buffer[i] == JA ||
                 buffer[i] == JAE || buffer[i] == JB || buffer[i] == JBE ||
                 buffer[i] == CALL || buffer[i] == JMP)
        {
            labels.insert (buffer[i + 1]);
            i += 2;
        }
        else
            i++;
    }

    return labels;
}

void make_command_file (int* buffer, const std::set < int > labels)
{
    FILE* output_file = fopen ("disassembling.txt", "w");
    assert (output_file);

    int i = 0;
    assert (&i);

    while (buffer[i] != 0)
    {
        if (labels.count (i))
            fprintf (output_file, ":%d\n", i);
	
        switch (buffer[i])
        {
            #define DEF_CMD(name, compiler_code, cpu_code, disassembler_code)\
                    disassembler_code
            #define DEF_REG(name, code)

            #include "commands.h"

            #undef DEF_REG
            #undef DEF_CMD
        }
        i++;
    }

    if (labels.count (i))
            fprintf (output_file, ":%d\n", i);

    fprintf (output_file, "END\n");

    fclose (output_file);
}
