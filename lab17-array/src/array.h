#ifndef MESA_CISC187_ARRAY
#define MESA_CISC187_ARRAY

#include <iostream>
namespace mesa {

template<typename T, size_t N>
class array {
private:
	T data[N];

public:
	typedef T value_type;
	
	array() {
		if (std::is_arithmetic<T>::value) {
			std::fill(data, data + N, T());
		}
	}

	explicit array(std::initializer_list<T> list) {
		std::copy(list.begin(), list.end(), data);
	}

	constexpr size_t size() const noexcept {
		return N;
	}

	constexpr T* begin() noexcept {
		return data;
	}
	constexpr T* end() noexcept {
		return data + N;
	}

	constexpr const T* begin() const noexcept {
		return data;
	}
	constexpr const T* end() const noexcept {
		return data + N;
	}

	constexpr bool empty() const noexcept {
		return N == 0;
	}

	void print() {
		for (const auto& e : data) {
			std::cout << e << " ";
		}
	}
};
}
#endif