#define VEC_NEW_CAPACITY 10

#include <stdlib.h>
#include <stdio.h>
#include "vec.h"

Vec *vec_new(int capacity)
{
    if (!capacity)
        capacity = VEC_NEW_CAPACITY;
    void **items = malloc(sizeof(void *) * capacity);
    if (items)
    {
        Vec vec = (Vec){.items = items, .capacity = VEC_NEW_CAPACITY, .length = 0};
        Vec *pVec = malloc(sizeof(Vec));
        if (pVec)
        {
            *pVec = vec;
            return pVec;
        }
        printf("vec error: vec_new(): could not allocate vec\n");
        return 0;
    }
    else
        printf("vec error: vec_new(): could not allocate items\n");
    return 0;
}

int vec_resize(Vec *vec, int capacity)
{
    if (vec)
    {
        void **items = realloc(vec->items, sizeof(void *) * capacity);
        if (items)
        {
            vec->items = items;
            vec->capacity = capacity;
            return 0;
        }
        printf("vec error: vec_resize(): could not resize items\n");
        return 1;
    }
    printf("vec error: vec_resize(): vec == 0\n");
    return 1;
}

int vec_set(Vec *vec, int i, void *item)
{
    if (!vec)
    {
        printf("vec error: vec_set(): vec == 0\n");
        return 1;
    }

    if (i < 0)
    {
        printf("vec error: vec_set(): i < 0\n");
        return 1;
    }

    if (i >= vec->capacity)
    {
        if (vec_resize(vec, i + 1))
        {
            printf("vec error: vec_set(): expanding vec failed\n");
            return 1;
        }
    }

    if (i >= vec->length)
        vec->length = i + 1;

    vec->items[i] = item;
    return 0;
}

int vec_append(Vec *vec, void *item)
{
    if (vec_set(vec, vec->length, item))
    {
        printf("vec error: vec_append(): appending vec failed\n");
        return 1;
    }
    return 0;
}

void *vec_get(Vec *vec, int i)
{
    if (vec)
    {
        if (i >= 0 && i < vec->length)
        {
            return vec->items[i];
        }
        printf("vec error: vec_get(): i < 0 || i > vec->length\n");
        return 0;
    }
    printf("vec error: vec_get(): vec == 0\n");
    return 0;
}

int vec_delete(Vec *vec, int i)
{
    for (int x = i; x < vec->length - 1; x++)
    {
        void *item = vec_get(vec, x + 1);

        if (vec_set(vec, x, item))
        {
            printf("vec error: vec_delete(): could not reorder vec (set)\n");
            return 1;
        }
    }

    if (vec_set(vec, vec->length - 1, NULL))
    {
        printf("vec error: vec_delete(): could not delete item\n");
        return 1;
    }

    vec->length--;

    return 0;
}

void vec_test()
{
    Vec *vec = vec_new(0);
    printf("%i\n", vec->capacity);
    vec_append(vec, "aaa");
    vec_append(vec, "bbb");
    vec_append(vec, "ccc");
    printf("%i\n", vec->length);
    printf("%s\n", (char *)vec_get(vec, 0));
    printf("%s\n", (char *)vec_get(vec, 1));
    printf("%s\n", (char *)vec_get(vec, 2));
    vec_delete(vec, 0);
    printf("%s\n", (char *)vec_get(vec, 0));
    printf("%s\n", (char *)vec_get(vec, 1));
    vec_set(vec, 1, "ddd");
    printf("%s\n", (char *)vec_get(vec, 0));
    printf("%s\n", (char *)vec_get(vec, 1));
    vec_set(vec, 20, "eee");
    printf("%s\n", (char *)vec_get(vec, 20));
}