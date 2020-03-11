#include "processor.h"

float Processor::Utilization() {
    std::vector<std::string> current_cpu_stats = LinuxParser::CpuUtilization();

    float total_CPU_time_since_boot {
        std::stof(current_cpu_stats[LinuxParser::CPUStates::kUser_]) + 
        std::stof(current_cpu_stats[LinuxParser::CPUStates::kNice_]) +
        std::stof(current_cpu_stats[LinuxParser::CPUStates::kSystem_]) +
        std::stof(current_cpu_stats[LinuxParser::CPUStates::kIdle_]) +
        std::stof(current_cpu_stats[LinuxParser::CPUStates::kIOwait_]) +
        std::stof(current_cpu_stats[LinuxParser::CPUStates::kIRQ_]) +
        std::stof(current_cpu_stats[LinuxParser::CPUStates::kSoftIRQ_]) + 
        std::stof(current_cpu_stats[LinuxParser::CPUStates::kSteal_])
    };

    float total_CPU_idle_time_since_boot {
        std::stof(current_cpu_stats[LinuxParser::CPUStates::kIdle_]) + 
        std::stof(current_cpu_stats[LinuxParser::CPUStates::kIOwait_])
    };

    float total_CPU_usage {total_CPU_time_since_boot - total_CPU_idle_time_since_boot};

    return total_CPU_usage / total_CPU_idle_time_since_boot;   
}