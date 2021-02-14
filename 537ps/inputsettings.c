//Author: Tyler Johnston
#include <stdlib.h>
#include <stdio.h>
#include "inputsettings.h"

/*https://stackoverflow.com/questions/3774193/constructor-for-structs-in-c*/

/* Below was my original format for comments. Going forward style will be different.*/

// InputSettings* initInputSettings(int argc)
//
// Overview: This is a constructor that allocates memeory for the
// InputSettings structure. The flags are initialized to their
// default values.
//
// Parameters: int argc - The upper bound on how many pid can be passed
// from the command line.
//
// Return: Returns the pointer to the newly initialized structure.
InputSettings* initInputSettings(int argc){

        // Allocate memory for InputSettings, including its members.
        //TODO: check return value of malloc
        InputSettings* inset_ptr = malloc(sizeof(*inset_ptr)+ sizeof(long[argc]));
        inset_ptr->pid_count = 0;
        inset_ptr->max_length = argc;
        inset_ptr->flag_p = 0;
        inset_ptr->flag_s = 0;
        inset_ptr->flag_U = 1;
        inset_ptr->flag_S = 0;
        inset_ptr->flag_v = 0;
        inset_ptr->flag_c = 1;
        return inset_ptr;
}

/*
 *int addPIDInputSettings(InputSettings* inset_ptr, long pid)
 *	parameters:
 *		InputSettings* inset_ptr: Pointer to an InputSettings object to be
 *		added to.
 *		long pid: pid to be added to the InputSetting object's pid_list.
 *	return:
 *		int: 1 if array full, pid can't be added.
 *		    -1 if count outside size of array, 
 *		    0 on success.
 *	description:
 *		Adds a pid to the list of pids in the InputSettings object pointed
 *		to by inset_ptr.
 *
 *	NOTE: Nothing special will happen if a duplicate pid is provided.
 *	This will likely lead to duplicate results being printed for that pid.
 *	This is expected behavior.
 * 			
 */
int addPIDInputSettings(InputSettings* inset_ptr, long pid){
        // 1 if full,
	// -1 if count is outside range of array
	// 0 if pid successfully added to list
	int count = inset_ptr->pid_count;
	int max_length = inset_ptr->max_length;

	if (count == max_length){
		return 1;
	} else if (count > max_length || count < 0){
		return -1;
	} else {
		inset_ptr->list_pid[count] = pid;
		count = count + 1;
		inset_ptr->pid_count = count;
		return 0;
	}
}


/*
 *
 * int freeInputSettings(InputSettings* inset_ptr)
 * 	parameters:
 * 		InputSettings* inset_ptr: Pointer to an InputSettings object that
 * 		is to be freed from memory.
 * 	return:
 * 		int: 0 on success,
 * 		else, TBD.
 * 	description:
 *		Frees the memory allocated by the inset_ptr. 
 *
 */
int freeInputSettings(InputSettings* inset_ptr){
        //TODO Handle return value of free
	free(inset_ptr);
	return 0;

}

/*
 * HELPER FUNCTION FOR PERSONAL TESTING
 */
void printInputSettings(InputSettings* inset_ptr){
	printf("flag_p: %d\n", inset_ptr->flag_p);
	printf("flag_s: %d\n", inset_ptr->flag_s);
	printf("flag_U: %d\n", inset_ptr->flag_U);
	printf("flag_S: %d\n", inset_ptr->flag_S);
	printf("flag_v: %d\n", inset_ptr->flag_v);
	printf("flag_c: %d\n", inset_ptr->flag_c);
	printf("max_length of pid list: %d\n", inset_ptr->max_length);
	printf("pid_count: %d\n", inset_ptr->pid_count);
	for (int i = 0; i < inset_ptr->pid_count; i++){
		printf("list_pid[%d]: %ld\n", i, inset_ptr->list_pid[i]);
	}
}
