#define _GNU_SOURCE
#include <dlfcn.h>
#include "liballocs.h"

struct uniqtype_cache_word
{
	unsigned long addr:47;
	unsigned flag:1;
	unsigned bits:16;
};
struct uniqtype
{
	struct uniqtype_cache_word cache_word;
	const char *name;
	unsigned short pos_maxoff; // 16 bits
	unsigned short neg_maxoff; // 16 bits
	unsigned nmemb:12;	 // 12 bits -- number of `contained's (always 1 if array)
	unsigned is_array:1;       // 1 bit
	unsigned array_len:19;     // 19 bits; 0 means undetermined length
	struct contained { 
		signed offset;
		struct uniqtype *ptr;
	} contained[];
};

struct s2a
{
	int x;
} s;

void *l2a(void)
{
	/* Get our __uniqtype__s2a. */
	struct uniqtype *resolved = dlsym(__liballocs_my_typeobj(), "__uniqtype__s2a");
	/* Return our __uniqtype__int$32. */
	return resolved->contained[0].ptr;
}
