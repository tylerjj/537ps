//Author: Tyler Johnston
#ifndef PROCESSSTAT
#define PROCESSSTAT

typedef struct {
        int pid;
        char* comm;
        char state;
        int ppid;
        int pgrp;
        int session;
        int tty_nr;
        int tpgid;
        unsigned int flags;
        unsigned long minflt;
        unsigned long cminflt;
        unsigned long majflt;
        unsigned long cmajflt;
        unsigned long utime;
        unsigned long stime;
        long int cutime;
        long int cstime;
        long int priority;
        long int nice;
        long int num_threads;
        long int itrealvalue;
        unsigned long long starttime;
        unsigned long vsize;
        long int rss;
        unsigned long rsslim;
        unsigned long startcode;
        unsigned long endcode;
        unsigned long startstack;
        unsigned long kstkesp;
        unsigned long kstkeip;
        unsigned long signal;
        unsigned long blocked;
        unsigned long sigignore;
        unsigned long sigcatch;
        unsigned long wchan;
        unsigned long nswap;
        unsigned long cnswap;
        int exit_signal;
        int processor;
        unsigned int rt_priority;
        unsigned int policy;
        unsigned long long delayacct_blkio_ticks;
        unsigned long guest_time;
        long int cguest_time;
        unsigned long start_data;
        unsigned long end_data;
        unsigned long start_brk;
        unsigned long arg_start;
        unsigned long arg_end;
        unsigned long env_start;
        unsigned long env_end;
        int exit_code;
}ProcessStat;

ProcessStat* parseStat(char* pid);

#endif
