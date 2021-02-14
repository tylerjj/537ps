//Author: Tyler Johnston
#ifndef PROCESSSTATM
#define PROCESSSTATM

typedef struct {
	unsigned long size;
	unsigned long resident;
	unsigned long shared;
	unsigned long text;
	int lib;
	unsigned long data;
	int dt;

}ProcessStatm;

ProcessStatm* parseStatm(char* pid);

#endif
