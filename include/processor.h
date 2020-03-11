#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "linux_parser.h"

#include <vector>

class Processor {
 public:
  Processor() = default;
  float Utilization();

//  private:
//   std::vector<float> cpu_stats_;
};

#endif