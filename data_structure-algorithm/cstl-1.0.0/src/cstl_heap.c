/*
 * =============================================================================
 *  Copyright (c) 2008 2009 ActiveSys.Wangbo
 *
 *  copyright description ...
 *
 *  Project:    cstl
 *  Module:     heap
 *  Filename:   cstl_heap.c
 *
 *  The implementation of heap.
 *
 *  2009-02-19 16:07:09
 * =============================================================================
 */

/** include section **/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "cstl_types.h"
#include "citerator.h"
#include "cfunctional.h"
#include "cstl_tools.h"
#include "cutility.h"

#include "cstl_algobase.h"
#include "cstl_algobase_private.h"

#include "cstl_heap.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/
/*
 *      Functionname: _adjust_heap
 *        Parameters: in) t_first: random_access_iterator_t
 *                            the first iterator.
 *                    in) t_last: random_access_iterator_t
 *                            the last iterator
 *                    in) t_parent: random_access_iterator_t
 *                            the parent iterator
 *                    in) t_binary_op: binary_function_t
 *                            binary function.
 *           Returns: void
 *       Description: adjust heap from parent.
 */
static void _adjust_heap(
    random_access_iterator_t t_first,
    random_access_iterator_t t_last,
    random_access_iterator_t t_parent,
    binary_function_t t_binary_op);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void algo_push_heap(
    random_access_iterator_t t_first, random_access_iterator_t t_last)
{
    char* s_typename = _tools_get_typename(t_first);
    assert(s_typename != NULL);

    algo_push_heap_if(t_first, t_last, _fun_get_binary(s_typename, _LESS_FUN));
}

void algo_push_heap_if(
    random_access_iterator_t t_first, random_access_iterator_t t_last,
    binary_function_t t_binary_op)
{
    bool_t                   t_result = false;
    size_t                   t_pos = 0;
    random_access_iterator_t t_parent;
    random_access_iterator_t t_current;

    assert(_tools_valid_iterator_range(t_first, t_last, _RANDOM_ACCESS_ITERATOR));

    if(t_binary_op == NULL)
    {
        t_binary_op = fun_default_binary;
    }

    /* not empty range */
    if(!iterator_equal(&t_first, t_last))
    {
        /* get position */
        t_pos = iterator_distance(t_first, t_last) - 1;
        t_current = t_last;
        iterator_prev(&t_current);
        t_parent = t_first;
        t_pos = t_pos == 0 ? t_pos : (t_pos - 1) / 2;
        iterator_next_n(&t_parent, t_pos);
        while(!iterator_equal(&t_current, t_first))
        {
            (*t_binary_op)(
                iterator_get_pointer(&t_current),
                iterator_get_pointer(&t_parent),
                &t_result);
            if(t_result) /* t_current < t_parent */
            {
                break;
            }

            algo_iter_swap(t_parent, t_current);
            t_current = t_parent;
            t_pos = t_pos == 0 ? t_pos : (t_pos - 1) / 2;
            t_parent = t_first;
            iterator_next_n(&t_parent, t_pos);
        }
    }
}

void algo_pop_heap(
    random_access_iterator_t t_first, random_access_iterator_t t_last)
{
    char* s_typename = _tools_get_typename(t_first);
    assert(s_typename != NULL);

    algo_pop_heap_if(t_first, t_last, _fun_get_binary(s_typename, _LESS_FUN));
}

void algo_pop_heap_if(
    random_access_iterator_t t_first, random_access_iterator_t t_last,
    binary_function_t t_binary_op)
{
    assert(_tools_valid_iterator_range(t_first, t_last, _RANDOM_ACCESS_ITERATOR));

    if(t_binary_op == NULL)
    {
        t_binary_op = fun_default_binary;
    }

    if(!iterator_equal(&t_first, t_last))
    {
        /* swap the first and prev */
        iterator_prev(&t_last);
        algo_iter_swap(t_first, t_last);

        _adjust_heap(t_first, t_last, t_first, t_binary_op);
    }
}

void algo_sort_heap(
    random_access_iterator_t t_first, random_access_iterator_t t_last)
{
    char* s_typename = _tools_get_typename(t_first);
    assert(s_typename != NULL);

    algo_sort_heap_if(t_first, t_last, _fun_get_binary(s_typename, _LESS_FUN));
}

void algo_sort_heap_if(
    random_access_iterator_t t_first, random_access_iterator_t t_last,
    binary_function_t t_binary_op)
{
    assert(_tools_valid_iterator_range(t_first, t_last, _RANDOM_ACCESS_ITERATOR));
    if(t_binary_op == NULL)
    {
        t_binary_op = fun_default_binary;
    }

    for(; !iterator_equal(&t_first, t_last); iterator_prev(&t_last))
    {
        algo_pop_heap_if(t_first, t_last, t_binary_op);
    }
}

void algo_make_heap(
    random_access_iterator_t t_first, random_access_iterator_t t_last)
{
    char* s_typename = _tools_get_typename(t_first);
    assert(s_typename != NULL);

    algo_make_heap_if(t_first, t_last, _fun_get_binary(s_typename, _LESS_FUN));
}

