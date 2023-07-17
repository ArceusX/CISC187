# Bag class allocator

The goal of this lab is to enhance our generic bag
with the addition of an allocator.
Our bag class is fairly generic, 
but makes two major assumptions:

- Every type `T` has a default constructor
- `delete[]` will destroy memory in all bag elements when we are done

The standard library provides facilities that help solve both problems.
An *allocator* is an object that can create, manage, and destroy
unitialized storage.

Allocators are used by the C++ Standard Library to handle 
the allocation and deallocation of elements stored in containers.
Using an allocator gives writers and container users 
more control over how containers construct objects and allocate memory.

In this last step, we will refactor our bag to add an allocator.

## Steps

### 1. Copy bag files
Copy your `bag.h` from the previous lab,
or my solution into the `src` directory.

Run all the unit tests and make sure everything passes.

### 2. Bag allocator
This lab has 1 step, but it's a 'biggie'.
We are going to refactor 

Refactoring recipie:

1. Modify the template declaration to include an allocator type:

   ```cpp
   template<class T, class Allocator = std::allocator<T>>
   ```

   We set the default allocator to be one generated from `T`,
   but a caller is free to supply one.
   Everyone else who doesn't need it can ignore it.
1. Add a private member of the template `Allocator` type
1. Replace all instances of `new` and `delete` with `allocate` and `deallocate`.
   The destructor needs a final `destroy` as well.
   For example:

   ```cpp
   data_ = new T*[size_];
   data_[i] = value;
   delete[] data_;
   ```

   becomes

   ```cpp
   std::allocator_traits<Allocator>::allocate(allocator_, size_);
   
   std::allocator_traits<Allocator>::construct(allocator_, &data_[i], value);

   std::allocator_traits<Allocator>::deallocate(allocator_, data_, capacity_);


   for (size_t i = 0; i < size_; ++i) {
     std::allocator_traits<Allocator>::destroy(allocator_, &data_[i]);
   }

   ```

Because statements containing `std::allocator_traits<Allocator>::allocate` 
get long quickly, consider aliasing it:

```cpp
using memory = std::allocator_traits<Allocator>;

memory::allocate(allocator_, size_);

memory:construct(allocator_, &data_[i], value);

memory::deallocate(allocator_, data_, capacity_);

for (size_t i = 0; i < size_; ++i) {
 memory::destroy(allocator_, &data_[i]);
}

```

When finished, all the tests that passed before the change
should still all pass.

Finally, use valgrind to ensure you're not leaking any memory
or have created memory access errors.

Allocators are a complex part of C++ and they have changed in
C++17 and C++20.

## Turnitin
Check your progress by running `make test` or `ctest -V`.
This will attempt to run all tests.
Check partial progress by running the tests for a single step.
You can run tests for a single step with an IDE or ctest,
for example, `ctest -R step2`.

- Add your new and modified files: `git add . . . `
- Save your changes: `git commit . . . `
- Submit your work for grading: `git push`

