# Sort detective solution
Not all every clue is needed to discriminate among the sorts
and in your solution you may have chosen a sort by 
process of elimination, which is acceptable.

These are the behaviors I picked on to discriminate the sorts.
You may have chosen others, which is also acceptable.

## TL;DR
A summary of the sort mappings is in the table below

| Sort    | Solution       |
| ----    | -----------    |
| alpha   | Heap sort      |
| beta    | Insertion sort |
| gamma   | Quick sort     |
| delta   | Shell sort     |
| epsilon | Bubble sort    |
| zeta    | Merge sort     |
| theta   | Selection sort |

# Analysis Summary
Sorts can be grouped into 2 broad categories:

- Exchange sorts
- Partitioning sorts

Exchange sorts will all make `n(n+1) / 2` comparisons on data.
Exchange sorts are always comparing adjacent elements.

Sorts beta, epsilon, and theta all sometimes generate exactly 
`n(n+1) / 2` comparisons on data.
These are our 3 exchange sorts.

Partitioning sorts use different strategies to partition a data set
and work on each partition (sometimes independently)
working towards a final solution.

Sorts alpha, gamma, delta, and zeta are the non-exchange sorts.

# Exchange sort analysis

## Bubble sort
1. The total number of comparisons is the sum of the first `n-1` integers
1. In the best case, if the array is already ordered, no exchanges will be made
1. In the worst case, every comparison will cause an exchange (3 moves)

Same # comparisons as beta, but more exchanges.

| Length (N) | Ordering | Sort  | Comparisons | Movements | Comment         |
| ---        |  ---     | ----  | ----------- | --------- | --------------- |
|32|random|epsilon|496|714| case #1: 496 = 31(31+1)/2|
|100|random order|epsilon|4950|7164|0 |
|32|reverse order|epsilon|496|1488|worst case: #3 |
|100|in order ascending|epsilon|4950|0|case #2: No movements |

Therefore, epsilon is the bubble sort.

## Selection sort
1. Same comparisons as bubble sort with fewer exchanges
1. No exchanges on sorted data


| Length (N) | Ordering | Sort  | Comparisons | Movements | Comments        |
| ---        |  ---     | ----  | ----------- | --------- | --------------- |
|32|random order|theta|496|81|case #1: fewer swaps than epsilon |
|100|random order|theta|4950|288| case #1: fewer swaps than epsilon |
|1000|random order|beta|499500|2973| grows at n^2 rate on random data |
|32|in order ascending|theta|496|0| case #2: No movements on sorted data |
|32|reverse order|theta|496|48| Fewest exchanges for reversed data |
|100|reverse order|theta|4950|150| Fewest exchanges for reversed data  |

## Insertion
- The max number of comparisons is the sum of the first `n-1` integers
  but in the best case, only one comparison needs to be done each pass

| Length (N) | Ordering | Sort  | Comparisons | Movements | Comments |
| ---        |  ---     | ----  | ----------- | --------- | --------------- |
|32|random order|beta|269|331|fewer comparisons than epsilon and theta |
|32|random order|beta|201|263| fewer swaps than epsilon |
|100|random order|beta|2394|2592| more swaps than theta |
|1000|random order|beta|246499|248497| grows at n^2 rate on random data |
|32|reverse order|beta|496|558|`n(n+1) / 2`comparisons worst case |
|100|reverse order|beta|4950|5148| `n(n+1) / 2` comparisons |
|32|in order ascending|beta|31|62| `n-1` comparisons for ordered data |

# Partitioning sort analysis

## Quick sort
The quick sort is an `O(n log(n)` sort with two interesting characteristics:
- It is is `O(n)` in the best case
- It makes `n^2` recursive calls in the worst case.
- Worst performance is on already sorted and reversed data

  This makes quick sort susceptible to stack overflow errors on large data sets.

