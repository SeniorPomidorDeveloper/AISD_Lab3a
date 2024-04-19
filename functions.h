#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "./libs/Tabel/tabel.h"

int add(Tabel *tabel, ULLI key, ULLI parent_key, ULLI value);
int del(Tabel *tabel, ULLI key);
int find(Tabel *tabel, ULLI key, size_t *index);
int find_children(Tabel *tabel, ULLI key, Tabel **new_tabel);

#endif // FUNCTIONS_H