#include "lab5.h"

// Set time object with provided parameters
void mesa::set(time_t& time,
	int hours, int minutes, int seconds, char period) {

	// Add matching error bit code if any error encountered 
	time.errors = 0;

	if (hours < 1 || hours > 12) {
		time.errors += ERROR_HOUR;
	}
	if (minutes < 0 || minutes > 59) {
		time.errors += ERROR_MINUTE;
	}
	if (seconds < 0 || seconds > 59) {
		time.errors += ERROR_SECOND;
	}
	if (period != 'a' && period != 'p') {
		time.errors += ERROR_PERIOD;
	}

	time.hours = hours;
	time.minutes = minutes;
	time.seconds = seconds;
	time.period = period;
}

// Send time to designated stream
void mesa::display(std::ostream& os, const time_t& time) {
	os << time.hours << ":" << time.minutes << ":" << time.seconds << " ";

	if (time.period == 'a') os << "AM";
	else if (time.period == 'p') os << "PM";

	else os << time.period;

	if (time.errors != 0) {
		// Print actual int and not char equivalent
		os << "[" << (int)time.errors << "]";
	}
}

int64_t mesa::time_to_jiffies(const time_t& time) {
	if (time.errors != 0) return 0;

	int64_t jiffies = time.hours;

	if (time.hours != 12) {
		if (time.period == 'p') jiffies += 12;
	}

	// 12 am (midnight) is 00h in 24-hr format
	else if (time.period == 'a') jiffies = 0;
	// 12 pm (noon) is 12h in 24-hr format (already assigned)

	jiffies = jiffies * 60 + time.minutes;
	jiffies = jiffies * 60 + time.seconds;
	jiffies *= HZ;

	return jiffies;
}

mesa::time_t mesa::jiffies_to_time(int64_t jiffies) {
	time_t time;
	time.seconds = jiffies / HZ;

	time.minutes = time.seconds / 60;
	time.seconds = time.seconds % 60;

	time.hours = time.minutes / 60;
	time.minutes = time.minutes % 60;

	// 0hr gets 0 am; 12hr gets 12 pm
	if (((time.hours / 12) % 2) == 1) {
		time.period = 'p';
	}
	else time.period = 'a';


	// Convert to 12-hour format
	time.hours = time.hours % 12;
	time.errors = 0;

	return time;
}

void mesa::advance(time_t& time, int hours, int minutes, int seconds) {
	// 12 am equals 00hr in 24-hour format
	if (time.hours == 12 && time.period == 'a') time.hours = 0;

	time.hours += hours;
	time.minutes += minutes;
	time.seconds += seconds;

	time.minutes += time.seconds / 60;
	time.seconds = time.seconds % 60;

	time.hours += time.minutes / 60;
	time.minutes = time.minutes % 60;

	if (((time.hours / 12) % 2) == 1) {
		time.period = 'p';
	}
	else time.period = 'a';

	// 24hr to 12hr format: 1 -> 1, 2 -> 2, 13 -> 1, but 12 -> 12, 24 -> 12
	time.hours = ((time.hours + 11) % 12 + 1);
}
