/*
 * =============================================================================
 *  Copyright (c) 2008 2009 ActiveSys.Wangbo
 *
 *  copyright description ...
 *
 *  Project:    cstl
 *  Module:     function
 *  Filename:   cstl_function.h
 *
 *  The interface of function.
 *
 *  2009-02-12 10:35:35
 * =============================================================================
 */

#ifndef _CSTL_FUNCTION_H
#define _CSTL_FUNCTION_H

#ifdef __cplusplus
extern "C" {
#endif

/** include section **/

/** constant declaration and macro section **/
/*
#define CSTL_BINARY_FUNCTION_BEGIN(\
    cpv_first, t_firsttype, cpv_second, t_secondtype, pv_output, t_outputtype)\
    assert(cpv_first != NULL && pv_output != NULL);\
    if(cpv_second == NULL){\
        if(strcmp(#t_firsttype, #t_outputtype) == 0){\
            *(t_outputtype*)pv_output = *(t_outputtype*)cpv_first;\
        }else if(strcmp(#t_outputtype, _CHAR_TYPE) == 0 ||\
                 strcmp(#t_outputtype, _SIGNED_CHAR_TYPE) == 0){\
            *(char*)pv_output = '\0';\
        }else if(strcmp(#t_outputtype, _UNSIGNED_CHAR_TYPE) == 0){\
            *(unsigned char*)pv_output = 0x00;\
        }else if(strcmp(#t_outputtype, _SHORT_TYPE) == 0 ||\
                 strcmp(#t_outputtype, _SHORT_INT_TYPE) == 0 ||\
                 strcmp(#t_outputtype, _SIGNED_SHORT_TYPE) == 0 ||\
                 strcmp(#t_outputtype, _SIGNED_SHORT_INT_TYPE) == 0){\
            *(short*)pv_output = 0;\
        }else if(strcmp(#t_outputtype, _UNSIGNED_SHORT_TYPE) == 0 ||\
                 strcmp(#t_outputtype, _UNSIGNED_SHORT_INT_TYPE) == 0){\
            *(unsigned short*)pv_output = 0;\
        }else if(strcmp(#t_outputtype, _INT_TYPE) == 0 ||\
                 strcmp(#t_outputtype, _SIGNED_TYPE) == 0 ||\
                 strcmp(#t_outputtype, _SIGNED_INT_TYPE) == 0){\
            *(int*)pv_output = 0;\
        }else if(strcmp(#t_outputtype, _UNSIGNED_TYPE) == 0 ||\
                 strcmp(#t_outputtype, _UNSIGNED_INT_TYPE) == 0){\
            *(unsigned int*)pv_output = 0;\
        }else if(strcmp(#t_outputtype, _LONG_TYPE) == 0 ||\
                 strcmp(#t_outputtype, _LONG_INT_TYPE) == 0 ||\
                 strcmp(#t_outputtype, _SIGNED_LONG_TYPE) == 0 ||\
                 strcmp(#t_outputtype, _SIGNED_LONG_INT_TYPE) == 0){\
            *(long*)pv_output = 0;\
        }else if(strcmp(#t_outputtype, _UNSIGNED_LONG_TYPE) == 0 ||\
                 strcmp(#t_outputtype, _UNSIGNED_LONG_INT_TYPE) == 0){\
            *(unsigned long*)pv_output = 0;\
        }else if(strcmp(#t_outputtype, _FLOAT_TYPE) == 0){\
            *(float*)pv_output = 0.0;\
        }else if(strcmp(#t_outputtype, _DOUBLE_TYPE) == 0){\
            *(double*)pv_output = 0.0;\
        }else if(strcmp(#t_outputtype, _BOOL_TYPE) == 0){\
            *(bool_t*)pv_output = false;\
        }\
    }else{
#define CSTL_BINARY_FUNCTION_END }
*/

/** data type declaration and struct, union, enum section **/

/** exported global variable declaration section **/

/** exported function prototype section **/
/* arithmetic function */
/* plus */
extern void fun_plus_char(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_plus_uchar(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_plus_short(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_plus_ushort(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_plus_int(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_plus_uint(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_plus_long(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_plus_ulong(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_plus_float(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_plus_double(
    const void* cpv_first, const void* cpv_second, void* pv_output);
/* minus */
extern void fun_minus_char(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_minus_uchar(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_minus_short(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_minus_ushort(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_minus_int(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_minus_uint(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_minus_long(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_minus_ulong(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_minus_float(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_minus_double(
    const void* cpv_first, const void* cpv_second, void* pv_output);
/* multiplies */
extern void fun_multiplies_char(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_multiplies_uchar(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_multiplies_short(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_multiplies_ushort(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_multiplies_int(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_multiplies_uint(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_multiplies_long(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_multiplies_ulong(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_multiplies_float(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_multiplies_double(
    const void* cpv_first, const void* cpv_second, void* pv_output);
/* divides */
extern void fun_divides_char(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_divides_uchar(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_divides_short(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_divides_ushort(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_divides_int(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_divides_uint(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_divides_long(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_divides_ulong(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_divides_float(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_divides_double(
    const void* cpv_first, const void* cpv_second, void* pv_output);
/* modulus */
extern void fun_modulus_char(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_modulus_uchar(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_modulus_short(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_modulus_ushort(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_modulus_int(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_modulus_uint(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_modulus_long(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_modulus_ulong(
    const void* cpv_first, const void* cpv_second, void* pv_output);
/* negation */
extern void fun_negate_char(
    const void* cpv_input, void* pv_output);
extern void fun_negate_short(
    const void* cpv_input, void* pv_output);
extern void fun_negate_int(
    const void* cpv_input, void* pv_output);
extern void fun_negate_long(
    const void* cpv_input, void* pv_output);
extern void fun_negate_float(
    const void* cpv_input, void* pv_output);
extern void fun_negate_double(
    const void* cpv_input, void* pv_output);

/* comparisons */
/* the output parameter must be bool_t */
/* equality */
extern void fun_equal_char(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_equal_uchar(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_equal_short(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_equal_ushort(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_equal_int(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_equal_uint(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_equal_long(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_equal_ulong(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_equal_float(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_equal_double(
    const void* cpv_first, const void* cpv_second, void* pv_output);
/* inequality */
extern void fun_not_equal_char(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_not_equal_uchar(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_not_equal_short(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_not_equal_ushort(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_not_equal_int(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_not_equal_uint(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_not_equal_long(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_not_equal_ulong(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_not_equal_float(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_not_equal_double(
    const void* cpv_first, const void* cpv_second, void* pv_output);
/* greater then */
extern void fun_great_char(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_great_uchar(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_great_short(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_great_ushort(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_great_int(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_great_uint(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_great_long(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_great_ulong(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_great_float(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_great_double(
    const void* cpv_first, const void* cpv_second, void* pv_output);
/* greater then or equal*/
extern void fun_great_equal_char(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_great_equal_uchar(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_great_equal_short(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_great_equal_ushort(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_great_equal_int(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_great_equal_uint(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_great_equal_long(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_great_equal_ulong(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_great_equal_float(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_great_equal_double(
    const void* cpv_first, const void* cpv_second, void* pv_output);
/* less then */
extern void fun_less_char(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_less_uchar(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_less_short(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_less_ushort(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_less_int(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_less_uint(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_less_long(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_less_ulong(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_less_float(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_less_double(
    const void* cpv_first, const void* cpv_second, void* pv_output);
/* less then or equal*/
extern void fun_less_equal_char(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_less_equal_uchar(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_less_equal_short(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_less_equal_ushort(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_less_equal_int(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_less_equal_uint(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_less_equal_long(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_less_equal_ulong(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_less_equal_float(
    const void* cpv_first, const void* cpv_second, void* pv_output);
extern void fun_less_equal_double(
    const void* cpv_first, const void* cpv_second, void* pv_output);

/* locical */
/* logical and */
extern void fun_logical_and_bool(
    const void* cpv_first, const void* cpv_second, void* pv_output);
/* logical or */
extern void fun_logical_or_bool(
    const void* cpv_first, const void* cpv_second, void* pv_output);
/* logical not */
extern void fun_logical_not_bool(
    const void* cpv_input, void* pv_output);

/* random number */
extern void fun_random_number(
    const void* cpv_input, void* pv_output);

/* note: there is no implementation of identity select and project function. */
/* note: there is no implementation of function adapters */

/* default unary and binary function */
extern void fun_default_unary(
    const void* cpv_input, void* pv_output);
extern void fun_default_binary(
    const void* cpv_first, const void* cpv_second, void* output);

#ifdef __cplusplus
}
#endif

#endif /* _CSTL_FUNCTION_H */
/** eof **/

