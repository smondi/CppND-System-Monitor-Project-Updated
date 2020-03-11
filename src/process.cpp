#include "linux_parser.h"
#include "process.h"

#include <cctype>
#include <sstream>
#include <string>
#include <unistd.h>

int Process::Pid() { 
    return pid_; 
}

float Process::CpuUtilization() const {
    return cpuUtilization_;
 }

std::string Process::Command() { 
    return command_; 
}

std::string Process::Ram() { 
    return ram_; 
}

std::string Process::User() { 
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