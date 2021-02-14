//Author: Tyler Johnston
#include <stdio.h>
#include "processdata.h"
#include "inputsettings.h"

/*
 * void displayOutput(InputSettings* inset, ProcessList* pl)
 * 	
 * 	parameters:
 * 		InputSettings* inset:
 * 		ProcessList* pl:
 *
 *	description:
 *		Displays output for each process in the ProcessList pointed to by
 *		pl. This output is enabled/disabled in parts by InputSettings
 *		flags.
 */
void displayOutput(InputSettings* inset, ProcessList* pl){
	for (int i = 0; i < pl->count; i++){
		ProcessData* pd = pl->pd_list[i];
		printf("%d: ", pd->pid);
        	if (inset->flag_s){
                	printf("%c ", pd->state);
       		}
        	if (inset->flag_U){
                	printf("utime=%ld ", pd->utime);
        	}	
        	if (inset->flag_S){
                	printf("stime=%ld ", pd->stime);
        	}
        	if (inset->flag_v){
                	printf("vmem=%ld ", pd->vmem);
        	}
       		if (inset->flag_c){
                	printf("[%s] ", pd->cmdline);
       	 	}
	        printf("\n");
	}
}
