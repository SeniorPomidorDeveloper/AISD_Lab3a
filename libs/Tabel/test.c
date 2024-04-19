#include <stdio.h>

#include "tabel.h"

int main()
{
    Tabel *tabel;
    init_Tabel(&tabel, 10);
    ULLI i = 6;
    add_iter_Tabel(tabel, 1, 0, i); 
    add_iter_Tabel(tabel, 3, 1, i); 
    add_Tabel(tabel, 2, 3, i); 
    add_Tabel(tabel, 5, 2, i); 
    add_Tabel(tabel, 4, 1, i);
    Tabel *new_tabel;
    find_children_Tabel(tabel, 1, &new_tabel);
    printf("new_tabel: %lld\n", new_tabel->keySpace[0]->key);
    free_Tabel(new_tabel);
    free_Tabel(tabel);
    return 0;
}