//Author: Tyler Johnston
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processdata.h"
#include "processstatus.h"
#include "processstat.h"
#include "processstatm.h"
#include "processcmdline.h"
#include "buffer.h"
#include <string.h> /*strtok */
#include <sys/types.h> /* getuid */
#include <unistd.h> /*getuid*/
#include <dirent.h> /* dirent */ 
#include <errno.h> /*errno*/
#include <ctype.h> /*isdigit*/

void loadProcessData(ProcessData* pd, char* pid){
	ProcessStat* ps = parseStat(pid);
	ProcessStatm* psm = parseStatm(pid);
	Buffer* cmdline = parseCmdline(pid);
	pd->pid = atoi(pid);
	pd->state = ps->state;
	pd->utime = ps->utime;
	pd->stime = ps->stime;
	pd->vmem = psm->size;
	pd->cmdline = malloc(sizeof(char)*cmdline->count);
	strncpy(pd->cmdline, cmdline->buff, cmdline->count);
	free(ps);
	free(psm);
	freeBuffer(cmdline);
}


ProcessList* handleProc(long* list_pid, int pid_count){
	// Started off running the following example on ssh to learn how readdir
	// worked, and then started editing it to navigate /proc.
	// I probably could've done more to make this method distinctly
	// my own, but time is running short. 
	// https://www.badprog.com/unix-gnu-linux-system-calls-readdir
        
	DIR *myDirectory;
        struct dirent *myFile;

        // The list of processes that we retrieve from proc.
	int list_size;
	if (pid_count > 0){
		list_size = pid_count;
	} else {
		list_size = 100;
	}
        ProcessList* pd_list = initProcessList(list_size);
	 // Get current user id
        long current_uid = (long) getuid();
        //printf("parseProc: get current_uid: %ld\n", current_uid);
       	
	// Open /proc
	myDirectory = opendir("/proc");

        // If this directory was successfully opened.
        if (myDirectory) {
                //puts("Ok the directory is opened, let's see its files:");
                // Start iterating through all the files/directories in /proc
                while ((myFile = readdir(myDirectory))){
			// Get current file/directory name in /proc
                        char* d_name = myFile->d_name;
                       // printf("Current file/directory: %s\n", d_name);
			
			int length = strlen(d_name);
			int isprocess = 1;
			for (int i = 0; i < length; i++){
				if (!isdigit(d_name[i])){
					isprocess = 0;	
				}
				
			}
			if (isprocess == 0){
				continue;
			}

                        // THIS IS A PROCESS.
                        // Case 1: (if pid_count > 0, get specified processes)
			// 	Then see if atol(d_name) is in list_pid.
			// 	If d_name in list_pid:
			//		Create new ProcessData object.
			//		Create new ProcessStat object.
			//		Create new ProcessStatm object.
			//		Create new char* cmdline. 
			//		Put the Stat, Statm, and cmdline 
			//		data into ProcessData object.
			//		Add ProcessData object to pd_list.
			if (pid_count > 0) {
				//puts("flag_p is on.\n");
				for (int i = 0; i < pid_count; i++){
					if (list_pid[i] == (atoi(d_name))){
						//Build&Add pd to pd_list
						ProcessData* pd = initProcessData();
						loadProcessData(pd,d_name);
						addPDProcessList(pd_list, pd);
						
						break;
					}
				}
			}
			else {
			// Case 2: (Getting all user processes)
                       	//      if (current_uid == parseStatusForUID(d_name))
                        //              Create new ProcessData object
                        //              Create new ProcessStat object
                        //              Create new char* cmdline.
                        //              Put the Stat, Statm, and cmdline
                        //              data into ProcessData object.
                        //              Add ProcessData object to pd_list.
				long process_uid;
			        process_uid = parseStatusForUID(d_name);
				if (current_uid == process_uid){
					//printf("User owns process %s\n", d_name);
					ProcessData* pd = initProcessData();
					//printf("Loading Process Data to %ld\n",process_uid);
					loadProcessData(pd, d_name);
					//printf("Adding Process %d to Process List.\n", pd->pid);
					addPDProcessList(pd_list, pd);
				}
			}
		}
                // Close /proc
                if (closedir(myDirectory) == 0){
                       // puts("The directory is now closed.");
                }
                else {
                        puts("The directory can not be closed.");
		}
	}
        else if (errno == ENOENT) {
                puts("This directory does not exist.");
        }
        else if (errno == ENOTDIR){
                puts("This file is not a directory.");
        }
        else if (errno == EACCES){
                puts("You do not have the right to open this folder.");
                puts("That's a new error, check the manual.");
        }

	return pd_list;
}

