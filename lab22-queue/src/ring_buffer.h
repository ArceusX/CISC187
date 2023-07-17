#ifndef MESA_CISC187_RING_BUFFER
#define MESA_CISC187_RING_BUFFER

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <memory>

namespace mesa {
	template <typename T, size_t capacity>
	class ring_buffer {
	private:
		T* buffer;
		size_t ptWrite = 0;
		size_t ptRead = 0;

		// Need this flag because checking ptWriter == ptRead
		// alone cannot distinguish full vs empty buffer
		bool flag = true;

	public:
		ring_buffer() : buffer(new T[capacity]) {}

		T pop() {
			if (empty()) {
				throw std::domain_error("buffer is empty. Nothing to pop.");
			}

			T item = buffer[ptRead];
			ptRead = (ptRead + 1) % capacity;

			// If after read, ptWrite == ptRead, ptRead caught ptWrite, set
			// flag = true so empty() clears 1 cond to block further pop
			flag = (ptRead == ptWrite);

			return item;
		}

		void push(const T& elem) {
			if (full()) {
				throw std::domain_error("buffer is full. Cannot push.");
			}
			overwrite(elem);
		}

		// overwrite forcibly write over data even if buffer is full
		void overwrite(const T& elem) {

			// If overwrite NOT called thru push, chance data may
			// be overwritten, for which overwritten data will
			// never be read, so move ptRead pass it
			if (full()) {
				ptRead = (ptRead + 1) % capacity;
			}

			buffer[ptWrite] = elem;
			ptWrite = (ptWrite + 1) % capacity;

			// If after write, ptWrite == ptRead, ptWrite caught ptRead, set
			// flag = false so full() clears 1 cond to block further push
			flag = !(ptWrite == ptRead);
		}

		// If true, know pop() set flag = true when noting ptRead caught
		//			ptWrite and all push() after has kept flag as true
		bool empty() { return (ptWrite == ptRead) && flag; }

		// If true, know push() set flag = false when noting ptWrite caught
		//			ptRead and all pop() after has kept flag as false
		bool full() { return (ptWrite == ptRead) && !flag; }

		void clear() {

			// Don't need to delete data right now. Need only set
			// vars back to original states at initialization
			ptWrite = ptRead = 0;
			flag = true;
		}

		~ring_buffer() {
			delete[] buffer;
		}
	};
}
#endif