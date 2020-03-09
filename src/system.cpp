#include "linux_parser.h"
#include "process.h"
#include "processor.h"
#include "system.h"

#include <cstddef>
#include <set>
#include <string>
#include <unistd.h>
#include <vector>

using std::set;
using std::size_t;
using std::string;
using std::vector;

std::unordered_map<std::string, std::string> System::usersInfo_;

System::System() {        
    std::ifstream fileStream("/etc/passwd");
    std::string passwdLine;    
    char delimiter{':'};
    std::string token;
    std::vector<std::string> tokens;
    if (fileStream.is_open()) {
        while(std::getline(fileStream, passwdLine)) {
            std::stringstream userLineStream(passwdLine);                  
            for (int i = 0; i < 3; ++i) {
                std::getline(userLineStream, token, delimiter);
                tokens.push_back(token);
            }
            usersInfo_.insert(std::make_pair(tokens[2], tokens[0]));
            tokens.clear();
        }
    }
}

Processor& System::Cpu() { 
    return cpu_; 
}

vector<Process>& System::Processes() {
    processes_.clear();
    vector<int> pIds = LinuxParser::Pids();    
    for (std::size_t i = 0; i < pIds.size(); ++i) {
        std::string user = LinuxParser::User(pIds[i]);
        long int upTime = LinuxParser::UpTime(pIds[i]);
        std::string ram = LinuxParser::Ram(pIds[i]);
        std::string command = LinuxParser::Command(pIds[i]); 
        float cpuUtilization = LinuxParser::CpuUtilization(pIds[i], UpTime());
        Process proc = Process(pIds[i], user, upTime, ram, command, cpuUtilization);
        processes_.push_back(proc);
    }
    std::sort(processes_.begin(), processes_.end(), std::greater<Process>());
    return processes_; 
}

std::string System::Kernel() {
    return LinuxParser::Kernel(); 
}

float System::MemoryUtilization() { 
    return LinuxParser::MemoryUtilization(); 
}

std::string System::OperatingSystem() {
    return LinuxParser::OperatingSystem();
}

int System::RunningProcesses() { 
    return LinuxParser::RunningProcesses(); 
}

int System::TotalProcesses() { 
    return LinuxParser::TotalProcesses();
}

long int System::UpTime() { 
    return LinuxParser::UpTime();    
 }

 std::unordered_map<std::string, std::string> System::UserInfo() {
     return usersInfo_;
 }

