# Critters
This is a C++ version of a lab assignment originally offered
as far as I can tell, first at Univerity of Washington
School of Computer Science & Engineering, CSE 142: Computer Programming I.

see: http://courses.cs.washington.edu/courses/cse142/

The whole idea is that the game is incomplete -
you have to write the code to make
the critters move, fight, mate, and eat.

Besides a fun way to wrap up the term,
this project also provides additional insight into why
we separate interfaces from implementation.
In this lab, you are provided the interfaces to the few things you
need to interact completely in the game world, the main ones are:

- `critters.h`
- `direction.h`
- `add_player.h` and `add_player.cpp`

No other source code is needed.
It is already compiled into a library which includes a `main()`
function and all the capabilites you need.

Your job is to focus on a winning critter.

If you want to see the full source, you can on 
[GitHub](https://github.com/DaveParillo/critters).

# Basic gameplay
Runs the critters (Rock, Paper, Scissors) competition using 'critters' as
combatants. The combat occurs in a 2D grid 'world' with animals moving around.

The critter world is divided into cells with integer coordinates. 
The world size is determined by the console size when the program is started.
The upper-left cell has coordinates (0, 0); 
x increases to the right and y increases downward.

run with `-h` command line argument to see what options are available.

Refer to the
[api docs](http://209.129.16.61/~dparillo/cisc187/critters/docs)
for more info and to see what functions are available for critters.

If when running the program over an ssh connection, no colors appear,
try changing your terminal settings.  On the command line, try:

```
TERM="screen-256color"
```

The ncurses view should display colors if the environment supports it.
You may have to modify your putty settings if using ssh via putty.
There are many sites that might help get the putty settings correct,
for example 
http://serverfault.com/questions/475925/how-to-fix-putty-showing-garbled-characters
but in the Mesa environment things work if in the Window/Translation tab
the character set is set to 'Use font encodings'.

## Movement
During each game turn, 
the game controller asks each critter object for a move direction. 
Each round a critter can move one square in any of the 8 'cardinal' directions, 
or stay at its current location (direction::CENTER).

If a critter moves into an empty square, the critter takes no other action
on that move.
If a critter moves into an occupied square, this informs the game that the
critter intends to take an action with the item in the destination cell.
Examples of actions are fighting, mating, and eating.

The world has a finite size, but it wraps around in all four directions. 
For example, moving east from the eastern-most (i.e. right) edge brings you back 
to the western-most (i.e. left) edge. 
You might want your critters to make several moves at once using a loop, but you can't. 
The only way a critter moves is to wait for the game to ask it for a 
single move and return that move.

## Fighting
A fight always occurs if two critters of two different species attempt to occupy the same location.
The winner lives and the loser is removed from the game.
Each critter chooses one of the 4 possible Attack options.
Each attack is strong against one other attack (e.g. roar beats scratch) 
and weak against another (roar loses to pounce). 
The following table summarizes the choices and which critter will win in each case. 
To remember which beats which, notice that the starting letters of 
**R** oar, **P** ounce, **S** cratch match those of a (hopefully) more familiar game, 
**R** ock, **P** aper, **S** cissors. 

 - Rock smashes Scissors
 - Scissors cut Paper
 - Paper covers Rock

If the critters make the same choice, the result is a Draw.

|                |             |          | Critter #2 |             |             |
|----------------|:------------|:--------:|:----------:|:-----------:|:-----------:|
|                |             | **ROAR** | **POUNCE** | **SCRATCH** | **FORFEIT** |
|                | **ROAR**    |   Draw   |   #2 wins  | #1 wins     |  #1 wins    |
| **Critter #1** | **POUNCE**  | #1 wins  |    Draw    | #2 wins     |  #1 wins    |
|                | **SCRATCH** | #2 wins  |   #1 wins  |   Draw      |  #1 wins    |
|                | **FORFEIT** | #2 wins  |   #2 wins  | #2 wins     |    Draw     |

## Mating
If two animals of the same species collide, they "mate" to produce a baby. 
Mating is optional - you are not obligated to move onto a critter of the same species.
Critters are vulnerable to attack while mating: 

- Any other species that attacks them wins automatically. 
- A critter can initiate mating only once during its lifetime.

Mating has high risks, but also high rewards.
Mating is the only way to add to your total critter count.
Not only does that increase your score (assuming you survive parenting),
but you also get a new helper to eat, kill, and mate.

## Eating
There is food on the world initially, and new food is added as consumed. 
As a critter moves, it may encounter food, in which case the game will ask your
critter whether it wants to eat it. 
Eating is optional - even when moving onto food, you don't have to eat it.
Eating always incurs a small risk - sleeping for at least 5 turns.
If a critter overindulges, then that critter will be forced to 
"sleep off" their gluttony for a larger amount of time. 
While asleep, critters cannot move,
and if they are attacked, they will always lose.
Critters that choose to never eat will eventually die of starvation.

## Obstacles / Hazards
Some items in the world are hazards and should be avoided.
If a critter moves onto a Stone, for example, it is 'stunned' for a time.
While stunned, a critter cannot move 
and if they are attacked they will always lose.
Simple rule: don't walk into rocks.

## Scoring
The game keeps a score for each class (species) of critter, 
shown on the top of the screen. 
A species's score is based on how many animals of that class are alive, 
how much food they have eaten, and how many other animals they have killed.

# Compiling
Requires cmake, a ISO C++14 compatible compiler, and the ncurses library.
Currently Windows is not well supported.
It is possible to compile on Windows under cygwin,
a unix-like environment for windows.
You'll need to install ncurses development libraries for cygwin
and run the program within the cygwin bash shell.

Critters compiles using cmake on Mac OS, GNU/linux, and cygwin with:

    mkdir build
    cmake ..
    make

Feel free to substitute you own cmake Generator.
Typing `cmake -G` will show you a list of generators for your cmake.

## Reflection
When you are done, take a moment to 
[rate this lab](https://forms.gle/cVXAeqTup8By1pMC7).
