# C/C++ Review
Review the core programming concepts you learned in your first semester of C or C++.

Name: Dave Parillo

## Overview
The primary objective of this first lab is to review
programming concepts from your first semester and
to begin working with unit tests.

## Making Change: 2.5 points, 30 minutes *maximum*
1. In your own words, without simply rewriting the code as plain text,
describe what [this function](src/change.cpp) is attempting to do:

   Purchase items, starting at 10 cents, 
  each additional purchase costs 10 additional cents.

2. Work through the logic manually (without compiling). 

   Write down the expected return value.

   Most people logically assume the values would be:

   ```
   purchase.items = 4
   purchase.funds = 0
   ```

   If not, you either missed the equality check in the for loop 
   terminating condition `funds >= price`
   Or you have already figured the entire lab out.


3. Compile and run the `test_change` program on buffy.
   What values are actually returned?

   ```
   purchase.items = 3
   purchase.funds = 0.4
   ```

4. Did the actual output match your expectations?

   Most people are surprised at the actual results.

   What do you think the problem is?

   When this happens to people 'in the wild',
   most people think the problem involves the loop in some way and
   spend a lot of time trying to fix a problem that does not exist.

   The fundamental problem is the *type* of data used to store price.

5. Run the example program in the 
   [sign and magnitude](https://daveparillo.github.io/cisc187-reader/beginnings/types.rst)
   section of course reader.

   Compare the exponent and mantissa for the different values. See any patterns?

   You should have noticed that the value `0.1` has a very different bit
   representation from the other numbers.
   Even values close to 0.1 in value have very different underlying representations.

   How might some representations create problems like the ones encountered in `test_change`?

   If a number has a repeating bit pattern then it will *by definition* be
   only an approximate value, even if the value is not a decimal with an
   infinte decimal expansion.

   These kinds of problems afre a common source of error in real world code written
   in many languages, not just C++.

   Find at least 3 other values with troublesome floating point representations.

   - Any decimal value that is not a multiple of 0.5.
   - Any integer value with less than `X` bits in the exponent expansion.

     The value of `X` will vary by operating system, but on my computer for example,
     the value `12345600` has an exact representation, while
     the value `12345678` does not.

6. How many more floating point numbers with approximate representations
   do you think you could find, if you looked?

   See above: there is a **very** large number of floating point numbers
   with this problem.

   And no, if you change `float` to `double` it doesn't make things better.

   Although most people know that a number like `1/9` has an 
   infitely repeating decimal expansion and that 
   division can easily result in lack of precision,
   it is less intuitive that simple subtraction can cause it as well.
   The problem here is that the number 0.1 can only be approximated on a computer,
   it can’t be represented exactly.

   If we only had 30 cents instead of a dollar,
   we would have never seen this problem -
   or perhaps we might not have seen it until we had run this code
   many times and then suddenly been confused when code we hadn't
   modified stopped working correctly or expressed a 'new' bug.
   This problem affects professional programmers if they are not careful.

   What is the key programming 'lesson learned' here?

   There are two fundamental lessons learned from this example:

   1) Never use floating point numbers when exact answers are required.
   2) Never check floating point numbers for equality.

   And in case you were wondering, no, this is not a C++ problem.
   In fact, this example was adapted from Effective Java, by Josh Bloch.

   This problem is a general limitation related to how
   floating point numbers are stored on a computer.

7. Fix the code in `change.h` and `change.cpp` so that it passes the tests.

   The real problem here is a design problem.
   The data type chosen for price is not fit for use in this situation.
   The fix is to changes the units from dollars to cents.
   Replace all the doubles with ints.

## Code reading: 1 point, 30 minutes *maximum*
For each of the problems that follow,
describe the intended program output, if any, and
whether the program compiles or not.

If it doesn't compile or produces unintended output,
what changes could be made to fix it?

**Reading #1**

```cpp
#include <iostream>
#include <string>

int main () {
  const std::string dudes[4] = {"paco", "fred", "connor", "shoney"};
  for (int i = 0; i <= 4; ++i) {
    std::cout << dudes[i] << std::endl;
  }
  return 0;
}
```

What is the problem (if any)?

This compiles and runs.

The array index in the for loop is wrong and displays random garbage when i == 4.

Fixed code:

```cpp
#include <iostream>
#include <string>

int main () {
  const std::string dudes[4] = {"paco", "fred", "connor", "shoney"};
  for (int i = 0; i < 4; ++i) {
    std::cout << dudes[i] << std::endl;
  }
  return 0;
}
```

**Reading #2**

```cpp
#include <iostream>

int main () {
  double x;
  double y = x;
  double z = 2.0 + x;

  std::cout << y << " and " << z << ".\n";
  return 0;
}
```
What is the problem (if any)?

This compiles and runs.

The values for these 3 doubles is unpredictable because x is declared, but not initialized.
There is no "sure fire" way to know in advance what value will be assigned to `y`.
The value is might change each time the program is run
or if run on different computers,
of if compiled on the same computer using different compilers.
    
Fixed code:

```cpp
#include <iostream>

int main () {
  double x = 0;
  double y = x;
  double z = 2.0 + x;

  std::cout << y << " and " << z << ".\n";
  return 0;
}
```



