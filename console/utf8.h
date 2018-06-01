#ifndef __utf8_h__
#define __utf8_h__

#include <stddef.h>

size_t utf8_char_block_length(char* ch)

char* utf8_char_advance(char* ch, size_t delta)

char* utf8_char_next(char* ch)

#endif
