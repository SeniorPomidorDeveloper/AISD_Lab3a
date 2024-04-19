#ifndef MENU_H
#define MENU_H

#include "./libs/Tabel/tabel.h"

enum menu_status
{
    OK,
    ERROR
};

int menu(Tabel *tabel);

#endif // MENU_H