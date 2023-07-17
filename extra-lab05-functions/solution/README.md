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
Which of these calls compile?
Provide an explanation for each function call that does not compile.

Given the following definitions of `x` and `y` when passed to `swap`:

```cpp
int x = 7;
int y = 9;
```

| Definitions and Function Call | Compiles (Y/N) | Explanation |
| ---                           | ---            | ---         |
| `swap_v(x,y);`                | Y              | The values are copied, then swapped.  The swaped values are lost when the function `swap_v` returns |
| `swap_r(x,y);`                | Y              | The values referred to by `x` and `y` are swapped |
| `swap_cr(x,y);`               | N              | Can't change the values of constant parameters `a` and `b` |

And when the following literals are passed to `swap`:

| Definitions and Function Call | Compiles (Y/N) | Explanation       |
| ---                           | ---            | ---               |
`swap_v(3,5);`                  | Y              | The values are copied, then swapped.  The swaped values are lost when the function `swap_v` returns |
`swap_r(3,5);`                  | N              | Can't swap a literal - no storage for a reference to refer to |

Given the following definitions of `cx` and `cy` when passed to `swap`:

```cpp
const int cx = 7;
const int cy = 9;
```

| Definitions and Function Call | Compiles (Y/N) | Explanation       |
| ---                            | ---           | ---               |
| `swap_v(cx,cy);`               | Y             | The values are copied, then swapped.  The swaped values are lost when the function `swap_v` returns                   |
| `swap_r(cx,cy);`               | N             | Can't change the values of constant parameters `a` and `b` |

And when the following literals are passed to `swap`:

| Definitions and Function Call | Compiles (Y/N) | Explanation           |
| ---                               | ---            | ---               |
| `swap_v(3.5,8.13);`               | Y              | Values are copied, *truncated*, and swapped. Swapped values are discarded when function returns. |
| `swap_r(3.5,8.13);`               | N              | Can't convert a double to an integer reference |

Given the following definitions of `dx` and `dy` when passed to `swap`:

```cpp
double dx = 3.5;
double dy = 8.13;
```

| Definitions and Function Call | Compiles (Y/N) | Explanation       |
| ---                           | ---            | ---               |
| `swap_v(dx,dy);`              | Y              | values are copied, truncated, and swapped. Swapped values are lost when function returns. |
| `swap_r(dx,dy);`              | N              | Can't convert from double to int& |


## Debugging: 2 points, 30 minutes
Examine the program provided in the src folder.

What is the expected output? Record your answer here.

```
original values:
a: 10, b: 20
after swap and add:
a: 21, b: 11
```


Now compile and run the program `src/lab5`.
What is the actual output?

with no command line arguments:

```
original values:
a: 10, b: 20
after swap and add:
a: 20, b: 10
abort
```

**What is wrong with this program?**

The fatal flaw in this program is using a

```cpp
using namespace std;
```

directive, and then not realizing the code in main() never calls the swap function 
defined in same translation unit.

Because the values in main are type int,
but the swap function takes parameters of type long,
the compiler (assuming you know what you are doing)
deduces that

```cpp
std::swap (int, int)
```

is a better match and calls that function instead.

This happens to inexperienced programmers more often than you might think.

This kind of unexpected behavior is why many programmers 
avoid `using namespace std`
in general and NEVER put it in an include file.



**What changes need to be made to fix it?**

There are several ways to fix this program.

Perhaps the most important thing to note is that the swap provided breaks
the first 'rule of functions': it does two things at once.

First remove the line 'using namespace std'.

Then add `using std::cout`, or just prepend 'std::' whenere needed.

Other changes are a matter of taste.
You could:

1. change the types in main to match the function
2. change the swap function to match the types in main

which is what the `v2` solution does,
but that is still not ideal.

the solution `lab5.cpp` deletes the swap function completely
and simply calls:

```cpp
std::swap(++a, ++b);
```

Sometimes less is more.

If a standard library function already exists and it meets your needs,
then use it.


Make your changes, make sure the program compiles and runs.
When complete, the program should print:

```
original values:
a: 10, b: 20
after swap and add:
a: 21, b: 11
```

when running with default arguments.

## Turnitin

- Add your new and modified files: `git add . . .`
- Save your changes: `git commit . . .`
- Submit your work for grading: `git push`


