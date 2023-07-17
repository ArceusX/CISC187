#ifndef MESA_CISC187_BAG
#define MESA_CISC187_BAG

#include <iostream>
#include <stdexcept>
#include <algorithm>

namespace mesa {
	template<typename T>
	class bag {
	private:
		size_t _capacity;
		T* _data;

	public:
		typedef T value_type;

		bag(size_t capacity = 0): _capacity(capacity) {
			if (_capacity != 0) {
				_data = new T[_capacity];
				if (std::is_arithmetic<T>::value) {
					std::fill(_data, _data + _capacity, T());
				}
			}
			else _data = nullptr;
		}

		bag(std::initializer_list<T> list) :
			_capacity(list.size()), _data(new T[list.size()]) {
			std::copy(list.begin(), list.end(), _data);
		}

		bag(const bag<T>& src):
			_capacity(src._capacity), _data(new T[src._capacity]) {
			std::copy(src.begin(), src.end(), _data);
		}

		bag(bag<T>&& src) noexcept:
			_capacity(src._capacity), _data(src._data) {
			src._data = nullptr;
		}

		bag<T>& operator=(const bag<T>& src) {

			bag<T> copy(src);
			std::swap(_data, copy._data);
			_capacity = src._capacity;

			return *this;
		}

		bag<T>& operator=(bag<T>&& src) noexcept {

			swap(_data, src._data);
			_capacity = src._capacity;

			return *this;
		}

		const size_t capacity() const noexcept { return _capacity; }

		constexpr T& operator[](size_t index) {
			return _data[index];
		}

		constexpr const T& operator[](size_t index) const {
			return _data[index];
		}

		constexpr const T& at(size_t index) const {
			if (index >= _capacity || index < 0) {
				throw std::out_of_range("bag<T>::at(): index is out of range");
			}
			return _data[index];
		}

		constexpr T& at(size_t index) {
			if (index >= _capacity || index < 0) {
				throw std::out_of_range("bag<T>::at(): index is out of range");
			}
			return _data[index];
		}

		T* data() {
			return _data;
		}

		constexpr const T* data() const {
			return _data;
		}

		T& back() {
			return _data[_capacity - 1];
		}

		constexpr const T& back() const {
			return _data[_capacity - 1];
		}

		size_t size() const {
			return _capacity;
		}

		constexpr T* begin() noexcept {
			return _data;
		}
		constexpr T* end() noexcept {
			return _data + _capacity;
		}

		constexpr const T* begin() const noexcept {
			return _data;
		}
		constexpr const T* end() const noexcept {
			return _data + _capacity;
		}

		constexpr bool empty() const noexcept {
			return _capacity == 0;
		}

		void print() {
			for (const auto& e : _data) {
				std::cout << e << " ";
			}
		}

		~bag() {
			delete[] _data;
		}
	};

	template <typename T>
	inline bool operator==(const mesa::bag<T>& lhs, const mesa::bag<T>& rhs) {
		return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <typename T>
	inline bool operator!=(const mesa::bag<T>& lhs, const mesa::bag<T>& rhs) {
		return !(lhs == rhs);
	}

	template <typename T>
	inline bool operator<(const mesa::bag<T>& lhs, const mesa::bag<T>& rhs) {
		return std::lexicographical_compare(
			lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <typename T>
	inline bool operator>=(const mesa::bag<T>& lhs, const mesa::bag<T>& rhs) {
		return !(lhs < rhs);
	}

	template <typename T>
	inline bool operator>(const mesa::bag<T>& lhs, const mesa::bag<T>& rhs) {
		return std::lexicographical_compare(
			rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	}

	template <typename T>
	inline bool operator<=(const mesa::bag<T>& lhs, const mesa::bag<T>& rhs) {
		return !(lhs < rhs);
	}
}
#endif