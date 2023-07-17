# Functions
The purpose of this lab is to practice working with
function parameters and namespaces.


## Pass by reference and pass by value: 2 points, 30 minutes *maximum*
This exercise is taken from
*Programming: Principles and Practice Using C++*.
Addison-Wesley Professional, 2nd edition,
June 2014. ISBN: 978-0321992789.

Given 3 functions:

```cpp
 void swap_v (int a, int b);
 void swap_r (int& a, int& b);
 void swap_cr(const int& a, const int& b);
```

And given that each function has the same body:

```cpp
   {
      int temp;
      temp = a;
      a = b;
      b = temp;
   }
```

This is a simple form of the *copy and swap idiom*.

Without compiling, 
determine the output of these functions and complete the table.
Not all of the examples in the table below will compile.

- Which of these calls compile?
- Provide a brief explanation of each function call

  - If it compiles, describe the result
  - If it does not compile, explain why

Given the following definitions of `x` and `y` when passed to `swap`:

```cpp
int x = 7;
int y = 9;
```

| Definitions and Function Call | Compiles | Explanation                             |
| ---                           | ---      | ---                                     |
| `swap_v(x,y);`                | Y        | Assigning to local copies to be deleted |
| `swap_r(x,y);`                | Y        | Correctly passing by reference          |
| `swap_cr(x,y);`               | N        | Error: Assigning to const references    |

And when the following literals are passed to `swap`:

| Definitions and Function Call | Compiles | Explanation                             |
| ---                           | ---      | ---                                     |
`swap_v(3,5);`                  | Y        | 3, 5                                    |
`swap_r(3,5);`                  | Y        | 5, 3                                    |

Given the following definitions of `cx` and `cy` when passed to `swap`:

```cpp
const int cx = 7;
const int cy = 9;
```

| Definitions and Function Call | Compiles | Explanation                            |
| ---                            | ---     | ---                                    |
| `swap_v(cx,cy);`               | Y       | Creating copy of const ref allowed     |
| `swap_r(cx,cy);`               | N       | Error: Binding const ref to ref        |

And when the following literals are passed to `swap`:

| Definitions and Function Call | Compiles | Explanation                            |
| ---                           | ---      | ---                                    |
| `swap_v(3.5,8.13);`           | Y        | float casted to int                    |
| `swap_r(3.5,8.13);`           | N        | Error: Binding ref to that with no ref |

Given the following definitions of `dx` and `dy` when passed to `swap`:

```cpp
double dx = 3.5;
double dy = 8.13;
```

| Definitions and Function Call | Compiles | Explanation                            |
| ---                           | ---      | ---                                    |
| `swap_v(dx,dy);`              | Y        | double casted to int                   |
| `swap_r(dx,dy);`              | N        | Error: Binding ref to that with no ref |
|                               |          | (once copy casted)                     |


## Debugging: 2 points, 30 minutes
Examine the program provided in the src folder.

What is the expected output? Record your answer here.


Now compile and run the program `src/lab5`.
What is the actual output?


What is wrong with this program?  What changes need to be made to fix it?

Make your changes, make sure the program compiles and runs.
When complete, the program should print:

```
original values:
a: 10, b: 20
after swap and add:
a: 21, b: 11
```
when running with default arguments.

The program in lab5.cpp compiles (completes the swap), but fails the assert, 
because the user-defined function void swap(long& x, long& y) is not actually called,
but rather the built-in std::swap() (T& a, T& b), which does not add 1. To see this,
rename the user-defined function to swap_r. Changing user-defined swap to swap(int& x, int& y) 
passes the assert.

## Turnitin

- Add your new and modified files: `git add . . .`
- Save your changes: `git commit . . .`
- Submit your work for grading: `git push`

## Reflection
When you are done, take a moment to 
[rate this lab](https://forms.gle/BRqfZsgapTvPdk159).


