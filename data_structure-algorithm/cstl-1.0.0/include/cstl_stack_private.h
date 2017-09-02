/*
 * =============================================================================
 *  Copyright (c) 2008 2009 ActiveSys.Wangbo
 *
 *  copyright description ...
 *
 *  Project:    cstl
 *  Module:     stack
 *  Filename:   cstl_stack_private.h
 *
 *  The stack private stack struct.
 *
 *  2008-12-14 17:22:07
 * =============================================================================
 */

#ifndef _CSTL_STACK_PRIVATE_H
#define _CSTL_STACK_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
#define _GET_STACK_DEQUE_SEQUENCE(_pt_stack)\
    (&((_pt_stack)->_t_sequence._t_deque))
#define _GET_STACK_LIST_SEQUENCE(_pt_stack)\
    (&((_pt_stack)->_t_sequence._t_list))
#define _GET_STACK_VECTOR_SEQUENCE(_pt_stack)\
    (&((_pt_stack)->_t_sequence._t_vector))

/** data type declaration and struct, union, enum section **/
/* the stack struct default use deque_t */
typedef struct _tagstack
{
    union
    {
        deque_t  _t_deque;
        list_t   _t_list;
        vector_t _t_vector;
    }_t_sequence; 
}stack_t;

/** exported global variable declaration section **/

/** exported function prototype section **/
/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _create_stack
 *        Parameters: in) t_typesize: size_t
 *                          the element type size.
 *                    in) s_typename: const char*
 *                          the element type name.
 *           Returns: stack_t
 *                          new stack.
 *       Description: create the new stack.
 *
 * ----------------------------------------------------------------------------
 */
extern stack_t _create_stack(size_t t_typesize, const char* s_typename);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _stack_push
 *        Parameters: in) pt_stack: stack_t*
 *                          the stack.
 *                    in) ...
 *                          the element.
 *           Returns: void
 *       Description: append a copy of element at the top.
 *
 * ----------------------------------------------------------------------------
 */
extern void _stack_push(stack_t* pt_stack, ...);

/*
 * ----------------------------------------------------------------------------
 *
 *      Functionname: _stack_push_varg
 *        Parameters: in) pt_stack: stack_t*
 *                          the stack.
 *                    in) val_elemlist: va_list
 *                          the element list.
 *           Returns: void
 *       Description: append a copy of element at the top.
 *
 * ----------------------------------------------------------------------------
 */
extern void _stack_push_varg(stack_t* pt_stack, va_list val_elemlist);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_STACK_PRIVATE_H */
/** eof **/

