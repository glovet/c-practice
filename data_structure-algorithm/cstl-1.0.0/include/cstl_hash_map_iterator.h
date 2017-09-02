/*
 * =============================================================================
 *  Copyright (c) 2008 2009 ActiveSys.Wangbo
 *
 *  copyright description ...
 *
 *  Project:    cstl
 *  Module:     hash_map
 *  Filename:   cstl_hash_map_iterator.h
 *
 *  The iterator interface of hash_map.
 *
 *  2009-01-15 19:44:45
 * =============================================================================
 */

#ifndef _CSTL_HASH_MAP_ITERATOR_H
#define _CSTL_HASH_MAP_ITERATOR_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
typedef iterator_t hash_map_iterator_t;
struct _taghashmap;

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _create_hash_map_iterator
 *        Parameters: void
 *           Returns: hash_map_iterator_t
 *                          new hash_map iterator.
 *       Description: create new hash_map iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern hash_map_iterator_t create_hash_map_iterator(void);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hash_map_iterator_get_value
 *        Parameters: in) cpt_hash_map: const struct _taghashmap*
 *                            the hash_map pointer.
 *                    in) cpt_iterator: const hash_map_iterator_t*
 *                            the iterator pointer for getting value.
 *                    modify)pv_value: void*
 *                            the value pointer.
 *           Returns: void
 *       Description: get the value of current hash_map iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void _hash_map_iterator_get_value(
    const struct _taghashmap* cpt_hash_map,
    const hash_map_iterator_t* cpt_iterator, 
    void* pv_value);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hash_map_iterator_get_pointer
 *        Parameters: in) cpt_hash_map: const struct _taghashmap*
 *                            the hash_map pointer.
 *                    in) cpt_iterator: const hash_map_iterator_t*
 *                            the iterator pointer for getting value.
 *           Returns: const void*
 *       Description: get the iterator pointer.
 *
 * ----------------------------------------------------------------------------
 */
extern const void* _hash_map_iterator_get_pointer(
    const struct _taghashmap* cpt_hash_map,
    const hash_map_iterator_t* cpt_iterator); 

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hash_map_iterator_next
 *        Parameters: in) cpt_hash_map: const struct _taghashmap*
 *                            the hash_map pointer.
 *                    in) pt_iterator: hash_map_iterator_t*
 *                            the iterator pointer for go to next position.
 *           Returns: void
 *       Description: to the next position of current hash_map iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void _hash_map_iterator_next(
    const struct _taghashmap* cpt_hash_map, hash_map_iterator_t* pt_iterator);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hash_map_iterator_equal
 *        Parameters: in) cpt_hash_map: const struct _taghashmap*
 *                            the hash_map pointer.
 *                    in) cpt_iterator: const hash_map_iterator_t*
 *                            the iterator pointer for getting value.
 *                    in) t_iterator: hash_map_iterator_t
 *                            the iterator.
 *           Returns: bool_t
 *                            if the first iterator equal the second.
 *       Description: test if the first iterator equal the second.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _hash_map_iterator_equal(
    const struct _taghashmap* cpt_hash_map,
    const hash_map_iterator_t* cpt_iterator,
    hash_map_iterator_t t_iterator);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hash_map_iterator_distance
 *        Parameters: in) cpt_begin: const hash_map_iterator_t*
 *                            the iterator pointer to the first node.
 *                    in) cpt_end: const hash_map_iterator_t*
 *                            the iterator pointer to the last node.
 *           Returns: int
 *                            the distance of two iterator
 *       Description: get the distance of two iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern int _hash_map_iterator_distance(
    const hash_map_iterator_t* cpt_begin, const hash_map_iterator_t* cpt_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _hash_map_iterator_before
 *        Parameters: in) cpt_iteratorfirst: const hash_map_iterator_t*
 *                            first rb_tree iterator pointer.
 *                    in) cpt_iteratorsecond: const hash_map_iterator_t*
 *                            second rb_tree iterator pointer.
 *           Returns: bool_t
 *       Description: test the first iterator before the second one.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _hash_map_iterator_before(
    const hash_map_iterator_t* cpt_iteratorfirst, 
    const hash_map_iterator_t* cpt_iteratorsecond);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_HASH_MAP_ITERATOR_H */
/** eof **/

