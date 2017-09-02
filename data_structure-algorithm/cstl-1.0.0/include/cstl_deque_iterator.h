/*
 * =============================================================================
 *  Copyright (c) 2008 2009 ActiveSys.Wangbo
 *
 *  copyright description ...
 *
 *  Project:    cstl
 *  Module:     deque, iterator
 *  Filename:   cstl_deque_iterator.h
 *      
 *  The deque iterator interface for iterator module.
 *
 *  2008-11-30 09:45:00
 * =============================================================================
 */

#ifndef _CSTL_DEQUE_ITERATOR_H
#define _CSTL_DEQUE_ITERATOR_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/

/** data type declaration and struct, union, enum section **/
typedef iterator_t deque_iterator_t;
typedef iterator_t deque_reverse_iterator_t;
struct _tagdeque;

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: create_deque_iterator
 *        Parameters: void
 *           Returns: deque_iterator_t
 *                          new deque iterator.
 *       Description: create new deque iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern deque_iterator_t create_deque_iterator(void);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _deque_iterator_equal
 *        Parameters: in) cpt_deque: const struct _tagdeque*
 *                            the deque pointer.
 *                    in) cpt_iterator: const deque_iterator_t*
 *                            the iterator pointer for getting value.
 *                    in) t_iterator: deque_iterator_t
 *                            the iterator.
 *           Returns: bool_t
 *                            if the first iterator equal the second.
 *       Description: test if the first iterator equal the second.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _deque_iterator_equal(
    const struct _tagdeque* cpt_deque,
    const deque_iterator_t* cpt_iterator,
    deque_iterator_t t_iterator);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _deque_iterator_get_value
 *        Parameters: in) cpt_deque: const struct _tagdeque*
 *                            the deque pointer.
 *                    in) cpt_iterator: const deque_iterator_t*
 *                            the iterator pointer for getting value.
 *                    modify)pv_value: void*
 *                            the value pointer.
 *           Returns: void
 *       Description: get the value of current deque iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void _deque_iterator_get_value(
    const struct _tagdeque* cpt_deque,
    const deque_iterator_t* cpt_iterator, 
    void* pv_value);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _deque_iterator_set_value
 *        Parameters: in) cpt_deque: const struct _tagdeque*
 *                            the deque pointer.
 *                    in) cpt_iterator: const deque_iterator_t*
 *                            the iterator pointer for getting value.
 *                    in) cpv_value: const void*
 *                            the value pointer.
 *           Returns: void
 *       Description: set the value of current deque iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void _deque_iterator_set_value(
    const struct _tagdeque* cpt_deque,
    const deque_iterator_t* cpt_iterator, 
    const void* cpv_value);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _deque_iterator_get_pointer
 *        Parameters: in) cpt_deque: const struct _tagdeque*
 *                            the deque pointer.
 *                    in) cpt_iterator: const deque_iterator_t*
 *                            the iterator pointer for getting value.
 *           Returns: const void*
 *       Description: get the iterator pointer.
 *
 * ----------------------------------------------------------------------------
 */
extern const void* _deque_iterator_get_pointer(
    const struct _tagdeque* cpt_deque,
    const deque_iterator_t* cpt_iterator); 

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _deque_iterator_next
 *        Parameters: in) cpt_deque: const struct _tagdeque*
 *                            the deque pointer.
 *                    in) pt_iterator: deque_iterator_t*
 *                            the iterator pointer for go to next position.
 *           Returns: void
 *       Description: to the next position of current deque iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void _deque_iterator_next(
    const struct _tagdeque* cpt_deque, deque_iterator_t* pt_iterator);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _deque_iterator_prev
 *        Parameters: in) cpt_deque: const struct _tagdeque*
 *                            the deque pointer.
 *                    in) pt_iterator: deque_iterator_t*
 *                            the iterator pointer for go to previous position.
 *           Returns: void
 *       Description: to the previous position of current deque iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void _deque_iterator_prev(
    const struct _tagdeque* cpt_deque, deque_iterator_t* pt_iterator);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _deque_iterator_at
 *        Parameters: in) cpt_deque: const struct _tagdeque*
 *                            the deque pointer.
 *                    in) cpt_iterator: const deque_iterator_t*
 *                            the iterator pointer for getting value.
 *                    in) un_index: unsigned int
 *                            the index n.
 *           Returns: void*
 *       Description: get the value of current deque iterator with index n.
 *
 * ----------------------------------------------------------------------------
 */
extern void* _deque_iterator_at(
    const struct _tagdeque* cpt_deque, 
    const deque_iterator_t* cpt_iterator,
    unsigned int un_index);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _deque_iterator_next_n
 *        Parameters: in) cpt_deque: const struct _tagdeque*
 *                            the deque pointer.
 *                    in) pt_iterator: deque_iterator_t*
 *                            the iterator pointer for go to next position.
 *                    in) n_step: int
 *                            the step of next.
 *           Returns: void
 *       Description: to the next position of current deque iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void _deque_iterator_next_n(
    const struct _tagdeque* cpt_deque, 
    deque_iterator_t* pt_iterator,
    int n_step);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _deque_iterator_prev_n
 *        Parameters: in) cpt_deque: const struct _tagdeque*
 *                            the deque pointer.
 *                    in) pt_iterator: deque_iterator_t*
 *                            the iterator pointer for go to previous position.
 *                    in) n_step: int
 *                            the step of previous.
 *           Returns: void
 *       Description: to the previous n position of current deque iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern void _deque_iterator_prev_n(
    const struct _tagdeque* cpt_deque, 
    deque_iterator_t* pt_iterator,
    int n_step);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _deque_iterator_minus
 *        Parameters: in) cpt_deque: const struct _tagdeque*
 *                            the deque pointer.
 *                    in) cpt_iterator: const deque_iterator_t*
 *                            the iterator pointer for getting value.
 *                    in) t_iterator: deque_iterator_t
 *                            the iterator.
 *           Returns: int
 *                            the distance of two iterator
 *       Description: compute the distance of two iterator.
 *
 * ----------------------------------------------------------------------------
 */
extern int _deque_iterator_minus(
    const struct _tagdeque* cpt_deque,
    const deque_iterator_t* cpt_iterator, 
    deque_iterator_t t_iterator);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _deque_iterator_less
 *        Parameters: in) cpt_deque: const struct _tagdeque*
 *                            the deque pointer.
 *                    in) cpt_iterator: const deque_iterator_t*
 *                            the iterator pointer for getting value.
 *                    in) t_iterator: deque_iterator_t
 *                            the iterator.
 *           Returns: bool_t
 *                            if the first iterator less then the second.
 *       Description: test if the first iterator less then the second.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _deque_iterator_less(
    const struct _tagdeque* cpt_deque,
    const deque_iterator_t* cpt_iterator,
    deque_iterator_t t_iterator);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _deque_iterator_before
 *        Parameters: in) cpt_iteratorfirst: const deque_iterator_t*
 *                           first deque iterator pointer.
 *                    in) cpt_iteratorsecond: const deque_iterator_t*
 *                           second deque iterator pointer.
 *           Returns: bool_t
 *       Description: test the first iterator before the second one.
 *
 * ----------------------------------------------------------------------------
 */
extern bool_t _deque_iterator_before(
    const deque_iterator_t* cpt_iteratorfirst, 
    const deque_iterator_t* cpt_iteratorsecond);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_DEQUE_ITERATOR_H */
/** eof **/

