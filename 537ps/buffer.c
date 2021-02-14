// Author: Tyler Johnston
#include <stdlib.h>
#include <stdio.h>
#include "buffer.h"

/*
 *	NOTE: These methods are implemented effectively using a template found
 *	in a stackoverflow response regarding dynamic arrays within malloced
 *	structs. 
 *	
 *	Peter Mortensen's respsonse in the following link is a heavy influence
 *	on both this file, and processdata.c.
 *	https://stackoverflow.com/questions/260915/how-can-i-create-a-dynamically-sized-array-of-structs
 *
 */

/*
 *
 * Buffer* initBuffer(int size)
 *
 * 	parameters:
 * 		int size: initial size of Buffer.
 * 	return:
 * 		Buffer* : pointer to a Buffer object.
 * 	description:
 * 		Initializes a Buffer object to contain
 * 		a char* array buff of size 'size'. 
 * 		
 */
Buffer* initBuffer(int size) {
	// TODO: check return value of malloc and handle it
	Buffer* b_ptr = malloc(sizeof(Buffer));
	b_ptr->size = size;
	b_ptr->count = 0;
	//TODO: check return value of malloc and handle it
	b_ptr->buff = malloc(sizeof(char)*size);
	return b_ptr;
}

/*
 *
 * void addToBuffer(Buffer* b, char c)
 *
 * 	parameters:
 * 		Buffer* b: pointer to a Buffer object that is to be added to.
 * 		char c: character to be added to the Buffer.
 * 	description:
 * 		Reallocates more space in the char* array that b->buff points to
 * 		in the case that b->count is greater than or equal to b->size, 
 * 		and increases b->size.
 * 		Adds c to b->buff[count]. Increments b->count.
 *
 */
void addToBuffer(Buffer* b, char c){
	if (b->count >= b->size){
		b->size = b->size * 2;
		//TODO: check return value of realloc and handle it
		void* expanded_list = realloc(b->buff,sizeof(char)*(b->size));
		b->buff = (char*)expanded_list;
	}
	b->buff[b->count] = c;
	b->count = b->count + 1;
}

/*
 *
 * void freeBuffer(Buffer* b)
 *
 * 	parameters:
 * 		Buffer* b: pointer to a Buffer object that is to be freed
 * 		from memory.
 * 	description:
 * 		First frees the memory of the char* member buff, belonging to
 * 		the Buffer objected that b points to. Next, b is freed from
 * 		memory. 
 * 
 */

void freeBuffer(Buffer* b){
	//TODO: check returns of both free calls and handle any unexpected
	//behavior.
	free(b->buff);
	free(b);
}

