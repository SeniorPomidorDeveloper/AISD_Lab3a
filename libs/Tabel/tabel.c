#include "tabel.h"

#include <stdlib.h>
#include <stdio.h>

int init_Tabel(Tabel **tabel, size_t keySpace_size)
{
    *tabel = (Tabel *) malloc(sizeof(Tabel));
    if (*tabel == NULL)
    {
        return ERROR_ALLOCATION;
    }
    (*tabel)->keySpace_size = keySpace_size;
    (*tabel)->len_keySpace = 0;
    (*tabel)->keySpace = (KeySpace **) malloc(keySpace_size * sizeof(KeySpace *));
    if ((*tabel)->keySpace == NULL)
    {
        return ERROR_ALLOCATION;
    }
    return SUCCESSFULLY;
}

bool is_empty_Tabel(Tabel *tabel)
{
    return tabel->len_keySpace == 0;
}

bool is_full_Tabel(Tabel *tabel)
{
    return tabel->len_keySpace == tabel->keySpace_size;
}

int find_Tabel(Tabel *tabel, ULLI key, size_t *index)
{
    if (key == 0){
        return FOUND;
    }
    for (size_t i = 0; i < tabel->len_keySpace; ++i)
    {
        if (tabel->keySpace[i]->key == key)
        {
            if (index != NULL)
            {
                *index = i;
            }
            return FOUND;
        }
    }
    return NOT_FOUND;
}

int add_Tabel(Tabel *tabel, ULLI key, ULLI parent_key, ULLI value)
{
    if (is_full_Tabel(tabel))
    {
        return TABEL_IS_FULL;
    }
    if (find_Tabel(tabel, key, NULL) == FOUND)
    {
        return FOUND;
    }
    if (find_Tabel(tabel, parent_key, NULL) == NOT_FOUND) {
        return NOT_FOUND;
    }
    KeySpace *new_item = (KeySpace *) malloc(sizeof(KeySpace));
    if (new_item == NULL)
    {
        return ERROR_ALLOCATION;
    }
    new_item->key = key;
    new_item->parent_key = parent_key;
    new_item->value = (ULLI *) malloc(sizeof(ULLI));
    if (new_item->value == NULL)
    {
        return ERROR_ALLOCATION;
    }
    *(new_item->value) = value;
    size_t index = tabel->len_keySpace;
    size_t i = tabel->len_keySpace;
    for (; i > 1; --i)
    {
        if (tabel->keySpace[i - 2]->parent_key != tabel->keySpace[i - 1]->parent_key && tabel->keySpace[i - 1]->parent_key > parent_key)
        {
            tabel->keySpace[index] = tabel->keySpace[i - 1];
            index = i - 1;
        } else if (tabel->keySpace[i - 1]->parent_key <= parent_key)
        {
            break;
        }
        if (tabel->keySpace[i - 2]->parent_key <= parent_key && parent_key <= tabel->keySpace[i - 1]->parent_key)  
        {
            --i;
            break;
        }
    }
    tabel->keySpace[i] = new_item;
    ++tabel->len_keySpace;
    return SUCCESSFULLY;
}

int find_children_Tabel(Tabel *tabel, ULLI parent_key, Tabel **new_tabel)
{
    if (new_tabel != NULL) 
    {
        if (init_Tabel(new_tabel, tabel->keySpace_size) == ERROR_ALLOCATION)
        {
            return ERROR_ALLOCATION;
        }
    }
    for (size_t i = 0; i < tabel->len_keySpace; ++i)
    {
        if (tabel->keySpace[i]->parent_key == parent_key)
        {
            if (new_tabel == NULL)
            {
                return FOUND;
            }
            int result_operation_add = add_Tabel(*new_tabel, tabel->keySpace[i]->key, 0, 
                                                 *(tabel->keySpace[i]->value));
            if (result_operation_add != SUCCESSFULLY)
            {
                return result_operation_add;
            }
        }
    }
    if (new_tabel != NULL)
    {
        return is_empty_Tabel(*new_tabel) ? FOUND : NOT_FOUND;
    }
    return NOT_FOUND;
}

