cmake_minimum_required(VERSION 2.8.3)
project(cpu_load)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
)

link_directories(
	${catkin_LIBRARY_DIRS}
	include
	)

add_message_files(
  FILES
  cpuload.msg
)

 generate_messages(
   DEPENDENCIES
   std_msgs
 )


catkin_package(
  INCLUDE_DIRS include
  LIBRARIES cpu_load
  CATKIN_DEPENDS roscpp std_msgs message_runtime
  DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  include
)


add_executable(
	cpu_load 
	src/cpu_load.cpp
	src/process.cpp
	src/calculate_load.cpp
	)


add_dependencies(cpu_load ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
 target_link_libraries(cpu_load
   ${catkin_LIBRARIES}
 )
