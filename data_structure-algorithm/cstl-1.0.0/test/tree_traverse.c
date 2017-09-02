/*
 * =============================================================================
 *  Copyright (c) 2008 ActiveSys.Wangbo
 *
 *  copyright description ...
 *
 *  Project:    cstl
 *  Module:     test
 *  Filename:   tree_traverse.c
 *
 *  file description ...
 *
 *  2008-12-27 10:01:25
 * =============================================================================
 */

/** include section **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include <unistd.h>

#include "citerator.h"
#include "cvector.h"
#include "clist.h"
#include "cdeque.h"
#include "cstack.h"
#include "cqueue.h"
#include "cslist.h"
#include "cutility.h"
#include "cset.h"
#include "cmap.h"
#include "chash_set.h"
#include "chash_map.h"

#include "cstl_avl_tree_iterator.h"
#include "cstl_avl_tree_private.h"

#include "cstl_rb_tree_iterator.h"
#include "cstl_rb_tree_private.h"

#include "cstl_hashtable_iterator.h"
#include "cstl_hashtable_private.h"

#include "tree_traverse.h"

/** local constant declaration and local macro section **/

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
void test_travel_avl_tree(
    avlnode_t* pt_root, size_t t_indentsize, void (*pfun_op)(avlnode_t*))
{
    int i = 0;

    if(pt_root != NULL)
    {
        test_travel_avl_tree(pt_root->_pt_right, t_indentsize+4, pfun_op);

        for(i = 0; i < (int)t_indentsize; ++i)
        {
            printf(" ");
        }

        if(pfun_op != NULL)
        {
            (*pfun_op)(pt_root);
        }

        test_travel_avl_tree(pt_root->_pt_left, t_indentsize+4, pfun_op);
    }
}

void test_travel_rb_tree(
    rbnode_t* pt_root, size_t t_indentsize, void (*pfun_op)(rbnode_t*))
{
    int i = 0;

    if(pt_root != NULL)
    {
        test_travel_rb_tree(pt_root->_pt_right, t_indentsize+4, pfun_op);

        for(i = 0; i < (int)t_indentsize; ++i)
        {
            printf(" ");
        }

        if(pfun_op != NULL)
        {
            (*pfun_op)(pt_root);
        }

        test_travel_rb_tree(pt_root->_pt_left, t_indentsize+4, pfun_op);
    }
}

void show_avlnode_info(avlnode_t* pt_root)
{
    assert(pt_root != NULL);
    printf("%d : %d\n", *(int*)pt_root->_pc_data, pt_root->_un_height);
}

void show_rbnode_info(rbnode_t* pt_root)
{
    assert(pt_root != NULL);
    printf("%d : ", *(int*)pt_root->_pc_data);
    if(pt_root->_t_color == red)
    {
        printf("r\n");
    }
    else
    {
        printf("b\n");
    }
}

void show_map_rbnode_info(rbnode_t* pt_root)
{
    assert(pt_root != NULL);
    printf("<%d,%f> : ",
        *(int*)(((pair_t*)(pt_root->_pc_data))->first),
        *(double*)(((pair_t*)(pt_root->_pc_data))->second));
    if(pt_root->_t_color == red)
    {
        printf("r\n");
    }
    else
    {
        printf("b\n");
    }
}

void test_travel_hashtable(vector_t* pt_vector)
{
    int i = 0;
    hashnode_t** ppt_bucket = NULL;
    hashnode_t*  pt_node = NULL;

    assert(pt_vector != NULL);

    for(i = 0; (size_t)i < vector_size(pt_vector); ++i)
    {
        printf("#%d:", i);
        ppt_bucket = (hashnode_t**)vector_at(pt_vector, i);
        pt_node = *ppt_bucket;
        while(pt_node != NULL)
        {
            printf(" %d,", *(int*)pt_node->_pc_data);
            pt_node = pt_node->_pt_next;
        }
        printf("\n");
    }
}

void test_travel_hashtable_pair(vector_t* pt_vector)
{
    int i = 0;
    hashnode_t** ppt_bucket = NULL;
    hashnode_t*  pt_node = NULL;

    assert(pt_vector != NULL);

    for(i = 0; (size_t)i < vector_size(pt_vector); ++i)
    {
        printf("#%d:", i);
        ppt_bucket = (hashnode_t**)vector_at(pt_vector, i);
        pt_node = *ppt_bucket;
        while(pt_node != NULL)
        {
            printf(" <%d,%f>,", 
                *(int*)((pair_t*)pt_node->_pc_data)->first,
                *(double*)((pair_t*)pt_node->_pc_data)->second);
            pt_node = pt_node->_pt_next;
        }
        printf("\n");
    }
}
/** local function implementation section **/
/** eof **/

