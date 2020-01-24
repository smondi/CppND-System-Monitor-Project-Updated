#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
//string Format::ElapsedTime(long seconds[[maybe_unused]]) { return string(); }

string Format::ElapsedTime(long seconds) { 
    int secs{0};
    int hours = seconds / 3600;
    secs = seconds % 3600;
    int minutes = secs / 60;    
    secs = secs % 60;
    return std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(secs);
}