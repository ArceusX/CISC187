#ifndef MESA_CISC187_LIST
#define MESA_CISC187_LIST

#include <iostream>

struct list {
	int value;
	list* next;

	explicit list(
		const int value = 0, list* next = nullptr)
		: value(value), next(next) {}

	list* insert(int value) {
		return new list(value, this);
	}
};

list* erase(list* node);

std::ostream& operator<<(std::ostream& os, const list* node);

#endif