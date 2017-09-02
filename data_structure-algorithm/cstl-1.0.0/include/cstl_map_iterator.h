/*
 * =============================================================================
 *  Copyright (c) 2008 2009 ActiveSys.Wangbo
 *
 *  copyright description ...
 *
 *  Project:    cstl
 *  Module:     map
 *  Filename:   cstl_map_iterator.h
 *
 *  The interface of map iterator.
 *
 *  2009-01-09 08:51:53
 * =============================================================================
 */

#ifndef _CSTL_MAP_ITERATOR_H
#define _CSTL_MAP_ITERATOR_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
typedef iterator_t map_iterator_t;
typedef iterator_t map_reverse_iterator_t;
struct _tagmap;

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: create_map_iterator
 *        Parameters: void
 *           Returns: map_iterator_t
 *                          new map iterator.
 *       Description: create new map iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern map_iterator_t create_map_iterator(void);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _map_iterator_get_value
 *        Parameters: in) cpt_map: const struct _tagrbtree*
 *                            the map pointer.
 *                    in) cpt_iterator: const map_iterator_t*
 *                            the iterator pointer for getting value.
 *                    modify)pv_value: void*
 *                            the value pointer.
 *           Returns: void
 *       Description: get the value of current map iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void _map_iterator_get_value(
    const struct _tagmap* cpt_map,
    const map_iterator_t* cpt_iterator, 
    void* pv_value);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _map_iterator_get_pointer
 *        Parameters: in) cpt_map: const struct _tagrbtree*
 *                            the map pointer.
 *                    in) cpt_iterator: const map_iterator_t*
 *                            the iterator pointer for getting value.
 *           Returns: const void*
 *       Description: get the iterator pointer.
 *
 * ----------------------------------------------------------------------------
 */
extern const void* _map_iterator_get_pointer(
    const struct _tagmap* cpt_map, 
    const map_iterator_t* cpt_iterator);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _map_iterator_next
 *        Parameters: in) cpt_map: const struct _tagrbtree*
 *                            the map pointer.
 *                    in) pt_iterator: map_iterator_t*
 *                            the iterator pointer for go to next position.
 *           Returns: void
 *       Description: to the next position of current map iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void _map_iterator_next(
    const struct _tagmap* cpt_map, map_iterator_t* pt_iterator);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _map_iterator_prev
 *        Parameters: in) cpt_map: const struct _tagrbtree*
 *                            the map pointer.
 *                    in) pt_iterator: map_iterator_t*
 *                            the iterator pointer for go to previous position.
 *           Returns: void
 *       Description: to the previous position of current map iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void _map_iterator_prev(
    const struct _tagmap* cpt_map, map_iterator_t* pt_iterator);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _map_iterator_equal
 *        Parameters: in) cpt_map: const struct _tagrbtree*
 *                            the map pointer.
 *                    in) cpt_iterator: const map_iterator_t*
 *                            the iterator pointer for getting value.
 *                    in) t_iterator: map_iterator_t
 *                            the iterator.
 *           Returns: bool_t
 *                            if the first iterator equal the second.
 *       Description: test if the first iterator equal the second.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _map_iterator_equal(
    const struct _tagmap* cpt_map,
    const map_iterator_t* cpt_iterator,
    map_iterator_t t_iterator);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _map_iterator_distance
 *        Parameters: in) cpt_begin: const map_iterator_t*
 *                            the iterator pointer to the first node.
 *                    in) cpt_end: const map_iterator_t*
 *                            the iterator pointer to the last node.
 *           Returns: int
 *                            the distance of two iterator
 *       Description: get the distance of two iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern int _map_iterator_distance(
    const map_iterator_t* cpt_begin, const map_iterator_t* cpt_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _map_iterator_before
 *        Parameters: in) cpt_iteratorfirst: const map_iterator_t*
 *                            first rb_tree iterator pointer.
 *                    in) cpt_iteratorsecond: const map_iterator_t*
 *                            second rb_tree iterator pointer.
 *           Returns: bool_t
 *       Description: test the first iterator before the second one.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _map_iterator_before(
    const map_iterator_t* cpt_iteratorfirst, 
    const map_iterator_t* cpt_iteratorsecond);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_MAP_ITERATOR_H */
/** eof **/

