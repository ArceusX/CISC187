#ifndef MESA_CISC187_ARRAY
#define MESA_CISC187_ARRAY

#include <iostream>
#include <stdexcept>
#include <algorithm>

namespace mesa {
	template<typename T, size_t N>
	class array {
	private:
		T values[N];

	public:
		typedef T value_type;

		array() {
			if (std::is_arithmetic<T>::value) {
				std::fill(values, values + N, T());
			}
		}

		explicit array(std::initializer_list<T> list) {
			std::copy(list.begin(), list.end(), values);
		}

		constexpr T& operator[](size_t index) {
			return values[index];
		}

		constexpr const T& operator[](size_t index) const {
			return values[index];
		}

		constexpr const T& at(size_t index) const {
			if (index >= N || index < 0) {
				throw std::out_of_range("array<T>::at(): index is out of range");
			}
			return values[index];
		}

		constexpr T& at(size_t index) {
			if (index >= N || index < 0) {
				throw std::out_of_range("array<T>::at(): index is out of range");
			}
			return values[index];
		}

		T* data() {
			return values;
		}

		constexpr const T* data() const {
			return values;
		}

		T& back() {
			return values[N-1];
		}

		constexpr const T& back() const {
			return values[N - 1];
		}

		size_t size() const {
			return N;
		}

		constexpr T* begin() noexcept {
			return values;
		}
		constexpr T* end() noexcept {
			return values + N;
		}

		constexpr const T* begin() const noexcept {
			return values;
		}
		constexpr const T* end() const noexcept {
			return values + N;
		}

		constexpr bool empty() const noexcept {
			return N == 0;
		}

		void print() {
			for (const auto& e : values) {
				std::cout << e << " ";
			}
		}
	};

	template <typename T, size_t N>
	inline bool operator==(const mesa::array<T, N>& lhs, const mesa::array<T, N>& rhs) {
		return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <typename T, size_t N>
	inline bool operator!=(const mesa::array<T, N>& lhs, const mesa::array<T, N>& rhs) {
		return !(lhs == rhs);
	}

	template <typename T, size_t N>
	inline bool operator<(const mesa::array<T, N>& lhs, const mesa::array<T, N>& rhs) {
		return std::lexicographical_compare(
			lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <typename T, size_t N>
	inline bool operator>=(const mesa::array<T, N>& lhs, const mesa::array<T, N>& rhs) {
		return !(lhs < rhs);
	}

	template <typename T, size_t N>
	inline bool operator>(const mesa::array<T, N>& lhs, const mesa::array<T, N>& rhs) {
		return std::lexicographical_compare(
			rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	}

	template <typename T, size_t N>
	inline bool operator<=(const mesa::array<T, N>& lhs, const mesa::array<T, N>& rhs) {
		return !(lhs < rhs);
	}
}
#endif