#include "functions.h"

int add(Tabel *tabel, ULLI key, ULLI parent_key, ULLI value)
{
    if (add_iter_Tabel(tabel, key, parent_key, value) == NULL)
    {
        return FOUND;
    }
    return SUCCESSFULLY;
}

int del(Tabel *tabel, ULLI key)
{
    iter_Tabel iter = find_iter_Tabel(tabel, key);
    if (iter == NULL)
    {
        return NOT_FOUND;
    }
    del_iter_Tabel(tabel, iter);
    return SUCCESSFULLY;
}

int find(Tabel *tabel, ULLI key, size_t *index)
{
    iter_Tabel iter = find_iter_Tabel(tabel, key);
    if (iter == NULL)
    {
        return NOT_FOUND;
    }
    *index = (size_t) (iter - begin_Tabel(tabel));
    return SUCCESSFULLY;
}

int find_children(Tabel *tabel, ULLI key, Tabel **new_tabel)
{
    return find_children_Tabel(tabel, key, new_tabel);
}