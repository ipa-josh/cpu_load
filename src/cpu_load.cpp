/*
 * cpu_load.cpp
 *
 *  Created on: Nov 3, 2015
 *      Author: mig-em
 */


#include "process.h"
#include "calculate_load.h"
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
#include <unordered_set>

int main(int argc, char **argv)
{

  ros::init(argc, argv, "cpu_load");

  ros::NodeHandle n;

  ros::Publisher cpuload_pub = n.advertise<cpu_load::cpuload>("cpu_load", 1000);

  ros::Rate loop_rate(10);

  cpu_load::cpuload msg;

  CalculateLoad calculateLoad;
  calculateLoad.init();

  std::vector<uint8_t> vproc_load(argc-1);

  std::unordered_set<std::shared_ptr<Process>> processes;

  for (int i = 0; i < argc-1; i++)				//Count to argc-1 because number of arguments is argc-1
  {
	  processes.insert(std::make_shared<Process>(argv[i+1]));
  }

  for (auto proc : processes)
        	  {
      	  	  calculateLoad.getTimes(proc->proc_id_, proc->process_times_);
      	  	  proc->backupTimes();
        	  }

  ros::Duration(0.5).sleep();
  while (ros::ok())
  {
	  auto it = vproc_load.begin();
	  for (auto& proc : processes)
	  {
		  proc->backupTimes();
		  calculateLoad.getTimes(proc->proc_id_, proc->process_times_);
		  //ROS_INFO("%s : %lu\n", proc->proc_name_.c_str(), proc->process_times_->cpu_total_time);
		  //int process_exists = calculateLoad.getTimes(proc->proc_id_, proc->process_times_);
		  /*if (process_exists != 0)
		  {
			  std::for_each( processes.begin(), processes.end(), [](std::string v ) { printf("%s\n",v.c_str()); });
			  processes.erase(processes.find(proc));
			  ROS_INFO("The process %s was closed. (or didn't exist)\n", proc->proc_name_.c_str());
			  continue;
		  }*/
		  calculateLoad.calcLoad(proc->process_times_, proc->previous_process_times_, proc->user_load_, proc->sys_load_);
		  proc->addLoads();
		  *it = proc->load_;
		  it++;
		  //ROS_INFO("%s : %i, %i.\n", proc->proc_name_.c_str(), proc->u_load_, proc->s_load_);
	  }

	  msg.proc_load = vproc_load;
	  msg.total_load = calculateLoad.getCurrentValue();
	  msg.header.stamp = ros::Time::now();
	  cpuload_pub.publish(msg);
	  ros::spinOnce();
	  loop_rate.sleep();

  }

  return 0;
}
