//Author: Tyler Johnston
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processdata.h"


/*
 * ProcessData* initProcessData()
 * 	return:
 * 		ProcessData*: Returns a memory allocated pointer to a ProcessData object.
 * 	description:
 * 		Initializes a memory allocated pointer to a ProcessData object.
 * 		Sets that object's default values. Returns the pointer.
 */
ProcessData* initProcessData()
{
	//TODO: check malloc return value, if unexpected, do _____?
        ProcessData* pd_ptr = malloc(sizeof(*pd_ptr)+sizeof(strlen(pd_ptr->cmdline)));
        pd_ptr->pid = -1;
        pd_ptr->state = '\0';
        pd_ptr->utime = -1;
        pd_ptr->stime = -1;
        pd_ptr->vmem = -1;
        pd_ptr->cmdline = NULL;
        return pd_ptr;
}

/*
 * void freeProcessData(ProcessData* pd)
 * 	parameter:
 * 		ProcessData* pd: Memory allocated pointer to a ProcessData object.
 * 	description:
 * 		If ProcessData object has a malloced cmdline member, free it.
 * 		Then, free the memory allocated ProcessData pointer. 
 * 		
 */
void freeProcessData(ProcessData* pd){
	if (pd->cmdline != NULL){
		//TODO: check free return value, if unexpected, do _____?
		free(pd->cmdline);
	}
	//TODO: check free return value, if unexpected, do _____?
        free(pd);
}

/*
 * EXTRANEOUS FUNCTION: NOT NECESSRARY FOR P01.
 * Was utilized only in testing.
 */
void printProcessData(ProcessData* pd) {
        printf("%d: ", pd->pid);
	if (pd->state != '\0'){
                printf("%c ", pd->state);
        }
        if (pd->utime >= 0){
                printf("utime=%ld ", pd->utime);
        }
        if (pd->stime >= 0){
                printf("stime=%ld ", pd->stime);
        }
        if (pd->vmem >= 0){
                printf("vmem=%ld ", pd->vmem);
        }
        if (pd->cmdline){
                printf("[%s] ", pd->cmdline);
        }
        printf("\n");
}

/*
 * ProcessList* initProcessList
 * 	parameters:
 * 		int size: size of ProcessData array to be memory allocated.
 * 	return:
 * 		Returns a memory allocated pointer to a ProcessList object.
 * 	description:
 * 		Create a pointer to a ProcessList with allocated memory.
 * 		Set default values for that ProcessList.
 * 		Set size to be size.
 * 		Create a pointer to an memory allocated array of ProcessData
 * 		objects.
 */ 
ProcessList* initProcessList(int size){
	// TODO: Check malloc return value, if unexpected, do ____?
        ProcessList* pl_ptr = malloc(sizeof(ProcessList));
        pl_ptr->size = size;
        pl_ptr->count = 0;
	// TODO: Check malloc return value, if unexpected, do ____?
        pl_ptr->pd_list = malloc(sizeof(ProcessData*)*size);
        return pl_ptr;
}

// https://stackoverflow.com/questions/23019576/how-we-can-insert-array-elements-when-array-size-is-already-fixed-in-c

/*QUICKDOC
 *	Adds memory allocated process data to a memory allocated process list.
 *	Return 0 on success. 
 */
int addPDProcessList(ProcessList* pl, ProcessData* pd){
        /* this might not work if size is 0 */
        int count = pl->count;
        int size = pl->size;

        if (count >= size) {
                size = size * 2;
                // Heavily leaned on example from stackoverflow here due to many errors.
                //https://stackoverflow.com/questions/260915/how-can-i-create-a-dynamically-sized-array-of-structs
                //TODO if realloc returns unexpected value, do _____?
	       	void* expanded_list = realloc(pl->pd_list, sizeof(ProcessData*)*size);
                pl->size = size;
                pl->pd_list = (ProcessData**)expanded_list;
                pl->pd_list[count] = pd;
        }
        pl->pd_list[count] = pd;
        ++pl->count;
	//printProcessData(pl->pd_list[count]);
	return 0;
}

/* QUICKDOC
 *	Frees each process data object in the list, and then frees the list.
 */
void freeProcessList(ProcessList* pl){
        for (int i = 0; i < pl->count; i++){
                freeProcessData(pl->pd_list[i]);
        }
	//TODO: if free turns unexpected value, do _____?
        free(pl);
}

/*
 * EXTRANEOUS FUNCTION: NOT NECESSRARY FOR P01.
 * Was utilized only in testing.
 */
void printProcessList(ProcessList* pl){
	printf("Printing Process List:\n");
	printf("List size: %d\n", pl->size);
	printf("List element count: %d\n", pl->count);
        for (int i = 0; i < pl->count;i++){
        	printProcessData(pl->pd_list[i]);
        }
}
