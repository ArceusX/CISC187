# C/C++ Review
Review the core programming concepts you learned in your first semester of C or C++.

## Overview
The primary objective of this first lab is to review
programming concepts from your first semester and
to begin working with unit tests.

This is a group assignment.
Everyone will be organized into groups of 3 or 4 people.

Before you start, complete the form below and assign a role to each member in your group. 
If your group has 3 people, combine the Speaker and Reflector roles.

Everyone should perform all of these steps individually in order to familiarize 
yourself with the basics, but you are free to help eachother as you go.

The work submitted by the **Recorder** will be graded for the entire team.

| Team Role | Team Member|
------------- | -------------
**Recorder:** records all answers & questions and provides to instructor.  | (name)
**Speaker:** talks to instructor.  | (name)
**Manager:** keeps track of time and ensures everyone contributes appropriately. | (name)
**Questioner:** question actions and decisions made by the team. | (name)

## Making Change: 2.5 points, 30 minutes *maximum*
1. In your own words, without simply rewriting the code as plain text,
describe what [this function](src/change.cpp) is attempting to do:

2. Work through the logic manually (without compiling). 

   Write down the expected return value.

3. Compile and run the `test_change` program on buffy.
   What values are actually returned?

4. Did the actual output match your expectations?


   What do you think the problem is?

5. Run the example program in the 
   [sign and magnitude](https://daveparillo.github.io/cisc187-reader/c_review/types.html#sign-and-magnitude)
   section of course reader.

   Compare the exponent and mantissa for the different values. See any patterns?

   How might some representations create problems like the ones encountered in `test_change`?

   Find at least 3 other values with troublesome floating point representations.

6. How many more floating point numbers with approximate representations
   do you think you could find, if you looked?

   What is the key programming 'lesson learned' here?

7. Fix the code in `change.h` and `change.cpp` so that it passes the tests.

## Code reading: 1 point, 30 minutes *maximum*
For each of the problems that follow,
describe the intended program output, if any, and
whether the program compiles or not.

If it doesn't compile or produces unintended output,
then describe what changes could be made to fix it?

**Reading #1**

```cpp
#include <iostream>
#include <string>

int main () {
  const std::string dudes[4] = {"paco", "fred", "connor", "shoney"};
  for (int i = 0; i <= 4; ++i) {
    std::cout << dudes[i] << '\n';
  }
  return 0;
}
```

What is the output?

What is the problem (if any) and what needs to change to fix it?

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

What is the output?

What is the problem (if any) and what needs to change to fix it?

**Reading #3**

```cpp
#include <iostream>
#include <string>

int main () {
  int sa[4][3] = {{1,2,3,4}, {5,6,7}};

  std::cout << "first: " << sa[0][0] << '\n';
  std::cout << "last:  " << sa[4][3] << '\n'; 
}
```

What is the output?

What is the problem (if any) and what needs to change to fix it?

## Expressions: 0.5 points, 30 minutes
For each expression below, write the result and describe the expression in plain english,
for example:

```cpp
double x = 2 * (2+3);
```

`x = 10`. *Add 2 and 3 and then multiply the result by 2.
Assign the result to x.*

If an operator appears unfamiliar to you, refer to
https://en.cppreference.com/w/cpp/language/expressions#Operators

a.  
```cpp
double x = 5 + 1/2;
```

b.  
```cpp
double x = 5 + 1/2.0;
```

c.  
```cpp
double x = 5 + 2^3;
```

d.  
```cpp
double x = (int) 5.0 << 1;
```

e.  
```cpp
auto x = 5 & 2;
```

f.  
```cpp
auto x = 5 | 2;
```

## Turnitin
Check your progress by running `make test` or `ctest -V`.

- Add your new and modified source files: 
  ```console
  git add src README.md
  ```
- Save your changes: 
  ```console
  git commit -m 'finish lab2'
  ```
- Submit your work for grading: 
  ```console
  git push
  ```

## Reflection
When you are done, take a moment to [rate this lab](https://forms.gle/mysDh7AUxo1nBA8Y8).

