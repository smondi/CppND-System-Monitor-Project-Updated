#include "linux_parser.h"
#include "process.h"

#include <cctype>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>

using std::string;
using std::to_string;
using std::vector;

int Process::Pid() { 
    return pid_; 
}

float Process::CpuUtilization() const {
    return cpuUtilization_;
 }

string Process::Command() { 
    return command_; 
}

string Process::Ram() { 
    return ram_; 
}

string Process::User() { 
    return user_; 
}

long int Process::UpTime() { 
    return upTime_; 
}

bool Process::operator<(Process const& process) const { 
    return CpuUtilization() < process.CpuUtilization() ? true : false; 
}

bool Process::operator>(Process const& process) const { 
    return CpuUtilization() > process.CpuUtilization() ? true : false; 
}