/*
 * =============================================================================
 *  Copyright (c) 2008 2009 ActiveSys.Wangbo
 *
 *  copyright description ...
 *
 *  Project:    cstl
 *  Module:     multimap
 *  Filename:   cstl_multimap_iterator.h
 *
 *  The iterator interface of multimap.
 *
 *  2009-01-12 09:27:08
 * =============================================================================
 */

#ifndef _CSTL_MULTIMAP_ITERATOR_H
#define _CSTL_MULTIMAP_ITERATOR_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
typedef iterator_t multimap_iterator_t;
typedef iterator_t multimap_reverse_iterator_t;
struct _tagmultimap;

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: create_multimap_iterator
 *        Parameters: void
 *           Returns: multimap_iterator_t
 *                          new multimap iterator.
 *       Description: create new multimap iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern multimap_iterator_t create_multimap_iterator(void);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _multimap_iterator_get_value
 *        Parameters: in) cpt_multimap: const struct _tagrbtree*
 *                            the multimap pointer.
 *                    in) cpt_iterator: const multimap_iterator_t*
 *                            the iterator pointer for getting value.
 *                    modify)pv_value: void*
 *                            the value pointer.
 *           Returns: void
 *       Description: get the value of current multimap iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void _multimap_iterator_get_value(
    const struct _tagmultimap* cpt_multimap,
    const multimap_iterator_t* cpt_iterator, 
    void* pv_value);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _multimap_iterator_get_pointer
 *        Parameters: in) cpt_multimap: const struct _tagrbtree*
 *                            the multimap pointer.
 *                    in) cpt_iterator: const multimap_iterator_t*
 *                            the iterator pointer for getting value.
 *           Returns: const void*
 *       Description: get the iterator pointer.
 *
 * ----------------------------------------------------------------------------
 */
extern const void* _multimap_iterator_get_pointer(
    const struct _tagmultimap* cpt_multimap, 
    const multimap_iterator_t* cpt_iterator);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _multimap_iterator_next
 *        Parameters: in) cpt_multimap: const struct _tagrbtree*
 *                            the multimap pointer.
 *                    in) pt_iterator: multimap_iterator_t*
 *                            the iterator pointer for go to next position.
 *           Returns: void
 *       Description: to the next position of current multimap iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void _multimap_iterator_next(
    const struct _tagmultimap* cpt_multimap, multimap_iterator_t* pt_iterator);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _multimap_iterator_prev
 *        Parameters: in) cpt_multimap: const struct _tagrbtree*
 *                            the multimap pointer.
 *                    in) pt_iterator: multimap_iterator_t*
 *                            the iterator pointer for go to previous position.
 *           Returns: void
 *       Description: to the previous position of current multimap iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void _multimap_iterator_prev(
    const struct _tagmultimap* cpt_multimap, multimap_iterator_t* pt_iterator);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _multimap_iterator_equal
 *        Parameters: in) cpt_multimap: const struct _tagrbtree*
 *                            the multimap pointer.
 *                    in) cpt_iterator: const multimap_iterator_t*
 *                            the iterator pointer for getting value.
 *                    in) t_iterator: multimap_iterator_t
 *                            the iterator.
 *           Returns: bool_t
 *                            if the first iterator equal the second.
 *       Description: test if the first iterator equal the second.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _multimap_iterator_equal(
    const struct _tagmultimap* cpt_multimap,
    const multimap_iterator_t* cpt_iterator,
    multimap_iterator_t t_iterator);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _multimap_iterator_distance
 *        Parameters: in) cpt_begin: const multimap_iterator_t*
 *                            the iterator pointer to the first node.
 *                    in) cpt_end: const multimap_iterator_t*
 *                            the iterator pointer to the last node.
 *           Returns: int
 *                            the distance of two iterator
 *       Description: get the distance of two iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern int _multimap_iterator_distance(
    const multimap_iterator_t* cpt_begin, const multimap_iterator_t* cpt_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _multimap_iterator_before
 *        Parameters: in) cpt_iteratorfirst: const multimap_iterator_t*
 *                            first rb_tree iterator pointer.
 *                    in) cpt_iteratorsecond: const multimap_iterator_t*
 *                            second rb_tree iterator pointer.
 *           Returns: bool_t
 *       Description: test the first iterator before the second one.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _multimap_iterator_before(
    const multimap_iterator_t* cpt_iteratorfirst, 
    const multimap_iterator_t* cpt_iteratorsecond);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_MULTIMAP_ITERATOR_H */
/** eof **/

