# Heaps
The goal of this lab is to introduce a min heap
and become familiar with their properties.

A **heap** is a type of *binary tree* with the following properties:

- The tree must be **complete**
- The order of elements must obey the *heap property*

For a **min-heap** a parent element must be `<=` all its children.

For a **max-heap** a parent element must be `>=` all its children.

Although conceptually a heap is a tree-like data structure,
because the tree must be complete, it fits easily into an array.
For a tree of height
![2^h -1 ](https://latex.codecogs.com/svg.image?2%5E%7Bh%7D-1)

- The parent of a node `i` is located ![i-1 over 2](https://latex.codecogs.com/svg.image?%5Cfrac%20%7Bi-1%7D%7B2%7D)
- The left child of a node `i` is located ![2i+1](https://latex.codecogs.com/svg.image?2i&plus;1)
- The right child of a node `i` is located ![2i+2](https://latex.codecogs.com/svg.image?2i&plus;2)

## Steps
For now, this is a "follow along" experience that we will all work
through together.

We will implement these functions:

```
front
insert
pop
clear
build_heap
percolate_down
percolate_up
```

## Turnitin
Check your progress by running `make test` or `ctest -V`.
This will attempt to run all tests.
Check partial progress by running the tests for a single step.
You can run tests for a single step with an IDE or ctest,
for example, `ctest -R step2`.

- Add your new and modified files: `git add . . . `
- Save your changes: `git commit . . . `
- Submit your work for grading: `git push`

## Reflection
When you are done, take a moment to 
[rate this lab](https://forms.gle/6MpBQCEFvBoKa9sr9).

