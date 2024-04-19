#include "program.h"

#include <stdio.h>
#include <stdlib.h>

#include "menu.h"


int read_file_for_tabel(Tabel **tabel, char *path_file)
{
    FILE *file = fopen(path_file, "r");
    if (file == NULL)
    {
        return ERROR_OPEN_FILE;
    }
    long long int keyspace_size_LLI;
    int result = fscanf(file, "%lld", &keyspace_size_LLI);
    if (result == EOF)
    {
        fclose(file);
        return EOF;
    }
    if (keyspace_size_LLI <= 0)
    {
        fclose(file);
        return ERROR_READ_FILE;
    }
    size_t keyspace_size = keyspace_size_LLI;
    if (init_Tabel(tabel, keyspace_size) == ERROR_ALLOCATION)
    {
        return ERROR_ALLOCATION;
    }
    long long int len_LLI;
    result = fscanf(file, "%lld", &len_LLI);
    if (len_LLI < 0)
    {
        fclose(file);
        return ERROR_READ_FILE;
    }
    if (result == EOF)
    {
        fclose(file);
        return EOF;
    }
    size_t len = len_LLI;
    for (size_t i = 0; i < len; ++i)
    {
        long long int key, parent_key, value;
        result = fscanf(file, "%lld %lld %lld", &key, &parent_key, &value);
        if (result == EOF)
        {
            free_Tabel(*tabel);
            fclose(file);
            return EOF;
        }
        if (key <= 0 || parent_key < 0 || value < 0)
        {
            free_Tabel(*tabel);
            fclose(file);
            return ERROR_READ_FILE;
        }
        if (result == 3)
        {
            if (add_Tabel(*tabel, key, parent_key, value) == ERROR_ALLOCATION)
            {
                free_Tabel(*tabel);
                fclose(file);
                return ERROR_ALLOCATION;
            }
        }
    }
    fclose(file);
    return OK;
}

int program()
{
    Tabel *tabel;
    char *path_file = "./files/test.txt";
    if (read_file_for_tabel(&tabel, path_file) != OK)
    {
        printf("[ERROR] Произошла ошибка чтения текстого файла!\n");
        return 1;
    } 
    menu(tabel);
    free_Tabel(tabel);
    return 0;
}