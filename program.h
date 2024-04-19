#ifndef PROGRAM_H
#define PROGRAM_H

#include "./libs/Tabel/tabel.h"

enum error_codes_program
{
    ERROR_OPEN_FILE,
    ERROR_READ_FILE
};

int read_file_for_tabel(Tabel **tabel, char *path_file);
int program();

#endif // PROGRAM_H