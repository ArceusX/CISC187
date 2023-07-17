#ifndef MESA_CISC187_BAG
#define MESA_CISC187_BAG

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <memory>

namespace mesa {
	template<typename T, typename Allocator = std::allocator<T>>
	class bag {

	private:
		size_t _size;
		size_t _capacity;
		T* _data;
		Allocator allocator;

		using memory = std::allocator_traits<Allocator>;

	public:
		typedef T value_type;

		bag(size_t size = 0) {
			_size = size;
			_capacity = _size;

			if (_size != 0) {
				//_data = new T[_size];
				_data = memory::allocate(allocator, _size);

				std::fill(_data, _data + _size, T());
			}
			else {
				_data = nullptr;
			}
		}

		bag(std::initializer_list<T> list):
			_size(list.size()),
			//_capacity(list.size()), _data(new T[list.size()]
			_capacity(list.size()), _data(memory::allocate(allocator, list.size())) {
			std::copy(list.begin(), list.end(), _data);
		}

		bag(const bag<T>& src):
			_size(src.size()),
			_capacity(src.capacity()), 
			//_data(new T[src.size()])
			_data(memory::allocate(allocator, src.size())) {
			std::copy(src.begin(), src.end(), _data);
		}

		bag<T>& operator=(const bag<T>& src) {
			delete[] _data;

			_size = src.size();
			_capacity = src.capacity();

			//_data = new T[_size];
			_data = memory::allocate(allocator, _size);

			std::copy(src.begin(), src.end(), _data);

			return *this;
		}

		const size_t capacity() const noexcept { return _capacity; }

		const size_t size() const noexcept {return _size;}

		void reserve(size_t new_capacity) {
			if (new_capacity > _capacity) {

				//T* temp_array = new T[new_capacity];
				T* temp_array = memory::allocate(allocator, new_capacity);

				std::copy(_data, _data + _size, temp_array);
				delete [] _data;

				//_data = new T[new_capacity];
				_data = memory::allocate(allocator, new_capacity);

				std::copy(temp_array, temp_array + _size, _data);
				delete [] temp_array;
				_capacity = new_capacity;
			}
		}

		void resize(size_t new_capacity) {
			reserve(new_capacity);
			if (new_capacity > _size) {
				std::fill(_data + _size, _data + new_capacity, T());
			}
			_size = new_capacity;
		}

		void push_back(T value) {
			if (_size == _capacity) {
				if (_capacity != 0) {
					reserve(_capacity * 2);
				}
				else {
					reserve(1);
				}
			}
			//_data[_size] = value;
			memory::construct(allocator, &_data[_size], value);
			_size++;
		}

		void pop_back() {
			_size = (_size > 0) ? (_size - 1) : 0;
		}

		constexpr T& operator[](size_t index) {
			return _data[index];
		}

		constexpr const T& operator[](size_t index) const {
			return _data[index];
		}

		constexpr const T& at(size_t index) const {
			if (index >= _size || index < 0) {
				throw std::out_of_range("bag<T>::at(): index is out of range");
			}
			return _data[index];
		}

		constexpr T& at(size_t index) {
			if (index >= _size || index < 0) {
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
			return _data[_size-1];
		}

		constexpr const T& back() const {
			return _data[_size-1];
		}

		constexpr T* begin() noexcept {
			return _data;
		}
		constexpr T* end() noexcept {
			return _data + _size;
		}

		constexpr const T* begin() const noexcept {
			return _data;
		}
		constexpr const T* end() const noexcept {
			return _data + _size;
		}

		constexpr bool empty() const noexcept {
			return _size == 0;
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