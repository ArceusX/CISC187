#include "lab9.h"

void mesa::to_lower(char* str) {
	if (str != nullptr) {
        while (*str) {
            *str = tolower(*str);
            str++;
        }
	}
}

char* mesa::copy(const char* source, const size_t count) {
    // Must allocate for null terminator
    char* target = new char[count + 1];
    strcpy(target, source);
    return target;
}

size_t mesa::count(const char* source, const char c) {
    size_t count = 0;

    while (*source) {
        if (*source == c) count++;
        source++;
    }
    return count;
}