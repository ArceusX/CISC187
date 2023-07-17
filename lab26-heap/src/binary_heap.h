#ifndef MESA_CISC187_BINARY_HEAP_H
#define MESA_CISC187_BINARY_HEAP_H

#include <cstdlib>
#include <ostream>
#include <vector>

template <class T>
// require T is comparable
struct binary_heap
{
    size_t size_ = 0;
    std::vector<T> heap;

    binary_heap()
      : size_{0}
      , heap(size_+4)
    { }
    explicit binary_heap(const std::vector<T>& items)
      : size_{items.size()}
      , heap(size_+10)
    {
    }

    constexpr
      bool empty() const noexcept { return size_ == 0;}
    constexpr
      size_t size() const noexcept { return size_;}
    constexpr
      const T& front() const { }

    // insert a value, allowing duplicates
    void insert (T value)
    {
    }
    
    // remove the min item from the heap
    void pop()
    {
      if (empty()) {
        throw std::domain_error("Cannot delete from an empty heap.");
      }
    }

    void clear();

    void build_heap();

    void percolate_down(size_t hole);

    void percolate_up(T value);

};

template <class T>
std::ostream& operator<<(std::ostream& os, const binary_heap<T>& rhs)
{
  for (const auto& value: rhs.heap) {
    os << value << ' ';
  }
  return os;
}

#endif