**Reading #3**

```cpp
#include <iostream>
#include <string>

int main () {
  for (int i = 0; i < 9; ++i) {
    int x = 5;
    std::string pet = "Dog - ";
    if (i < 3) {
      ++x;
    } else {
      x += 2;
    }
  }
  std::cout << pet << x << '\n';
}
```

What is the problem (if any)?

As written this does not compile.
The variables pet and x are out of scope when used on line 12.

Fixed code:

```cpp
#include <iostream>
#include <string>

int main () {
  int x = 5;
  std::string pet = "Dog - ";
  for (int i = 0; i < 9; ++i) {
    if (i < 3) {
      ++x;
    } else {
      x += 2;
    }
  }
  std::cout << pet << x << '\n';
}
```

This just one possible fix.
With this fix, the result is `Dog - 20`.


**Reading #4**

```cpp
#include <iostream>
#include <string>

int main () {
  int sa[4][3] = {{1,2,3,4}, {5,6,7}};

  std::cout << "first: " << sa[0][0] << '\n';
  std::cout << "last:  " << sa[4][3] << '\n'; 
}
```

What is the problem (if any)?

This program appears to want to display the first and last elements of the two-dimensional array sa.

It has multiple problems.

Assuming the values in the initializer list are what was really desired, the declaration is wrong.
`int [4][3]` declares **4 arrays** with **3 elements each** - NOT a 4x3 array.
It is also attempting to access values off the end of this array.

Only the first two arrays are explicitly initialized.

This is legal!

The last two are implicitly initialized to 0.
The last element in the fourth array (0) is at position `[3][2]`, not `[4][3]`.

The last initialized element (7) is at position`[1][2]`.
    
Fixed code:

```cpp
#include <iostream>
#include <string>

int main () {
  int sa[4][3] = {{1,2,3}, {5,6,7}};

  std::cout << "first: " << sa[0][0] << std::endl;
  std::cout << "last:  " << sa[3][2] << std::endl;
}
```

## Expressions: 0.5 points, 30 minutes
For each expression below, write the expression in plain english,
for example:

```cpp
double x = 2 * (2+3);
```

*Add 2 and 3 and then multiply the result by 2.
Assign the result to x.*

If an operator appears unfamiliar to you, refer to
http://en.cppreference.com/w/cpp/

**Note:** All of these examples compile.

There are languages in which these expressions fail to compile
but C++ is very forgiving.
C++ assumes you know what you are doing.


a.  
```cpp
double x = 5 + 1/2;           // result = 5
```

Divide 2 into 1 (0), then add nothing to 5, convert to a double and
assign the result to x.

b.  
```cpp
double x = 5 + 1/2.0;         // result = 5.5
```

Divide 2 into 1, then add .5 to 5 and assign the result to x.

c.  
```cpp
double x = 5 + 2^3;
```

Add 2 and 5, the "exclusivly or" the result with 3.
Assign 4 to x.

The white space is misleading here.
Order of operations: addition first, then '^', 
which is exclusive or, not an exponent operator.
There is not an exponent operator in C++.

When operating with bit operators, it is always the bits being manipulated, so:
```
5 + 2 ^ 3 = 7 ^ 3
```

The bit representation of 7 = '111' and 3 = '011'.
If two bits are exclusively or'ed, the result is 1 only if one bit = 0 and the other = 1.

```
    1 1 1  (7)
  ^ 0 1 1  (3)
    -----
    1 0 0  (4)
```
 
 The int representation of '100' = 4.

```
f.  
```cpp
double x = (int) 5.0 << 1;        // result = 10
```

Convert 5.0 to an integer and shift the bits in 5 1 position left.
Assign 10 to x.

The `operator<<` is the 'bit shift left' operator.

Each bit in the number is shifted one position to the left.
The first operand (10) is read as bits.
The second operand is treated as a regular number and is the number of bit positions to shift.

```
1 0 1 << 1 = 1 0 1 0
```

The int representation of '1010' = 10.

e.  
```cpp
auto x = 5 & 2;
```

`operator&` is the 'bitwise and' operator.
Compare each bit in 5 with each bit in 2.
If both bits equal 1, then set that bit in the result.
Since no bits are both set in the same position in these values,
`x` is initialized to 0.

The type of `x` is `int`.

```
    1 0 1. (5)
  & 0 1 0. (2)
    -----
    0 0 0. (0)
```

f.  
```cpp
auto x = 5 | 2;
```

`operator|` is the 'bitwise or' operator.
Compare each bit in 5 with each bit in 2.
If either bit equals 1, then set that bit in the result.
Since the first 3 bits are set in the either 2 or 5
`x` is initialized to 7.

The type of `x` is `int`.

```
    1 0 1. (5)
  | 0 1 0. (2)
    -----
    1 1 1. (7)
```


## Turnitin
Check your progress by running `make test` or `ctest -V`.

- Add your new and modified source files: 
  ```
  git add src
  git add README.md
  ```
- Save your changes: `git commit -m 'finished lab2'`
- Submit your work for grading: `git push`


