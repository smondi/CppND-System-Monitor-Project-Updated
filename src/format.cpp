#include <string>
#include <sstream>
#include <iomanip>

#include "format.h"

using std::string;


string Format::ElapsedTime(long seconds) { 
    int secs{0};
    int hours = seconds / 3600;
    secs = seconds % 3600;
    int minutes = secs / 60;    
    secs = secs % 60;
    std::ostringstream oHours;
    std::ostringstream oMinutes;
    std::ostringstream oSeconds;
    oHours << std::setfill('0') << std::setw(2) << hours;
    oMinutes << std::setfill('0') << std::setw(2) << minutes;
    oSeconds << std::setfill('0') << std::setw(2) << secs;
    return oHours.str() + ':' + oMinutes.str() + ':' + oSeconds.str();
}