#include "linux_parser.h"
#include "system.h"

#include <dirent.h>
#include <iomanip>
#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>

constexpr int megaByetes = 1024;

std::string LinuxParser::OperatingSystem() {
  std::string line;
  std::string key;
  std::string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

std::string LinuxParser::Kernel() {
  std::string os;
  std::string version;
  std::string kernel;
  std::string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

std::vector<int> LinuxParser::Pids() {
  std::vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      std::string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = std::stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

float LinuxParser::MemoryUtilization() {
    int MemTotal{0};
    int MemFree{0};
    int value;
    std::string key;
    std::string line;
    std::ifstream file_stream(kProcDirectory + kMeminfoFilename);
    if (file_stream.is_open()) {
        while (std::getline(file_stream, line)) {
            std::istringstream linestream(line);
            linestream >> key >> value;
            if (key == "MemTotal:") {
                MemTotal = value;
            }
            if (key == "MemFree:") {
                MemFree = value;
            }
        }
    }
    float memUsage = static_cast<float>(MemTotal - MemFree) / MemTotal;
    return memUsage;     
}

long int LinuxParser::UpTime() { 
    long systemUpTime{0};
    long idleProcesses{0};
    std::string line;
    std::ifstream stream(kProcDirectory + kUptimeFilename);    
    if (stream.is_open()) {
        std::getline(stream, line);
        std::istringstream linestream(line);
        linestream >> systemUpTime >> idleProcesses;        
    }
    return systemUpTime;
 }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
std::vector<std::string> LinuxParser::CpuUtilization() {
    std::vector<std::string> cpu_stats{};
    std::string line;
    std::string value;
    std::ifstream file_stream(kProcDirectory + kStatFilename);
    if (file_stream.is_open()) {
        std::getline(file_stream, line);
        std::istringstream line_stream(line);
        while (line_stream >> value) {
            cpu_stats.push_back(value);
        }
        cpu_stats.erase(cpu_stats.begin());
    }
    return cpu_stats; 
}

int LinuxParser::TotalProcesses() {    
    int value;
    std::string line;
    std::string key;
    std::ifstream fileStream(kProcDirectory + kStatFilename);
    if (fileStream.is_open()) {                    
        while (std::getline(fileStream, line)) {
            std::istringstream linestream(line);
            linestream >> key >> value;
            if (key == "processes") {     
                return value;
            }
        }        
    }
    return -1;    
}

int LinuxParser::RunningProcesses() {
    int value;
    std::string key;    
    std::string line;
    std::ifstream fileStream(kProcDirectory + kStatFilename);
    if (fileStream.is_open()) {                    
        while (std::getline(fileStream, line)) {
            std::istringstream linestream(line);
            linestream >> key >> value;
            if (key == "procs_running") {     
                return value;
            }
        }        
    }
    return -1;  
}


std::string LinuxParser::Command(int pid) {
    std::string command;
    std::string procId = std::to_string(pid);
    std::string line;
    std::ifstream fileStream(kProcDirectory + procId + kCmdlineFilename);
    if (fileStream.is_open()) {        
        std::getline(fileStream, line);
        std::istringstream linestream(line);
        linestream >> command;         
    }
    return command; 
}

std::string LinuxParser::Ram(int pid) {    
    std::string ram;
    std::string procId = std::to_string(pid);
    std::string key;
    std::string value;
    std::string line;
    std::ifstream fileStream(kProcDirectory + procId + kStatusFilename);
    if (fileStream.is_open()) {                           
         while (std::getline(fileStream, line)) {
            std::istringstream linestream(line);
            linestream >> key >> value;
            if (key == "VmSize:") 
                ram = std::to_string(std::stol(value) / megaByetes);
         }        
    }
    return ram;
}

std::string LinuxParser::Uid(int pid) { 
    int value;
    std::string uId;
    std::string procId = std::to_string(pid);
    std::string key;
    std::string line;
    std::ifstream fileStream(kProcDirectory + procId + kStatusFilename);
    if (fileStream.is_open()) {                    
        while (std::getline(fileStream, line)) {
            std::istringstream linestream(line);
            linestream >> key >> value;
            if (key == "Uid:") {     
                uId = std::to_string(value);
            }
        }        
    }
    return uId; 
 }


std::string LinuxParser::User(int pid) {
    std::string uId = LinuxParser::Uid(pid);           
    // auto userInfo = System::UserInfo().find(uId);
    // std::string test{userInfo};
    // return test;
    // std::stringstream userId{};
    // if (userInfo != System::UserInfo().end()) {
    //     auto user_str {userInfo->second};              
    //     userId << std::setw(5) << std::left << user_str;
    // } else {
    //     userId << std::setw(10) << std::left << " ";
    // }
    // return userId.str();
    std::stringstream userId{};
     try {
         userId << std::setw(10) << std::left << System::UserInfo().at(uId);
         return userId.str();        
     } catch (...) {
         userId << std::setw(10) << std::left << "";
         return userId.str();
     }
};

float LinuxParser::CpuUtilization(int pId, long int upTime) {    
    std::vector<std::string> proc_stats{};
    std::string procId = std::to_string(pId);
    std::string value;   
    std::string line;
    std::ifstream fileStream(kProcDirectory + procId + kStatFilename);
    if (fileStream.is_open()) {        
        std::getline(fileStream, line);
        std::istringstream linestream(line);                 
        while (linestream >> value) {           
            proc_stats.push_back(value);
        }        
    }
    float uTime = std::stof(proc_stats[ProcessStates::kUtime_]);
    float sTime = std::stof(proc_stats[ProcessStates::kStime_]);
    float cuTime = std::stof(proc_stats[ProcessStates::kCuTime_]);
    float csTime = std::stof(proc_stats[ProcessStates::kCsTime_]);
    float startTime = std::stof(proc_stats[ProcessStates::kStartTime_]);
    // total_time = utime + stime;
    float totalTime = uTime + sTime;
    // Adding time for sub processes
    totalTime += cuTime + csTime;
    // Elapsed time since process started in seconds
    float elapsedTime = upTime - (startTime / sysconf(_SC_CLK_TCK));
    // CPU Utilization = 100 * ((totalTime / Hertz) / elapsedTime)
    float cpuUtilization = ((totalTime / sysconf(_SC_CLK_TCK)) / elapsedTime);
    return cpuUtilization;  
}


long LinuxParser::UpTime(int pid) {
    char delimiter {' '};   
    std::string user {std::to_string(pid).c_str()};
    std::string procId = std::to_string(pid);
    std::string token;    
    std::vector<std::string> tokens;
    std::ifstream fileStream(kProcDirectory + procId + kStatFilename);
    if (fileStream.is_open()) {                    
        while (std::getline(fileStream, token, delimiter)) {
            tokens.push_back(token);
        }        
    }
    long UpTime_secs = std::stoll(tokens[21]) / sysconf(_SC_CLK_TCK);    
    return UpTime_secs; 
}

