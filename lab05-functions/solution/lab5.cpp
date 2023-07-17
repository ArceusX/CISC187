#include <cstdint>
#include <iostream>

#include "lab5.h"

void mesa::set(mesa::time_t& time, 
               int hours, int minutes, int seconds, char period)
{
  time = {hours, minutes, seconds, period, NO_ERRORS};
  if (outside_limits(hours, MIN_HOURS, MAX_HOURS))       {time.errors |= ERROR_HOUR;}
  if (outside_limits(minutes, MIN_MINUTES, MAX_MINUTES)) {time.errors |= ERROR_MINUTE;}
  if (outside_limits(seconds, MIN_SECONDS, MAX_SECONDS)) {time.errors |= ERROR_SECOND;}
  if (period != 'a' && period != 'p')                    {time.errors |= ERROR_PERIOD;}
}

void mesa::display(std::ostream& os, const mesa::time_t& time)
{
  os << time.hours << ':' << time.minutes << ':' << time.seconds << ' ';
  if (time.period == 'a') {
    os << "AM";
  } else if (time.period == 'p') {
    os << "PM";
  } else {
    os << time.period;
  }
  if (time.errors != NO_ERRORS) {
    os << '[' << int(time.errors) << ']';
  }
}

int64_t mesa::time_to_jiffies(const mesa::time_t& time)
{
  int64_t jiffies = 0;
  if (time.errors == NO_ERRORS) {
    auto hrs = time.hours;
    if (time.period == 'a' && time.hours == MAX_HOURS) { hrs = 0; }
    if (time.period == 'p' && time.hours <  MAX_HOURS) { hrs += MAX_HOURS; }
    jiffies =  mesa::HZ * hms_to_seconds(hrs, time.minutes, time.seconds);
  }
  return jiffies;
}

mesa::time_t mesa::jiffies_to_time(int64_t jiffies)
{
  mesa::time_t value {0,0,0,'a'};
  int64_t sec = jiffies_to_seconds(jiffies);
  value.hours = int(sec / SECONDS_PER_HOUR);
  sec        -= value.hours*SECONDS_PER_HOUR;
  if (value.hours%HOURS_PER_DAY >= MAX_HOURS) {
    value.period = 'p';
  }
  value.hours %= MAX_HOURS;
  if (value.hours == 0) {
    value.hours = MAX_HOURS;
  }
  value.minutes = int(sec / SECONDS_PER_MINUTE);
  value.seconds = int(sec - value.minutes*SECONDS_PER_MINUTE);
  return value;
}

void mesa::advance(mesa::time_t& time, int hours, int minutes, int seconds)
{
  auto ticks = time_to_jiffies(time);
  ticks += mesa::HZ * hms_to_seconds(hours, minutes, seconds);
  time = jiffies_to_time(ticks);
}

