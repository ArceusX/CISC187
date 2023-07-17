#include <iostream>

namespace mesa {
	#ifdef _WIN32
		const long HZ = 100;          
	#elif  _WIN64
		const long HZ = 1000;
	#else
		const long HZ = sysconf(_SC_CLK_TCK);
	#endif

	// Data structure to represent time of day
	struct time_t {
		int hours;     // hours since midnight (1-12)
		int minutes;   // minutes after the hour
		int seconds;   // seconds after the minute
		char period;   // AM/PM designator
		unsigned char errors; // bitmask to check validity and report issues
	};

	void set(time_t& time,
		int hours, int minutes, int seconds, char period = 'a');

	void display(std::ostream& os, const time_t& time);

	int64_t time_to_jiffies(const time_t& time);

	time_t jiffies_to_time(int64_t jiffies);

	void advance(time_t& time, int hours = 0, int minutes = 0, int seconds = 0);

	constexpr unsigned char ERROR_HOUR = 1;
	constexpr unsigned char ERROR_MINUTE = 2;
	constexpr unsigned char ERROR_SECOND = 4;
	constexpr unsigned char ERROR_PERIOD = 8;
}