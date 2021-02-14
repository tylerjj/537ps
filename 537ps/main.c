//Author: Tyler Johnston
#include <stdio.h>
#include <stdlib.h>
#include "inputsettings.h"
#include "optionhandler.h"
#include "processdata.h"
#include "prochandler.h"
#include "outputprinter.h"


int main(int argc, char *argv[]){
	
	// Get input settings.
	InputSettings* inset_ptr = handleOptions(argc, argv);
	// Get process data.
	ProcessList* pd_list_ptr = handleProc(inset_ptr->list_pid, inset_ptr->pid_count); 


/* The following commented code will display all process data as if all flags were
 * set to true.
 */	

//	printf("Process List: All Data\n");
//	printProcessList(pd_list_ptr);
//	printf("\n");
//	printf("Process List: Custom Input\n");

	// Display output.
	displayOutput(inset_ptr, pd_list_ptr);
	
	// Free memory of input settings.
	freeInputSettings(inset_ptr);
	// Free memory of process data list
	freeProcessList(pd_list_ptr);
	return 0;
}
