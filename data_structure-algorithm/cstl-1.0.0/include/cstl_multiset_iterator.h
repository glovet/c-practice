/*
 * =============================================================================
 *  Copyright (c) 2008 2009 ActiveSys.Wangbo
 *
 *  copyright description ...
 *
 *  Project:    cstl
 *  Module:     multiset
 *  Filename:   cstl_multiset_iterator.h
 *
 *  The iterator interface of multiset.
 *
 *  2009-01-08 10:43:23
 * =============================================================================
 */

#ifndef _CSTL_MULTISET_ITERATOR_H
#define _CSTL_MULTISET_ITERATOR_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
typedef iterator_t multiset_iterator_t;
typedef iterator_t multiset_reverse_iterator_t;
struct _tagmultiset;

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: create_multiset_iterator
 *        Parameters: void
 *           Returns: multiset_iterator_t
 *                          new multiset iterator.
 *       Description: create new multiset iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern multiset_iterator_t create_multiset_iterator(void);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _multiset_iterator_get_value
 *        Parameters: in) cpt_multiset: const struct _tagrbtree*
 *                            the multiset pointer.
 *                    in) cpt_iterator: const multiset_iterator_t*
 *                            the iterator pointer for getting value.
 *                    modify)pv_value: void*
 *                            the value pointer.
 *           Returns: void
 *       Description: get the value of current multiset iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void _multiset_iterator_get_value(
    const struct _tagmultiset* cpt_multiset,
    const multiset_iterator_t* cpt_iterator, 
    void* pv_value);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _multiset_iterator_get_pointer
 *        Parameters: in) cpt_multiset: const struct _tagrbtree*
 *                            the multiset pointer.
 *                    in) cpt_iterator: const multiset_iterator_t*
 *                            the iterator pointer for getting value.
 *           Returns: const void*
 *       Description: get the iterator pointer.
 *
 * ----------------------------------------------------------------------------
 */
extern const void* _multiset_iterator_get_pointer(
    const struct _tagmultiset* cpt_multiset, 
    const multiset_iterator_t* cpt_iterator);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _multiset_iterator_next
 *        Parameters: in) cpt_multiset: const struct _tagrbtree*
 *                            the multiset pointer.
 *                    in) pt_iterator: multiset_iterator_t*
 *                            the iterator pointer for go to next position.
 *           Returns: void
 *       Description: to the next position of current multiset iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void _multiset_iterator_next(
    const struct _tagmultiset* cpt_multiset, multiset_iterator_t* pt_iterator);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _multiset_iterator_prev
 *        Parameters: in) cpt_multiset: const struct _tagrbtree*
 *                            the multiset pointer.
 *                    in) pt_iterator: multiset_iterator_t*
 *                            the iterator pointer for go to previous position.
 *           Returns: void
 *       Description: to the previous position of current multiset iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void _multiset_iterator_prev(
    const struct _tagmultiset* cpt_multiset, multiset_iterator_t* pt_iterator);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _multiset_iterator_equal
 *        Parameters: in) cpt_multiset: const struct _tagrbtree*
 *                            the multiset pointer.
 *                    in) cpt_iterator: const multiset_iterator_t*
 *                            the iterator pointer for getting value.
 *                    in) t_iterator: multiset_iterator_t
 *                            the iterator.
 *           Returns: bool_t
 *                            if the first iterator equal the second.
 *       Description: test if the first iterator equal the second.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _multiset_iterator_equal(
    const struct _tagmultiset* cpt_multiset,
    const multiset_iterator_t* cpt_iterator,
    multiset_iterator_t t_iterator);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _multiset_iterator_distance
 *        Parameters: in) cpt_begin: const multiset_iterator_t*
 *                            the iterator pointer to the first node.
 *                    in) cpt_end: const multiset_iterator_t*
 *                            the iterator pointer to the last node.
 *           Returns: int
 *                            the distance of two iterator
 *       Description: get the distance of two iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern int _multiset_iterator_distance(
    const multiset_iterator_t* cpt_begin, const multiset_iterator_t* cpt_end);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _multiset_iterator_before
 *        Parameters: in) cpt_iteratorfirst: const multiset_iterator_t*
 *                            first rb_tree iterator pointer.
 *                    in) cpt_iteratorsecond: const multiset_iterator_t*
 *                            second rb_tree iterator pointer.
 *           Returns: bool_t
 *       Description: test the first iterator before the second one.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _multiset_iterator_before(
    const multiset_iterator_t* cpt_iteratorfirst, 
    const multiset_iterator_t* cpt_iteratorsecond);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_MULTISET_ITERATOR_H */
/** eof **/

