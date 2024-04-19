#include "functions.h"

int add(Tabel *tabel, ULLI key, ULLI parent_key, ULLI value)
{
    return add_Tabel(tabel, key, parent_key, value);
}

int del(Tabel *tabel, ULLI key)
{
    return del_Tabel(tabel, key);
}

int find(Tabel *tabel, ULLI key, size_t *index)
{
    return find_Tabel(tabel, key, index);
}

int find_children(Tabel *tabel, ULLI key, Tabel **new_tabel)
{
    return find_children_Tabel(tabel, key, new_tabel);
}