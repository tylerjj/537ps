//Author: Tyler Johnston
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <getopt.h>
#include "inputsettings.h"
#include "optionhandler.h"

/*
 * Error Helper Function
 *	- Called when any legal flag other than -p is given an argument that isn't '-')
 */
static void errorInvalidNegation(int optopt){
        fprintf(stderr, "For option -%c, the only legal argument is %s\n", optopt, "-");
        exit(EXIT_FAILURE);
}

/*
 * 
 *	NOTE: This is a file in which I heavily leaned on outside source material to
 *	get to a working product. 
 *	The following link was my primary source, alongside the man page for getopt.
 *	I used both of their examples as templates to accomplish what I wanted for
 *	flag parsing.
 *
 *	https://azrael.digipen.edu/~mmead/www/mg/getopt/index.html 
 *
 */

/*
 * InputSettings* handleOptions(int argc, char* argv[])
 * 	parameters:
 * 		int argc: number of arguments in argv
 * 		char* argv[]: array of strings representing command line input.
 *	return:
 *		InputSettings*: returns a memory allocated pointer to an InputSettings
 *		object.
 *	description:
 *		Takes command line information, parses it for flags and pid args,
 *		and loads that information into an InputSettings object, to which a
 *		pointer is returned.
 *
 *	Note: Much of the code in the switch block seems repetitive. I probably could
 *	have done more to utilize helper functions there.
 *
 */
InputSettings* handleOptions(int argc, char* argv[]){
        int opt, pid;
	InputSettings* inset_ptr = initInputSettings(argc);
        while ((opt = getopt(argc, argv, "-:p:s::U::S::v::c::"))!= -1)
        {
                switch(opt)
                {
                        case 'p':
                                if (isdigit(optarg[0])){
                                        pid = atoi(optarg);
                                       //NOTE: Going to allow multiple -p with same pid to 
				       // add duplicate pids to the list of processes to be
				       // printed. 
                                        addPIDInputSettings(inset_ptr, pid);
                                        inset_ptr->flag_p = 1;
                                }
                                else {
                                        fprintf(stderr, "Option -p was provided an invalid argument.\n");
                                        fprintf(stderr, "For [-p pid], pid is a positive integer value.\n");
                                        exit(EXIT_FAILURE);
                                }
                               // printf("Option p was provided \n");
                                break;
                        case 's':
                                if (optarg){
                                        if (strcmp(optarg,"-")==0){
                                                inset_ptr->flag_s = 0;
                                        }
                                        else {
                                                errorInvalidNegation(optopt);
                                        }
                                }
                                else {
                                        inset_ptr->flag_s = 1;
                                }
                               // printf("Option s was provided \n");
                                break;
                        case 'U':
                                if (optarg){
                                        if (strcmp(optarg, "-")==0){
                                                inset_ptr->flag_U = 0;
                                        }
                                         else {
                                                errorInvalidNegation(optopt);
                                        }
                                }
                                else {
                                        inset_ptr->flag_U = 1;
                                }
                               // printf("Option U was provided \n");
                                break;
                        case 'S':
                                if (optarg){
                                        if (strcmp(optarg, "-")==0){
                                                inset_ptr->flag_S = 0;
                                        }
                                        else {
                                                errorInvalidNegation(optopt);
                                        }
                                }
                                else {
                                        inset_ptr->flag_S = 1;
                                }
                               // printf("Option S was provided \n");
                                break;
                        case 'v':
                                if (optarg){
                                        if (strcmp(optarg, "-")==0){
                                                inset_ptr->flag_v = 0;
                                        }
                                        else {
                                                errorInvalidNegation(optopt);
                                        }
                                }
                                else {
                                        inset_ptr->flag_v = 1;
                                }
                                printf("Option v was provided \n");
                                break;
                        case 'c':
                                if (optarg){
                                        if (strcmp(optarg, "-")==0){
                                                inset_ptr->flag_c = 0;
                                        }
                                        else {
                                                errorInvalidNegation(optopt);
                                        }
                                }
                                else {
                                        inset_ptr->flag_c = 1;
                                }
                               // printf("Option c was provided \n");
                                break;
                        case ':':
                                fprintf(stderr, "Option -%c is missing a required argument.\n", optopt);
                                 exit(EXIT_FAILURE);
                        default:
                                fprintf(stderr, "Usage: %s [-p pid] [-s] [-U] [-S] [-v] [-c] \n", argv[0]);
                                exit(EXIT_FAILURE);
                }
               // printf("Optarg value: %s\n", optarg);
        }
	return inset_ptr;
}
