/*
 * =============================================================================
 *  Copyright (c) 2008 2009 ActiveSys.Wangbo
 *
 *  copyright description ...
 *
 *  Project:    cstl
 *  Module:     avl tree
 *  Filename:   cstl_avl_tree.c
 *
 *  Implementation of avl tree.
 *
 *  2008-12-24 19:16:05
 * =============================================================================
 */

/** include section **/
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "cstl_types.h"
#include "cstl_alloc.h"
#include "cstl_iterator.h"

#include "cstl_avl_tree_iterator.h"
#include "cstl_avl_tree_private.h"

/** local constant declaration and local macro section **/
#define _AVL_TREE_NODE_SIZE(typesize)\
    ((typesize) + sizeof(avlnode_t) - 1)

/** local data type declaration and local struct, union, enum section **/
/* this struct if for _insert_avlnode function */
typedef struct _taginsertresult
{
    avlnode_t* _pt_adjust;   /* the adjusted avlnode_t pointer */
    avlnode_t* _pt_new;      /* the new inserting avlnode_t* pointer */
}_insert_result_t;

/** local function prototype section **/
#ifndef NDEBUG
/*
 *  Functionname: _iterator_belong_to_avl_tree
 *    Parameters: in) cpt_avl_tree: const avl_tree_t*
 *                    avl_tree pointer.
 *                in) cpt_iterator: const avl_tree_iterator_t*
 *                    avl_tree iterator pointer.
 *       Returns: bool_t
 *   Description: test the iterator is valid one belong to the avl_tree.
 */
static bool_t _iterator_belong_to_avl_tree(
    const avl_tree_t* cpt_avl_tree, const avl_tree_iterator_t* cpt_iterator);

/*
 *  Functionname: _iterator_for_one_and_the_same_avl_tree
 *    Parameters: in) cpt_iteratorfirst: const avl_tree_iterator_t*
 *                    first avl_tree iterator pointer.
 *                in) cpt_iteratorsecond: const avl_tree_iterator_t*
 *                    second avl_tree iterator pointer.
 *       Returns: bool_t
 *   Description: test the two avl_tree iterator is one and the same of avl_tree.
 */
static bool_t _iterator_for_one_and_the_same_avl_tree(
    const avl_tree_iterator_t* cpt_iteratorfirst, 
    const avl_tree_iterator_t* cpt_iteratorsecond);

/*
 *  Functionname: _same_avl_tree_type
 *    Parameters: in) cpt_avl_treefirst: const avl_tree_t*
 *                    first avl_tree pointer.
 *                in) cpt_avl_treesecond: const avl_tree_t*
 *                    second avl_tree pointer.
 *       Returns: bool_t
 *   Description: test the two avl_tree is have the same type.
 */
static bool_t _same_avl_tree_type(
    const avl_tree_t* cpt_avl_treefirst, const avl_tree_t* cpt_avl_treesecond);

/*
 *  Functionname: _same_avl_tree_iterator_type
 *    Parameters: in) cpt_avl_tree: const avl_tree_t*
 *                    the avl_tree pointer
 *                in) cpt_iterator: const avl_tree_iterator_t*
 *                    the avl_tree iterator pointer
 *       Returns: bool_t
 *   Description: test the avl_tree and iterator have the same type.
 */
static bool_t _same_avl_tree_iterator_type(
    const avl_tree_t* cpt_avl_tree, const avl_tree_iterator_t* cpt_iterator);

/*
 *  Functionname: _find_iterator
 *    Parameters: in) cpt_root: const avlnode_t*
 *                    the root of subtree.
 *                in) cpt_pos: const avlnode_t*
 *                    position needed to find.
 *       Returns: bool_t
 *                    find result.
 *   Description: travel subtree for find the position in preorder.
 */
static bool_t _find_iterator(
    const avlnode_t* cpt_root, const avlnode_t* cpt_pos);
#endif /* NDEBUG */

/*
 *  Functionname: _find_value
 *    Parameters: in) cpt_avl_tree: const avl_tree_t
 *                    avl tree pointer.
 *                in) cpt_root: const avlnode_t*
 *                    the root of subtree.
 *                in) cpv_value: const void*
 *                    value needed to find.
 *       Returns: avlnode_t*
 *                    find result.
 *   Description: travel subtree for find the value in preorder.
 */
static avlnode_t* _find_value(
    const avl_tree_t* cpt_avl_tree,
    const avlnode_t* cpt_root, 
    const void* cpv_value); 

/*
 *  Functionname: _destroy_avl_tree
 *    Parameters: in) pt_avl_tree: avl_tree_t*
 *                    avl tree pointer
 *                in) pt_root: avlnode_t*
 *                    the root of subtree.
 *       Returns: void
 *   Description: destroy the subtree with postorder traverse.
 */
static avlnode_t* _destroy_avl_tree(
    avl_tree_t* pt_avl_tree, avlnode_t* pt_root);

/*
 *  Functionname: _left_signal_rotate
 *    Parameters: in) pt_root: avlnode_t*
 *                    subtree root.
 *       Returns: avlnode_t*
 *                    new subtree root after rotate.
 *   Description: ll rotate.
 */
static avlnode_t* _left_signal_rotate(avlnode_t* pt_root);

/*
 *  Functionname: _right_signal_rotate
 *    Parameters: in) pt_root: avlnode_t*
 *                    subtree root.
 *       Returns: avlnode_t*
 *                    new subtree root after rotate.
 *   Description: rr rotate.
 */
static avlnode_t* _right_signal_rotate(avlnode_t* pt_root);

/*
 *  Functionname: _left_double_rotate
 *    Parameters: in) pt_root: avlnode_t*
 *                    subtree root.
 *       Returns: avlnode_t*
 *                    new subtree root after rotate.
 *   Description: lr rotate.
 */
static avlnode_t* _left_double_rotate(avlnode_t* pt_root);

/*
 *  Functionname: _right_double_rotate
 *    Parameters: in) pt_root: avlnode_t*
 *                    subtree root.
 *       Returns: avlnode_t*
 *                    new subtree root after rotate.
 *   Description: rl rotate.
 */
static avlnode_t* _right_double_rotate(avlnode_t* pt_root);

/*
 *  Functionname: _insert_avlnode
 *    Parameters: in) cpt_avl_tree: const avl_tree_t
 *                    avl tree pointer.
 *                in) cpt_root: const avlnode_t*
 *                    the root of subtree.
 *                in) cpv_value: const void*
 *                    value needed to find.
 *       Returns: _insert_result_t
 *                    insert result.
 *   Description: insert the value into subtree.
 */
static _insert_result_t _insert_avlnode(
    const avl_tree_t* cpt_avl_tree, avlnode_t* pt_root, const void* cpv_value);

/*
 *  Functionname: _get_height
 *    Parameters: in) cpt_root: const avlnode_t*
 *                    subtree root.
 *       Returns: int
 *                    the height of this avl tree node.
 *   Description: get avl node height.
 */
static int _get_height(const avlnode_t* cpt_root);

/*
 *  Functionname: _get_min_avlnode
 *    Parameters: in) cpt_root: const avlnode_t*
 *                    subtree root.
 *       Returns: avlnode_t*
 *                    the minimum avlnode pointer
 *   Description: get minimum avlnode pointer.
 */
static avlnode_t* _get_min_avlnode(const avlnode_t* cpt_root);

/*
 *  Functionname: _get_max_avlnode
 *    Parameters: in) cpt_root: const avlnode_t*
 *                    subtree root.
 *       Returns: avlnode_t*
 *                    the maximum avlnode pointer
 *   Description: get maximum avlnode pointer.
 */
static avlnode_t* _get_max_avlnode(const avlnode_t* cpt_root);

/*
 *  Functionname: _rebalance_avl_tree
 *    Parameters: in) pt_root: avlnode_t*
 *                    the root of subtree.
 *       Returns: avlnode_t*
 *                    new root after rebalance.
 *   Description: rebalance the subtree and update the root height.
 */
static avlnode_t* _rebalance_avl_tree(avlnode_t* pt_root);

/** exported global variable definition section **/

/** local global variable definition section **/

/** exported function implementation section **/
/* avl tree iterator function */
avl_tree_iterator_t _create_avl_tree_iterator(void)
{
    avl_tree_iterator_t t_newiterator;

    _GET_AVL_TREE_COREPOS(&t_newiterator) = NULL;
    _GET_AVL_TREE_POINTER(&t_newiterator) = NULL;

    _GET_CONTAINER(&t_newiterator) = NULL;

    return t_newiterator;
}