Even though merge sort, heap sort, and quick sort are all recursive,
it is the recursive calls in quick sort that grow at the fastest rate.
Data sets have to be extremely large before merge and heap sorts suffer
a stack overflow on most modern computers.

| Length (N) | Ordering | Sort  | Comparisons | Movements | Comments |
| ---        |  ---     | ----  | ----------- | --------- | --------------- |
|100|random order|gamma|668|606| |
|1000|random order|gamma|13590|8061| growth less than n^2 |
|100|in order ascending|gamma|4950|297| |
|1000|in order ascending|gamma|499500|2997| n^2 comparisons on ordered data|
|10000|in order ascending|gamma|49995000|29997| Note 1 |
|100000|reverse order|gamma| -- | -- | seg fault |

**Note 1**

Notice the growth in the comparisons and movements when the data is already sorted.

## Merge sort
The merge sort is an `O(n log(n)` sort.
It is the only sort in our list that is also `Omega(n*log(n))` in the worst case.

The data shows it is insenstive to the order of the data originally provided.
There is some overhead involved in creating sub-arrays during the sorting process.

Note the worst case sort performance is *not* `n^2` in the worst case.

| Length (N) | Ordering | Sort  | Comparisons | Movements | Sort time(msec) |
| ---        |  ---     | ----  | ----------- | --------- | --------------- |
|100|in order ascending|zeta|316|356|0 |
|1000|in order ascending|zeta|4932|5044|0 |
|10000|in order ascending|zeta|64608|69008|1 |
|100|reverse order|zeta|356|672|0 |
|1000|reverse order|zeta|5044|9976|0 |
|10000|reverse order|zeta|69008|133616|1 |
|100|random order|zeta|457|475|0 |
|100|random order|zeta|436|525|0 |
|1000|random order|zeta|7197|6315|0 |
|1000|random order|zeta|7295|6080|0 |
|10000|random order|zeta|94093|93144|1 |
|10000|random order|zeta|102261|83501|1 |
|999000|random order|zeta|14568688|12646324|172 |



## Heap sort
The heap sort is an `O(n log(n)` sort.

We should expect heap sort performance to be very similar to merge sort,
but slightly worse in the worst case.
For many data sets, the differences may be a toss up,
But generally, merge sort should outperform heap in terms of
comparisons and movements, but because of the additional storage requirements
in merge sort can make the heap sort run time faster.

Note the worst case sort perforamnce is *not* `n^2` in the worst case.

| Length (N) | Ordering | Sort  | Comparisons | Movements | Sort time(msec) |
| ---        |  ---     | ----  | ----------- | --------- | --------------- |
|100|in order ascending|alpha|1094|1136|0 |
|1000|in order ascending|alpha|17626|14704|0 |
|10000|in order ascending|alpha|244576|181952|0 |
|100|reverse order|alpha|956|1012|0 |
|1000|reverse order|alpha|15982|13312|0 |
|10000|reverse order|alpha|226720|166692|0 |
|100|random order|alpha|1036|1079|0 |
|1000|random order|alpha|16856|14059|0 |
|10000|random order|alpha|235446|174162|0 |
|999000|random order|alpha|36754382|24022890|113 |


## Shell sort
The shell sort is an `O(n log(n)` sort, but `n^2` in the worst case.

Notice that when the number of elements increases 10x,
then run time grows much larger than 10x.
Another characteristic of shell sort is that the number of movements
is consistently (roughly) 1.5 times the number of comparisons,
regardless of the original element order.

| Length (N) | Ordering | Sort  | Comparisons | Movements | Sort time(msec) |
| ---        |  ---     | ----  | ----------- | --------- | --------------- |
|100|reverse order|delta|763|1266|0 |
|1000|reverse order|delta|12706|20712|0 |
|10000|reverse order|delta|182565|302570|14 |
|100000|reverse order|delta|2344566|3844572|1807 |
|100|random order|delta|865|1368|0 |
|10000|random order|delta|261789|381794|18 |
|100000|random order|delta|4320101|5820107|1807 |

