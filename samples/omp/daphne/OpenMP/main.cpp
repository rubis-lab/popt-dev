/**
 * Author:  Florian Stock, Technische Universität Darmstadt,
 * Embedded Systems & Applications Group 2018
 * License: Apache 2.0 (see attachached File)
 */
#include <chrono>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <rts/core/pts.hpp>
#include "benchmark.h"

std::chrono::high_resolution_clock::time_point start,end;
std::chrono::duration<double> elapsed;
std::chrono::high_resolution_clock timer;
bool isPaused = false;

// how many testcases should be executed in sequence (before checking for correctness)
int pipelined = 1;

extern kernel& eucKernel;
extern kernel& ndtKernel;
extern kernel& p2iKernel;


// void pause_timer()
// {
//   end = timer.now();
//   elapsed += (end-start);
//   isPaused = true;
// }  

// void unpause_timer() 
// {
//   isPaused = false;
//   start = timer.now();
// }

void usage(char *exec)
{
  std::cout << "Usage: \n" << exec << " [-p N]\nOptions:\n  -p N   executes N invocations in sequence,";
  std::cout << "before taking time and check the result.\n";
  std::cout << "         Default: N=1\n";
}

int main(int argc, char **argv) {

  if ((argc != 1) && (argc !=  3))
    {
      usage(argv[0]);
      exit(2);
    }
  if (argc == 3)
    {
      if (strcmp(argv[1], "-p") != 0)
	{
	  usage(argv[0]);
	  exit(3);
	}
      errno = 0;
      pipelined = strtol(argv[2], NULL, 10);
      if (errno || (pipelined < 1) )
	{
	  usage(argv[0]);
	  exit(4);
	}
      std::cout << "Invoking kernel " << pipelined << " time(s) per measure/checking step\n";
      
    }
    // read input data

    //euc
    std::cout << "invoking euc" << std::endl;
    eucKernel.init();
    eucKernel.run(pipelined);
    if (eucKernel.check_output()) {
	    std::cout << "result ok\n";
    } else {
        std::cout << "error: wrong result\n";
    }

    //ndt  
    std::cout << "invoking ndt" << std::endl;
    ndtKernel.init();
    ndtKernel.run(pipelined);
    if (ndtKernel.check_output()) {
	    std::cout << "result ok\n";
    } else {
        std::cout << "error: wrong result\n";
    }

    //p2i
    std::cout << "invoking p2i" << std::endl;
    p2iKernel.init();
    p2iKernel.run(pipelined);
    if (p2iKernel.check_output()) {
	    std::cout << "result ok\n";
    } else {
        std::cout << "error: wrong result\n";
    }
}

// std::cout << "invoking ndt" << std::endl;
//     ndtKernel.set_timer_functions(pause_timer, unpause_timer);
//     ndtKernel.init();
//     start = timer.now();
//     ndtKernel.run(pipelined);
//     if (!isPaused) {
// 	    end = timer.now();
//     	elapsed += end-start;
//     }
//     std::cout <<  "elapsed time: "<< elapsed.count() << " seconds, average time per testcase (#"
// 	      << ndtKernel.testcases << "): " << elapsed.count() / (double) ndtKernel.testcases
// 	      << " seconds" << std::endl;
//     if (ndtKernel.check_output()) {
// 	    std::cout << "result ok\n";
//     } else {
//         std::cout << "error: wrong result\n";
//     }