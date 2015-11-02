#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "ros/ros.h"
#include "cpu_load/cpuload.h"


static unsigned long long lastTotalUser, lastTotalUserLow, lastTotalSys, lastTotalIdle;


void init(){
    FILE* file = fopen("/proc/stat", "r");
    fscanf(file, "cpu %llu %llu %llu %llu", &lastTotalUser, &lastTotalUserLow,
        &lastTotalSys, &lastTotalIdle);
    fclose(file);
    }


double getCurrentValue(){
    double percent;
    FILE* file;
    unsigned long long totalUser, totalUserLow, totalSys, totalIdle, total;


    file = fopen("/proc/stat", "r");
    fscanf(file, "cpu %llu %llu %llu %llu", &totalUser, &totalUserLow,
        &totalSys, &totalIdle);
    fclose(file);


    if (totalUser < lastTotalUser || totalUserLow < lastTotalUserLow ||
        totalSys < lastTotalSys || totalIdle < lastTotalIdle){
        //Overflow detection. Just skip this value.
        percent = -1.0;
    }
    else{
        total = (totalUser - lastTotalUser) + (totalUserLow - lastTotalUserLow) +
            (totalSys - lastTotalSys);
        percent = total;
        total += (totalIdle - lastTotalIdle);
        percent /= total;
        percent *= 100;
    }


    lastTotalUser = totalUser;
    lastTotalUserLow = totalUserLow;
    lastTotalSys = totalSys;
    lastTotalIdle = totalIdle;


    return percent;
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "cpu_load");

  ros::NodeHandle n;

  ros::Publisher cpuload_pub = n.advertise<cpu_load::cpuload>("cpu_load", 1000);

  ros::Rate loop_rate(10);

  init();

  int count = 0;
  while (ros::ok())
  {

    cpu_load::cpuload msg;

    msg.load = getCurrentValue();
    msg.header.stamp = ros::Time::now();


    //ROS_INFO("%s", msg.load);


    cpuload_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
