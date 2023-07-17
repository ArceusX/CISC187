#include <iostream>
#include "list.h"

int main() {
  using std::cout;
  using mesa::list;

  list<int> nums;
  nums.push_front(4);
  nums.push_front(3);
  nums.push_front(2);
  nums.push_front(1);

  nums.insert_after(1, 99);
  nums.insert_after(0, -1);
  nums.insert_after(5, 77);

  cout << nums << '\n';
  cout << nums.front() << '\n';
  int& f = nums.front();
  f = 13;
  cout << "front is 13\t";
  cout << f << '\n';
  cout << nums << '\n';
  while (!nums.empty()) {
    cout << nums << '\n';
    nums.pop_front();
  }

  // list<int> foo = nums;

  cout << "after purge\n";
  cout << nums << '\n';
  cout << "done.\n";

  return 0;
}
