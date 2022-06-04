#ifndef _VEC_H_
#define _VEC_H_

typedef struct
{
    void **items;
    int capacity;
    int length;
} Vec;

Vec *vec_new(int capacity);
int vec_resize(Vec *vec, int capacity);
int vec_set(Vec *vec, int i, void *item);
int vec_append(Vec *vec, void *item);
void *vec_get(Vec *vec, int i);
int vec_delete(Vec *vec, int i);
void vec_test();

#endif