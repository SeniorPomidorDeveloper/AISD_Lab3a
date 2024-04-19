#include "menu.h"

#include "./libs/Gets/gets.h"
#include "functions.h"

#include <stdbool.h>
#include <stdio.h>

bool check_option(long long int option)
{
    return option >= 0 && option <= 4;
}

bool check_positive(long long int num)
{
    return num > 0;
}

bool check_no_negative(long long int num)
{
    return num >= 0;
}

void print_tabel(Tabel *tabel, const char *name)
{
    printf("---------%s---------\n", name);
    for (size_t i = 0; i < tabel->len_keySpace; i++)
    {
        printf("(key: %lld; parent_key: %lld; value: %lld)\n", tabel->keySpace[i]->key, 
               tabel->keySpace[i]->parent_key, *(tabel->keySpace[i]->value));
    }
    printf("---------------------------\n");
}

int case_add(Tabel *tabel)
{
    long long int key, parent_key, value;
    if (GetLLInt(&key, "Введите ключ: ", check_positive) == EOF)
    {
        return EOF;
    }
    if (GetLLInt(&parent_key, "Введите родительский ключ: ", check_no_negative) == EOF)
    {
        return EOF;
    }
    if (GetLLInt(&value, "Введите значение: ", check_no_negative) == EOF)
    {
        return EOF;
    }
    if (add(tabel, key, parent_key, value) != SUCCESSFULLY)
    {
        printf("[WARNING] Не удалось добавить новый элемент!\n");
        return ERROR;
    }
    return OK;
}

int case_del(Tabel *tabel)
{
    long long int key;
    if (GetLLInt(&key, "Введите ключ: ", check_no_negative) == EOF)
    {
        return EOF;
    }
    if (del(tabel, key) != SUCCESSFULLY)
    {
        printf("[WARNING] Не удалось удалить элемент!\n");
        return ERROR;
    }
    return OK;
}

int case_find_children(Tabel *tabel)
{
    long long int key;
    if (GetLLInt(&key, "Введите ключ: ", check_no_negative) == EOF)
    {
        return EOF;
    }
    Tabel *new_tabel = NULL;
    int result = find_children(tabel, key, &new_tabel);
    if (!is_empty_Tabel(new_tabel)) 
    {
        print_tabel(new_tabel, "Children");
    } else 
    {
        printf("[WARNING] Не удалось найти дочерние элементы!\n");
    }
    free_Tabel(new_tabel);
    return result;
}

int case_find(Tabel *tabel)
{
    long long int key;
    if (GetLLInt(&key, "Введите ключ: ", check_positive) == EOF)
    {
        return EOF;
    }
    size_t index;
    int result = find(tabel, key, &index);
    if (result == NOT_FOUND)
    {
        printf("[WARNING] Элемент не найден!\n");
    } else {
        printf("(key: %lld; parent_key: %lld; value: %lld)\n", tabel->keySpace[index]->key, 
               tabel->keySpace[index]->parent_key, *(tabel->keySpace[index]->value));
    }
    return result;
}

void print_menu()
{
    printf("1. Добавить новый элемент\n");
    printf("2. Удалить элемент\n");
    printf("3. Найти элемент\n");
    printf("4. Найти дочерние элементы\n");
    printf("0. Выход\n");
}

int menu(Tabel *tabel)
{
    long long int option;
    int (*function[]) (Tabel *tabel) = {case_add, case_del, case_find, case_find_children};
    do 
    {
        print_tabel(tabel, "Tabel");
        print_menu();
        if (GetLLInt(&option, "Введите пункт меню: ", check_option) == EOF)
        {
            return EOF;
        }  
        if (option == 0) {
            break;
        }
        if (function[option - 1](tabel) == EOF) 
        {
            return EOF;
        }
    } while (option);
    return OK;
}