#ifndef SYSTEM_H
#define SYSTEM_H

#include "process.h"
#include "processor.h"

#include <string>
#include <vector>
#include <unordered_map>

class System {
 public:
  System();
  Processor& Cpu();
  std::vector<Process>& Processes();
  float MemoryUtilization();  
  long UpTime();
  int TotalProcesses();          
  int RunningProcesses();
  std::string Kernel();      
  std::string OperatingSystem();
  static std::unordered_map<std::string, std::string> UserInfo();

 private:
  Processor cpu_;
  std::vector<Process> processes_;
  static std::unordered_map<std::string, std::string> usersInfo_;
};

#endif