/*
 * =============================================================================
 *  Copyright (c) 2008 2009 ActiveSys.Wangbo
 *
 *  copyright description ...
 *
 *  Project:    cstl
 *  Module:     test
 *  Filename:   test_heap.c
 *
 *  The implementation of heap test.
 *
 *  2009-02-19 16:08:50
 * =============================================================================
 */

/** include section **/
#include <stdio.h>
#include <stdarg.h>
#include "cnumeric.h"
#include "cvector.h"
#include "cdeque.h"
#include "clist.h"
#include "cslist.h"
#include "cset.h"
#include "cmap.h"
#include "chash_set.h"
#include "chash_map.h"
#include "cstring.h"
#include "cutility.h"
#include "cfunctional.h"
#include "calgorithm.h"

#include "test_heap.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void test_heap(void)
{
    vector_t t_v = create_vector(int);
    iterator_t t_i;

    vector_init(&t_v);

    vector_push_back(&t_v, 32);
    algo_push_heap(vector_begin(&t_v), vector_end(&t_v));
    for(t_i = vector_begin(&t_v);
        !iterator_equal(&t_i, vector_end(&t_v));
        iterator_next(&t_i))
    {
        printf("%d, ", *(int*)iterator_get_pointer(&t_i));
    }
    printf("\n");
    vector_push_back(&t_v, 13);
    algo_push_heap(vector_begin(&t_v), vector_end(&t_v));
    for(t_i = vector_begin(&t_v);
        !iterator_equal(&t_i, vector_end(&t_v));
        iterator_next(&t_i))
    {
        printf("%d, ", *(int*)iterator_get_pointer(&t_i));
    }
    printf("\n");
    vector_push_back(&t_v, 65);
    algo_push_heap(vector_begin(&t_v), vector_end(&t_v));
    for(t_i = vector_begin(&t_v);
        !iterator_equal(&t_i, vector_end(&t_v));
        iterator_next(&t_i))
    {
        printf("%d, ", *(int*)iterator_get_pointer(&t_i));
    }
    printf("\n");
    vector_push_back(&t_v, 31);
    algo_push_heap(vector_begin(&t_v), vector_end(&t_v));
    for(t_i = vector_begin(&t_v);
        !iterator_equal(&t_i, vector_end(&t_v));
        iterator_next(&t_i))
    {
        printf("%d, ", *(int*)iterator_get_pointer(&t_i));
    }
    printf("\n");
    vector_push_back(&t_v, 68);
    algo_push_heap(vector_begin(&t_v), vector_end(&t_v));
    for(t_i = vector_begin(&t_v);
        !iterator_equal(&t_i, vector_end(&t_v));
        iterator_next(&t_i))
    {
        printf("%d, ", *(int*)iterator_get_pointer(&t_i));
    }
    printf("\n");
    vector_push_back(&t_v, 50);
    algo_push_heap(vector_begin(&t_v), vector_end(&t_v));
    for(t_i = vector_begin(&t_v);
        !iterator_equal(&t_i, vector_end(&t_v));
        iterator_next(&t_i))
    {
        printf("%d, ", *(int*)iterator_get_pointer(&t_i));
    }
    printf("\n");
    vector_push_back(&t_v, 5);
    algo_push_heap(vector_begin(&t_v), vector_end(&t_v));
    for(t_i = vector_begin(&t_v);
        !iterator_equal(&t_i, vector_end(&t_v));
        iterator_next(&t_i))
    {
        printf("%d, ", *(int*)iterator_get_pointer(&t_i));
    }
    printf("\n");
    vector_push_back(&t_v, 34);
    algo_push_heap(vector_begin(&t_v), vector_end(&t_v));
    for(t_i = vector_begin(&t_v);
        !iterator_equal(&t_i, vector_end(&t_v));
        iterator_next(&t_i))
    {
        printf("%d, ", *(int*)iterator_get_pointer(&t_i));
    }
    printf("\n");
    vector_push_back(&t_v, 12);
    algo_push_heap(vector_begin(&t_v), vector_end(&t_v));
    for(t_i = vector_begin(&t_v);
        !iterator_equal(&t_i, vector_end(&t_v));
        iterator_next(&t_i))
    {
        printf("%d, ", *(int*)iterator_get_pointer(&t_i));
    }
    printf("\n");
    vector_push_back(&t_v, 42);
    algo_push_heap(vector_begin(&t_v), vector_end(&t_v));
    for(t_i = vector_begin(&t_v);
        !iterator_equal(&t_i, vector_end(&t_v));
        iterator_next(&t_i))
    {
        printf("%d, ", *(int*)iterator_get_pointer(&t_i));
    }
    printf("\n");

    printf("\n");
    while(!vector_empty(&t_v))
    {
        algo_pop_heap(vector_begin(&t_v), vector_end(&t_v));
        vector_pop_back(&t_v);
        for(t_i = vector_begin(&t_v);
                !iterator_equal(&t_i, vector_end(&t_v));
                iterator_next(&t_i))
        {
            printf("%d, ", *(int*)iterator_get_pointer(&t_i));
        }
        printf("\n");
    }
    /*algo_sort_heap_if(vector_begin(&t_v), vector_end(&t_v), fun_great_int);*/
    /*for(t_i = vector_begin(&t_v);*/
    /*!iterator_equal(&t_i, vector_end(&t_v));*/
    /*iterator_next(&t_i))*/
    /*{*/
    /*printf("%d, ", *(int*)iterator_get_pointer(&t_i));*/
    /*}*/
    /*printf("\n");*/
    printf("is heap:%d\n",
        algo_is_heap_if(vector_begin(&t_v), vector_end(&t_v), fun_great_int));
    vector_push_back(&t_v, 150);
    printf("is heap:%d\n",
        algo_is_heap_if(vector_begin(&t_v), vector_end(&t_v), fun_great_int));
    vector_push_back(&t_v, 80);
    printf("is heap:%d\n",
        algo_is_heap_if(vector_begin(&t_v), vector_end(&t_v), fun_great_int));
    vector_push_back(&t_v, 40);
    printf("is heap:%d\n",
        algo_is_heap_if(vector_begin(&t_v), vector_end(&t_v), fun_great_int));
    vector_push_back(&t_v, 30);
    printf("is heap:%d\n",
        algo_is_heap_if(vector_begin(&t_v), vector_end(&t_v), fun_great_int));
    vector_push_back(&t_v, 10);
    printf("is heap:%d\n",
        algo_is_heap_if(vector_begin(&t_v), vector_end(&t_v), fun_great_int));
    vector_push_back(&t_v, 70);
    printf("is heap:%d\n",
        algo_is_heap_if(vector_begin(&t_v), vector_end(&t_v), fun_great_int));
    vector_push_back(&t_v, 110);
    vector_push_back(&t_v, 100);
    vector_push_back(&t_v, 20);
    vector_push_back(&t_v, 90);
    vector_push_back(&t_v, 60);
    vector_push_back(&t_v, 50);
    vector_push_back(&t_v, 120);
    vector_push_back(&t_v, 140);
    vector_push_back(&t_v, 130);
    printf("is heap:%d\n",
        algo_is_heap(vector_begin(&t_v), vector_end(&t_v)));
    algo_make_heap_if(vector_begin(&t_v), vector_end(&t_v), fun_great_int);
    for(t_i = vector_begin(&t_v);
        !iterator_equal(&t_i, vector_end(&t_v));
        iterator_next(&t_i))
    {
        printf("%d, ", *(int*)iterator_get_pointer(&t_i));
    }
    printf("\n");
    printf("is heap:%d\n",
        algo_is_heap_if(vector_begin(&t_v), vector_end(&t_v), fun_great_int));
 
    vector_destroy(&t_v);
}

/** local function implementation section **/

/** eof **/

