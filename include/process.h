#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <vector>
#include <unordered_map>

class Process {
 public:
    Process(int pId = 0, std::string user = "", long upTime = 0l, 
            std::string ram = "0.0", std::string command = "", float cpuUtilization = 0.0f)
    :pid_(pId), user_(user), upTime_(upTime), ram_(ram), command_(command), cpuUtilization_(cpuUtilization) {};

  int Pid();                               
  std::string User();                      
  std::string Command();                   
  float CpuUtilization() const;
  std::string Ram();            
  long int UpTime();                       
  bool operator<(Process const& process) const;
  bool operator>(Process const& process) const;


 private:
  int pid_;  
  std::string user_;
  std::string command_;
  float cpuUtilization_;
  std::string ram_;
  long int upTime_;  
};

#endif