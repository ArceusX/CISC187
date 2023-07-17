# Extra credit project: Elevator Simulation
The goal of this project is to implement a simple elevator simulator
and measuring the performance of the elevator scheduler.


## Simulation requirements
Create a simplified elevator simulator with the following requirements:

- The number of elevators and floors in the building, 
  and a scheduler must be provided when the simulator is created
- The simulation should be able to handle up to 10 elevators 100 floors each
- When the system is first started, every elevator must be on the ground floor
- Each elevator travels at a constant velocity of 1 floor/sec and has its own
  independently timed drive system

The elevator scheduler should be implemented as a separate set of classes from the main
simulation.

Create a default scheduler that satisfies the specification outlined in the 
*Default Scheduler* section, below.

To reduce the scope of this assignment, you may assume that:

- Every elevator services every floor of the building (there are no express elevators)
- Floors are numbered `1 .. n` - there are no special floors
- Passengers are mostly ignored, we are measuring elevator travel

  - The sim keeps track of the number of passengers in a car, but
    assume passengers move instantly, have no mass, and
    an infinite number may fit in a car.
    
- Acceleration can be ignored
- The system runs forever

## Default Scheduler
Implement a scheduler that defines a 'home floor' for each elevator.
When the sim is started, each elevator moves to it's home floor.
When a request is made for an elevator,
the car that responds should be the one that will travel the least distance to (time) to
service the request and return to its home floor.

Assume, for this scheduler, that elevators in motion will attempt to 
service requests in a first-come, first-served manner, but
will pick up / drop off any passengers that happen to have a destination floor that is already on its journey.

For example, suppose:

- There are two elevators and 10 floors.
- A stationary elevator (elevator 1) on floor 5 has a home of floor 5
- A moving elevator (elevator 2) is on floor 3 delivering its final passenger to floor 2.
  This elevator has a home floor of 8.
- A new call request comes in, with an origin of floor 7, and a destination of floor 9.

If we assigned this new request to elevator 1,
it would take 8 seconds to service the request and return home. 

When assigned to elevator 1,
it would take 1 second for elevator 2 to drop off its existing passenger,
and 6 seconds to return to its home floor, for a total of 7 seconds.
Thus, the time for both elevators to reach their home floors would be 8 seconds, (the max of 8 seconds and 7 seconds).

If we assigned this new request to elevator 2, 
it would take 1 second for the elevator to drop off its existing passenger,
7 seconds to service the new call request, and 1 second to return to its home floor,
for a total of 9 seconds.
Meanwhile, elevator 1 would remain stationary at its home floor,
so it would take 0 seconds to get back to its home floor.
Thus, the time for both elevators to reach their home floors would be 9 seconds (the max of 0 and 9 seconds).

The scheduler should therefore decide to assign the call request to elevator 1,
because in 8 seconds, all elevators will be back to their home floors,
as opposed to 9 seconds if it is assigned to elevator 2.

## Input and output
The program must support the following command-line arguments:

```
  Usage: elevator [-h] -f <file name> [-c <file name>]
  Options:
    -h   Show this text and exit. Optional.

    -f   Required. File name containing elevator commands
    -c   Optional. File name containing scheduler configuration parameters
```

File format for the elevator commands file may be in any format
you choose, as long as all the required information is
stored and can be read when the program starts.

When the simulation finishes,
it should print a report showing the statics associated with each
command in the elevator simulation commands file:

- Which cab was set in motion by a command
- Travel time for each elevator after each command
- Time to return to home floor

Scheduler configuration commands are expected to vary depending on what scheduler is implemented.
For the default scheduler,
the config is simply the home floor for each elevator.
A scheduler is expected to provide a default configuration.

## Turn in checklist
All projects will be graded according to the project rubric in Canvas.

Before uploading your project,
make sure it meets all of the rubric criteria in order to get full credit.

1. Ensure all project requirements are met and all results are correct.
2. Source code contains no global variables.
   Globals created as side effects of using library functions are OK (getopt, etc.).
3. Ensure the intent behind every program element is "crystal clear".
   Add documentation where it makes sense to do so.
4. Ensure the top of each source file includes your name and student ID.
5. Your finished project must compile on buffy.

## Project Requirements
In order to receive full credit, your project must satisfy **all**
of the following requirements:

1. Process command line arguments as described in *Input and output*.

   Ensure all interactions with users are correct and
   perform all simulation functions.

2. Program implements the program described in the *Simulation requirements* section
3. No memory leaks when analyzed using valgrind on the mesa server.
4. Program functions should be small and each function should perform
   exactly one task.
5. Project rubric requirements for correctness, clarity, design,
   and coding are met or exceeded.


