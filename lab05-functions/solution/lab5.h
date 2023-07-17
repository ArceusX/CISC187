#ifndef MESA_CISC187_TIME_H
#define MESA_CISC187_TIME_H

#include <unistd.h>

#include <cstdint>
#include <iosfwd>

namespace mesa {

  constexpr unsigned char ERROR_HOUR = 1;
  constexpr unsigned char ERROR_MINUTE = 2;
  constexpr unsigned char ERROR_SECOND = 4;
  constexpr unsigned char ERROR_PERIOD = 8;

#ifdef _WIN32
  const long HZ = 100;                    // user clock ticks hardcode on windows
#elif  _WIN64
  const long HZ = 1000;                   // user clock ticks hardcode on windows
#else
  const long HZ = sysconf(_SC_CLK_TCK);   // user clock ticks / sec
#endif


  // a data structure to represent the time of day
  struct time_t {
    int hours;     // hours since midnight (1-12)
    int minutes;   // minutes after the hour
    int seconds;   // seconds after the minute
    char period;   // AM/PM designator
    // bitmask used to check validity and report issues
    unsigned char errors;
  };

  // Set a time object using the provided parameters
  void set(time_t& time, 
           int hours, int minutes, int seconds, char period = 'a');

  // Convert a time struct to jiffies
  int64_t time_to_jiffies(const time_t& time);

  // Convert jiffies to time
  time_t jiffies_to_time(int64_t jiffies);

  // Advance a clock a set number of hours, minutes, and seconds
  void advance(time_t& time, int hours = 0, int minutes = 0, int seconds = 0);

  // Send time to the designated stream
  void display(std::ostream& os, const time_t& time);


  // These definitions and inline functions
  // help simplify or clarify the lab functions
  // or help reduce duplicate code.
  constexpr unsigned char NO_ERRORS = 0;
  constexpr int MIN_HOURS           = 1;
  constexpr int MAX_HOURS           = 12;
  constexpr int HOURS_PER_DAY       = 24;
  constexpr int MIN_MINUTES         = 0;
  constexpr int MAX_MINUTES         = 59;
  constexpr int MIN_SECONDS         = 0;
  constexpr int MAX_SECONDS         = 59;
  constexpr int SECONDS_PER_MINUTE  = 60;
  constexpr int SECONDS_PER_HOUR    = 3600;

  // check that a value is beyond the specified range (inclusive)
  constexpr bool outside_limits (int value, int min, int max)
  {
    return value < min || value > max;
  }
  
  inline  // mesa::HZ is not constexpr
  int64_t jiffies_to_seconds (int64_t jiffies)
  {
    return jiffies / mesa::HZ;
  }

  constexpr
  int64_t hms_to_seconds (int hours, int minutes, int seconds)
  {
    return hours * SECONDS_PER_HOUR 
               + minutes * SECONDS_PER_MINUTE
               + seconds;
  }

} // end namespace mesa

#endif

