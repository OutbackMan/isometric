#ifndef __common_h__
#define __common_h__

#include <stddef.h>

void i_common_exit(int exit_status);

void* i_common_xmalloc(size_t num_bytes);

void* i_common_xcalloc(size_t num_elements, size_t element_size);

void* i_common_xrealloc(void* ptr, size_t num_bytes);

#endif
