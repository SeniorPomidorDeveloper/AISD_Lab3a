#ifndef TABEL_H
#define TABEL_H

#include <stddef.h>
#include <stdbool.h>

#define ULLI unsigned long long int

enum statuses
{
    SUCCESSFULLY,
    ERROR_ALLOCATION,
    FOUND,
    NOT_FOUND,
    added,
    TABEL_IS_FULL,
    TABEL_IS_EMPTY,
    DELETED
};

typedef struct KeySpace
{
    ULLI key;
    ULLI parent_key;
    ULLI *value;
} KeySpace;

typedef struct Tabel
{
    KeySpace **keySpace;
    size_t keySpace_size;
    size_t len_keySpace;
} Tabel;

typedef KeySpace ** iter_Tabel;

int init_Tabel(Tabel **tabel, size_t keySpace_size);  // Инициализация таблицы
bool is_empty_Tabel(Tabel *tabel);  // Проверка на наличие элементов в таблице
bool is_full_Tabel(Tabel *tabel);   // Проверка на наличие пустого пространства
int find_Tabel(Tabel *tabel, ULLI key, size_t *index); // Поиск элемента в таблице по ключу
int add_Tabel(Tabel *tabel, ULLI key, ULLI parent_key, ULLI value);  // Вставка элемента по ключу
int find_children_Tabel(Tabel *tabel, ULLI parent_key, Tabel **new_tabel);   // Поиск элементов по ключу родительского элемента
int del_Tabel(Tabel *tabel, ULLI key);  // Удаление элемента с заданным ключом
KeySpace *get_Tabel(Tabel *tabel, size_t index);
void free_Tabel(Tabel *tabel);  // Отчистка таблицы

iter_Tabel begin_Tabel(Tabel *tabel);   // Получение итератора указывающего на первый элемент
iter_Tabel end_Tabel(Tabel *tabel); // Получение итератора указывающего на последний элемент
iter_Tabel next_Tabel(Tabel *tabel, iter_Tabel iter);   // Получение итератора указывающего на следующий элемент

iter_Tabel add_iter_Tabel(Tabel *tabel, ULLI key, ULLI parent_key, ULLI value);    // Вставка элемента и возврат итератора указывающего на него
iter_Tabel del_iter_Tabel(Tabel *tabel, iter_Tabel iter);
iter_Tabel find_iter_Tabel(Tabel *tabel, ULLI key);



#endif // TABEL_H