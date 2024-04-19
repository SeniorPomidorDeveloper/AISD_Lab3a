#ifndef GETS_H
#define GETS_H

#include "stddef.h"
#include "stdbool.h"

bool StandatrCheckSize_t(size_t num);
bool StandartCheckLLInt(long long int num);
int GetSize_t(size_t *num, const char *message, bool (*CheckFunction)(const size_t));
int GetLLInt(long long int *num, const char *message, bool (*CheckFunction)(long long int num));

#endif