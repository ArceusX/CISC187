1. Insertion Sort     
    
I remember this one! This was a sorting algo I used to sort books as a
library assistant. I think it is the one that comes most naturally to most people.
We start expanding the "currently sorted" region from the leftmost book.
Basically, one book by itself is considered sorted just like a list with one item is
considered sorted. Then, look at the next item in the unsorted region (initially
all the items). Compare it to all the previously sorted items. Place it in the
appropriate location among the sorted, or if it is larger than all the previous sorted
item, keep it where it is. All the items in the sorted region are considered sorted
among themselves, but the rest of the list still needs to be sorted.
The goal of insertion sort is to expand the sorted region and when that region comprises
the entire list, the original list is considered fully sorted.   
    
There's a push that required when placing an item in its new position that I think is the most
inefficient part of insertion sort, but it shouldn't be so bad if the list is nearly sorted
and necessary swaps don't happen often.   
   
2. Selection Sort   
    
Basically, I would look in a section/subject, find current unsorted book with the smallest
"order" (author's last name), take it out (the computer would keep a reference to it),
and place it back in on the leftmost still unsorted region (the computer would
swap that smallest unsorted item with the item occupying the spot it wants to go).

Selection sort is pretty nice, better than bubble sort, but when sorting books physically,
I found it to be less efficient and effortful than insertion sort. Most sections in the
library are almost nearly sorted, so often the slot intended for the kth smallest item
already contains the kth smallest item (the book and slot match). Selection sorted forced
me to verify that it is indeed the kth smallest item, and it almost always is for a nearly
sorted list, and most of the checks are true, but I have to verify, and that makes selection
sort somewhat inefficient.

When sorting books, I prefer insertion sort, especially for a list that nearly sorted.

3. Bubble sort
    
Technically, I know insertion, selection, and bubble sort are all O(n^2) in the
worst and average cases. But bubble sort is just a pain. It is like a worse insertion sort.
Starting from first item, compare every adjacent pair, swap their position if the right one
(higher index) is smaller than the left one (lower index). After each iteration, one less
item is needed to be compared until there are no more items left to be compared.
     
Bubble sort is horrendous because it requires many swaps (physically, taking a book out, then
putting it into a new position). But it doesn't require many swaps for a nearly sorted list.    
     
--------------------------------   
    

sort-detective -f markdown -o ordered -l 256    
------ Experiment -------
Length (N):      256
Ordering:        in order ascending   
   
|256|in order ascending|alpha|3458|3248|0 |   
|256|in order ascending|beta |255|510|0 |   
|256|in order ascending|gamma|32640|765|0 |    
|256|in order ascending|delta|1793|3586|0 |    
|256|in order ascending|zeta|1024|2048|0 |   
    
|256|in order ascending|theta|32640|0|0 |    

|256|in order ascending|epsilon|32640|0|0 |    

On a list that's already sorted, algos theta and epsilon are the only algos that do    
no swap. The only algos out of the seven given that bear that result to already sorted
data are inertion and bubble sort. Theta or epsilon must be insertion or bubble.    
    
On other aspects of sortedness (eg random), insertion performs better than bubble.    
    
Random   
sort-detective -f markdown -o random -l 256   
    
|256|random|epsilon|32640|50100|0 |   
    
|256|random|theta|32640|747|0 |
    
Theta performs better than epsilon on random data.     
**Theta must be insertion and epsilon must be bubble.**    
     

sort-detective -f markdown -o ordered -l 256
|256|in order ascending|gamma|32640|765|0 |    

|256|in order ascending|theta|32640|0|0 |   

On sorted data, gamma does the same number of comparisons as theta, which I surmise is insertion
sort, but more swaps than theta. Shellsort is based on insertion sort, so given the similarity
between gamma and theta, and between shellshort and insertion sort, **gamma is shellsort.**    
     
sort-detective -f markdown -o reverse -l 2048  
|2048|reverse order|alpha|37002|29490|0 |     
|2048|reverse order|beta|2047|2100222|3 |    
|2048|reverse order|delta|31745|52226|0 |    
|2048|reverse order|zeta|11264|22528|0 |    
     
|2048|reverse order|epsilon|2096128|6288384|3 |    
|2048|reverse order|gamma|2098175|6144|4 |    
|2048|reverse order|theta|2096128|3072|1 |
    
Of the algos I have yet to identify, beta takes the longest time (3 msec) on reverse sorted
data of size n=2048, while all the unidentified algos take no measureable time.
**Beta must be selection**, which is known to be slow for large data and reversed data.    
    
sort-detective -f markdown -o random -l 30000   
|30000|random order|alpha|800764|569730|2 |    
|30000|random order|delta|944930|1334937|134 |
|30000|random order|zeta|408462|447232|5 |
    
For a large array size (n = 30000), for the remaining identified algos (alpha, delta, zeta),
delta is the slowest and out of the remaining heapsort, quicksort, and mergesort, mergesort
is the slowest on large array size, so **delta is mergesort.**    
    
Quicksort and heapsort perform similarly, but heapsort performs better on large datasets,
and for this large dataset, alpha takes a shorter time than zeta,    
so I think **alpha is heapsort and zeta is quicksort.**    
    
In summary, I think   
    
**alpha == heapsort**   
**beta == selection sort**   
**gamma == shellsort**   
**delta == megesort**  
**epsilon == bubble sort**   
**zeta == quicksort**  
**theta == insertion sort**   
   
   
# Sort Detective
The goal of this lab is to use a program which allows you to measure
the behavior of 7 different sorting algorithm implementations.
It runs the selected sort and displays
total number of comparisons,
total data movements, and
total execution time in milliseconds.
You must apply your understanding of the general properties of the algorithms
(and in some cases of the code used to implement them)
to determine which algorithm is associated with each sort option.

A secondary objective of this lab is for you to gain experience writing a concise,
but complete analysis of a system.

## Game Plan
As you alerady know,
if you double the size of the data set that you give to a quadratic algorithm,
it will do four times the work.
In contrast, an `O(n log n)` algorithm will do a bit more than twice as much.
A linear algorithm will do only twice as much work.
Also recall the characteristics of the input data set can affect the expected
performance of many of our sorting algorithms.
For example, some algorithms perform differently when the data sets is nearly
sorted, perfectly sorted, or very large or small.
Before you begin the lab,
you should review the expected performance of the algorithms on various data sets.

The sorting algorithms under study this week include (in alphabetical order):

- Bubble Sort,
- Heap Sort,
- Insertion Sort,
- Merge Sort,
- Quick Sort,
- Selection Sort, and
- Shell Sort.

| **Note** |
| :--------: |
| Read all of the following before beginning |

## Steps

### 1. Explore sort program
Run the program `sort-detective` installed on the Mesa server.
It should be in your path.

Make sure you can run this program and play with it a bit.

The **first** thing you should do is run `sort-detective -h`
and understand the options available.

Notice that the sort option names do not give any indication which sort
they will execute.

### 2. Make a plan
Devise a plan which will enable you to match an algorithm to a sort name.

It may make sense to try to divide the sorts into initial groups and
then to work on each group separately.
Divide and conquer: it works for algorithms and it can work here, too.

### 3. Execute your plan
Execute your plan, taking careful notes as you go.

The SortLab does not store results from previous runs,
so it is up to you to record results as you go.

## 4. Document results
Describe the results of your experiment in a summary document.
Begin with a two column table listing each sort option by name
(alpha, beta, etc.) and the sort that goes with it.

**Ensure you justify your results!!**

- Simply listing which options perform which sorts
  is **not** enough documentation to earn credit.
- Dumping or listing a bunch of data with little or no explanation
  is **not** enough documentation to earn credit.

**Collecting data**

The program will provide the following data, as an example:

| Length (N) | Ordering | Sort  | Comparisons | Movements | Sort time(msec) |
| ---        |  ---     | ----  | ----------- | --------- | --------------- |
|32 | random | alpha | 496 | 687 | 0 |

The program can provide data as plain text,
in CSV format suitable for copying into a spreadsheet,
and in markdown format, suitable for adding to a document on GitHub.


**Writing Notes**

There is no coding in this lab.
Expect a significant portion of the lab grade will be determined by
the quality of the writing of the report.
This includes the completeness of the report,
the clarity (and grammar) of the writing, and general presentation.

Some of the sorts are difficult to distinguish.
A carefully outlined experiment may compensate for an error in these cases
if the writing makes it clear that your conclusions 
and/or guesses are substantiated by the data.

Finally, remember that your report needn't detail every experiment you ran.
Provide sufficient information to justify your conclusions.
It is possible to write a very short report that is completely correct
if your experiments are well chosen.

**Reports are not graded on length**, 
rather they are graded on **quality & correctness**. 
In fact, an extremely long report is an excellent indication you
probably don’t know what you are doing.
Plus you open yourself up to more opportunities to lose points due to mistakes.
After you discover the matching,
you might consider if there was a shorter way to arrive at your conclusion.

## Turnitin
Don't forget to commit your documents and notes when you are done.

- Add your new and modified files: `git add . . . `
- Save your changes: `git commit -m 'finish sort lab'`
- Submit your work for grading: `git push`

## Reflection
When you are done, take a moment to 
[rate this lab](https://forms.gle/MDwCzQCqRvtjGecz8).

