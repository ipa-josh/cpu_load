/*
 * get_cpu_load.h
 *
 *  Created on: Nov 3, 2015
 *      Author: mig-em
 */

#ifndef CPU_LOAD_INCLUDE_CPU_LOAD_CALCULATE_LOAD_H_
#define CPU_LOAD_INCLUDE_CPU_LOAD_CALCULATE_LOAD_H_

#include "pstat.h"

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "ros/ros.h"
#include "cpu_load/cpuload.h"
#include <memory>


class CalculateLoad {
public:
	CalculateLoad();
	~CalculateLoad();
	unsigned long long lastTotalUser, lastTotalUserLow, lastTotalSys, lastTotalIdle;
	void init();
	double getCurrentValue();
	int getTimes(const pid_t pid, struct pstat* result);
	void calcLoad(const struct pstat* cur_usage, const struct pstat* last_usage, int* ucpu_usage, int* scpu_usage);
};

#endif /* CPU_LOAD_INCLUDE_CPU_LOAD_CALCULATE_LOAD_H_ */
