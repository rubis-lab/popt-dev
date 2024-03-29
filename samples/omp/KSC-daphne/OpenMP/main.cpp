/**
 * Author:  Florian Stock, Technische Universität Darmstadt,
 * Embedded Systems & Applications Group 2018
 * License: Apache 2.0 (see attachached File)
 */
#include <chrono>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <cstdlib>
#include <rts/core/pts.hpp>
#include "benchmark.h"
#include "seq_log.hpp"
#include "omp_log.hpp"

std::chrono::high_resolution_clock::time_point start,end;
std::chrono::duration<double> elapsed;
std::chrono::high_resolution_clock timer;
bool isPaused = false;

// how many testcases should be executed in sequence (before checking for correctness)
int pipelined = 1;

extern kernel& eucKernel;
extern kernel& ndtKernel;
extern kernel& p2iKernel;

void usage(char *exec)
{
  std::cout << "Usage: \n" << exec << " [-p N]\nOptions:\n  -p N   executes N invocations in sequence,";
  std::cout << "before taking time and check the result.\n";
  std::cout << "         Default: N=1\n";
}

int main(int argc, char **argv) {
  // read input data

  //euc
   std::cout << "invoking euc" << std::endl;
   eucKernel.init();
   eucKernel.run(pipelined, std::atoi(argv[1]));
   if (eucKernel.check_output()) {
     std::cout << "result ok\n";
   } else {
       std::cout << "error: wrong result\n";
   }

  //ndt  
   std::cout << "invoking ndt" << std::endl;
   ndtKernel.init();
   ndtKernel.run(pipelined, std::atoi(argv[1]));
   if (ndtKernel.check_output()) {
     std::cout << "result ok\n";
   } else {
       std::cout << "error: wrong result\n";
   }

  //p2i
  std::cout << "invoking p2i" << std::endl;
  p2iKernel.init();
  
  p2iKernel.run(pipelined, std::atoi(argv[1]));
  if (p2iKernel.check_output()) {
    std::cout << "result ok\n\n";
  } else {
      std::cout << "error: wrong result\n";
  }
}