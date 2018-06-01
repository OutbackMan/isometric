#include "utf8.h"

size_t utf8_char_block_length(unsigned char ch)
{
	if (ch & 0xc0 == 0x00) {
		return 1;		
	} else if (ch >> 5 == 0x06) {
		return 2;		
	} else if (ch >> 4 == 0x0e) {
		return 3;	
	} else if (ch >> 3 == 0x1e) {
		return 4;		
	} else {
		return 0;		
	}
}

char* utf8_char_next(char* ch)
{
	size_t block_length = utf8_char_block_length(ch);	

	if (block_length == 0) {
		return 0;
	} else {
		for (size_t block_index = 0; block_index < block_length; ++block_index) {
			++ch;			
		}		
	}

	return ch;
}

char* utf8_char_advance(char* ch, size_t delta)
{
	for (size_t utf8_char_index = 0; utf8_char_index < delta && ch[utf8_char_index] != '\0'; ++utf8_char_index) {
		ch = utf8_next_char(ch);
	}

	return ch;
}
