/*
 * =============================================================================
 *  Copyright (c) 2008 2009 ActiveSys.Wangbo
 *
 *  copyright description ...
 *
 *  Project:    cstl
 *  Module:     hashtable
 *  Filename:   cstl_hashtable.c
 *
 *  The implementation of hashtable.
 *
 *  2009-01-12 15:33:47
 * =============================================================================
 */

/** include section **/
#include <assert.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "cstl_types.h"
#include "cstl_alloc.h"
#include "cstl_iterator.h"

#include "cstl_vector_iterator.h"
#include "cstl_vector_private.h"
#include "cstl_vector.h"

#include "cstl_hashtable_iterator.h"
#include "cstl_hashtable_private.h"

/** local constant declaration and local macro section **/
#define _HASHTABLE_NODE_SIZE(typesize)\
    ((typesize) + sizeof(hashnode_t) - 1)

#define _HASHTABLE_NODE_NAME            "hashnode_t"
#define _HASHTABLE_DEFAULT_BUCKET_COUNT 50
#define _HASHTABLE_PRIME_LIST_COUNT     28

/** local data type declaration and local struct, union, enum section **/

/** local function prototype section **/
#ifndef NDEBUG
/*
 *  Functionname: _iterator_belong_to_hashtable
 *    Parameters: in) cpt_hashtable: const hashtable_t*
 *                    hashtable pointer.
 *                in) cpt_iterator: const hashtable_iterator_t*
 *                    hashtable iterator pointer.
 *       Returns: bool_t
 *   Description: test the iterator is valid one belong to the hashtable.
 */
static bool_t _iterator_belong_to_hashtable(
    const hashtable_t* cpt_hashtable, 
    const hashtable_iterator_t* cpt_iterator);

/*
 *  Functionname: _same_hashtable_type
 *    Parameters: in) cpt_hashtablefirst: const hashtable_t*
 *                    first hashtable pointer.
 *                in) cpt_hashtablesecond: const hashtable_t*
 *                    second hashtable pointer.
 *       Returns: bool_t
 *   Description: test the two hashtable is have the same type.
 */
static bool_t _same_hashtable_type(
    const hashtable_t* cpt_hashtablefirst, 
    const hashtable_t* cpt_hashtablesecond);

/*
 *  Functionname: _same_hashtable_iterator_type
 *    Parameters: in) cpt_hashtable: const hashtable_t*
 *                    the hashtable pointer
 *                in) cpt_iterator: const hashtable_iterator_t*
 *                    the hashtable iterator pointer
 *       Returns: bool_t
 *   Description: test the hashtable and iterator have the same type.
 */
static bool_t _same_hashtable_iterator_type(
    const hashtable_t* cpt_hashtable, const hashtable_iterator_t* cpt_iterator);

/*
 *  Functionname: _iterator_for_one_and_the_same_hashtable
 *    Parameters: in) cpt_iteratorfirst: const hashtable_iterator_t*
 *                    first hashtable iterator pointer.
 *                in) cpt_iteratorsecond: const hashtable_iterator_t*
 *                    second hashtable iterator pointer.
 *       Returns: bool_t
 *   Description: test the two hashtable iterator is one and the same of hashtable.
 */
static bool_t _iterator_for_one_and_the_same_hashtable(
    const hashtable_iterator_t* cpt_iteratorfirst, 
    const hashtable_iterator_t* cpt_iteratorsecond);
#endif /* NDEBUG */

/*
 *  Functionname: _hash_function_family
 *    Parameters: in) cpv_value: const void*
 *                    the element pointer.
 *                in) t_typesize: size_t
 *                    the element size.
 *                in) t_bucketcount: size_t
 *                    the bucket count.
 *       Returns: int
 *                    bucket index.
 *   Description: The default hash function.
 */
static int _hash_function_for_int(
    const void* cpv_value, size_t t_typesize, size_t t_bucketcount);
static int _hash_function_for_unsigned_int(
    const void* cpv_value, size_t t_typesize, size_t t_bucketcount);
static int _hash_function_for_short(
    const void* cpv_value, size_t t_typesize, size_t t_bucketcount);
static int _hash_function_for_unsigned_short(
    const void* cpv_value, size_t t_typesize, size_t t_bucketcount);
static int _hash_function_for_long(
    const void* cpv_value, size_t t_typesize, size_t t_bucketcount);
static int _hash_function_for_unsigned_long(
    const void* cpv_value, size_t t_typesize, size_t t_bucketcount);
static int _hash_function_for_double(
    const void* cpv_value, size_t t_typesize, size_t t_bucketcount);
static int _hash_function_for_float(
    const void* cpv_value, size_t t_typesize, size_t t_bucketcount);
static int _hash_function_for_other(
    const void* cpv_value, size_t t_typesize, size_t t_bucketcount);

/*
 *  Functionname: _get_next_prime
 *    Parameters: in) ul_basenum: unsigned long
 *                    the base number.
 *       Returns: unsigned long
 *                    the next prime.
 *   Description: get the next prime base the ul_basenum.
 */
static unsigned long _get_next_prime(unsigned long ul_basenum);

/** exported global variable definition section **/

/** local global variable definition section **/
static const unsigned long _hashtable_prime_list[_HASHTABLE_PRIME_LIST_COUNT] =
{
    53,         97,           193,         389,       769,
    1543,       3079,         6151,        12289,     24593,
    49157,      98317,        196613,      393241,    786433,
    1572869,    3145739,      6291469,     12582917,  25165843,
    50331653,   100663319,    201326611,   402653189, 805306457,
    1610612741, 3221225473ul, 4294967291ul
};

/** exported function implementation section **/
/* hashtable iterator function */
hashtable_iterator_t _create_hashtable_iterator(void)
{
    hashtable_iterator_t t_newiterator;

    _GET_HASHTABLE_BUCKETPOS(&t_newiterator) = NULL;
    _GET_HASHTABLE_COREPOS(&t_newiterator) = NULL;
    _GET_HASHTABLE_POINTER(&t_newiterator) = NULL;

    _GET_CONTAINER(&t_newiterator) = NULL;

    return t_newiterator;
}

