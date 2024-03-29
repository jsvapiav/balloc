#ifndef BALLOC_PLATFORM_H
#include <stdint.h>

#define BALLOC_PLATFORM_PREFIX_CANARY (0xDEADBEAF)
#define BALLOC_PLATFORM_POSTFIX_CANARY (0xBEAFCAFE)

typedef int64_t balloc_platform_fast_int;
typedef uint64_t balloc_platform_fast_uint;
typedef balloc_platform_fast_uint balloc_platform_canary_int;

/*
 * Here should be defined compare and set function
 * with following definition:

 * balloc_platform_fast_uint balloc_platform_compare_and_set(
 * 				balloc_platform_fast_uint *ptr,
 *				balloc_platform_fast_uint oldval,
 *				balloc_platform_fast_uint newval);
 *
 * As example for x86_64 platform:
 *
 * uint64_t* ptr;
 * uint64_t ret_val, old_val, new_val;
 *
 * asm volatile("lock\n\tcmpxchgq %1,%2"
 *   :"=a"(ret_val)
 *   :"r"(new_val), "m"(*ptr), "0"(old_val)
 *   :"memory"
 *   );
 *
 * But due to gcc already has support for atomic compare and swap function
 * just use it.
 */

balloc_platform_fast_uint balloc_platform_compare_and_set(
				balloc_platform_fast_uint *ptr,
				balloc_platform_fast_uint oldval,
				balloc_platform_fast_uint newval)
{
	return __sync_bool_compare_and_swap(ptr, oldval, newval);
}

#define BALLOC_PLATFORM_H
#endif
