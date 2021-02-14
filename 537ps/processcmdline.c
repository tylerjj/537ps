//Author: Tyler Johnston
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /*strcpy*/
#include "processcmdline.h"
#include "buffer.h"

/*
 * Buffer* parseCmdline(char* pid)
 * 	parameters:
 * 		char* pid: pid string specifying the process whose
 * 		cmdline is to be parsed.
 * 	return:
 * 		Buffer*: Returns a memory allocated pointer to a Buffer object,
 * 		containing the parsed cmdline file's data. (cmdline's '\0' 
 * 		char values are replaced with whitespace chars ' '). 
 * 	description:
 * 		Parses /proc/[pid]/cmdline and stores that information in a
 * 		Buffer that is referenced by a memory allocated pointer.
 * 		(I hope that terminology is correct. I have a feeling I might
 * 		mean it the other way around.)
 */
Buffer* parseCmdline(char* pid){

	FILE* file;
	// Arbitrarily large file size. Chances are this isn't ok.
	// Not sure what I should do as an alternative.
	const int size_file = 100000;

	Buffer* buffer = initBuffer(size_file);;
	
	// If I weren't running low on time, I would turn this into its own function. 
	// proc/[pid]/status shouldn't exceed 1000 characters.
        char filepath[1000];
        char* parse_file = "/cmdline";
        strcpy(filepath, "/proc/");
        strcat(filepath, pid);
        strcat(filepath, parse_file);
	
	//TODO if file is NULL, then do _____
	file = fopen(filepath, "r");
	
	int c;
	for (int i = 0; i < size_file; i++){
		c = fgetc(file);
		if (c == EOF){
			buffer->buff[i-1] = '\0';
			break;
		}
		else if (c == '\0'){
			if ((i+1)!=size_file){
				c = ' ';
			}
		}
		addToBuffer(buffer, c);
	}
	//TODO if file can't close, then do ______
	fclose(file);

	return buffer;

}