bool_t _hashtable_iterator_equal(
    const struct _taghashtable* cpt_hashtable, 
    const hashtable_iterator_t* cpt_iterator, 
    hashtable_iterator_t t_iterator)
{
#ifdef NDEBUG
    hashtable_t* pt_avoidwarning = NULL;
    pt_avoidwarning = (hashtable_t*)cpt_hashtable;
#endif
    assert(_iterator_belong_to_hashtable(cpt_hashtable, cpt_iterator));
    assert(_iterator_belong_to_hashtable(cpt_hashtable, &t_iterator));

    if(_GET_HASHTABLE_BUCKETPOS(cpt_iterator) == 
        _GET_HASHTABLE_BUCKETPOS(&t_iterator) &&
       _GET_HASHTABLE_COREPOS(cpt_iterator) == 
        _GET_HASHTABLE_COREPOS(&t_iterator))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void _hashtable_iterator_get_value(
    const struct _taghashtable* cpt_hashtable,
    const hashtable_iterator_t* cpt_iterator,
    void* pv_value)
{
    assert(pv_value != NULL);
    assert(_iterator_belong_to_hashtable(cpt_hashtable, cpt_iterator));
    assert(
        !_hashtable_iterator_equal(
            cpt_hashtable, cpt_iterator, _hashtable_end(cpt_hashtable)));

    memcpy(
        pv_value,
        ((hashnode_t*)_GET_HASHTABLE_COREPOS(cpt_iterator))->_pc_data,
        cpt_hashtable->_t_typesize);
}

const void* _hashtable_iterator_get_pointer(
    const struct _taghashtable* cpt_hashtable,
    const hashtable_iterator_t* cpt_iterator)
{
#ifdef NDEBUG
    hashtable_t* pt_avoidwarning = NULL;
    pt_avoidwarning = (hashtable_t*)cpt_hashtable;
#endif

    assert(_iterator_belong_to_hashtable(cpt_hashtable, cpt_iterator));
    assert(
        !_hashtable_iterator_equal(
            cpt_hashtable, cpt_iterator, _hashtable_end(cpt_hashtable)));

    return ((hashnode_t*)_GET_HASHTABLE_COREPOS(cpt_iterator))->_pc_data;
}

void _hashtable_iterator_next(
    const struct _taghashtable* cpt_hashtable, 
    hashtable_iterator_t* cpt_iterator)
{
    vector_iterator_t t_vectoriterator;
    hashnode_t*       pt_node = NULL;

    assert(_iterator_belong_to_hashtable(cpt_hashtable, cpt_iterator));
    assert(
        !_hashtable_iterator_equal(
            cpt_hashtable, cpt_iterator, _hashtable_end(cpt_hashtable)));

    pt_node = (hashnode_t*)_GET_HASHTABLE_COREPOS(cpt_iterator);
    assert(pt_node != NULL);

    if(pt_node->_pt_next == NULL)
    {
        /* iterator from current bucket pos to end */
        t_vectoriterator = vector_begin(&cpt_hashtable->_t_bucket);
        _GET_VECTOR_COREPOS(&t_vectoriterator) = 
            _GET_HASHTABLE_BUCKETPOS(cpt_iterator);
        for(iterator_next(&t_vectoriterator);
            !iterator_equal(
                &t_vectoriterator, vector_end(&cpt_hashtable->_t_bucket));
            iterator_next(&t_vectoriterator))
        {
            _GET_HASHTABLE_BUCKETPOS(cpt_iterator) = 
                _GET_VECTOR_COREPOS(&t_vectoriterator);
            if(*(hashnode_t**)_GET_HASHTABLE_BUCKETPOS(cpt_iterator) != NULL)
            {
                _GET_HASHTABLE_COREPOS(cpt_iterator) = 
                    (char*)(*(hashnode_t**)_GET_HASHTABLE_BUCKETPOS(cpt_iterator));
                break;
            }
        }
        if(iterator_equal(
            &t_vectoriterator, vector_end(&cpt_hashtable->_t_bucket)))
        {
            assert((hashnode_t*)_GET_HASHTABLE_COREPOS(cpt_iterator) == pt_node);
            _GET_HASHTABLE_COREPOS(cpt_iterator) = NULL;
            _GET_HASHTABLE_BUCKETPOS(cpt_iterator) = 
                _GET_VECTOR_COREPOS(&t_vectoriterator);
        }
    }
    else
    {
        _GET_HASHTABLE_COREPOS(cpt_iterator) = (char*)pt_node->_pt_next;
    }
}

int _hashtable_iterator_distance(
    const hashtable_iterator_t* cpt_begin, const hashtable_iterator_t* cpt_end)
{
    hashtable_iterator_t t_iterator;
    hashtable_t*         pt_hashtable = NULL;
    int                  n_distance = 0;

    if(_hashtable_iterator_before(cpt_begin, cpt_end))
    {
        pt_hashtable = _GET_HASHTABLE(cpt_begin);
        for(t_iterator = *cpt_begin;
            !_hashtable_iterator_equal(pt_hashtable, &t_iterator, *cpt_end);
            _hashtable_iterator_next(pt_hashtable, &t_iterator))
        {
            n_distance++;
        }
        return n_distance;
    }
    else if(_hashtable_iterator_before(cpt_end, cpt_begin))
    {
        pt_hashtable = _GET_HASHTABLE(cpt_end);
        for(t_iterator = *cpt_end;
            !_hashtable_iterator_equal(pt_hashtable, &t_iterator, *cpt_begin);
            _hashtable_iterator_next(pt_hashtable, &t_iterator))
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

bool_t _hashtable_iterator_before(
    const hashtable_iterator_t* cpt_iteratorfirst,
    const hashtable_iterator_t* cpt_iteratorsecond)
{
    hashtable_iterator_t t_iterator;
    hashtable_t*         pt_hashtable = NULL;

    assert(_iterator_for_one_and_the_same_hashtable(
        cpt_iteratorfirst, cpt_iteratorsecond));
    assert(
        _iterator_belong_to_hashtable(
            _GET_HASHTABLE(cpt_iteratorfirst), cpt_iteratorfirst) &&
        _iterator_belong_to_hashtable(
            _GET_HASHTABLE(cpt_iteratorsecond), cpt_iteratorsecond));
    assert(
        _GET_HASHTABLE(cpt_iteratorfirst) != NULL &&
        _GET_HASHTABLE(cpt_iteratorsecond) != NULL);
    assert(
        _GET_HASHTABLE_BUCKETPOS(cpt_iteratorfirst) != NULL &&
        _GET_HASHTABLE_BUCKETPOS(cpt_iteratorsecond) != NULL);

    if(_GET_HASHTABLE_COREPOS(cpt_iteratorfirst) ==
       _GET_HASHTABLE_COREPOS(cpt_iteratorsecond))
    {
        return false;
    }

    pt_hashtable = _GET_HASHTABLE(cpt_iteratorfirst);
    for(t_iterator = *cpt_iteratorfirst;
        !_hashtable_iterator_equal(
            pt_hashtable, &t_iterator, _hashtable_end(pt_hashtable));
        _hashtable_iterator_next(pt_hashtable, &t_iterator))
    {
        if(_hashtable_iterator_equal(
            pt_hashtable, &t_iterator, *cpt_iteratorsecond))
        {
            return true;
        }
    }

    if(_hashtable_iterator_equal(
        pt_hashtable, cpt_iteratorsecond, _hashtable_end(pt_hashtable)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void _hashtable_resize(hashtable_t* pt_hashtable, size_t t_resize)
{
    int          n_hashindex = 0;
    size_t       t_index = 0;
    size_t       t_bucketcount = 0;
    hashnode_t*  pt_node = NULL;
    hashnode_t*  pt_nodelist = NULL;
    hashnode_t** ppt_bucket = NULL;

    assert(pt_hashtable != NULL);

    if(t_resize > _hashtable_bucket_count(pt_hashtable))
    {
        /* select all element in hash node list */
        for(t_index = 0; 
            t_index < vector_size(&pt_hashtable->_t_bucket);
            ++t_index)
        {
            ppt_bucket = (hashnode_t**)vector_at(
                &pt_hashtable->_t_bucket, t_index);
            pt_node = *ppt_bucket;
            while(pt_node != NULL)
            {
                *ppt_bucket = pt_node->_pt_next;
                pt_node->_pt_next = pt_nodelist;
                pt_nodelist = pt_node;
                pt_node = *ppt_bucket;
            }
        }

        /* resize vector bucket */
        vector_resize(&pt_hashtable->_t_bucket, _get_next_prime(t_resize));
        t_bucketcount = _hashtable_bucket_count(pt_hashtable);

        /* rehash */
        while(pt_nodelist != NULL)
        {
            pt_node = pt_nodelist;
            pt_nodelist = pt_node->_pt_next;

            n_hashindex = (*pt_hashtable->_pfun_hash)(
                pt_node->_pc_data, pt_hashtable->_t_typesize, t_bucketcount);
            assert(n_hashindex >= 0 && (size_t)n_hashindex < t_bucketcount);
            ppt_bucket = (hashnode_t**)vector_at(
                &pt_hashtable->_t_bucket, n_hashindex);
            pt_node->_pt_next = *ppt_bucket;
            *ppt_bucket = pt_node;
        }
    }
}

hashtable_iterator_t _hashtable_insert_equal(
    hashtable_t* pt_hashtable, const void* cpv_value)
{
    int                  n_hashindex = 0;
    size_t               t_bucketcount = 0;
    hashnode_t*          pt_node = NULL;
    hashnode_t*          pt_cur = NULL;
    hashnode_t**         ppt_nodelist = NULL;
    hashtable_iterator_t t_iterator = _create_hashtable_iterator();

    assert(pt_hashtable != NULL && cpv_value != NULL);

    /* resize */
    _hashtable_resize(pt_hashtable, _hashtable_size(pt_hashtable)+1);

    /* allocate node */
    pt_node = allocate(
        &pt_hashtable->_t_allocater, 
        _HASHTABLE_NODE_SIZE(pt_hashtable->_t_typesize), 
        1);
    assert(pt_node != NULL);
    memcpy(pt_node->_pc_data, cpv_value, pt_hashtable->_t_typesize);

    /* hash */
    t_bucketcount = _hashtable_bucket_count(pt_hashtable);
    n_hashindex = (*pt_hashtable->_pfun_hash)(
        pt_node->_pc_data, pt_hashtable->_t_typesize, t_bucketcount);
    assert(n_hashindex >= 0 && (size_t)n_hashindex < t_bucketcount);

    /* insert node into hashtable, note the node has same value together */
    ppt_nodelist = 
        (hashnode_t**)vector_at(&pt_hashtable->_t_bucket, n_hashindex);
    assert(ppt_nodelist != NULL);
    pt_cur = *ppt_nodelist;
    if(pt_hashtable->_pfun_cmp != NULL)
    {
        if(pt_cur == NULL ||
           (*pt_hashtable->_pfun_cmp)(
               pt_cur->_pc_data, pt_node->_pc_data) == 0)
        {
            pt_node->_pt_next = pt_cur;
            *ppt_nodelist = pt_node;
        }
        else
        {
            while(pt_cur->_pt_next != NULL && 
                  (*pt_hashtable->_pfun_cmp)(
                      pt_cur->_pt_next->_pc_data, pt_node->_pc_data) != 0)
            {
                pt_cur = pt_cur->_pt_next;
            }
            pt_node->_pt_next = pt_cur->_pt_next;
            pt_cur->_pt_next = pt_node;
        }
    }
    else
    {
        if(pt_cur == NULL ||
           memcmp(
               pt_cur->_pc_data, 
               pt_node->_pc_data, 
               pt_hashtable->_t_typesize) == 0)
        {
            pt_node->_pt_next = pt_cur;
            *ppt_nodelist = pt_node;
        }
        else
        {
            while(pt_cur->_pt_next != NULL && 
                  memcmp(
                      pt_cur->_pt_next->_pc_data, 
                      pt_node->_pc_data,
                      pt_hashtable->_t_typesize) != 0)
            {
                pt_cur = pt_cur->_pt_next;
            }
            pt_node->_pt_next = pt_cur->_pt_next;
            pt_cur->_pt_next = pt_node;
        }
    }
    pt_hashtable->_t_nodecount++;

    _GET_HASHTABLE_BUCKETPOS(&t_iterator) = (char*)ppt_nodelist;
    _GET_HASHTABLE_COREPOS(&t_iterator) = (char*)pt_node;
    _GET_HASHTABLE_POINTER(&t_iterator) = pt_hashtable;

    return t_iterator;
}

hashtable_result_pair_t _hashtable_insert_unique(
    hashtable_t* pt_hashtable, const void* cpv_value)
{
    hashtable_result_pair_t t_result;

    if(_hashtable_empty(pt_hashtable))
    {
        t_result._t_first = _hashtable_insert_equal(pt_hashtable, cpv_value);
        t_result._t_second._t_bool = true;
    }
    else
    {
        t_result._t_first = _hashtable_find(pt_hashtable, cpv_value);
        if(!_hashtable_iterator_equal(
            pt_hashtable, &t_result._t_first, _hashtable_end(pt_hashtable)))
        {
            t_result._t_second._t_bool = false;
        }
        else
        {
            t_result._t_first = _hashtable_insert_equal(pt_hashtable, cpv_value);
            t_result._t_second._t_bool = true;
        }
    }

    return t_result;
}

hashtable_iterator_t _hashtable_find(
    const hashtable_t* cpt_hashtable, const void* cpv_value)
{
    hashtable_iterator_t t_iterator = _create_hashtable_iterator();
    int                  n_hashindex = 0;
    size_t               t_bucketcount = 0;
    hashnode_t*          pt_node = NULL;
    hashnode_t**         ppt_bucket = NULL;

    assert(cpt_hashtable != NULL && cpv_value != NULL);

    t_bucketcount = _hashtable_bucket_count(cpt_hashtable);
    n_hashindex = (*cpt_hashtable->_pfun_hash)(
        cpv_value, cpt_hashtable->_t_typesize, t_bucketcount);
    assert(n_hashindex >= 0 && (size_t)n_hashindex < t_bucketcount);
    ppt_bucket = (hashnode_t**)vector_at(&cpt_hashtable->_t_bucket, n_hashindex);
    pt_node = *ppt_bucket;

    if(cpt_hashtable->_pfun_cmp != NULL)
    {
        while(pt_node != NULL)
        {
            if((*cpt_hashtable->_pfun_cmp)(pt_node->_pc_data, cpv_value) == 0)
            {
                break;
            }
            else
            {
                pt_node = pt_node->_pt_next;
            }
        }
    }
    else
    {
        while(pt_node != NULL)
        {
            if(memcmp(
                pt_node->_pc_data, cpv_value, cpt_hashtable->_t_typesize) == 0)
            {
                break;
            }
            else
            {
                pt_node = pt_node->_pt_next;
            }
        }
    }

    if(pt_node == NULL)
    {
        return _hashtable_end(cpt_hashtable);
    }
    else
    {
        _GET_HASHTABLE_BUCKETPOS(&t_iterator) = (char*)ppt_bucket;
        _GET_HASHTABLE_COREPOS(&t_iterator) = (char*)pt_node;
        _GET_HASHTABLE_POINTER(&t_iterator) = (hashtable_t*)cpt_hashtable;

        return t_iterator;
    }
}

hashtable_result_pair_t _hashtable_equal_range(
    const hashtable_t* cpt_hashtable, const void* cpv_value)
{
    hashtable_result_pair_t t_result;
    int                     i = 0;
    int                     n_hashindex = 0;
    size_t                  t_bucketcount = 0;
    hashnode_t*             pt_begin = NULL;
    hashnode_t*             pt_end = NULL;
    hashnode_t**            ppt_bucket = NULL;

    assert(cpt_hashtable != NULL && cpv_value != NULL);

    t_result._t_first = _create_hashtable_iterator();
    t_result._t_second._t_iterator = _create_hashtable_iterator();

    t_bucketcount = _hashtable_bucket_count(cpt_hashtable);
    n_hashindex = (*cpt_hashtable->_pfun_hash)(
        cpv_value, cpt_hashtable->_t_typesize, t_bucketcount);
    assert(n_hashindex >= 0 && (size_t)n_hashindex < t_bucketcount);
    ppt_bucket = (hashnode_t**)vector_at(&cpt_hashtable->_t_bucket, n_hashindex);

    if(cpt_hashtable->_pfun_cmp != NULL)
    {
        for(pt_begin = *ppt_bucket; 
            pt_begin != NULL; 
            pt_begin = pt_begin->_pt_next)
        {
            if((*cpt_hashtable->_pfun_cmp)(pt_begin->_pc_data, cpv_value) == 0)
            {
                for(pt_end = pt_begin->_pt_next;
                    pt_end != NULL;
                    pt_end = pt_end->_pt_next)
                {
                    if((*cpt_hashtable->_pfun_cmp)(
                        pt_end->_pc_data, cpv_value) != 0)
                    {
                        _GET_HASHTABLE_BUCKETPOS(&t_result._t_first) = 
                            (char*)ppt_bucket;
                        _GET_HASHTABLE_COREPOS(&t_result._t_first) = 
                            (char*)pt_begin;
                        _GET_HASHTABLE_POINTER(&t_result._t_first) =
                            (hashnode_t*)cpt_hashtable;

                        _GET_HASHTABLE_BUCKETPOS(&t_result._t_second._t_iterator) =
                            (char*)ppt_bucket;
                        _GET_HASHTABLE_COREPOS(&t_result._t_second._t_iterator) =
                            (char*)pt_end;
                        _GET_HASHTABLE_POINTER(&t_result._t_second._t_iterator) =
                            (hashtable_t*)cpt_hashtable;

                        return t_result;
                    }
                }
                
                _GET_HASHTABLE_BUCKETPOS(&t_result._t_first) = 
                    (char*)ppt_bucket;
                _GET_HASHTABLE_COREPOS(&t_result._t_first) = 
                    (char*)pt_begin;
                _GET_HASHTABLE_POINTER(&t_result._t_first) = 
                    (hashtable_t*)cpt_hashtable;

                for(i = n_hashindex+1; (size_t)i < t_bucketcount; ++i)
                {
                    ppt_bucket = 
                        (hashnode_t**)vector_at(&cpt_hashtable->_t_bucket, i);
                    pt_end = *ppt_bucket;
                    if(pt_end != NULL)
                    {
                        _GET_HASHTABLE_BUCKETPOS(&t_result._t_second._t_iterator) =
                            (char*)ppt_bucket;
                        _GET_HASHTABLE_COREPOS(&t_result._t_second._t_iterator) =
                            (char*)pt_end;
                        _GET_HASHTABLE_POINTER(&t_result._t_second._t_iterator) =
                            (hashtable_t*)cpt_hashtable;

                        return t_result;
                    }
                }

                t_result._t_second._t_iterator = _hashtable_end(cpt_hashtable);

                return t_result;
            }
        }

        t_result._t_first = _hashtable_end(cpt_hashtable);
        t_result._t_second._t_iterator = _hashtable_end(cpt_hashtable);

        return t_result;
    }
    else
    {
        for(pt_begin = *ppt_bucket; 
            pt_begin != NULL; 
            pt_begin = pt_begin->_pt_next)
        {
            if(memcmp(
                pt_begin->_pc_data, 
                cpv_value, 
                cpt_hashtable->_t_typesize) == 0)
            {
                for(pt_end = pt_begin->_pt_next;
                    pt_end != NULL;
                    pt_end = pt_end->_pt_next)
                {
                    if(memcmp(
                        pt_end->_pc_data, 
                        cpv_value,
                        cpt_hashtable->_t_typesize) != 0)
                    {
                        _GET_HASHTABLE_BUCKETPOS(&t_result._t_first) = 
                            (char*)ppt_bucket;
                        _GET_HASHTABLE_COREPOS(&t_result._t_first) = 
                            (char*)pt_begin;
                        _GET_HASHTABLE_POINTER(&t_result._t_first) =
                            (hashnode_t*)cpt_hashtable;

                        _GET_HASHTABLE_BUCKETPOS(&t_result._t_second._t_iterator) =
                            (char*)ppt_bucket;
                        _GET_HASHTABLE_COREPOS(&t_result._t_second._t_iterator) =
                            (char*)pt_end;
                        _GET_HASHTABLE_POINTER(&t_result._t_second._t_iterator) =
                            (hashtable_t*)cpt_hashtable;

                        return t_result;
                    }
                }
                
                _GET_HASHTABLE_BUCKETPOS(&t_result._t_first) = 
                    (char*)ppt_bucket;
                _GET_HASHTABLE_COREPOS(&t_result._t_first) = 
                    (char*)pt_begin;
                _GET_HASHTABLE_POINTER(&t_result._t_first) = 
                    (hashtable_t*)cpt_hashtable;

                for(i = n_hashindex+1; (size_t)i < t_bucketcount; ++i)
                {
                    ppt_bucket = 
                        (hashnode_t**)vector_at(&cpt_hashtable->_t_bucket, i);
                    pt_end = *ppt_bucket;
                    if(pt_end != NULL)
                    {
                        _GET_HASHTABLE_BUCKETPOS(&t_result._t_second._t_iterator) =
                            (char*)ppt_bucket;
                        _GET_HASHTABLE_COREPOS(&t_result._t_second._t_iterator) =
                            (char*)pt_end;
                        _GET_HASHTABLE_POINTER(&t_result._t_second._t_iterator) =
                            (hashtable_t*)cpt_hashtable;

                        return t_result;
                    }
                }

                t_result._t_second._t_iterator = _hashtable_end(cpt_hashtable);

                return t_result;
            }
        }

        t_result._t_first = _hashtable_end(cpt_hashtable);
        t_result._t_second._t_iterator = _hashtable_end(cpt_hashtable);

        return t_result;
    }
}

size_t _hashtable_count(
    const hashtable_t* cpt_hashtable, const void* cpv_value)
{
    hashtable_result_pair_t t_result = 
        _hashtable_equal_range(cpt_hashtable, cpv_value);

    return abs(_hashtable_iterator_distance(
         &t_result._t_first, &t_result._t_second._t_iterator));
}

void _hashtable_erase_pos(
    hashtable_t* pt_hashtable, hashtable_iterator_t t_pos)
{
    hashnode_t** ppt_bucket = NULL;
    hashnode_t*  pt_node = NULL;
    hashnode_t*  pt_deletion = NULL;

    assert(_iterator_belong_to_hashtable(pt_hashtable, &t_pos));
    assert(
        !_hashtable_iterator_equal(
            pt_hashtable, &t_pos, _hashtable_end(pt_hashtable)));

    /* get the previous node */
    ppt_bucket = (hashnode_t**)_GET_HASHTABLE_BUCKETPOS(&t_pos);
    pt_node = *ppt_bucket;
    pt_deletion = (hashnode_t*)_GET_HASHTABLE_COREPOS(&t_pos);
    if(pt_node == pt_deletion)
    {
        /* the deletion node is the first node of node list */
        *ppt_bucket = pt_node->_pt_next;
    }
    else
    {
        while(pt_node->_pt_next != NULL)
        {
            if(pt_node->_pt_next == pt_deletion)
            {
                pt_node->_pt_next = pt_deletion->_pt_next;
                break;
            }
            else
            {
                pt_node = pt_node->_pt_next;
            }
        }
    }
    /* delete the node */
    if(pt_hashtable->_pfun_destroy_elem != NULL)
    {
        (*pt_hashtable->_pfun_destroy_elem)(pt_deletion->_pc_data);
    }
    deallocate(
        &pt_hashtable->_t_allocater, pt_deletion,
        _HASHTABLE_NODE_SIZE(pt_hashtable->_t_typesize), 1);
    /* update the hashtable size */
    pt_hashtable->_t_nodecount--;
}

void _hashtable_erase_range(
    hashtable_t* pt_hashtable, 
    hashtable_iterator_t t_begin,
    hashtable_iterator_t t_end)
{
    hashtable_iterator_t t_iterator;
    hashtable_iterator_t t_next;

    assert(_iterator_belong_to_hashtable(pt_hashtable, &t_begin));
    assert(
        _hashtable_iterator_equal(_GET_HASHTABLE(&t_begin), &t_begin, t_end) ||
        _hashtable_iterator_before(&t_begin, &t_end));

    t_iterator = t_next = t_begin;
    if(!_hashtable_iterator_equal(
        pt_hashtable, &t_next, _hashtable_end(pt_hashtable)))
    {
        _hashtable_iterator_next(pt_hashtable, &t_next);
    }
    while(!_hashtable_iterator_equal(pt_hashtable, &t_iterator, t_end))
    {
        _hashtable_erase_pos(pt_hashtable, t_iterator);

        t_iterator = t_next;
        if(!_hashtable_iterator_equal(
            pt_hashtable, &t_next, _hashtable_end(pt_hashtable)))
        {
            _hashtable_iterator_next(pt_hashtable, &t_next);
        }
    }
}

size_t _hashtable_erase(hashtable_t* pt_hashtable, const void* cpv_value)
{
    size_t t_countsize = _hashtable_count(pt_hashtable, cpv_value);
    hashtable_result_pair_t t_result = 
        _hashtable_equal_range(pt_hashtable, cpv_value);

    if(!_hashtable_iterator_equal(
        pt_hashtable, &t_result._t_first, _hashtable_end(pt_hashtable)))
    {
        _hashtable_erase_range(
            pt_hashtable, t_result._t_first, t_result._t_second._t_iterator);
    }

    return t_countsize;
}

void _hashtable_swap(
    hashtable_t* pt_hashtablefirst, hashtable_t* pt_hashtablesecond)
{
    hashtable_t t_hashtableswap;

    assert(_same_hashtable_type(pt_hashtablefirst, pt_hashtablesecond));

    t_hashtableswap = *pt_hashtablefirst;
    *pt_hashtablefirst = *pt_hashtablesecond;
    *pt_hashtablesecond = t_hashtableswap;
}

/* hashtable private function */
hashtable_t _create_hashtable(size_t t_typesize, const char* s_typename)
{
    hashtable_t t_newhashtable;

    assert(t_typesize > 0 && s_typename != NULL);

    /* initialize type size and name */
    t_newhashtable._t_typesize = t_typesize;
    memset(t_newhashtable._sz_typename, '\0', _ELEM_TYPE_NAME_SIZE+1);
    strncpy(t_newhashtable._sz_typename, s_typename, _ELEM_TYPE_NAME_SIZE);
    _unify_types(t_newhashtable._t_typesize, t_newhashtable._sz_typename);

    /* create new vector */
    t_newhashtable._t_bucket = _create_vector(
        sizeof(hashnode_t*), _HASHTABLE_NODE_NAME);

    t_newhashtable._pfun_hash = NULL;
    t_newhashtable._pfun_cmp = NULL;
    t_newhashtable._pfun_destroy_elem = NULL;

    return t_newhashtable;
}

void _hashtable_init(
    hashtable_t* pt_hashtable, 
    size_t t_bucketcount,
    int (*pfun_hash)(const void*, size_t, size_t),
    int (*pfun_cmp)(const void*, const void*),
    void (*pfun_destroy_elem)(void*))
{
    assert(
        pt_hashtable != NULL &&
        pt_hashtable->_pfun_hash == NULL &&
        pt_hashtable->_pfun_cmp == NULL &&
        pt_hashtable->_pfun_destroy_elem == NULL);

    /* initialize the allocator */
    allocate_init(&pt_hashtable->_t_allocater);

    /* initialize the bucket vector and node count */
    vector_init(&pt_hashtable->_t_bucket);
    if(t_bucketcount > 0)
    {
        vector_resize(&pt_hashtable->_t_bucket, _get_next_prime(t_bucketcount));
    }
    else
    {
        vector_resize(
            &pt_hashtable->_t_bucket, 
            _get_next_prime(_HASHTABLE_DEFAULT_BUCKET_COUNT));
    }
    pt_hashtable->_t_nodecount = 0;

    /* initialize the hash, compare and destroy element function */
    if(pfun_hash != NULL)
    {
        pt_hashtable->_pfun_hash = pfun_hash;
    }
    else
    {
        /* hash function for int */
        if(strncmp(
            pt_hashtable->_sz_typename, 
            _INT_TYPE, 
            _ELEM_TYPE_NAME_SIZE) == 0)
        {
            pt_hashtable->_pfun_hash = _hash_function_for_int;
        }
        /* hash function for unsigned int */
        else if(strncmp(
            pt_hashtable->_sz_typename,
            _UNSIGNED_INT_TYPE,
            _ELEM_TYPE_NAME_SIZE) == 0)
        {
            pt_hashtable->_pfun_hash = _hash_function_for_unsigned_int;
        }
        /* hash function for short */
        else if(strncmp(
            pt_hashtable->_sz_typename,
            _SHORT_TYPE,
            _ELEM_TYPE_NAME_SIZE) == 0)
        {
            pt_hashtable->_pfun_hash = _hash_function_for_short;
        }
        /* hash function for unsigned short */
        else if(strncmp(
            pt_hashtable->_sz_typename,
            _UNSIGNED_SHORT_TYPE,
            _ELEM_TYPE_NAME_SIZE) == 0)
        {
            pt_hashtable->_pfun_hash = _hash_function_for_unsigned_short;
        }
        /* hash function for long */
        else if(strncmp(
            pt_hashtable->_sz_typename,
            _LONG_TYPE,
            _ELEM_TYPE_NAME_SIZE) == 0)
        {
            pt_hashtable->_pfun_hash = _hash_function_for_long;
        }
        /* hash function for unsigned long */
        else if(strncmp(
            pt_hashtable->_sz_typename,
            _UNSIGNED_LONG_TYPE,
            _ELEM_TYPE_NAME_SIZE) == 0)
        {
            pt_hashtable->_pfun_hash = _hash_function_for_unsigned_long;
        }
        /* hash function for double */
        else if(strncmp(
            pt_hashtable->_sz_typename,
            _DOUBLE_TYPE,
            _ELEM_TYPE_NAME_SIZE) == 0)
        {
            pt_hashtable->_pfun_hash = _hash_function_for_double;
        }
        /* hash function for float */
        else if(strncmp(
            pt_hashtable->_sz_typename,
            _FLOAT_TYPE,
            _ELEM_TYPE_NAME_SIZE) == 0)
        {
            pt_hashtable->_pfun_hash = _hash_function_for_float;
        }
        else
        {
            pt_hashtable->_pfun_hash = _hash_function_for_other;
        }
    }
    if(pfun_cmp != NULL)
    {
        pt_hashtable->_pfun_cmp = pfun_cmp;
    }
    else
    {
        pt_hashtable->_pfun_cmp = _get_cmp_function(pt_hashtable->_sz_typename);
    }
    pt_hashtable->_pfun_destroy_elem = pfun_destroy_elem;
}

void _hashtable_destroy(hashtable_t* pt_hashtable)
{
    assert(pt_hashtable != NULL);

    /* destroy all elements */
    _hashtable_clear(pt_hashtable);

    /* destroy bucket vector */
    vector_destroy(&pt_hashtable->_t_bucket);

    /* destroy allocator */
    allocate_destroy(&pt_hashtable->_t_allocater);

    /* destroy hash, compare and destroy element function */
    pt_hashtable->_pfun_cmp = NULL;
    pt_hashtable->_pfun_destroy_elem = NULL;
    pt_hashtable->_pfun_hash = NULL;
}

void _hashtable_init_copy(
    hashtable_t* pt_hashtabledest, const hashtable_t* cpt_hashtablesrc)
{
    assert(pt_hashtabledest != NULL && cpt_hashtablesrc != NULL);
    assert(
        pt_hashtabledest->_t_typesize == cpt_hashtablesrc->_t_typesize &&
        strncmp(
            pt_hashtabledest->_sz_typename,
            cpt_hashtablesrc->_sz_typename,
            _ELEM_TYPE_NAME_SIZE) == 0);

    /* initialize the dest hashtable with src hashtable attribute */
    _hashtable_init(
        pt_hashtabledest,
        _hashtable_bucket_count(cpt_hashtablesrc),
        cpt_hashtablesrc->_pfun_hash,
        cpt_hashtablesrc->_pfun_cmp,
        cpt_hashtablesrc->_pfun_destroy_elem);
    /* insert node from src to dest */
    if(!_hashtable_empty(cpt_hashtablesrc))
    {
        _hashtable_insert_equal_range(
            pt_hashtabledest, 
            _hashtable_begin(cpt_hashtablesrc), 
            _hashtable_end(cpt_hashtablesrc));
    }
}

void _hashtable_init_copy_range(
    hashtable_t* pt_hashtabledest, 
    hashtable_iterator_t t_begin,
    hashtable_iterator_t t_end,
    size_t t_bucketcount,
    int (*pfun_hash)(const void*, size_t, size_t),
    int (*pfun_cmp)(const void*, const void*))
{
    assert(pt_hashtabledest != NULL);
    assert(
        _GET_HASHTABLE(&t_begin) != pt_hashtabledest &&
        _GET_HASHTABLE(&t_end) != pt_hashtabledest &&
        _GET_HASHTABLE(&t_begin) == _GET_HASHTABLE(&t_end));
    assert(
        pt_hashtabledest->_t_typesize == _GET_HASHTABLE(&t_begin)->_t_typesize &&
        strncmp(
            pt_hashtabledest->_sz_typename,
            _GET_HASHTABLE(&t_begin)->_sz_typename,
            _ELEM_TYPE_NAME_SIZE) == 0);

    /* initialize the dest hashtable with src hashtable attribute */
    _hashtable_init(
        pt_hashtabledest, t_bucketcount, pfun_hash, pfun_cmp,
        _GET_HASHTABLE(&t_begin)->_pfun_destroy_elem);
    /* insert node from src to dest */
    if(!_hashtable_empty(_GET_HASHTABLE(&t_begin)))
    {
        _hashtable_insert_equal_range(pt_hashtabledest, t_begin, t_end);
    }
}

void _hashtable_assign(
    hashtable_t* pt_hashtabledest, const hashtable_t* cpt_hashtablesrc)
{
    assert(_same_hashtable_type(pt_hashtabledest, cpt_hashtablesrc));

    /* destroy the dest hashtable */
    _hashtable_destroy(pt_hashtabledest);
    /* initialize the dest hashtable with src hashtable attribute */
    _hashtable_init(
        pt_hashtabledest,
        _hashtable_bucket_count(cpt_hashtablesrc),
        cpt_hashtablesrc->_pfun_hash,
        cpt_hashtablesrc->_pfun_cmp,
        cpt_hashtablesrc->_pfun_destroy_elem);
    /* insert node from src to dest */
    if(!_hashtable_empty(cpt_hashtablesrc))
    {
        _hashtable_insert_equal_range(
            pt_hashtabledest, 
            _hashtable_begin(cpt_hashtablesrc), 
            _hashtable_end(cpt_hashtablesrc));
    }
}

size_t _hashtable_size(const hashtable_t* cpt_hashtable)
{
    assert(cpt_hashtable != NULL);

    return cpt_hashtable->_t_nodecount;
}

bool_t _hashtable_empty(const hashtable_t* cpt_hashtable)
{
    assert(cpt_hashtable != NULL);

    if(cpt_hashtable->_t_nodecount == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

size_t _hashtable_max_size(const hashtable_t* cpt_hashtable)
{
    assert(cpt_hashtable != NULL);

    return (size_t)(-1) / cpt_hashtable->_t_typesize;
}

size_t _hashtable_bucket_count(const hashtable_t* cpt_hashtable)
{
    assert(cpt_hashtable != NULL);

    return vector_size(&cpt_hashtable->_t_bucket);
}

hashtable_iterator_t _hashtable_begin(const hashtable_t* cpt_hashtable)
{
    vector_iterator_t    t_vectoriterator;
    hashtable_iterator_t t_newiterator = _create_hashtable_iterator();

    assert(cpt_hashtable != NULL);

    for(t_vectoriterator = 
            vector_begin(&cpt_hashtable->_t_bucket);
        !iterator_equal(
            &t_vectoriterator, vector_end(&cpt_hashtable->_t_bucket));
        iterator_next(&t_vectoriterator))
    {
        _GET_HASHTABLE_BUCKETPOS(&t_newiterator) = 
            _GET_VECTOR_COREPOS(&t_vectoriterator);
        if(*(hashnode_t**)_GET_HASHTABLE_BUCKETPOS(&t_newiterator) != NULL)
        {
            _GET_HASHTABLE_COREPOS(&t_newiterator) = 
                (char*)*(hashnode_t**)_GET_HASHTABLE_BUCKETPOS(&t_newiterator);
            break;
        }
    }
    if(iterator_equal(
        &t_vectoriterator, vector_end(&cpt_hashtable->_t_bucket)))
    {
        assert(_GET_HASHTABLE_COREPOS(&t_newiterator) == NULL);
        _GET_HASHTABLE_BUCKETPOS(&t_newiterator) = 
            _GET_VECTOR_COREPOS(&t_vectoriterator);
    }
    _GET_HASHTABLE_POINTER(&t_newiterator) = (hashtable_t*)cpt_hashtable;

    return t_newiterator;
}

hashtable_iterator_t _hashtable_end(const hashtable_t* cpt_hashtable)
{
    vector_iterator_t    t_vectorend;
    hashtable_iterator_t t_newiterator = _create_hashtable_iterator();

    assert(cpt_hashtable != NULL);

    t_vectorend = vector_end(&cpt_hashtable->_t_bucket);
    _GET_HASHTABLE_BUCKETPOS(&t_newiterator) = 
        _GET_VECTOR_COREPOS(&t_vectorend);
    _GET_HASHTABLE_COREPOS(&t_newiterator) = NULL;
    _GET_HASHTABLE_POINTER(&t_newiterator) = (hashtable_t*)cpt_hashtable;

    return t_newiterator;
}

void _hashtable_clear(hashtable_t* pt_hashtable)
{
    size_t      t_bucketcount = 0;
    int         i = 0;
    hashnode_t* pt_node = NULL;
    hashnode_t* pt_deletion = NULL;

    assert(pt_hashtable != NULL);

    t_bucketcount = vector_size(&pt_hashtable->_t_bucket);
    /* iterator all bucket node */
    for(i = 0; i < (int)t_bucketcount; ++i)
    {
        /* iterator all element list for one bucket node */
        pt_node = *(hashnode_t**)vector_at(&pt_hashtable->_t_bucket, i);
        *(hashnode_t**)vector_at(&pt_hashtable->_t_bucket, i) = NULL;
        while(pt_node != NULL)
        {
            /* delete each element */
            pt_deletion = pt_node;
            pt_node = pt_node->_pt_next;

            if(pt_hashtable->_pfun_destroy_elem != NULL)
            {
                (*pt_hashtable->_pfun_destroy_elem)(pt_deletion->_pc_data);
            }
            deallocate(
                &pt_hashtable->_t_allocater,  pt_deletion, 
                _HASHTABLE_NODE_SIZE(pt_hashtable->_t_typesize), 1);
        }
    }
    
    pt_hashtable->_t_nodecount = 0;
}

int (*_hashtable_hash_func(const hashtable_t* cpt_hashtable))(
    const void*, size_t, size_t)
{
    assert(cpt_hashtable != NULL);

    return cpt_hashtable->_pfun_hash;
}

int (*_hashtable_key_comp(const hashtable_t* cpt_hashtable))(
    const void*, const void*)
{
    assert(cpt_hashtable != NULL);

    return cpt_hashtable->_pfun_cmp;
}

bool_t _hashtable_equal(
    const hashtable_t* cpt_hashtablefirst, 
    const hashtable_t* cpt_hashtablesecond)
{
    hashtable_iterator_t t_first;
    hashtable_iterator_t t_second;

    assert(cpt_hashtablefirst != NULL && cpt_hashtablesecond != NULL);

    /* check type */
    if(cpt_hashtablefirst->_t_typesize != 
            cpt_hashtablesecond->_t_typesize ||
       strncmp(
            cpt_hashtablefirst->_sz_typename,
            cpt_hashtablesecond->_sz_typename,
            _ELEM_TYPE_NAME_SIZE) != 0)
    {
        return false;
    }
    /* check size */
    if(_hashtable_size(cpt_hashtablefirst) != 
       _hashtable_size(cpt_hashtablesecond))
    {
        return false;
    }
    /* check hash, compare and destroy element function */
    if(cpt_hashtablefirst->_pfun_hash != 
            cpt_hashtablesecond->_pfun_hash ||
       cpt_hashtablefirst->_pfun_cmp != 
            cpt_hashtablesecond->_pfun_cmp ||
       cpt_hashtablefirst->_pfun_destroy_elem != 
            cpt_hashtablesecond->_pfun_destroy_elem)
    {
        return false;
    }
    /* check vector bucket count */
    if(vector_size(&cpt_hashtablefirst->_t_bucket) != 
       vector_size(&cpt_hashtablesecond->_t_bucket))
    {
        return false;
    }
    /* check each element */
    if(cpt_hashtablefirst->_pfun_cmp != NULL)
    {
        for(t_first = _hashtable_begin(cpt_hashtablefirst),
                t_second = _hashtable_begin(cpt_hashtablesecond);
            !_hashtable_iterator_equal(
                    cpt_hashtablefirst, 
                    &t_first, 
                    _hashtable_end(cpt_hashtablefirst)) && 
                !_hashtable_iterator_equal(
                    cpt_hashtablesecond,
                    &t_second,
                    _hashtable_end(cpt_hashtablesecond));
            _hashtable_iterator_next(cpt_hashtablefirst, &t_first),
                _hashtable_iterator_next(cpt_hashtablesecond, &t_second))
        {
            if((*cpt_hashtablefirst->_pfun_cmp)(
                ((hashnode_t*)_GET_HASHTABLE_COREPOS(&t_first))->_pc_data,
                ((hashnode_t*)_GET_HASHTABLE_COREPOS(&t_second))->_pc_data) != 0)
            {
                return false;
            }
        }
    }
    else
    {
        for(t_first = _hashtable_begin(cpt_hashtablefirst),
                t_second = _hashtable_begin(cpt_hashtablesecond);
            !_hashtable_iterator_equal(
                    cpt_hashtablefirst, 
                    &t_first, 
                    _hashtable_end(cpt_hashtablefirst)) && 
                !_hashtable_iterator_equal(
                    cpt_hashtablesecond,
                    &t_second,
                    _hashtable_end(cpt_hashtablesecond));
            _hashtable_iterator_next(cpt_hashtablefirst, &t_first),
                _hashtable_iterator_next(cpt_hashtablesecond, &t_second))
        {
            if(memcmp(
                ((hashnode_t*)_GET_HASHTABLE_COREPOS(&t_first))->_pc_data,
                ((hashnode_t*)_GET_HASHTABLE_COREPOS(&t_second))->_pc_data,
                cpt_hashtablefirst->_t_typesize) != 0)
            {
                return false;
            }
        }
    }

    assert(
        _hashtable_iterator_equal(
            cpt_hashtablefirst, &t_first, _hashtable_end(cpt_hashtablefirst)) &&
        _hashtable_iterator_equal(
            cpt_hashtablesecond, &t_second, _hashtable_end(cpt_hashtablesecond)));

    return true;
}

bool_t _hashtable_not_equal(
    const hashtable_t* cpt_hashtablefirst,
    const hashtable_t* cpt_hashtablesecond)
{
    return !_hashtable_equal(cpt_hashtablefirst, cpt_hashtablesecond);
}

void _hashtable_insert_equal_range(
    hashtable_t* pt_hashtable, 
    hashtable_iterator_t t_begin, 
    hashtable_iterator_t t_end)
{
    hashtable_iterator_t t_iterator;

    assert(_same_hashtable_iterator_type(pt_hashtable, &t_begin));
    assert(
        _hashtable_iterator_equal(_GET_HASHTABLE(&t_begin), &t_begin, t_end) ||
        _hashtable_iterator_before(&t_begin, &t_end));

    for(t_iterator = t_begin;
        !_hashtable_iterator_equal(_GET_HASHTABLE(&t_begin), &t_iterator, t_end);
        _hashtable_iterator_next(_GET_HASHTABLE(&t_begin), &t_iterator))
    {
        _hashtable_insert_equal(
            pt_hashtable, 
            ((hashnode_t*)_GET_HASHTABLE_COREPOS(&t_iterator))->_pc_data);
    }
}

void _hashtable_insert_unique_range(
    hashtable_t* pt_hashtable,
    hashtable_iterator_t t_begin,
    hashtable_iterator_t t_end)
{
    hashtable_iterator_t t_iterator;

    assert(_same_hashtable_iterator_type(pt_hashtable, &t_begin));
    assert(
        _hashtable_iterator_equal(_GET_HASHTABLE(&t_begin), &t_begin, t_end) ||
        _hashtable_iterator_before(&t_begin, &t_end));

    for(t_iterator = t_begin;
        !_hashtable_iterator_equal(_GET_HASHTABLE(&t_begin), &t_iterator, t_end);
        _hashtable_iterator_next(_GET_HASHTABLE(&t_begin), &t_iterator))
    {
        _hashtable_insert_unique(
            pt_hashtable,
            ((hashnode_t*)_GET_HASHTABLE_COREPOS(&t_iterator))->_pc_data);
    }
}

/** local function implementation section **/
#ifndef NDEBUG
static bool_t _iterator_belong_to_hashtable(
    const hashtable_t* cpt_hashtable, const hashtable_iterator_t* cpt_iterator)
{
    vector_iterator_t t_vectoriterator;

    assert(cpt_hashtable != NULL && cpt_iterator != NULL);
    assert(_GET_HASHTABLE(cpt_iterator) == cpt_hashtable);

    /* check for the end node */
    t_vectoriterator = vector_end(&cpt_hashtable->_t_bucket);
    if(_GET_VECTOR_COREPOS(&t_vectoriterator) == 
        _GET_HASHTABLE_BUCKETPOS(cpt_iterator) &&
       _GET_HASHTABLE_COREPOS(cpt_iterator) == NULL)
    {
        return true;
    }
    else
    {
        hashnode_t* pt_node = NULL;
        for(t_vectoriterator = 
                vector_begin(&cpt_hashtable->_t_bucket);
            !iterator_equal(
                &t_vectoriterator, vector_end(&cpt_hashtable->_t_bucket));
            iterator_next(&t_vectoriterator))
        {
            if(_GET_HASHTABLE_BUCKETPOS(cpt_iterator) == 
                _GET_VECTOR_COREPOS(&t_vectoriterator))
            {
                pt_node = *(hashnode_t**)_GET_VECTOR_COREPOS(&t_vectoriterator);
                while(pt_node != NULL)
                {
                    if(pt_node == 
                       (hashnode_t*)_GET_HASHTABLE_COREPOS(cpt_iterator))
                    {
                        return true;
                    }

                    pt_node = pt_node->_pt_next;
                }
            }
        }

        return false;
    }
}

static bool_t _same_hashtable_type(
    const hashtable_t* cpt_hashtablefirst, 
    const hashtable_t* cpt_hashtablesecond)
{
    assert(cpt_hashtablefirst != NULL && cpt_hashtablesecond != NULL);

    /* check type */
    assert(
        cpt_hashtablefirst->_t_typesize == cpt_hashtablesecond->_t_typesize &&
        strncmp(
            cpt_hashtablefirst->_sz_typename,
            cpt_hashtablesecond->_sz_typename,
            _ELEM_TYPE_NAME_SIZE) == 0);
    /* check hash, compare and destroy function */
    assert(
        cpt_hashtablefirst->_pfun_cmp == 
            cpt_hashtablesecond->_pfun_cmp &&
        cpt_hashtablefirst->_pfun_destroy_elem == 
            cpt_hashtablesecond->_pfun_destroy_elem &&
        cpt_hashtablefirst->_pfun_hash == 
            cpt_hashtablesecond->_pfun_hash);

    return true;
}

static bool_t _iterator_for_one_and_the_same_hashtable(
    const hashtable_iterator_t* cpt_iteratorfirst,
    const hashtable_iterator_t* cpt_iteratorsecond)
{
    assert(cpt_iteratorfirst != NULL && cpt_iteratorsecond != NULL);
    assert(
        _GET_HASHTABLE(cpt_iteratorfirst) == _GET_HASHTABLE(cpt_iteratorsecond));

    return true;
}

static bool_t _same_hashtable_iterator_type(
    const hashtable_t* cpt_hashtable, const hashtable_iterator_t* cpt_iterator)
{
    assert(
        cpt_hashtable != NULL && 
        cpt_iterator != NULL && 
        _GET_HASHTABLE(cpt_iterator) != NULL);
    assert(
        cpt_hashtable->_t_typesize == 
            _GET_HASHTABLE(cpt_iterator)->_t_typesize &&
        strncmp(
            cpt_hashtable->_sz_typename,
            _GET_HASHTABLE(cpt_iterator)->_sz_typename,
            _ELEM_TYPE_NAME_SIZE) == 0);
    assert(
        cpt_hashtable->_pfun_cmp == 
            _GET_HASHTABLE(cpt_iterator)->_pfun_cmp &&
        cpt_hashtable->_pfun_destroy_elem == 
            _GET_HASHTABLE(cpt_iterator)->_pfun_destroy_elem &&
        cpt_hashtable->_pfun_hash == 
            _GET_HASHTABLE(cpt_iterator)->_pfun_hash);

    return true;
}
#endif /* NDEBUG */

static unsigned long _get_next_prime(unsigned long ul_basenum)
{
    int i;
    for(i = 0; i < _HASHTABLE_PRIME_LIST_COUNT; ++i)
    {
        if(_hashtable_prime_list[i] >= ul_basenum)
        {
            return _hashtable_prime_list[i];
        }
    }

    return ul_basenum;
}

static int _hash_function_for_int(
    const void* cpv_value, size_t t_typesize, size_t t_bucketcount)
{
    t_typesize = 0;
    return abs(*(int*)cpv_value % t_bucketcount);
}

static int _hash_function_for_unsigned_int(
    const void* cpv_value, size_t t_typesize, size_t t_bucketcount)
{
    t_typesize = 0;
    return *(unsigned int*)cpv_value % t_bucketcount;
}

static int _hash_function_for_short(
    const void* cpv_value, size_t t_typesize, size_t t_bucketcount)
{
    t_typesize = 0;
    return abs(*(short*)cpv_value % t_bucketcount);
}

static int _hash_function_for_unsigned_short(
    const void* cpv_value, size_t t_typesize, size_t t_bucketcount)
{
    t_typesize = 0;
    return *(unsigned short*)cpv_value % t_bucketcount;
}

static int _hash_function_for_long(
    const void* cpv_value, size_t t_typesize, size_t t_bucketcount)
{
    t_typesize = 0;
    return abs(*(long*)cpv_value % t_bucketcount);
}

static int _hash_function_for_unsigned_long(
    const void* cpv_value, size_t t_typesize, size_t t_bucketcount)
{
    t_typesize = 0;
    return *(unsigned long*)cpv_value % t_bucketcount;
}

static int _hash_function_for_double(
    const void* cpv_value, size_t t_typesize, size_t t_bucketcount)
{
    t_typesize = 0;
    return (unsigned long)*(double*)cpv_value % t_bucketcount;
}

static int _hash_function_for_float(
    const void* cpv_value, size_t t_typesize, size_t t_bucketcount)
{
    t_typesize = 0;
    return (unsigned long)*(float*)cpv_value % t_bucketcount;
}

static int _hash_function_for_other(
    const void* cpv_value, size_t t_typesize, size_t t_bucketcount)
{
    int    i = 0;
    size_t t_sum = 0;
    char*  pc_value = NULL;

    assert(cpv_value != NULL && t_typesize > 0 && t_bucketcount > 0);

    pc_value = (char*)cpv_value;
    for(i = 0; i < (int)t_typesize; ++i)
    {
        t_sum += (size_t)pc_value[i];
    }

    return (int)(t_sum % t_bucketcount);
}

/** eof **/

