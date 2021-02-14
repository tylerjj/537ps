//Author: Tyler Johnston
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processstatus.h"

long parseStatusForUID(char* pid){
        FILE* file;
        // I didn't want to use a constant, but
        // fseek/ftell doesn't work on /proc files.
        const int size_file = 100000;
        char buffer[size_file];

        //char* buffer;
        //long size_file;
        // proc/[pid]/status shouldn't exceed 1000 characters.
        char filepath[1000];
        char* parse_file = "/status";

        strcpy(filepath, "/proc/");
        strcat(filepath, pid);
        strcat(filepath, parse_file);

        //printf("parseStatusForUID: filepath to be parsed: %s\n", filepath);

        //file = fopen("status", "r");
        file = fopen(filepath, "r");

        if (file == NULL){
                printf("filepath: %s could not be opened\n", filepath);
                exit(EXIT_FAILURE);
        }

        //fseek(file, 0, SEEK_END);
        //size_file = ftell(file);
        //fseek(file, 0, SEEK_SET);

        //buffer = (char*)calloc(size_file, sizeof(char));

        long uid = -1;
        //TODO WHY IS THIS RETURNING 0????
        //printf("Size_file: %ld\n", size_file);
        while (fgets(buffer, size_file, file) != NULL){
                //https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm
                char* token = strtok(buffer,"\t");
                while (token != NULL){
                        //printf("Token: %s\n", token);
                        if (strcmp(token, "Uid:")==0){
                                char* uid_val = strtok(NULL, "\t");
                                uid = atol(uid_val);
                                break;
                        }
                        else {
                                token = strtok(NULL, "\t");
                        }
                }
                if (uid >= 0){
                        break;
                }
        }
        fclose(file);
        //free(buffer);
        return uid;
}