void algo_make_heap_if(
    random_access_iterator_t t_first, random_access_iterator_t t_last,
    binary_function_t t_binary_op)
{
    size_t                   t_pos = 0;
    size_t                   t_len = 0;
    random_access_iterator_t t_parent;

    assert(_tools_valid_iterator_range(t_first, t_last, _RANDOM_ACCESS_ITERATOR));
    if(t_binary_op == NULL)
    {
        t_binary_op = fun_default_binary;
    }

    t_len = iterator_distance(t_first, t_last);
    if(t_len >= 2)
    {
        t_pos = (t_len - 2) / 2;
        for(;;)
        {
            t_parent = t_first;
            iterator_next_n(&t_parent, t_pos);
            _adjust_heap(t_first, t_last, t_parent, t_binary_op);

            if(t_pos == 0)
            {
                break;
            }

            t_pos--;
        }
    }
}

bool_t algo_is_heap(
    random_access_iterator_t t_first, random_access_iterator_t t_last)
{
    char* s_typename = _tools_get_typename(t_first);
    assert(s_typename != NULL);

    return algo_is_heap_if(t_first, t_last, _fun_get_binary(s_typename, _LESS_FUN));
}

bool_t algo_is_heap_if(
    random_access_iterator_t t_first, random_access_iterator_t t_last,
    binary_function_t t_binary_op)
{
    bool_t                   t_result = false;
    size_t                   t_len = 0;
    size_t                   t_ppos = 0;
    size_t                   t_lpos = 0;
    size_t                   t_rpos = 0;
    random_access_iterator_t t_parent;
    random_access_iterator_t t_left;
    random_access_iterator_t t_right;

    assert(_tools_valid_iterator_range(t_first, t_last, _RANDOM_ACCESS_ITERATOR));
    if(t_binary_op == NULL)
    {
        t_binary_op = fun_default_binary;
    }

    if(iterator_equal(&t_first, t_last))
    {
        return false;
    }

    t_len = iterator_distance(t_first, t_last);
    for(t_ppos = 0; t_ppos < t_len; ++t_ppos)
    {
        t_lpos = t_ppos * 2 + 1;
        t_rpos = t_ppos * 2 + 2;

        t_parent = t_first;
        iterator_next_n(&t_parent, t_ppos);

        if(t_lpos < t_len)
        {
            t_left = t_first;
            iterator_next_n(&t_left, t_lpos);

            (*t_binary_op)(
                iterator_get_pointer(&t_parent),
                iterator_get_pointer(&t_left),
                &t_result);
            if(t_result) /* t_parent < t_left */
            {
                return false;
            }
        }
        if(t_rpos < t_len)
        {
            t_right = t_first;
            iterator_next_n(&t_right, t_rpos);

            (*t_binary_op)(
                iterator_get_pointer(&t_parent),
                iterator_get_pointer(&t_right),
                &t_result);
            if(t_result) /* t_parent < t_right */
            {
                return false;
            }
        }
    }

    return true;
}

/** local function implementation section **/
static void _adjust_heap(
    random_access_iterator_t t_first,
    random_access_iterator_t t_last,
    random_access_iterator_t t_parent,
    binary_function_t t_binary_op)
{
    bool_t                   t_result = false;
    size_t                   t_len = 0;
    size_t                   t_ppos = 0;
    size_t                   t_lpos = 0;
    size_t                   t_rpos = 0;
    random_access_iterator_t t_left;
    random_access_iterator_t t_right;

    assert(_tools_valid_iterator_range(t_first, t_parent, _RANDOM_ACCESS_ITERATOR));
    assert(_tools_valid_iterator_range(t_parent, t_last, _RANDOM_ACCESS_ITERATOR));
    assert(t_binary_op != NULL);

    if(!iterator_equal(&t_first, t_last))
    {
        /* get left child and right child */
        t_len = iterator_distance(t_first, t_last);
        t_ppos = iterator_distance(t_first, t_parent);
        t_lpos = t_ppos * 2 + 1;
        t_rpos = t_ppos * 2 + 2;
        while(t_lpos < t_len)
        {
            if(t_rpos < t_len)
            {
                t_left = t_right = t_first;
                iterator_next_n(&t_left, t_lpos);
                iterator_next_n(&t_right, t_rpos);
                (*t_binary_op)(
                    iterator_get_pointer(&t_right),
                    iterator_get_pointer(&t_left),
                    &t_result);
                /* t_right < t_left */
                if(t_result)
                {
                    (*t_binary_op)(
                        iterator_get_pointer(&t_left),
                        iterator_get_pointer(&t_parent),
                        &t_result);
                    /* t_left < t_parent */
                    if(t_result)
                    {
                        break;
                    }
                    else /* t_left >= t_parent */
                    {
                        algo_iter_swap(t_parent, t_left);
                        t_parent = t_left;
                        t_ppos = t_lpos;
                    }
                }
                else /* t_right >= t_lef */
                {
                    (*t_binary_op)(
                        iterator_get_pointer(&t_right),
                        iterator_get_pointer(&t_parent),
                        &t_result);
                    /* t_right < t_parent */
                    if(t_result)
                    {
                        break;
                    }
                    else
                    {
                        algo_iter_swap(t_parent, t_right);
                        t_parent = t_right;
                        t_ppos = t_rpos;
                    }
                }
            }
            else /* don't have right child */
            {
                t_left = t_first;
                iterator_next_n(&t_left, t_lpos);

                (*t_binary_op)(
                    iterator_get_pointer(&t_left),
                    iterator_get_pointer(&t_parent),
                    &t_result);
                /* t_left < t_parent */
                if(t_result)
                {
                    break;
                }
                else /* t_left >= t_parent */
                {
                    algo_iter_swap(t_parent, t_left);
                    t_parent = t_left;
                    t_ppos = t_lpos;
                }
            }

            t_lpos = t_ppos * 2 + 1;
            t_rpos = t_ppos * 2 + 2;
        }
    }
}

/** eof **/

