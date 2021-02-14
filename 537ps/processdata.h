//Author: Tyler Johnston
#ifndef PROCESSDATA
#define PROCESSDATA

typedef struct {
        /* I'm assuming that max_pid size is
          * approx = to 4,000,000. Well within the
          * max range of an signed int.
          */
        int pid;
        char state;
        long utime;
        long stime;
        long vmem;
        char* cmdline;

}ProcessData;

typedef struct {
        int size;
        int count;
        ProcessData** pd_list;
}ProcessList;

ProcessData* initProcessData();
void freeProcessData(ProcessData* pd);
void printProcessData(ProcessData* pd);

ProcessList* initProcessList(int size);
int addPDProcessList(ProcessList* pl, ProcessData* pd);
void freeProcessList(ProcessList* pl);
void printProcessList(ProcessList* pl);

#endif
