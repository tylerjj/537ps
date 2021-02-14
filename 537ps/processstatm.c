//Author: Tyler Johnston
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processstatm.h"

ProcessStatm* parseStatm(char* pid){
	FILE* file;
	const int size_file = 100000;
	char buffer[size_file];
//	char* buffer;
//	long size_file;

	// proc/[pid]/status shouldn't exceed 1000 characters.
        char filepath[1000];
        char* parse_file = "/statm";

        strcpy(filepath, "/proc/");
        strcat(filepath, pid);
        strcat(filepath, parse_file);


	file = fopen(filepath, "r");
//	fseek(file, 0, SEEK_END);
//	size_file = ftell(file);
//	fseek(file, 0, SEEK_SET);

//	buffer = (char*) calloc(size_file, sizeof(char));

	fread(buffer, sizeof(char), size_file, file);

	fclose(file);

	ProcessStatm* psm = malloc(sizeof(*psm));
	sscanf(buffer, "%lu %lu %lu %lu %d %lu %d", &psm->size, &psm->resident, &psm->shared, &psm->text, &psm->lib, &psm->data, &psm->dt);
//	free(buffer);
	return psm;
}
