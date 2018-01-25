/**-------------------------------------
	base64.h
	
	encode/decode functions heather file
----------------------------------------*/

#ifndef BASE64_H
#define BASE64_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


void encode(char *s_string, size_t s_size, char *d_string, size_t d_size);
void decode(char *s_string, size_t s_size, char *d_string, size_t d_size);

#endif
