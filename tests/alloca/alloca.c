#define _GNU_SOURCE
#include <alloca.h>
#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <liballocs.h>

extern __thread void *__current_allocsite __attribute__((weak));

int main(void)
{
	void *a = alloca(42 * sizeof (int));
	struct uniqtype *got_type = __liballocs_get_alloc_type(a);
	struct uniqtype *int_type = dlsym(RTLD_DEFAULT, "__uniqtype__int");
	assert(int_type);
	assert(got_type);
	assert(got_type == int_type);
	
	void *b = alloca(69105);
	// can we still get the type of a?
	struct uniqtype *got_type_again = __liballocs_get_alloc_type(a);
	assert(got_type_again);
	assert(got_type_again == int_type);
	return 0;
}

