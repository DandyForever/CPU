///FUNCTIONS TO CHECK VERSION OF CPU AND TO MAKE BUFFER OF VALUES FROM FILE
//-------------------------------------------------------------------------
#define CHECK_VERSION\
        if (!version_check (input_file))\
        {\
            printf ("NEED ANOTHER VERSION OF CPU\n");\
        }\
        else

const int VERSION_SIZE = 10;

bool version_check                  (FILE* input_file);
int sizeofFILE                      (FILE *filein);
void readfile                       (int* buffer, FILE* input_file);
int* make_buffer                    (FILE* input_file);

//----------------------------------------------------
//! Compare version of CPU with version CPU in file
//!
//! @param [in] input_file    pointer on file variable
//!
//! @return 1 if versions are the same and 0 else
//----------------------------------------------------
bool version_check (FILE* input_file)
{
    char* version = (char*) calloc (VERSION_SIZE, sizeof (*version));
    assert (version);

    fscanf (input_file, "%s", version);

    return (!strcmp (version, VERSION));
}


//----------------------------------------------------
//! Size of input file
//!
//! @param [in] input_file    pointer on file variable
//!
//! @return size of input file
//!
//! @note tell size from current pointer
//----------------------------------------------------
int sizeofFILE (FILE *filein)
{
    const int versize = ftell (filein);

    fseek (filein, 0, SEEK_END);
    const int file_length = ftell (filein) - versize;
    rewind (filein);

    fseek (filein, versize, SEEK_SET);

    return file_length;
}

//----------------------------------------------------
//! Make buffer of commands
//!
//! @param [in] input_file    pointer on file variable
//!
//! @return pointer on the beginning of commands
//----------------------------------------------------
int* make_buffer (FILE* input_file)
{
    int file_size = sizeofFILE(input_file);

    int* buffer = (int*) calloc (file_size, sizeof (*buffer));
    assert (buffer);

    readfile (buffer, input_file);

    return buffer;
}

//----------------------------------------------------------------
//! Reading input file
//!
//! @param [in] buffer        pointer on the beginning of commands
//! @param [in] input_file    pointer on file variable
//----------------------------------------------------------------
void readfile (int* buffer, FILE* input_file)
{
    int i = 0;
    double value = -1;

    while ((int) value != END)
    {
        fscanf (input_file, "%lf", &value);

        buffer[i++] = (int)value;
        if (value == PUSH || value == POP)
        {
            fscanf (input_file, "%lf", &value);
            buffer[i++] = (int)value;

            fscanf (input_file, "%lf", &value);
            buffer[i++] = (int)value;

            value = -1;
        }
        else if (value == JMP || value == JE ||
                 value == JNE || value == JA || value == JAE ||
                 value == JB || value == JBE || value == CALL)
        {
            fscanf (input_file, "%lf", &value);
            buffer[i++] = (int)value;

            value = -1;
        }
    }
}
