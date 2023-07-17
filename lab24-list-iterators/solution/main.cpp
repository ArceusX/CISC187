#include <iostream>

#include "list.h"

int main() {
  using std::cout;
  using mesa::list;

  list<int> nums;
  cout << "MT\t";
  cout << nums << '\n';
  nums.push_front(4);
  nums.push_front(3);
  nums.push_front(2);
  nums.push_front(1);
  cout << "after pushes\t";
  cout << nums << '\n';

  auto it = nums.begin();
  // ++it;
  it = nums.insert_after(it, 99);
  cout << "after first insert\t";
  cout << nums << '\n';
  it = nums.insert_after(it, -1);
  cout << "after 2nd insert\t";
  cout << nums << '\n';
  it = nums.insert_after(it, 77);


  cout << "++ operators\t";
  it = nums.begin();
  cout << *++it << '\t';
  cout << *it++ << '\t';
  // incrementing postfix return values is disabled
  //
  // cout << *(it++)++ << '\n';

  cout << nums << '\n';
  cout << nums.front() << '\n';
  int& f = nums.front();
  f = 13;
  cout << "front is 13\t";
  cout << f << '\n';
  nums.erase_after(nums.begin());
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
