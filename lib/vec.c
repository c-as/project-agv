#define VEC_NEW_CAPACITY 10

#include <stdlib.h>
#include <stdio.h>
#include "vec.h"

Vec *vec_new(int capacity)
{
    if (!capacity)
        capacity = VEC_NEW_CAPACITY;
    volatile void **items = malloc(sizeof(void *) * capacity);
    if (items)
    {
        Vec *vec = malloc(sizeof(Vec));
        if (vec)
        {
            *vec = (Vec){.items = items, .capacity = VEC_NEW_CAPACITY, .length = 0};
            return vec;
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
    if (!vec)
    {
        printf("vec error: vec_resize(): vec == 0\n");
        return 1;
    }

    volatile void **items = realloc(vec->items, sizeof(void *) * capacity);
    if (items)
    {
        vec->items = items;
        vec->capacity = capacity;
        return 0;
    }
    printf("vec error: vec_resize(): could not resize items\n");
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
    if (!vec)
    {
        printf("vec error: vec_append(): vec == 0\n");
        return 1;
    }

    if (vec_set(vec, vec->length, item))
    {
        printf("vec error: vec_append(): appending vec failed\n");
        return 1;
    }
    return 0;
}

int vec_insert(Vec *vec, int i, void *item)
{
    if (!vec)
    {
        printf("vec error: vec_insert(): vec == 0\n");
        return 1;
    }

    for (int x = vec->length; x > i; x--)
    {
        void *item = vec_get(vec, x - 1);

        if (vec_set(vec, x, item))
        {
            printf("vec error: vec_insert(): could not reorder vec (set)\n");
            return 1;
        }
    }

    if (vec_set(vec, i, item))
    {
        printf("vec error: vec_insert(): could not insert item\n");
        return 1;
    }

    return 0;
}

void *vec_get(Vec *vec, int i)
{
    if (!vec)
    {
        printf("vec error: vec_get(): vec == 0\n");
        return (void *)0;
    }

    if (i >= 0 && i < vec->length)
    {
        return vec->items[i];
    }
    printf("vec error: vec_get(): i < 0 || i > vec->length\n");
    return 0;
}

int vec_delete(Vec *vec, int i)
{
    if (!vec)
    {
        printf("vec error: vec_delete(): vec == 0\n");
        return 1;
    }

    void *deleted = vec_get(vec, i);
    if (!deleted)
    {
        printf("vec error: vec_delete(): could not get item\n");
        return 1;
    }

    free(deleted);

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

    if (vec->capacity - vec->length > 10)
    {

        if (vec_resize(vec, vec->capacity - 5))
        {

            printf("vec error: vec_delete(): could not resize vec\n");
            return 1;
        };
    }

    return 0;
}

int vec_free(Vec *vec)
{
    if (!vec)
    {
        printf("vec error: vec_free(): vec == 0\n");
        return 1;
    }

    for (int i = 0; i < vec->length; i++)
    {
        void *item = vec_get(vec, i);
        free(item);
    }

    free(vec->items);
    free(vec);

    return 0;
}

Vec *vec;
void vec_test_new()
{
    vec = vec_new(0);
    printf("%i\n", vec->capacity);
}

void vec_test_append()
{
    vec_append(vec, "aaa");
    vec_append(vec, "bbb");
    vec_append(vec, "ccc");
    printf("%i\n", vec->length);
    printf("%s\n", (char *)vec_get(vec, 0));
    printf("%s\n", (char *)vec_get(vec, 1));
    printf("%s\n", (char *)vec_get(vec, 2));
}

void vec_test_delete()
{
    vec_delete(vec, 0);
    printf("%s\n", (char *)vec_get(vec, 0));
    printf("%s\n", (char *)vec_get(vec, 1));
    printf("%i\n", vec->capacity);
}

void vec_test_set()
{
    vec_set(vec, 1, "ddd");
    printf("%s\n", (char *)vec_get(vec, 0));
    printf("%s\n", (char *)vec_get(vec, 1));
}

void vec_test_set_resize()
{
    vec_set(vec, 20, "eee");
    printf("%s\n", (char *)vec_get(vec, 20));
    printf("%i\n", vec->capacity);
    printf("%i\n", vec->length);
}

void vec_test_insert()
{
    vec_insert(vec, 1, "ccc");
    printf("%s\n", (char *)vec_get(vec, 0));
    printf("%s\n", (char *)vec_get(vec, 1));
    printf("%s\n", (char *)vec_get(vec, 2));
    printf("%i\n", vec->length);
}

void vec_test_delete_resize()
{
    for (int i = vec->length; i > 5; i--)
    {
        vec_delete(vec, i - 1);
    }
    printf("%i\n", vec->capacity);
    printf("%i\n", vec->length);
}

void vec_test()
{
    vec_test_new();
    vec_test_append();
    vec_test_delete();
    vec_test_set();
    vec_test_set_resize();
    vec_test_insert();
    vec_test_delete_resize();
}