bool_t _avl_tree_iterator_equal(
    const struct _tagavltree* cpt_avl_tree,
    const avl_tree_iterator_t* cpt_iterator,
    avl_tree_iterator_t t_iterator)
{
#ifdef NDEBUG
    avl_tree_t* pt_avoidwarning = NULL;
    pt_avoidwarning = (avl_tree_t*)cpt_avl_tree;
#endif

    assert(_iterator_belong_to_avl_tree(cpt_avl_tree, cpt_iterator));
    assert(_iterator_belong_to_avl_tree(cpt_avl_tree, &t_iterator));

    if(_GET_AVL_TREE_COREPOS(cpt_iterator) == 
       _GET_AVL_TREE_COREPOS(&t_iterator))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void _avl_tree_iterator_get_value(
    const struct _tagavltree* cpt_avl_tree,
    const avl_tree_iterator_t* cpt_iterator,
    void* pv_value)
{
    assert(_iterator_belong_to_avl_tree(cpt_avl_tree, cpt_iterator));
    assert(pv_value != NULL);
    assert(
        !_avl_tree_iterator_equal(
            cpt_avl_tree, cpt_iterator, _avl_tree_end(cpt_avl_tree)));

    memcpy(
        pv_value, 
        ((avlnode_t*)_GET_AVL_TREE_COREPOS(cpt_iterator))->_pc_data,
        cpt_avl_tree->_t_typesize);
}

const void* _avl_tree_iterator_get_pointer(
    const struct _tagavltree* cpt_avl_tree,
    const avl_tree_iterator_t* cpt_iterator)
{
#ifdef NDEBUG
    avl_tree_t* pt_avoidwarning = NULL;
    pt_avoidwarning = (avl_tree_t*)cpt_avl_tree;
#endif

    assert(_iterator_belong_to_avl_tree(cpt_avl_tree, cpt_iterator));
    assert(
        !_avl_tree_iterator_equal(
            cpt_avl_tree, cpt_iterator, _avl_tree_end(cpt_avl_tree)));

    return ((avlnode_t*)_GET_AVL_TREE_COREPOS(cpt_iterator))->_pc_data;
}

void _avl_tree_iterator_next(
    const struct _tagavltree* cpt_avl_tree, avl_tree_iterator_t* pt_iterator)
{
    avlnode_t* pt_next = NULL;  /* next pos */
    avlnode_t* pt_cur = (avlnode_t*)_GET_AVL_TREE_COREPOS(pt_iterator);

#ifdef NDEBUG
    avl_tree_t* pt_avoidwarning = NULL;
    pt_avoidwarning = (avl_tree_t*)cpt_avl_tree;
#endif

    assert(_iterator_belong_to_avl_tree(cpt_avl_tree, pt_iterator));
    assert(
        !_avl_tree_iterator_equal(
            cpt_avl_tree, pt_iterator, _avl_tree_end(cpt_avl_tree)));

    if(pt_cur->_pt_right != NULL)
    {
        pt_next = pt_cur->_pt_right;
        while(pt_next->_pt_left != NULL)
        {
            pt_next = pt_next->_pt_left;
        }

        _GET_AVL_TREE_COREPOS(pt_iterator) = (char*)pt_next;
    }
    else
    {
        pt_next = pt_cur->_pt_parent;
        while(pt_cur == pt_next->_pt_right)
        {
            pt_cur = pt_next;
            pt_next = pt_next->_pt_parent;
        }
        /* 
         * this is special condition, when the next pos is root's parent.
         * when the avl tree has only one node, this condition is came.
         */
        if(pt_cur->_pt_right != pt_next)
        {
            _GET_AVL_TREE_COREPOS(pt_iterator) = (char*)pt_next;
        }
        else /* here is special condition */
        {
            _GET_AVL_TREE_COREPOS(pt_iterator) = (char*)pt_cur;
        }
    }
}

void _avl_tree_iterator_prev(
    const struct _tagavltree* cpt_avl_tree, avl_tree_iterator_t* pt_iterator)
{
    avlnode_t* pt_prev = NULL;
    avlnode_t* pt_cur = (avlnode_t*)_GET_AVL_TREE_COREPOS(pt_iterator);

#ifdef NDEBUG
    avl_tree_t* pt_avoidwarning = NULL;
    pt_avoidwarning = (avl_tree_t*)cpt_avl_tree;
#endif

    assert(_iterator_belong_to_avl_tree(cpt_avl_tree, pt_iterator));
    assert(
        !_avl_tree_iterator_equal(
            cpt_avl_tree, pt_iterator, _avl_tree_begin(cpt_avl_tree)));

    /* previous end */
    if(_avl_tree_iterator_equal(cpt_avl_tree, pt_iterator, _avl_tree_end(cpt_avl_tree)))
    {
        _GET_AVL_TREE_COREPOS(pt_iterator) = (char*)cpt_avl_tree->_t_avlroot._pt_right;
    }
    else
    {
        if(pt_cur->_pt_left != NULL)
        {
            pt_prev = pt_cur->_pt_left;
            while(pt_prev->_pt_right != NULL)
            {
                pt_prev = pt_prev->_pt_right;
            }

            _GET_AVL_TREE_COREPOS(pt_iterator) = (char*)pt_prev;
        }
        else
        {
            pt_prev = pt_cur->_pt_parent;
            while(pt_cur == pt_prev->_pt_left)
            {
                pt_cur = pt_prev;
                pt_prev = pt_prev->_pt_parent;
            }

            /* 
             * there is no same special condition as next, because the begin 
             * iterator is the valid iterator 
             */
            _GET_AVL_TREE_COREPOS(pt_iterator) = (char*)pt_prev;
        }
    }
}

int _avl_tree_iterator_distance(
    const avl_tree_iterator_t* cpt_begin, const avl_tree_iterator_t* cpt_end)
{
    avl_tree_iterator_t t_iterator;
    avl_tree_t*         pt_avl_tree = NULL;
    int                 n_distance = 0;

    if(_avl_tree_iterator_before(cpt_begin, cpt_end))
    {
        pt_avl_tree = _GET_AVL_TREE(cpt_begin);
        for(t_iterator = *cpt_begin; 
            !_avl_tree_iterator_equal(pt_avl_tree, &t_iterator, *cpt_end);
            _avl_tree_iterator_next(pt_avl_tree, &t_iterator))
        {
            n_distance++;
        }

        return n_distance;
    }
    else if(_avl_tree_iterator_before(cpt_end, cpt_begin))
    {
        pt_avl_tree = _GET_AVL_TREE(cpt_begin);
        for(t_iterator = *cpt_end;
            !_avl_tree_iterator_equal(pt_avl_tree, &t_iterator, *cpt_begin);
            _avl_tree_iterator_next(pt_avl_tree, &t_iterator))
        {
            n_distance++;
        }

        return -n_distance;
    }
    else
    {
        return 0;
    }
}

bool_t _avl_tree_iterator_before(
    const avl_tree_iterator_t* cpt_iteratorfirst, 
    const avl_tree_iterator_t* cpt_iteratorsecond)
{
    avl_tree_iterator_t t_iterator;
    avl_tree_t*         pt_avl_tree = NULL;

    assert(
        _iterator_for_one_and_the_same_avl_tree(
            cpt_iteratorfirst, cpt_iteratorsecond));
    assert(
        _iterator_belong_to_avl_tree(
            _GET_AVL_TREE(cpt_iteratorfirst), cpt_iteratorfirst) &&
        _iterator_belong_to_avl_tree(
            _GET_AVL_TREE(cpt_iteratorsecond), cpt_iteratorsecond));
    assert(
        _GET_AVL_TREE(cpt_iteratorfirst) != NULL &&
        _GET_AVL_TREE(cpt_iteratorsecond) != NULL);
    assert(
        _GET_AVL_TREE_COREPOS(cpt_iteratorfirst) != NULL &&
        _GET_AVL_TREE_COREPOS(cpt_iteratorsecond) != NULL);

    /* first iterator equal to second iterator */
    if(_GET_AVL_TREE_COREPOS(cpt_iteratorfirst) == 
       _GET_AVL_TREE_COREPOS(cpt_iteratorsecond))
    {
        return false;
    }
    /* else travel subtree for search second iterator */
    pt_avl_tree = _GET_AVL_TREE(cpt_iteratorfirst);
    for(t_iterator = *cpt_iteratorfirst;
        !_avl_tree_iterator_equal(
            pt_avl_tree, &t_iterator, _avl_tree_end(pt_avl_tree));
        _avl_tree_iterator_next(pt_avl_tree, &t_iterator))
    {
        if(_avl_tree_iterator_equal(
            pt_avl_tree, &t_iterator, *cpt_iteratorsecond))
        {
            return true;
        }
    }

    if(_avl_tree_iterator_equal(
        pt_avl_tree, cpt_iteratorsecond, _avl_tree_end(pt_avl_tree)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/* avl private function */
avl_tree_t _create_avl_tree(size_t t_typesize, const char* s_typename)
{
    avl_tree_t t_newavltree;

    t_newavltree._t_typesize = t_typesize;
    memset(t_newavltree._sz_typename, '\0', _ELEM_TYPE_NAME_SIZE+1);
    strncpy(t_newavltree._sz_typename, s_typename, _ELEM_TYPE_NAME_SIZE);
    _unify_types(t_newavltree._t_typesize, t_newavltree._sz_typename);

    t_newavltree._t_avlroot._pt_parent = NULL;
    t_newavltree._t_avlroot._pt_left = NULL;
    t_newavltree._t_avlroot._pt_right = NULL;
    t_newavltree._t_avlroot._un_height = 0;
    t_newavltree._t_nodecount = 0;

    t_newavltree._pfun_cmp = NULL;
    t_newavltree._pfun_destroy_elem = NULL;

    return t_newavltree;
}

void _avl_tree_init(
    avl_tree_t* pt_avl_tree,
    int (*pfun_cmp)(const void*, const void*),
    void (*pfun_destroy_elem)(void*))
{
    assert(
        pt_avl_tree != NULL &&
        pt_avl_tree->_t_nodecount == 0 &&
        pt_avl_tree->_t_avlroot._pt_parent == NULL &&
        pt_avl_tree->_t_avlroot._pt_left == NULL &&
        pt_avl_tree->_t_avlroot._pt_right == NULL &&
        pt_avl_tree->_t_avlroot._un_height == 0 &&
        pt_avl_tree->_pfun_cmp == NULL &&
        pt_avl_tree->_pfun_destroy_elem == NULL);

    pt_avl_tree->_t_avlroot._pt_left = &pt_avl_tree->_t_avlroot;
    pt_avl_tree->_t_avlroot._pt_right = &pt_avl_tree->_t_avlroot;

    allocate_init(&pt_avl_tree->_t_allocater);

    if(pfun_cmp != NULL)
    {
        pt_avl_tree->_pfun_cmp = pfun_cmp;
    }
    else
    {
        pt_avl_tree->_pfun_cmp = _get_cmp_function(pt_avl_tree->_sz_typename);
    }
    pt_avl_tree->_pfun_destroy_elem = pfun_destroy_elem;
}

void _avl_tree_destroy(avl_tree_t* pt_avl_tree)
{
    assert(pt_avl_tree != NULL);

    /* destroy all elements */
    pt_avl_tree->_t_avlroot._pt_parent = 
        _destroy_avl_tree(pt_avl_tree, pt_avl_tree->_t_avlroot._pt_parent);
    assert(pt_avl_tree->_t_avlroot._pt_parent == NULL);
    pt_avl_tree->_t_avlroot._pt_left = &pt_avl_tree->_t_avlroot;
    pt_avl_tree->_t_avlroot._pt_right = &pt_avl_tree->_t_avlroot;
    pt_avl_tree->_t_nodecount = 0;

    /* destroy allocator */
    allocate_destroy(&pt_avl_tree->_t_allocater);

    pt_avl_tree->_pfun_cmp = NULL;
    pt_avl_tree->_pfun_destroy_elem = NULL;
}

void _avl_tree_init_copy(
    avl_tree_t* pt_avl_tree_dest, const avl_tree_t* cpt_avl_tree_src)
{
    assert(pt_avl_tree_dest != NULL && cpt_avl_tree_src != NULL);
    assert(
        pt_avl_tree_dest->_t_typesize == cpt_avl_tree_src->_t_typesize &&
        strncmp(
            pt_avl_tree_dest->_sz_typename,
            cpt_avl_tree_src->_sz_typename,
            _ELEM_TYPE_NAME_SIZE) == 0);

    /* init the avl tree with the src avl tree */
    _avl_tree_init(
        pt_avl_tree_dest, 
        cpt_avl_tree_src->_pfun_cmp,
        cpt_avl_tree_src->_pfun_destroy_elem);
    /* insert all elements of src into dest */
    if(!_avl_tree_empty(cpt_avl_tree_src))
    {
        _avl_tree_insert_equal_range(
            pt_avl_tree_dest, 
            _avl_tree_begin(cpt_avl_tree_src), 
            _avl_tree_end(cpt_avl_tree_src));
    }
}

void _avl_tree_init_copy_range(
    avl_tree_t* pt_avl_tree_dest, 
    avl_tree_iterator_t t_begin,
    avl_tree_iterator_t t_end)
{
    assert(pt_avl_tree_dest != NULL);
    assert(
        pt_avl_tree_dest->_t_typesize == _GET_AVL_TREE(&t_begin)->_t_typesize &&
        strncmp(
            pt_avl_tree_dest->_sz_typename,
            _GET_AVL_TREE(&t_begin)->_sz_typename,
            _ELEM_TYPE_NAME_SIZE) == 0);
    assert(
        _avl_tree_iterator_equal(_GET_AVL_TREE(&t_begin), &t_begin, t_end) ||
        _avl_tree_iterator_before(&t_begin, &t_end));

    /* init the avl tree with the src avl tree */
    _avl_tree_init(
        pt_avl_tree_dest, 
        _GET_AVL_TREE(&t_begin)->_pfun_cmp,
        _GET_AVL_TREE(&t_begin)->_pfun_destroy_elem);
    /* insert all elements of src into dest */
    if(!_avl_tree_empty(_GET_AVL_TREE(&t_begin)))
    {
        _avl_tree_insert_equal_range(pt_avl_tree_dest, t_begin, t_end);
    }
}

void _avl_tree_init_copy_range_cmp(
    avl_tree_t* pt_avl_tree_dest, 
    avl_tree_iterator_t t_begin,
    avl_tree_iterator_t t_end,
    int (*pfun_cmp)(const void*, const void*))
{
    assert(pt_avl_tree_dest != NULL);
    assert(
        pt_avl_tree_dest->_t_typesize == _GET_AVL_TREE(&t_begin)->_t_typesize &&
        strncmp(
            pt_avl_tree_dest->_sz_typename,
            _GET_AVL_TREE(&t_begin)->_sz_typename,
            _ELEM_TYPE_NAME_SIZE) == 0);
    assert(
        _avl_tree_iterator_equal(_GET_AVL_TREE(&t_begin), &t_begin, t_end) ||
        _avl_tree_iterator_before(&t_begin, &t_end));

    /* init the avl tree with the src avl tree */
    _avl_tree_init(
        pt_avl_tree_dest,
        pfun_cmp,
        _GET_AVL_TREE(&t_begin)->_pfun_destroy_elem);
    /* insert all elements of src into dest */
    if(!_avl_tree_empty(_GET_AVL_TREE(&t_begin)))
    {
        _avl_tree_insert_equal_range(pt_avl_tree_dest, t_begin, t_end);
    }
}

void _avl_tree_assign(
    avl_tree_t* pt_avl_tree_dest, const avl_tree_t* cpt_avl_tree_src)
{
    assert(_same_avl_tree_type(pt_avl_tree_dest, cpt_avl_tree_src));

    /* destroy dest avl tree */
    _avl_tree_destroy(pt_avl_tree_dest);
    /* init the avl tree with the src avl tree */
    _avl_tree_init(
        pt_avl_tree_dest, 
        cpt_avl_tree_src->_pfun_cmp,
        cpt_avl_tree_src->_pfun_destroy_elem);
    /* insert all elements of src into dest */
    if(!_avl_tree_empty(cpt_avl_tree_src))
    {
        _avl_tree_insert_equal_range(
            pt_avl_tree_dest, 
            _avl_tree_begin(cpt_avl_tree_src), 
            _avl_tree_end(cpt_avl_tree_src));
    }
}

bool_t _avl_tree_empty(const avl_tree_t* cpt_avl_tree)
{
    assert(cpt_avl_tree != NULL);

    if(cpt_avl_tree->_t_nodecount == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

size_t _avl_tree_size(const avl_tree_t* cpt_avl_tree)
{
    assert(cpt_avl_tree != NULL);

    return cpt_avl_tree->_t_nodecount;
}

size_t _avl_tree_max_size(const avl_tree_t* cpt_avl_tree)
{
    assert(cpt_avl_tree != NULL);

    return (size_t)(-1) / cpt_avl_tree->_t_typesize;
}

avl_tree_iterator_t _avl_tree_begin(const avl_tree_t* cpt_avl_tree)
{
    avl_tree_iterator_t t_newiterator = _create_avl_tree_iterator();

    assert(cpt_avl_tree != NULL);

    _GET_AVL_TREE_POINTER(&t_newiterator) = (void*)cpt_avl_tree;
    _GET_AVL_TREE_COREPOS(&t_newiterator) = 
        (char*)cpt_avl_tree->_t_avlroot._pt_left;

    return t_newiterator;
}

avl_tree_iterator_t _avl_tree_end(const avl_tree_t* cpt_avl_tree)
{
    avl_tree_iterator_t t_newiterator = _create_avl_tree_iterator();

    assert(cpt_avl_tree != NULL);

    _GET_AVL_TREE_POINTER(&t_newiterator) = (void*)cpt_avl_tree;
    _GET_AVL_TREE_COREPOS(&t_newiterator) = (char*)&cpt_avl_tree->_t_avlroot;

    return t_newiterator;
}

avl_tree_reverse_iterator_t _avl_tree_rbegin(const avl_tree_t* cpt_avl_tree)
{
    avl_tree_reverse_iterator_t t_newiterator = _create_avl_tree_iterator();

    assert(cpt_avl_tree != NULL);

    _GET_AVL_TREE_POINTER(&t_newiterator) = (void*)cpt_avl_tree;
    _GET_AVL_TREE_COREPOS(&t_newiterator) = 
        (char*)cpt_avl_tree->_t_avlroot._pt_right;

    return t_newiterator;
}

avl_tree_reverse_iterator_t _avl_tree_rend(const avl_tree_t* cpt_avl_tree)
{
    avl_tree_reverse_iterator_t t_newiterator = _create_avl_tree_iterator();

    assert(cpt_avl_tree != NULL);

    _GET_AVL_TREE_POINTER(&t_newiterator) = (void*)cpt_avl_tree;
    _GET_AVL_TREE_COREPOS(&t_newiterator) = 
        (char*)&cpt_avl_tree->_t_avlroot;

    return t_newiterator;
}

int (*_avl_tree_key_comp(const avl_tree_t* cpt_avl_tree))(
    const void*, const void*)
{
    assert(cpt_avl_tree != NULL);

    return cpt_avl_tree->_pfun_cmp;
}

avl_tree_iterator_t _avl_tree_find(
    const avl_tree_t* cpt_avl_tree, const void* cpv_value)
{
    avl_tree_iterator_t t_iterator;

    assert(cpt_avl_tree != NULL && cpv_value != NULL);

    _GET_AVL_TREE_POINTER(&t_iterator) = (void*)cpt_avl_tree;
    _GET_AVL_TREE_COREPOS(&t_iterator) = 
        (char*)_find_value(
            cpt_avl_tree, cpt_avl_tree->_t_avlroot._pt_parent, cpv_value);
    if(_GET_AVL_TREE_COREPOS(&t_iterator) == NULL)
    {
        _GET_AVL_TREE_COREPOS(&t_iterator) = (char*)&cpt_avl_tree->_t_avlroot;
    }

    return t_iterator;
}

void _avl_tree_clear(avl_tree_t* pt_avl_tree)
{
    assert(pt_avl_tree != NULL);

    /* destroy all elements */
    pt_avl_tree->_t_avlroot._pt_parent = 
        _destroy_avl_tree(pt_avl_tree, pt_avl_tree->_t_avlroot._pt_parent);
    assert(pt_avl_tree->_t_avlroot._pt_parent == NULL);
    pt_avl_tree->_t_avlroot._pt_left = &pt_avl_tree->_t_avlroot;
    pt_avl_tree->_t_avlroot._pt_right = &pt_avl_tree->_t_avlroot;
    pt_avl_tree->_t_nodecount = 0;
}

size_t _avl_tree_count(
    const avl_tree_t* cpt_avl_tree, const void* cpv_value)
{
    avl_tree_result_pair_t t_resultpair;

    assert(cpt_avl_tree != NULL && cpv_value != NULL);

    t_resultpair = _avl_tree_equal_range(cpt_avl_tree, cpv_value);

    return abs(_avl_tree_iterator_distance(
        &t_resultpair._t_first, &t_resultpair._t_second._t_iterator));
}

avl_tree_iterator_t _avl_tree_lower_bound(
    const avl_tree_t* cpt_avl_tree, const void* cpv_value)
{
    avlnode_t*          pt_cur = NULL;
    avlnode_t*          pt_prev = NULL;
    int                 n_cmpresult = 0;
    avl_tree_iterator_t t_iterator;

    assert(cpt_avl_tree != NULL && cpv_value != NULL);

    t_iterator = _create_avl_tree_iterator();
    _GET_AVL_TREE_POINTER(&t_iterator) = (void*)cpt_avl_tree;

    if(!_avl_tree_empty(cpt_avl_tree))
    {
        pt_prev = cpt_avl_tree->_t_avlroot._pt_parent;
        if(cpt_avl_tree->_pfun_cmp != NULL)
        {
            n_cmpresult = 
                (*cpt_avl_tree->_pfun_cmp)(cpv_value, pt_prev->_pc_data);
            if(n_cmpresult <= 0)
            {
                pt_cur = pt_prev->_pt_left;
            }
            else
            {
                pt_cur = pt_prev->_pt_right;
            }
            while(pt_cur != NULL)
            {
                pt_prev = pt_cur;
                n_cmpresult = 
                    (*cpt_avl_tree->_pfun_cmp)(cpv_value, pt_prev->_pc_data);
                if(n_cmpresult <= 0)
                {
                    pt_cur = pt_prev->_pt_left;
                }
                else
                {
                    pt_cur = pt_prev->_pt_right;
                }
            }
        }
        else
        {
            n_cmpresult = 
                memcmp(cpv_value, pt_prev->_pc_data, cpt_avl_tree->_t_typesize);
            if(n_cmpresult <= 0)
            {
                pt_cur = pt_prev->_pt_left;
            }
            else
            {
                pt_cur = pt_prev->_pt_right;
            }
            while(pt_cur != NULL)
            {
                pt_prev = pt_cur;
                n_cmpresult = memcmp(
                    cpv_value, pt_prev->_pc_data, cpt_avl_tree->_t_typesize);
                if(n_cmpresult <= 0)
                {
                    pt_cur = pt_prev->_pt_left;
                }
                else
                {
                    pt_cur = pt_prev->_pt_right;
                }
            }
        }

        if(n_cmpresult <= 0)
        {
            assert(pt_prev->_pt_left == NULL);
            _GET_AVL_TREE_COREPOS(&t_iterator) = (char*)pt_prev;
            assert(_iterator_belong_to_avl_tree(cpt_avl_tree, &t_iterator));
        }
        else
        {
            assert(pt_prev->_pt_right == NULL);
            _GET_AVL_TREE_COREPOS(&t_iterator) = (char*)pt_prev;
            _avl_tree_iterator_next(cpt_avl_tree, &t_iterator);
        }
    }
    else
    {
        t_iterator = _avl_tree_end(cpt_avl_tree);
    }

    return t_iterator;
}

avl_tree_iterator_t _avl_tree_upper_bound(
    const avl_tree_t* cpt_avl_tree, const void* cpv_value)
{
    avlnode_t*          pt_cur = NULL;
    avlnode_t*          pt_prev = NULL;
    int                 n_cmpresult = 0;
    avl_tree_iterator_t t_iterator;

    assert(cpt_avl_tree != NULL && cpv_value != NULL);

    t_iterator = _create_avl_tree_iterator();
    _GET_AVL_TREE_POINTER(&t_iterator) = (void*)cpt_avl_tree;

    if(!_avl_tree_empty(cpt_avl_tree))
    {
        pt_prev = cpt_avl_tree->_t_avlroot._pt_parent;
        if(cpt_avl_tree->_pfun_cmp != NULL)
        {
            n_cmpresult = 
                (*cpt_avl_tree->_pfun_cmp)(cpv_value, pt_prev->_pc_data);
            if(n_cmpresult < 0)
            {
                pt_cur = pt_prev->_pt_left;
            }
            else
            {
                pt_cur = pt_prev->_pt_right;
            }
            while(pt_cur != NULL)
            {
                pt_prev = pt_cur;
                n_cmpresult = 
                    (*cpt_avl_tree->_pfun_cmp)(cpv_value, pt_prev->_pc_data);
                if(n_cmpresult < 0)
                {
                    pt_cur = pt_prev->_pt_left;
                }
                else
                {
                    pt_cur = pt_prev->_pt_right;
                }
            }
        }
        else
        {
            n_cmpresult = 
                memcmp(cpv_value, pt_prev->_pc_data, cpt_avl_tree->_t_typesize);
            if(n_cmpresult < 0)
            {
                pt_cur = pt_prev->_pt_left;
            }
            else
            {
                pt_cur = pt_prev->_pt_right;
            }
            while(pt_cur != NULL)
            {
                pt_prev = pt_cur;
                n_cmpresult = memcmp(
                    cpv_value, pt_prev->_pc_data, cpt_avl_tree->_t_typesize);
                if(n_cmpresult < 0)
                {
                    pt_cur = pt_prev->_pt_left;
                }
                else
                {
                    pt_cur = pt_prev->_pt_right;
                }
            }
        }

        if(n_cmpresult < 0)
        {
            assert(pt_prev->_pt_left == NULL);
            _GET_AVL_TREE_COREPOS(&t_iterator) = (char*)pt_prev;
            assert(_iterator_belong_to_avl_tree(cpt_avl_tree, &t_iterator));
        }
        else
        {
            assert(pt_prev->_pt_right == NULL);
            _GET_AVL_TREE_COREPOS(&t_iterator) = (char*)pt_prev;
            _avl_tree_iterator_next(cpt_avl_tree, &t_iterator);
        }
    }
    else
    {
        t_iterator = _avl_tree_end(cpt_avl_tree);
    }

    return t_iterator;
}

avl_tree_result_pair_t _avl_tree_equal_range(
    const avl_tree_t* cpt_avl_tree, const void* cpv_value)
{
    avl_tree_result_pair_t t_resultpair;

    assert(cpt_avl_tree != NULL && cpv_value != NULL);

    t_resultpair._t_first = 
        _avl_tree_lower_bound(cpt_avl_tree, cpv_value);
    t_resultpair._t_second._t_iterator = 
        _avl_tree_upper_bound(cpt_avl_tree, cpv_value);

    return t_resultpair;
}

bool_t _avl_tree_equal(
    const avl_tree_t* cpt_avl_treefirst, const avl_tree_t* cpt_avl_treesecond)
{
    avl_tree_iterator_t t_first;
    avl_tree_iterator_t t_second;

    assert(cpt_avl_treefirst != NULL && cpt_avl_treesecond != NULL);
    
    /* test type */
    if(cpt_avl_treefirst->_t_typesize != cpt_avl_treesecond->_t_typesize ||
       strncmp(
            cpt_avl_treefirst->_sz_typename,
            cpt_avl_treesecond->_sz_typename,
            _ELEM_TYPE_NAME_SIZE) != 0)
    {
        return false;
    }
    /* test compare and destroy element function */
    if(cpt_avl_treefirst->_pfun_cmp != cpt_avl_treesecond->_pfun_cmp ||
       cpt_avl_treefirst->_pfun_destroy_elem != 
            cpt_avl_treesecond->_pfun_destroy_elem)
    {
        return false;
    }
    /* test avl tree size */
    if(_avl_tree_size(cpt_avl_treefirst) != _avl_tree_size(cpt_avl_treesecond))
    {
        return false;
    }
    /* test each element */
    if(cpt_avl_treefirst->_pfun_cmp != NULL)
    {
        for(t_first = _avl_tree_begin(cpt_avl_treefirst), 
                t_second = _avl_tree_begin(cpt_avl_treesecond);
            !_avl_tree_iterator_equal(
                    cpt_avl_treefirst, 
                    &t_first, 
                    _avl_tree_end(cpt_avl_treefirst)) &&
                !_avl_tree_iterator_equal(
                    cpt_avl_treesecond, 
                    &t_second, 
                    _avl_tree_end(cpt_avl_treesecond));
            _avl_tree_iterator_next(cpt_avl_treefirst, &t_first),
                _avl_tree_iterator_next(cpt_avl_treesecond, &t_second))
        {
            if((*cpt_avl_treefirst->_pfun_cmp)(
                ((avlnode_t*)_GET_AVL_TREE_COREPOS(&t_first))->_pc_data,
                ((avlnode_t*)_GET_AVL_TREE_COREPOS(&t_second))->_pc_data) != 0)
            {
                return false;
            }
        }
    }
    else
    {
        for(t_first = _avl_tree_begin(cpt_avl_treefirst), 
                t_second = _avl_tree_begin(cpt_avl_treesecond);
            !_avl_tree_iterator_equal(
                    cpt_avl_treefirst, 
                    &t_first, 
                    _avl_tree_end(cpt_avl_treefirst)) &&
                !_avl_tree_iterator_equal(
                    cpt_avl_treesecond, 
                    &t_second, 
                    _avl_tree_end(cpt_avl_treesecond));
            _avl_tree_iterator_next(cpt_avl_treefirst, &t_first),
                _avl_tree_iterator_next(cpt_avl_treesecond, &t_second))
        {
            if(memcmp(
                ((avlnode_t*)_GET_AVL_TREE_COREPOS(&t_first))->_pc_data,
                ((avlnode_t*)_GET_AVL_TREE_COREPOS(&t_second))->_pc_data, 
                cpt_avl_treefirst->_t_typesize) != 0)
            {
                return false;
            }
        }
    }

    assert(
        _avl_tree_iterator_equal(
            cpt_avl_treefirst, &t_first, _avl_tree_end(cpt_avl_treefirst)) &&
        _avl_tree_iterator_equal(
            cpt_avl_treesecond, &t_second, _avl_tree_end(cpt_avl_treesecond)));

    return true;
}

bool_t _avl_tree_not_equal(
    const avl_tree_t* cpt_avl_treefirst, const avl_tree_t* cpt_avl_treesecond)
{
    return!_avl_tree_equal(cpt_avl_treefirst, cpt_avl_treesecond);
}

bool_t _avl_tree_less(
    const avl_tree_t* cpt_avl_treefirst, const avl_tree_t* cpt_avl_treesecond)
{
    avl_tree_iterator_t t_first;
    avl_tree_iterator_t t_second;
    int                 n_cmpresult = 0;

    assert(_same_avl_tree_type(cpt_avl_treefirst, cpt_avl_treesecond));

    /* test each element */
    if(cpt_avl_treefirst->_pfun_cmp != NULL)
    {
        for(t_first = _avl_tree_begin(cpt_avl_treefirst), 
                t_second = _avl_tree_begin(cpt_avl_treesecond);
            !_avl_tree_iterator_equal(
                    cpt_avl_treefirst, 
                    &t_first, 
                    _avl_tree_end(cpt_avl_treefirst)) &&
                !_avl_tree_iterator_equal(
                    cpt_avl_treesecond, 
                    &t_second, 
                    _avl_tree_end(cpt_avl_treesecond));
            _avl_tree_iterator_next(cpt_avl_treefirst, &t_first),
                _avl_tree_iterator_next(cpt_avl_treesecond, &t_second))
        {
            n_cmpresult = (*cpt_avl_treefirst->_pfun_cmp)(
                ((avlnode_t*)_GET_AVL_TREE_COREPOS(&t_first))->_pc_data,
                ((avlnode_t*)_GET_AVL_TREE_COREPOS(&t_second))->_pc_data);
            if(n_cmpresult < 0)
            {
                return true;
            }
            else if(n_cmpresult > 0)
            {
                return false;
            }
        }
    }
    else
    {
        for(t_first = _avl_tree_begin(cpt_avl_treefirst), 
                t_second = _avl_tree_begin(cpt_avl_treesecond);
            !_avl_tree_iterator_equal(
                    cpt_avl_treefirst, 
                    &t_first, 
                    _avl_tree_end(cpt_avl_treefirst)) &&
                !_avl_tree_iterator_equal(
                    cpt_avl_treesecond, 
                    &t_second, 
                    _avl_tree_end(cpt_avl_treesecond));
            _avl_tree_iterator_next(cpt_avl_treefirst, &t_first),
                _avl_tree_iterator_next(cpt_avl_treesecond, &t_second))
        {
            n_cmpresult = memcmp(
                ((avlnode_t*)_GET_AVL_TREE_COREPOS(&t_first))->_pc_data,
                ((avlnode_t*)_GET_AVL_TREE_COREPOS(&t_second))->_pc_data, 
                cpt_avl_treefirst->_t_typesize);
            if(n_cmpresult < 0)
            {
                return true;
            }
            else if(n_cmpresult > 0)
            {
                return false;
            }
        }
    }

    if(_avl_tree_size(cpt_avl_treefirst) < _avl_tree_size(cpt_avl_treesecond))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool_t _avl_tree_less_equal(
    const avl_tree_t* cpt_avl_treefirst, const avl_tree_t* cpt_avl_treesecond)
{
    return _avl_tree_less(cpt_avl_treefirst, cpt_avl_treesecond) ||
           _avl_tree_equal(cpt_avl_treefirst, cpt_avl_treesecond);
}

bool_t _avl_tree_great(
    const avl_tree_t* cpt_avl_treefirst, const avl_tree_t* cpt_avl_treesecond)
{
    return _avl_tree_less(cpt_avl_treesecond, cpt_avl_treefirst);
}

bool_t _avl_tree_great_equal(
    const avl_tree_t* cpt_avl_treefirst, const avl_tree_t* cpt_avl_treesecond)
{
    return _avl_tree_great(cpt_avl_treefirst, cpt_avl_treesecond) ||
           _avl_tree_equal(cpt_avl_treefirst, cpt_avl_treesecond);
}

void _avl_tree_swap(avl_tree_t* pt_avl_treefirst, avl_tree_t* pt_avl_treesecond)
{
    avl_tree_t t_avl_treetmp;

    assert(pt_avl_treefirst != NULL && pt_avl_treesecond != NULL);

    t_avl_treetmp = *pt_avl_treefirst;
    *pt_avl_treefirst = *pt_avl_treesecond;
    *pt_avl_treesecond = t_avl_treetmp;

    if(_avl_tree_empty(pt_avl_treefirst))
    {
        pt_avl_treefirst->_t_avlroot._pt_left = &pt_avl_treefirst->_t_avlroot;
        pt_avl_treefirst->_t_avlroot._pt_right = &pt_avl_treefirst->_t_avlroot;
    }
    else
    {
        pt_avl_treefirst->_t_avlroot._pt_parent->_pt_parent = 
            &pt_avl_treefirst->_t_avlroot;
    }

    if(_avl_tree_empty(pt_avl_treesecond))
    {
        pt_avl_treesecond->_t_avlroot._pt_left = &pt_avl_treesecond->_t_avlroot;
        pt_avl_treesecond->_t_avlroot._pt_right = &pt_avl_treesecond->_t_avlroot;
    }
    else
    {
        pt_avl_treesecond->_t_avlroot._pt_parent->_pt_parent = 
            &pt_avl_treesecond->_t_avlroot;
    }
}

avl_tree_iterator_t _avl_tree_insert_equal(
    avl_tree_t* pt_avl_tree, const void* cpv_value)
{
    _insert_result_t    t_insert_result;
    avl_tree_iterator_t t_iterator = _create_avl_tree_iterator();

    assert(pt_avl_tree != NULL && cpv_value != NULL);

    t_insert_result = _insert_avlnode(
            pt_avl_tree, pt_avl_tree->_t_avlroot._pt_parent, cpv_value);
    assert(
        t_insert_result._pt_adjust != NULL && 
        t_insert_result._pt_new != NULL);

    pt_avl_tree->_t_avlroot._pt_parent = t_insert_result._pt_adjust;
    pt_avl_tree->_t_avlroot._pt_parent->_pt_parent = &pt_avl_tree->_t_avlroot;
    pt_avl_tree->_t_avlroot._pt_left = 
        _get_min_avlnode(pt_avl_tree->_t_avlroot._pt_parent);
    pt_avl_tree->_t_avlroot._pt_right = 
        _get_max_avlnode(pt_avl_tree->_t_avlroot._pt_parent);
    pt_avl_tree->_t_nodecount++;

    _GET_AVL_TREE_POINTER(&t_iterator) = pt_avl_tree;
    _GET_AVL_TREE_COREPOS(&t_iterator) = (char*)t_insert_result._pt_new;

    return t_iterator;
}

avl_tree_result_pair_t _avl_tree_insert_unique(
    avl_tree_t* pt_avl_tree, const void* cpv_value)
{
    avl_tree_result_pair_t t_result;

    assert(pt_avl_tree != NULL && cpv_value != NULL);

    /* if the avl tree is empty */
    if(_avl_tree_empty(pt_avl_tree))
    {
        t_result._t_first = _avl_tree_insert_equal(pt_avl_tree, cpv_value);
        t_result._t_second._t_bool = true;

        return t_result;
    }
    /* else */
    else
    {
        /* find value in avl tree */
        t_result._t_first = _avl_tree_find(pt_avl_tree, cpv_value);
        /* if the value is exist */
        if(!_avl_tree_iterator_equal(
            pt_avl_tree, &t_result._t_first, _avl_tree_end(pt_avl_tree)))
        {
            /* return false pair */
            t_result._t_second._t_bool = false;

            return t_result;
        }
        /* else */
        else
        {
            /* insert value into avl tree */
            t_result._t_first = _avl_tree_insert_equal(pt_avl_tree, cpv_value);
            /* return true pair */
            t_result._t_second._t_bool = true;

            return t_result;
        }
    }
}

void _avl_tree_insert_equal_range(
    avl_tree_t* pt_avl_tree,
    avl_tree_iterator_t t_begin,
    avl_tree_iterator_t t_end)
{
    avl_tree_iterator_t t_iterator;
    avl_tree_t*         pt_src_avl_tree = NULL;

    assert(_same_avl_tree_iterator_type(pt_avl_tree, &t_begin));
    assert(
        _avl_tree_iterator_equal(_GET_AVL_TREE(&t_begin), &t_begin, t_end) ||
        _avl_tree_iterator_before(&t_begin, &t_end));

    pt_src_avl_tree = _GET_AVL_TREE(&t_begin);
    for(t_iterator = t_begin;
        !_avl_tree_iterator_equal(pt_src_avl_tree, &t_iterator, t_end);
        _avl_tree_iterator_next(pt_src_avl_tree, &t_iterator))
    {
        _avl_tree_insert_equal(
            pt_avl_tree, 
            ((avlnode_t*)_GET_AVL_TREE_COREPOS(&t_iterator))->_pc_data);
    }
}

void _avl_tree_insert_unique_range(
    avl_tree_t* pt_avl_tree, 
    avl_tree_iterator_t t_begin, 
    avl_tree_iterator_t t_end)
{
    avl_tree_iterator_t t_iterator;
    avl_tree_t*         pt_src_avl_tree = NULL;

    assert(_same_avl_tree_iterator_type(pt_avl_tree, &t_begin));
    assert(
        _avl_tree_iterator_equal(_GET_AVL_TREE(&t_begin), &t_begin, t_end) ||
        _avl_tree_iterator_before(&t_begin, &t_end));

    pt_src_avl_tree = _GET_AVL_TREE(&t_begin);
    for(t_iterator = t_begin;
        !_avl_tree_iterator_equal(pt_src_avl_tree, &t_iterator, t_end);
        _avl_tree_iterator_next(pt_src_avl_tree, &t_iterator))
    {
        _avl_tree_insert_unique(
            pt_avl_tree, 
            ((avlnode_t*)_GET_AVL_TREE_COREPOS(&t_iterator))->_pc_data);
    }
}

void _avl_tree_erase_pos(avl_tree_t* pt_avl_tree, avl_tree_iterator_t t_pos)
{
    avlnode_t* pt_parent = NULL;
    avlnode_t* pt_cur = NULL;

    assert(_iterator_belong_to_avl_tree(pt_avl_tree, &t_pos));
    assert(
        !_avl_tree_iterator_equal(
            pt_avl_tree, &t_pos, _avl_tree_end(pt_avl_tree)));
    
    pt_cur = (avlnode_t*)_GET_AVL_TREE_COREPOS(&t_pos);
    pt_parent = pt_cur->_pt_parent;

    /* delete node X express deleting */
    if(pt_cur->_pt_left == NULL && pt_cur->_pt_right == NULL)
    {
        /*
         *  P       P
         *  |   =>   
         *  X
         */
        if(pt_parent == &pt_avl_tree->_t_avlroot)
        {
            pt_parent->_pt_parent = NULL;
        }
        /*
         *    P       P
         *   /   =>   
         *  X
         */
        else if(pt_cur == pt_parent->_pt_left)
        {
            pt_parent->_pt_left = NULL;
        }
        /*
         *   P         P
         *    \   =>  
         *     X
         */
        else
        {
            pt_parent->_pt_right = NULL;
        }
    }
    else if(pt_cur->_pt_left != NULL && pt_cur->_pt_right == NULL)
    {
        /*
         *   P          P
         *   |          |
         *   X     =>   L
         *  /
         * L
         */
        if(pt_parent == &pt_avl_tree->_t_avlroot)
        {
            pt_parent->_pt_parent = pt_cur->_pt_left;
            pt_parent->_pt_parent->_pt_parent = pt_parent;
        }
        /*
         *     P          P
         *    /          /
         *   X     =>   L
         *  /
         * L
         */
        else if(pt_cur == pt_parent->_pt_left)
        {
            pt_parent->_pt_left = pt_cur->_pt_left;
            pt_parent->_pt_left->_pt_parent = pt_parent;
        }
        /*
         *  P           P
         *   \           \
         *    X   =>      L
         *   /
         *  L
         */
        else
        {
            pt_parent->_pt_right = pt_cur->_pt_left;
            pt_parent->_pt_right->_pt_parent = pt_parent;
        }
    }
    else if(pt_cur->_pt_left == NULL && pt_cur->_pt_right != NULL)
    {
        /*
         *     P             P
         *     |             |
         *     X     =>      R
         *      \
         *       R
         */
        if(pt_parent == &pt_avl_tree->_t_avlroot)
        {
            pt_parent->_pt_parent = pt_cur->_pt_right;
            pt_parent->_pt_parent->_pt_parent = pt_parent;
        }
        /*
         *   P             P
         *    \             \
         *     X     =>      R
         *      \
         *       R
         */
        else if(pt_cur == pt_parent->_pt_right)
        {
            pt_parent->_pt_right = pt_cur->_pt_right;
            pt_parent->_pt_right->_pt_parent = pt_parent;
        }
        /*
         *    P              R
         *   /              /
         *  X       =>     R
         *   \
         *    R
         */
        else
        {
            pt_parent->_pt_left = pt_cur->_pt_right;
            pt_parent->_pt_left->_pt_parent = pt_parent;
        }
    }
    else
    {
        avlnode_t* pt_parenttmp = NULL;
        avlnode_t* pt_curtmp = NULL;

        if(pt_parent == &pt_avl_tree->_t_avlroot)
        {
            pt_curtmp = _get_min_avlnode(pt_cur->_pt_right);
            /*
             *     P              P
             *     |              | 
             *     X       =>     B
             *    / \            / \
             *   A   B          A   C
             *        \
             *         C
             */
            if(pt_cur == pt_curtmp->_pt_parent)
            {
                /* pt_curtmp express B */
                pt_curtmp->_pt_left = pt_cur->_pt_left;
                pt_curtmp->_pt_left->_pt_parent = pt_curtmp;
                pt_curtmp->_pt_parent = pt_cur->_pt_parent;
                pt_curtmp->_pt_parent->_pt_parent = pt_curtmp;

                pt_parent = pt_curtmp;
            }
            /*
             *     P              P
             *     |              | 
             *     X       =>     S
             *    / \            / \
             *   A   B          A   B
             *      / \            / \
             *     S   C          D   C
             *      \
             *       D
             */
            else
            {
                /* pt_curtmp express S; pt_parenttmp express B */
                pt_parenttmp = pt_curtmp->_pt_parent;
                pt_parenttmp->_pt_left = pt_curtmp->_pt_right;
                if(pt_parenttmp->_pt_left != NULL)
                {
                    pt_parenttmp->_pt_left->_pt_parent = pt_parenttmp;
                }

                pt_curtmp->_pt_left = pt_cur->_pt_left;
                pt_curtmp->_pt_left->_pt_parent = pt_curtmp;
                pt_curtmp->_pt_right = pt_cur->_pt_right;
                pt_curtmp->_pt_right->_pt_parent = pt_curtmp;
                pt_curtmp->_pt_parent = pt_cur->_pt_parent;
                pt_curtmp->_pt_parent->_pt_parent = pt_curtmp;

                pt_parent = pt_parenttmp;
            }
        }
        else if(pt_cur == pt_parent->_pt_left)
        {
            pt_curtmp = _get_min_avlnode(pt_cur->_pt_right);
            /*
             *       P              P
             *      /              / 
             *     X       =>     B
             *    / \            / \
             *   A   B          A   C
             *        \
             *         C
             */
            if(pt_cur == pt_curtmp->_pt_parent)
            {
                /* pt_curtmp express B */
                pt_curtmp->_pt_left = pt_cur->_pt_left;
                pt_curtmp->_pt_left->_pt_parent = pt_curtmp;
                pt_curtmp->_pt_parent = pt_cur->_pt_parent;
                pt_curtmp->_pt_parent->_pt_left = pt_curtmp;

                pt_parent = pt_curtmp;
            }
            /*
             *       P              P
             *      /              / 
             *     X       =>     S
             *    / \            / \
             *   A   B          A   B
             *      / \            / \
             *     S   C          D   C
             *      \
             *       D
             */
            else
            {
                /* pt_curtmp express S; pt_parenttmp express B */
                pt_parenttmp = pt_curtmp->_pt_parent;
                pt_parenttmp->_pt_left = pt_curtmp->_pt_right;
                if(pt_parenttmp->_pt_left != NULL)
                {
                    pt_parenttmp->_pt_left->_pt_parent = pt_parenttmp;
                }

                pt_curtmp->_pt_left = pt_cur->_pt_left;
                pt_curtmp->_pt_left->_pt_parent = pt_curtmp;
                pt_curtmp->_pt_right = pt_cur->_pt_right;
                pt_curtmp->_pt_right->_pt_parent = pt_curtmp;
                pt_curtmp->_pt_parent = pt_cur->_pt_parent;
                pt_curtmp->_pt_parent->_pt_left = pt_curtmp;

                pt_parent = pt_parenttmp;
            }
        }
        else
        {
            pt_curtmp = _get_min_avlnode(pt_cur->_pt_right);
            /*
             *      P            P
             *       \            \
             *        X     =>     B
             *       / \          / \
             *      A   B        A   C
             *           \
             *            C
             */
            if(pt_cur == pt_curtmp->_pt_parent)
            {
                /* pt_curtmp express B */
                pt_curtmp->_pt_left = pt_cur->_pt_left;
                pt_curtmp->_pt_left->_pt_parent = pt_curtmp;
                pt_curtmp->_pt_parent = pt_cur->_pt_parent;
                pt_curtmp->_pt_parent->_pt_right = pt_curtmp;

                pt_parent = pt_curtmp;
            }
            /*
             *      P            P
             *       \            \
             *        X     =>     S
             *       / \          / \
             *      A   B        A   B
             *         / \          / \
             *        C   D        C   D
             *       / \          / \
             *      S   E        F   E
             *       \
             *        F
             */
            else
            {
                /* pt_curtmp express S; pt_parenttmp express C */
                pt_parenttmp = pt_curtmp->_pt_parent;
                pt_parenttmp->_pt_left = pt_curtmp->_pt_right;
                if(pt_parenttmp->_pt_left != NULL)
                {
                    pt_parenttmp->_pt_left->_pt_parent = pt_parenttmp;
                }

                pt_curtmp->_pt_left = pt_cur->_pt_left;
                pt_curtmp->_pt_left->_pt_parent = pt_curtmp;
                pt_curtmp->_pt_right = pt_cur->_pt_right;
                pt_curtmp->_pt_right->_pt_parent = pt_curtmp;
                pt_curtmp->_pt_parent = pt_cur->_pt_parent;
                pt_curtmp->_pt_parent->_pt_right = pt_curtmp;

                pt_parent = pt_parenttmp;
            }
        }
    }

    /* rebalance until to root */
    if(pt_parent != &pt_avl_tree->_t_avlroot)
    {
        avlnode_t* pt_newcur = pt_parent;
        pt_parent = pt_newcur->_pt_parent;
        while(pt_parent != &pt_avl_tree->_t_avlroot)
        {
            if(pt_newcur == pt_parent->_pt_left)
            {
                pt_parent->_pt_left = _rebalance_avl_tree(pt_parent->_pt_left);
                pt_parent->_pt_left->_pt_parent = pt_parent;
            }
            else
            {
                pt_parent->_pt_right = _rebalance_avl_tree(pt_parent->_pt_right);
                pt_parent->_pt_right->_pt_parent = pt_parent;
            }

            pt_newcur = pt_parent;
            pt_parent = pt_newcur->_pt_parent;
        }
    }

    /* rebalance root */
    if(pt_parent->_pt_parent != NULL)
    {
        pt_parent->_pt_parent = _rebalance_avl_tree(pt_parent->_pt_parent);
        pt_parent->_pt_parent->_pt_parent = pt_parent;
    }

    /* destroy node */
    if(pt_avl_tree->_pfun_destroy_elem != NULL)
    {
        (*pt_avl_tree->_pfun_destroy_elem)(pt_cur->_pc_data);
    }
    deallocate(
        &pt_avl_tree->_t_allocater, pt_cur,
        _AVL_TREE_NODE_SIZE(pt_avl_tree->_t_typesize), 1);
    pt_avl_tree->_t_nodecount--;
    if(pt_avl_tree->_t_nodecount == 0)
    {
        pt_avl_tree->_t_avlroot._pt_parent = NULL;
        pt_avl_tree->_t_avlroot._pt_left = &pt_avl_tree->_t_avlroot;
        pt_avl_tree->_t_avlroot._pt_right = &pt_avl_tree->_t_avlroot;
    }
    else
    {
        pt_avl_tree->_t_avlroot._pt_left = 
            _get_min_avlnode(pt_avl_tree->_t_avlroot._pt_parent);
        pt_avl_tree->_t_avlroot._pt_right = 
            _get_max_avlnode(pt_avl_tree->_t_avlroot._pt_parent);
    }
}

void _avl_tree_erase_range(
    avl_tree_t* pt_avl_tree,
    avl_tree_iterator_t t_begin,
    avl_tree_iterator_t t_end)
{
    avl_tree_iterator_t t_iterator;
    avl_tree_iterator_t t_next;

    assert(_same_avl_tree_iterator_type(pt_avl_tree, &t_begin));
    assert(
        _avl_tree_iterator_equal(_GET_AVL_TREE(&t_begin), &t_begin, t_end) ||
        _avl_tree_iterator_before(&t_begin, &t_end));

    t_iterator = t_next = t_begin;
    if(!_avl_tree_iterator_equal(
            pt_avl_tree, &t_next, _avl_tree_end(pt_avl_tree)))
    {
        _avl_tree_iterator_next(pt_avl_tree, &t_next);
    }
    while(!_avl_tree_iterator_equal(pt_avl_tree, &t_iterator, t_end))
    {
        _avl_tree_erase_pos(pt_avl_tree, t_iterator);
        
        t_iterator = t_next;
        if(!_avl_tree_iterator_equal(
                pt_avl_tree, &t_next, _avl_tree_end(pt_avl_tree)))
        {
            _avl_tree_iterator_next(pt_avl_tree, &t_next);
        }
    }
}

size_t _avl_tree_erase(avl_tree_t* pt_avl_tree, const void* cpv_value)
{
    size_t t_countsize = _avl_tree_count(pt_avl_tree, cpv_value);
    avl_tree_result_pair_t t_resultpair = 
        _avl_tree_equal_range(pt_avl_tree, cpv_value);

    if(!_avl_tree_iterator_equal(
        pt_avl_tree, &t_resultpair._t_first, _avl_tree_end(pt_avl_tree)))
    {
        _avl_tree_erase_range(
            pt_avl_tree, 
            t_resultpair._t_first, 
            t_resultpair._t_second._t_iterator);
    }

    return t_countsize;
}

/** local function implementation section **/
#ifndef NDEBUG
static bool_t _iterator_belong_to_avl_tree(
    const avl_tree_t* cpt_avl_tree, const avl_tree_iterator_t* cpt_iterator)
{
    assert(cpt_avl_tree != NULL && cpt_iterator != NULL);
    assert(_GET_AVL_TREE_COREPOS(cpt_iterator) != NULL);
    assert(_GET_AVL_TREE(cpt_iterator) == cpt_avl_tree);

    /* if iterator is end */
    if(_GET_AVL_TREE_COREPOS(cpt_iterator) == (char*)&cpt_avl_tree->_t_avlroot)
    {
        return true;
    }
    /* else travel avl tree for search the pointer */
    else
    {
        return _find_iterator(
            cpt_avl_tree->_t_avlroot._pt_parent, 
            (avlnode_t*)_GET_AVL_TREE_COREPOS(cpt_iterator));
    }
}

static bool_t _same_avl_tree_type(
    const avl_tree_t* cpt_avl_treefirst, const avl_tree_t* cpt_avl_treesecond)
{
    assert(cpt_avl_treefirst != NULL && cpt_avl_treesecond != NULL);

    assert(
        cpt_avl_treefirst->_t_typesize == cpt_avl_treesecond->_t_typesize &&
        strncmp(
            cpt_avl_treefirst->_sz_typename,
            cpt_avl_treesecond->_sz_typename,
            _ELEM_TYPE_NAME_SIZE) == 0);
    assert(
        cpt_avl_treefirst->_pfun_cmp == cpt_avl_treesecond->_pfun_cmp &&
        cpt_avl_treefirst->_pfun_destroy_elem == 
            cpt_avl_treesecond->_pfun_destroy_elem);

    return true;
}

static bool_t _same_avl_tree_iterator_type(
    const avl_tree_t* cpt_avl_tree, const avl_tree_iterator_t* cpt_iterator)
{
    assert(
        cpt_avl_tree != NULL &&
        cpt_iterator != NULL &&
        _GET_AVL_TREE(cpt_iterator) != NULL);
    assert(
        cpt_avl_tree->_t_typesize == _GET_AVL_TREE(cpt_iterator)->_t_typesize &&
        strncmp(
            cpt_avl_tree->_sz_typename,
            _GET_AVL_TREE(cpt_iterator)->_sz_typename,
            _ELEM_TYPE_NAME_SIZE) == 0);
    assert(
        cpt_avl_tree->_pfun_cmp == 
            _GET_AVL_TREE(cpt_iterator)->_pfun_cmp &&
        cpt_avl_tree->_pfun_destroy_elem == 
            _GET_AVL_TREE(cpt_iterator)->_pfun_destroy_elem);

    return true;
}

static bool_t _iterator_for_one_and_the_same_avl_tree(
    const avl_tree_iterator_t* cpt_iteratorfirst,
    const avl_tree_iterator_t* cpt_iteratorsecond)
{
    assert(cpt_iteratorfirst != NULL && cpt_iteratorsecond != NULL);
    assert(
        _GET_AVL_TREE(cpt_iteratorfirst) == _GET_AVL_TREE(cpt_iteratorsecond));

    return true;
}

static bool_t _find_iterator(
    const avlnode_t* cpt_root, const avlnode_t* cpt_pos)
{
    if(cpt_root == NULL || cpt_pos == NULL)
    {
        return false;
    }
    else if(cpt_root == cpt_pos)
    {
        return true;
    }
    else
    {
        return _find_iterator(cpt_root->_pt_left, cpt_pos) ||
               _find_iterator(cpt_root->_pt_right, cpt_pos);
    }
}
#endif /* NDEBUG */

static avlnode_t* _find_value(
    const avl_tree_t* cpt_avl_tree, 
    const avlnode_t* cpt_root, 
    const void* cpv_value) 
{
    int n_cmpresult = 0;

    assert(cpt_avl_tree != NULL && cpv_value != NULL);

    if(cpt_root == NULL)
    {
        return NULL;
    }

    if(cpt_avl_tree->_pfun_cmp != NULL)
    {
        n_cmpresult = (*cpt_avl_tree->_pfun_cmp)(cpv_value, cpt_root->_pc_data);
        if(n_cmpresult == 0)
        {
            return (avlnode_t*)cpt_root;
        }
        else if(n_cmpresult < 0)
        {
            return _find_value(cpt_avl_tree, cpt_root->_pt_left, cpv_value);
        }
        else
        {
            return _find_value(cpt_avl_tree, cpt_root->_pt_right, cpv_value);
        }
    }
    else
    {
        n_cmpresult = 
            memcmp(cpv_value, cpt_root->_pc_data, cpt_avl_tree->_t_typesize);
        if(n_cmpresult == 0)
        {
            return (avlnode_t*)cpt_root;
        }
        else if(n_cmpresult < 0)
        {
            return _find_value(cpt_avl_tree, cpt_root->_pt_left, cpv_value);
        }
        else
        {
            return _find_value(cpt_avl_tree, cpt_root->_pt_right, cpv_value);
        }
    }
}

static avlnode_t* _destroy_avl_tree(
    avl_tree_t* pt_avl_tree, avlnode_t* pt_root)
{
    assert(pt_avl_tree != NULL);

    if(pt_root != NULL)
    {
        pt_root->_pt_left = 
            _destroy_avl_tree(pt_avl_tree, pt_root->_pt_left);
        pt_root->_pt_right = 
            _destroy_avl_tree(pt_avl_tree, pt_root->_pt_right);

        assert(pt_root->_pt_left == NULL && pt_root->_pt_right == NULL);

        if(pt_avl_tree->_pfun_destroy_elem != NULL)
        {
            (*pt_avl_tree->_pfun_destroy_elem)(pt_root->_pc_data);
        }
        deallocate(
            &pt_avl_tree->_t_allocater, pt_root, 
            _AVL_TREE_NODE_SIZE(pt_avl_tree->_t_typesize), 1);
    }
    
    return NULL;
}

/*
 *     A         B
 *    /         / \
 *   B    =>   C   A
 *  / \           /
 * C   D         D
 */
static avlnode_t* _left_signal_rotate(avlnode_t* pt_root)
{
    avlnode_t* pt_left = NULL;

    assert(pt_root != NULL && pt_root->_pt_left != NULL);
    
    /* rotate */
    pt_left = pt_root->_pt_left;
    pt_root->_pt_left = pt_left->_pt_right;
    pt_left->_pt_right = pt_root;
    /* change parent */
    pt_root->_pt_parent = pt_left;
    if(pt_root->_pt_left != NULL)
    {
        pt_root->_pt_left->_pt_parent = pt_root;
    }
    /* update height */
    pt_root->_un_height = (unsigned int)(
        (_get_height(pt_root->_pt_left) > _get_height(pt_root->_pt_right) ?
         _get_height(pt_root->_pt_left) : _get_height(pt_root->_pt_right))+1);
    pt_left->_un_height = (unsigned int)(
        (_get_height(pt_left->_pt_left) > _get_height(pt_left->_pt_right) ?
         _get_height(pt_left->_pt_left) : _get_height(pt_left->_pt_right))+1);

    return pt_left;
}

/*
 *  A              B
 *   \            / \
 *    B     =>   A   D
 *   / \          \
 *  C   D          C
 */
static avlnode_t* _right_signal_rotate(avlnode_t* pt_root)
{
    avlnode_t* pt_right = NULL;

    assert(pt_root != NULL && pt_root->_pt_right != NULL);

    /* rotate */
    pt_right = pt_root->_pt_right;
    pt_root->_pt_right = pt_right->_pt_left;
    pt_right->_pt_left = pt_root;
    /* change parent */
    pt_root->_pt_parent = pt_right;
    if(pt_root->_pt_right != NULL)
    {
        pt_root->_pt_right->_pt_parent = pt_root;
    }
    /* update height */
    pt_root->_un_height = (unsigned int)(
        (_get_height(pt_root->_pt_left) > _get_height(pt_root->_pt_right) ?
         _get_height(pt_root->_pt_left) : _get_height(pt_root->_pt_right))+1);
    pt_right->_un_height = (unsigned int)(
        (_get_height(pt_right->_pt_left) > _get_height(pt_right->_pt_right) ?
         _get_height(pt_right->_pt_left) : _get_height(pt_right->_pt_right))+1);

    return pt_right;
}

/*
 *       A               A                 E
 *      / \             / \              /   \
 *     B   C           E   C            B     A
 *    / \       =>    / \        =>    / \   / \
 *   D   E           B   G            D   F G   C
 *      / \         / \
 *     F   G       D   F
 */        
static avlnode_t* _left_double_rotate(avlnode_t* pt_root)
{
    assert(pt_root != NULL);

    pt_root->_pt_left = _right_signal_rotate(pt_root->_pt_left);
    pt_root->_pt_left->_pt_parent = pt_root;
    return _left_signal_rotate(pt_root);
}

/*
 *       A               A                   D 
 *      / \             / \                /   \
 *     B   C           B   D              A     C
 *        / \    =>       / \       =>   / \   / \
 *       D   E           F   C          B   F G   E
 *      / \                 / \
 *     F   G               G   E
 */
static avlnode_t* _right_double_rotate(avlnode_t* pt_root)
{
    assert(pt_root != NULL);

    pt_root->_pt_right = _left_signal_rotate(pt_root->_pt_right);
    pt_root->_pt_right->_pt_parent = pt_root;
    return _right_signal_rotate(pt_root);
}

static int _get_height(const avlnode_t* cpt_root)
{
    if(cpt_root == NULL)
    {
        return -1;
    }
    else
    {
        return (int)cpt_root->_un_height;
    }
}

static avlnode_t* _get_min_avlnode(const avlnode_t* cpt_root)
{
    avlnode_t* pt_min = (avlnode_t*)cpt_root;

    assert(cpt_root != NULL);

    while(pt_min->_pt_left != NULL)
    {
        pt_min = pt_min->_pt_left;
    }

    return pt_min;
}

static avlnode_t* _get_max_avlnode(const avlnode_t* cpt_root)
{
    avlnode_t* pt_max = (avlnode_t*)cpt_root;

    assert(cpt_root != NULL);

    while(pt_max->_pt_right != NULL)
    {
        pt_max = pt_max->_pt_right;
    }

    return pt_max;
}

static _insert_result_t _insert_avlnode(
    const avl_tree_t* cpt_avl_tree, avlnode_t* pt_root, const void* cpv_value)
{
    int              n_cmpresult = 0;
    _insert_result_t t_insert_result;

    assert(cpt_avl_tree != NULL && cpv_value != NULL);

    /* if root is NULL then allocate memory */
    if(pt_root == NULL)
    {
        pt_root = allocate(
            (alloc_t*)&cpt_avl_tree->_t_allocater, 
            _AVL_TREE_NODE_SIZE(cpt_avl_tree->_t_typesize),
            1);
        assert(pt_root != NULL);

        pt_root->_pt_left = pt_root->_pt_right = NULL;
        pt_root->_un_height = 0;
        memcpy(pt_root->_pc_data, cpv_value, cpt_avl_tree->_t_typesize);
        t_insert_result._pt_adjust = pt_root;
        t_insert_result._pt_new = pt_root;

        return t_insert_result;
    }

    /* compare the value and current node */
    if(cpt_avl_tree->_pfun_cmp != NULL)
    {
        n_cmpresult = 
            (*cpt_avl_tree->_pfun_cmp)(cpv_value, pt_root->_pc_data);
    }
    else
    {
        n_cmpresult = 
            memcmp(cpv_value, pt_root->_pc_data, cpt_avl_tree->_t_typesize);
    }

    /* if value < current node then insert into left subtree */
    if(n_cmpresult < 0)
    {
        t_insert_result = 
            _insert_avlnode(cpt_avl_tree, pt_root->_pt_left, cpv_value);
        pt_root->_pt_left = t_insert_result._pt_adjust;
        pt_root->_pt_left->_pt_parent = pt_root;

        pt_root = _rebalance_avl_tree(pt_root);
        t_insert_result._pt_adjust = pt_root;

        return t_insert_result;
    }
    /* else insert into right subtree */
    else
    {
        t_insert_result = 
            _insert_avlnode(cpt_avl_tree, pt_root->_pt_right, cpv_value);
        pt_root->_pt_right =  t_insert_result._pt_adjust;
        pt_root->_pt_right->_pt_parent = pt_root;

        pt_root = _rebalance_avl_tree(pt_root);
        t_insert_result._pt_adjust = pt_root;

        return t_insert_result;
    }
}

static avlnode_t* _rebalance_avl_tree(avlnode_t* pt_root)
{
    if(pt_root != NULL)
    {
        /* if left - right > 1 */
        if(_get_height(pt_root->_pt_left) - 
           _get_height(pt_root->_pt_right) > 1)
        {
            /* ll */
            if(_get_height(pt_root->_pt_left->_pt_left) >=
               _get_height(pt_root->_pt_left->_pt_right))
            {
                pt_root = _left_signal_rotate(pt_root);
            }
            /* lr */
            else
            {
                pt_root = _left_double_rotate(pt_root);
            }
        }
        /* else if right - left > 1 */
        else if(_get_height(pt_root->_pt_right) - 
                _get_height(pt_root->_pt_left) > 1)
        {
            /* rr */
            if(_get_height(pt_root->_pt_right->_pt_right) >= 
               _get_height(pt_root->_pt_right->_pt_left))
            {
                pt_root = _right_signal_rotate(pt_root);
            }
            /* rl */
            else
            {
                pt_root = _right_double_rotate(pt_root);
            }
        }

        pt_root->_un_height = (unsigned int)(
            (_get_height(pt_root->_pt_left) > 
             _get_height(pt_root->_pt_right) ?
             _get_height(pt_root->_pt_left) : 
             _get_height(pt_root->_pt_right)) + 1);
    }

    return pt_root;
}

/** eof **/

