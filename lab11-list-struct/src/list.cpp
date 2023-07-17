#include "list.h"

list* erase(list* node) {
	list* next = node->next;
	delete node;
	return next;
}

std::ostream& operator<<(std::ostream& os, const list* node) {
	const list* current = node;
	while (current) {
		os << current->value << " ";
		current = current->next;
	}
	return os;
}