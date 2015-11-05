/*
 * process.h
 *
 *  Created on: Nov 3, 2015
 *      Author: mig-em
 */

#ifndef CPU_LOAD_INCLUDE_CPU_LOAD_PROCESS_H_
#define CPU_LOAD_INCLUDE_CPU_LOAD_PROCESS_H_

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



class Process {
public:
	Process();
	~Process();
	Process(std::string proc_name);

	inline bool operator ==(const Process& p1)
		{
			if (p1.proc_id_ == proc_id_) return true;
			else return false;
		}


	pstat* process_times_ = new pstat;
	pstat* previous_process_times_ = new pstat;
	int u_load_ = 0;
	int s_load_ = 0;
	int load_ = 0;
	int* user_load_ = &u_load_;
	int* sys_load_ = &s_load_;
	std::string proc_name_;
	int proc_id_ = 0;
	int getProcIdByName(std::string proc_name);
	void backupTimes() { *previous_process_times_ = *process_times_; }
	void addLoads() { load_ = u_load_ + s_load_; };
};

namespace std {
	template<>
	struct hash<Process>{

		size_t operator()(const Process& p1) const noexcept
				{
					size_t hash_key = p1.proc_id_;
					return hash_key;
				}
	};

}

#endif /* CPU_LOAD_INCLUDE_CPU_LOAD_PROCESS_H_ */
