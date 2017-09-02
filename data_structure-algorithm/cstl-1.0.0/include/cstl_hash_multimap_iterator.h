/*
 * =============================================================================
 *  Copyright (c) 2008 2009 ActiveSys.Wangbo
 *
 *  copyright description ...
 *
 *  Project:    cstl
 *  Module:     hash_multimap
 *  Filename:   cstl_hash_multimap_iterator.h
 *
 *  The iterator interface of hash_multimap.
 *
 *  2009-01-16 19:48:37
 * =============================================================================
 */

#ifndef _CSTL_HASH_MULTIMAP_ITERATOR_H
#define _CSTL_HASH_MULTIMAP_ITERATOR_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
typedef iterator_t hash_multimap_iterator_t;
struct _taghashmultimap;

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _create_hash_multimap_iterator
 *        Parameters: void
 *           Returns: hash_multimap_iterator_t
 *                          new hash_multimap iterator.
 *       Description: create new hash_multimap iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern hash_multimap_iterator_t create_hash_multimap_iterator(void);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hash_multimap_iterator_get_value
 *        Parameters: in) cpt_hash_multimap: const struct _taghashmultimap*
 *                            the hash_multimap pointer.
 *                    in) cpt_iterator: const hash_multimap_iterator_t*
 *                            the iterator pointer for getting value.
 *                    modify)pv_value: void*
 *                            the value pointer.
 *           Returns: void
 *       Description: get the value of current hash_multimap iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void _hash_multimap_iterator_get_value(
    const struct _taghashmultimap* cpt_hash_multimap,
    const hash_multimap_iterator_t* cpt_iterator, 
    void* pv_value);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hash_multimap_iterator_get_pointer
 *        Parameters: in) cpt_hash_multimap: const struct _taghashmultimap*
 *                            the hash_multimap pointer.
 *                    in) cpt_iterator: const hash_multimap_iterator_t*
 *                            the iterator pointer for getting value.
 *           Returns: const void*
 *       Description: get the iterator pointer.
 *
 * ----------------------------------------------------------------------------
 */
extern const void* _hash_multimap_iterator_get_pointer(
    const struct _taghashmultimap* cpt_hash_multimap,
    const hash_multimap_iterator_t* cpt_iterator); 

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hash_multimap_iterator_next
 *        Parameters: in) cpt_hash_multimap: const struct _taghashmultimap*
 *                            the hash_multimap pointer.
 *                    in) pt_iterator: hash_multimap_iterator_t*
 *                            the iterator pointer for go to next position.
 *           Returns: void
 *       Description: to the next position of current hash_multimap iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void _hash_multimap_iterator_next(
    const struct _taghashmultimap* cpt_hash_multimap, 
    hash_multimap_iterator_t* pt_iterator);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hash_multimap_iterator_equal
 *        Parameters: in) cpt_hash_multimap: const struct _taghashmultimap*
 *                            the hash_multimap pointer.
 *                    in) cpt_iterator: const hash_multimap_iterator_t*
 *                            the iterator pointer for getting value.
 *                    in) t_iterator: hash_multimap_iterator_t
 *                            the iterator.
 *           Returns: bool_t
 *                            if the first iterator equal the second.
 *       Description: test if the first iterator equal the second.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _hash_multimap_iterator_equal(
    const struct _taghashmultimap* cpt_hash_multimap,
    const hash_multimap_iterator_t* cpt_iterator,
    hash_multimap_iterator_t t_iterator);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hash_multimap_iterator_distance
 *        Parameters: in) cpt_begin: const hash_multimap_iterator_t*
 *                            the iterator pointer to the first node.
 *                    in) cpt_end: const hash_multimap_iterator_t*
 *                            the iterator pointer to the last node.
 *           Returns: int
 *                            the distance of two iterator
 *       Description: get the distance of two iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern int _hash_multimap_iterator_distance(
    const hash_multimap_iterator_t* cpt_begin, 
    const hash_multimap_iterator_t* cpt_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hash_multimap_iterator_before
 *        Parameters: in) cpt_iteratorfirst: const hash_multimap_iterator_t*
 *                            first rb_tree iterator pointer.
 *                    in) cpt_iteratorsecond: const hash_multimap_iterator_t*
 *                            second rb_tree iterator pointer.
 *           Returns: bool_t
 *       Description: test the first iterator before the second one.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _hash_multimap_iterator_before(
    const hash_multimap_iterator_t* cpt_iteratorfirst, 
    const hash_multimap_iterator_t* cpt_iteratorsecond);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_HASH_MULTIMAP_ITERATOR_H */
/** eof **/

