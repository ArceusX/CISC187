#ifndef MESA_CISC187_STACK
#define MESA_CISC187_STACK

#include <stdexcept>
#include <algorithm>
#include "bag.h"

namespace mesa {
	template<typename T, typename Container = mesa::bag<T>>
	class stack {

	private:
		Container container;

	public:
		typedef Container container_type;
		typedef typename container_type::value_type value_type;
		static_assert((std::is_same<T, value_type>::value),
			"stack type must match underlying container value type");

		stack(): container(Container()) {}

		stack(const Container& other): container(other) {}

		stack(std::initializer_list<T> list): container(list) {}

		stack(const stack<T>& other): container(other.container) {}

		stack(stack<T>&& other) noexcept: 
			container(std::move(other.container)) {}

		stack<T, Container>& operator=(const stack<T>& other) {
			container = other.container;
			return *this;
		}

		stack<T, Container>& operator=(stack<T>&& other) noexcept {
			container = std::move(other.container);
			return *this;
		}

		constexpr bool empty() const noexcept {
			return container.empty();
		}
		constexpr size_t size() const noexcept {
			return container.size();
		}

		T& top() {
			return container.back();
		}
		constexpr const T& top() const noexcept {
			return container.back();
		}
		void push(const T& value) {
			container.push_back(value);
		}
		void pop() {
			container.pop_back();
		}

		const Container& getContainer() const {
			return container;
		}
	};

	template <typename T, typename Container>
	inline bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return std::equal(lhs.getContainer().begin(), lhs.getContainer().end(), 
			rhs.getContainer().begin(), rhs.getContainer().end());
	}

	template <typename T, typename Container>
	inline bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return !(lhs == rhs);
	}

	template <typename T, typename Container>
	inline bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return std::lexicographical_compare(
			lhs.getContainer().begin(), lhs.getContainer().end(), 
			rhs.getContainer().begin(), rhs.getContainer().end());
	}

	template <typename T, typename Container>
	inline bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return !(lhs < rhs);
	}

	template <typename T, typename Container>
	inline bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return std::lexicographical_compare(
			rhs.getContainer().begin(), rhs.getContainer().end(), 
			lhs.getContainer().begin(), lhs.getContainer().end());
	}

	template <typename T, typename Container>
	inline bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return !(lhs < rhs);
	}
}

#endif