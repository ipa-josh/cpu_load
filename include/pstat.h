/*
 * pstat.h
 *
 *  Created on: Nov 4, 2015
 *      Author: mig-em
 */

#ifndef CPU_LOAD_INCLUDE_CPU_LOAD_PSTAT_H_
#define CPU_LOAD_INCLUDE_CPU_LOAD_PSTAT_H_

struct pstat {
    long unsigned int utime_ticks;
    long int cutime_ticks;
    long unsigned int stime_ticks;
    long int cstime_ticks;
    long unsigned int vsize; // virtual memory size in bytes
    long unsigned int rss; //Resident  Set  Size in bytes

    long unsigned int cpu_total_time;
};

#endif /* CPU_LOAD_INCLUDE_CPU_LOAD_PSTAT_H_ */
