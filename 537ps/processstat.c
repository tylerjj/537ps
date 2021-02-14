//Author: Tyler Johnston
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /*strcpy*/
#include "processstat.h"

ProcessStat* parseStat(char* pid){
        FILE* file;
	int size_file = 100000;
	char buffer[size_file];

	// proc/[pid]/stat shouldn't exceed 1000 characters.
        char filepath[1000];
        char* parse_file = "/stat";

        //TODO: check return values of all three below functions.
       	strcpy(filepath, "/proc/");
        strcat(filepath, pid);
        strcat(filepath, parse_file);


        //TODO: error check
        file = fopen(filepath, "r");

        // https://www.tutorialspoint.com/c_standard_library/c_function_fread.htm
        // buffer: ptr to block of memory with minimum size of
        // sizeof(char)*size_file bytes
        //
        // sizeof(char): size in bytes of each element to be read
        //
        // size_file: number of elements, each one with a size of
        // sizeof(char) bytes.
        //
        // file: this is the pointer to a file object that specifies
        // an input stream.
        fread(buffer, sizeof(char), size_file, file);
	fclose(file);
        //printf("The file called \"stat\" contains this text:\n\n%s", buffer);
	//TODO check if return of malloc is unexpected, if so ___?
        ProcessStat* ps = malloc(sizeof(*ps));
	int total_read;        

	/* For some reason the following chunk of code wasn't working. It would stop after the first argument.*/
	//total_read = sscanf(buffer,"%d %s %c %d %d %d %d %d %u %lu %lu %lu %lu %lu %lu %ld %ld %ld %ld %ld %ld %llu %lu %ld %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %d %d %u %u %llu %lu %ld %lu %lu %lu %lu %lu %lu %lu %d", &ps->pid, ps->comm, &ps->state, &ps->ppid, &ps->pgrp, &ps->session, &ps->tty_nr, &ps->tpgid, &ps->flags, &ps->minflt, &ps->cminflt, &ps->majflt, &ps->majflt, &ps->utime, &ps->stime, &ps->cutime, &ps->cstime, &ps->priority, &ps->nice, &ps->num_threads, &ps->itrealvalue, &ps->starttime, &ps->vsize, &ps->rss, &ps->rsslim, &ps->startcode, &ps->endcode, &ps->startstack, &ps->kstkesp, &ps->kstkeip, &ps->signal, &ps->blocked, &ps->sigignore, &ps->sigcatch, &ps->wchan, &ps->nswap, &ps->cnswap, &ps->exit_signal, &ps->processor, &ps->rt_priority, &ps->policy, &ps->delayacct_blkio_ticks, &ps->guest_time, &ps->cguest_time, &ps->start_data, &ps->end_data, &ps->start_brk, &ps->arg_start, &ps->arg_end, &ps->env_start, &ps->env_end, &ps->exit_code);
//      printf("Total Amount Read in buffer: %d\n", total_read);
//	printf("pid %d\ncomm %s\nstate %c\nutime %lu\nstime %lu\n", ps->pid, ps->comm, ps->state, ps->utime, ps->stime);
	
	//https://www.thecodingforums.com/threads/assignment-suppression-in-sscanf.721569/
	total_read = sscanf(buffer, "%d %*s %c %*d %*d %*d %*d %*u %*u %*u %*u %*u %*u %lu %lu", &ps->pid, &ps->state, &ps->utime, &ps->stime);

	if (total_read != 4){
		printf("Total Amount Read in Buffer: %d\n", total_read);
	}
	//printf("pid %d state %c utime %lu stime %lu\n",ps->pid, ps->state, ps->utime, ps->stime);
	return ps;
}