int del_Tabel(Tabel *tabel, ULLI key)
{
    if (find_children_Tabel(tabel, key, NULL) == FOUND)
    {
        return FOUND;
    }
    size_t index;
    if (find_Tabel(tabel, key, &index) == NOT_FOUND)
    {
        return NOT_FOUND;
    }
    free(tabel->keySpace[index]->value);
    free(tabel->keySpace[index]);
    for (size_t i = index + 1; i < tabel->len_keySpace - 1; ++i)
    {
        if (tabel->keySpace[i]->parent_key != tabel->keySpace[i + 1]->parent_key)
        {
            tabel->keySpace[index] = tabel->keySpace[i];
            index = i;
        }
    }
    tabel->keySpace[index] = tabel->keySpace[tabel->len_keySpace - 1];
    --tabel->len_keySpace;
    return SUCCESSFULLY;
}

KeySpace *get_Tabel(Tabel *tabel, size_t index)
{
    return tabel->keySpace[index];
}

void free_Tabel(Tabel *tabel)
{
    for (size_t i = 0; i < tabel->len_keySpace; ++i)
    {
        free(tabel->keySpace[i]->value);
        free(tabel->keySpace[i]);
    }
    free(tabel->keySpace);
    free(tabel);
}

iter_Tabel begin_Tabel(Tabel *tabel)
{
    if (is_empty_Tabel(tabel))
    {
        return NULL;
    }
    return tabel->keySpace;
}

iter_Tabel end_Tabel(Tabel *tabel)
{
    if (is_empty_Tabel(tabel))
    {
        return NULL;
    }
    return tabel->keySpace + tabel->len_keySpace - 1;
}

iter_Tabel next_Tabel(Tabel *tabel, iter_Tabel iter)
{
    if (is_empty_Tabel(tabel) || iter == end_Tabel(tabel))
    {
        return NULL;
    }
    return iter + 1;
}

iter_Tabel find_iter_Tabel(Tabel *tabel, ULLI key)
{
    if (is_empty_Tabel(tabel))
    {
        return NULL;
    }
    iter_Tabel begin = begin_Tabel(tabel);
    for (iter_Tabel i = begin; i != NULL; i = next_Tabel(tabel, i))
    {
        if ((*i)->key == key)
        {
            return i;
        }
    }
    return NULL;
}

iter_Tabel add_iter_Tabel(Tabel *tabel, ULLI key, ULLI parent_key, ULLI value)
{
    if (is_full_Tabel(tabel) || find_iter_Tabel(tabel, key) || (!find_iter_Tabel(tabel, parent_key) && parent_key != 0) || key == 0)
    {
        return NULL;
    }
    KeySpace *new_item = (KeySpace *) malloc(sizeof(KeySpace));
    if (new_item == NULL)
    {
        return NULL;
    }
    new_item->key = key;
    new_item->parent_key = parent_key;
    new_item->value = (ULLI *) malloc(sizeof(ULLI));
    if (new_item->value == NULL)
    {
        return NULL;
    }
    *(new_item->value) = value;
    if (is_empty_Tabel(tabel))
    {
        iter_Tabel iter = tabel->keySpace;
        *(iter) = new_item;
        ++tabel->len_keySpace;
        return iter;
    }
    iter_Tabel index = end_Tabel(tabel) + 1;
    iter_Tabel i = end_Tabel(tabel) + 1;
    iter_Tabel begin = begin_Tabel(tabel) + 1;
    for (; i > begin; --i)
    {
        if ((*(i - 2))->parent_key != (*(i - 1))->parent_key && (*(i - 1))->parent_key > parent_key)
        {
            *index = *(i - 1);
            index = i - 1;
        } else if ((*(i - 1))->parent_key <= parent_key)
        {
            break;
        }
        if ((*(i - 2))->parent_key <= parent_key && parent_key <= (*(i - 1))->parent_key)  
        {
            --i;
            break;
        }
    }
    *i = new_item;
    ++tabel->len_keySpace;
    return i;
}

iter_Tabel del_iter_Tabel(Tabel *tabel, iter_Tabel iter)
{
    if (is_empty_Tabel(tabel) || find_children_Tabel(tabel, (*iter)->key, NULL) == FOUND || !find_iter_Tabel(tabel, (*iter)->key))
    {
        return NULL;
    }
    free((*iter)->value);
    free(*iter);
    iter_Tabel end = end_Tabel(tabel);
    for (iter_Tabel i = iter + 1; i < end; i = next_Tabel(tabel, i))
    {
        if ((*i)->parent_key != (*(i + 1))->parent_key)
        {
            *iter = *i;
            iter = i;
        }
    }
    *iter = *end;
    --tabel->len_keySpace;
    return iter + 1;
}

bool compare_iter_Tabel(iter_Tabel *iter_1, iter_Tabel *iter_2)
{
    return iter_1 == iter_2;
}