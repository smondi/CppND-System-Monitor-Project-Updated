#include "processor.h"


Processor::Processor() {
    std::vector<std::string> current_cpu_stats = LinuxParser::CpuUtilization();
    for (std::size_t i = 0; i < current_cpu_stats.size(); ++i) {
        this->cpu_stats_.push_back(std::stof(current_cpu_stats[i]));
    }
}

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
    std::vector<std::string> current_cpu_stats = LinuxParser::CpuUtilization();
    
    // idle = idle + iowait
    float idle = std::stof(current_cpu_stats[LinuxParser::CPUStates::kIdle_]) + 
                 std::stof(current_cpu_stats[LinuxParser::CPUStates::kIOwait_]);
    // prev_idle += previowait
    float prev_idle = (cpu_stats_[3] + cpu_stats_[4]) + (cpu_stats_[4]);

    // non_idle = user + nice + system + irq + softirq + steal
    float non_idle = std::stof(current_cpu_stats[LinuxParser::CPUStates::kUser_]) + 
                     std::stof(current_cpu_stats[LinuxParser::CPUStates::kNice_]) +
                     std::stof(current_cpu_stats[LinuxParser::CPUStates::kSystem_]) + 
                     std::stof(current_cpu_stats[LinuxParser::CPUStates::kIRQ_]) +
                     std::stof(current_cpu_stats[LinuxParser::CPUStates::kSoftIRQ_]) + 
                     std::stof(current_cpu_stats[LinuxParser::CPUStates::kSteal_]);

    // prev_non_idle = prev_user + prev_nice + prev_system + prev_irq + prev_softirq + prev_steal
    float prev_non_idle = cpu_stats_[LinuxParser::CPUStates::kUser_] + 
                          cpu_stats_[LinuxParser::CPUStates::kNice_] +
                          cpu_stats_[LinuxParser::CPUStates::kSystem_] + 
                          cpu_stats_[LinuxParser::CPUStates::kIRQ_] +
                          cpu_stats_[LinuxParser::CPUStates::kSoftIRQ_] + 
                          cpu_stats_[LinuxParser::CPUStates::kSteal_];

    // total = idle + non_idle
    float total = idle + non_idle;
    
    // prev_total = prev_idle + prev_non_idle
    float prev_total = prev_idle + prev_non_idle;

    // total_d = total - prev_total
    float total_d = total - prev_total;

    // idle_d = idle - prev_idle;
    float idle_d = idle - prev_idle;

    // cpu_percentage = (total_d - idle_d) / total_d;
    float cpu_percentage = (total_d - idle_d) / total_d;

    for (std::size_t i = 0; i < current_cpu_stats.size(); ++i) {
        this->cpu_stats_[i] = std::stof(current_cpu_stats[i]);
    } 

    return cpu_percentage;    
}