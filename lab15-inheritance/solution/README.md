# Class inheritance


## 1. Base and derived classes: 30 minutes *maximum*
### Part a.
Given the following classes:    
```cpp
  class Animal {
    public:
    virtual void make_noise() {}
    void eat() {}
    void sleep() {}
    void roam() {}
  };

  class Canine : public Animal {
    public:
    void roam() {}
    void eat() {}
  };


  class Wolf : public Canine {
    public:
    void make_noise() {}
    void eat() {}

  };
```

And given:    
```cpp
  void call (Animal& a) {
    a.make_noise();
    a.roam();
    a.eat();
    a.sleep();
  }

  int main () {
    Wolf w;
    call(w);
  }
```

Identify which of the versions of the methods called by `Wolf w` are invoked.

Only `make_noise` calls the Wolf version.

All the others call the Animal version.

Only `make_noise` is declared `virtual`,
so only `make_noise` can have it's animal behavior replaced with a Wolf version.

See the differences in the two programs 'animal shadow' an 'animal virtual'.

### Part b.
Given the following classes:

```
Musician
RockStar
MusicFan
BassPlayer
ConcertPianist
```

- Identify appropriate derived classes and base classes.

  There is no one correct answer here.
  There are many correct answers.
  The idea is to think about possible design choices,
  how those choices impact your design, and
  reasonable alternatives.

  Language ambiguities create problems for programmers.

  `BassPlayer` and `ConcertPianist` are both `Musician`s.
  All the classes on this list could inherit from `MusicFan`, 
  but you could argue a case against it.

  `BassPlayer` is ambiguous.
  There are different bass instruments used in different genres.

  A `ConcertPianist` is probably not `RockStar`.


- Draw an inheritance diagram that makes sense.  
  Not everything needs to be connected to something else.

  Don't over engineer this diagram.
  Simple ASCII art like:

  ```
   BassClass <|-- DerivedClass // inheritance
   Car  *-- Engine             // composition
  ```

  is sufficient.

One possible answer:

```
MusicFan <|-- Musician
         <|-- RockStar

Musician <|-- RockStar
         <|-- ConcertPianist
         <|-- BassPlayer
```

Another:

```
RockStar

MusicFan <|-- Musician <|-- ConcertPianist
                       <|-- BassPlayer
```


Another:

```
MusicFan            RockStar

Musician <|-- ConcertPianist
         <|-- BassPlayer
```


### Part c.
Given the following classes:

```
  Bathtub     Bathroom     Bubbles     Sink
```

- Identify appropriate derived classes and base classes.

There are no appropriate derived classes here.

None of these classes passes the *is-a* test for another.

- Draw an inheritance diagram that makes sense.  
  Not everything needs to be connected to something else.


Kind of a trick question.

There is no inheritance, but there is composition,
assuming you have a bathroom with a tub and a sink.
If our ASCII art uses '*--' for composition, then:

```
  Bathroom *-- Bathtub *--  Bubbles
  Bathroom *-- Sink    *-- Bubbles
```

is one possible design,
but this:

```
  Bathtub     Bathroom     Bubbles     Sink
```

is perfectly OK also,
since I asked specifically for *inheritance*.


## 2. Inheritance Declarations
Identify the relationships that make sense.

If a relationship doesn't make sense, explain why.

```cpp
struct Base : Derived       // no. Relationship is backwards.
  
struct Oven : Kitchen       // no. An Oven is not a Kitchen

struct Guitar : Instrument  // ok.

struct Person : Employee    // No.  Relationship is backwards.
  
  // Not all people are employees.

struct Ferrari : Engine     // No. Should use composition.

 // A Ferrari *has an* Engine

struct FriedEgg : Food      // ok, maybe, depends on application.


struct Beagle : Pet        // ok. Wild beagles are possible, but unlikely.

struct Porch : House       // No. 

 // A House *has a* Porch


struct Metal : Titanium    // No.  Relation is backwards.

 // Not all metal are titanium

struct GratefulDead : Band  // ok, I dated myself apparently.
```


## 3. Abstract classes: 30 minutes *maximum*
Given the following classes and a main method that uses them:

```cpp
  class Car {
    public:
    // insert A here
  };

  class RaceCar : public Car {
    public:
    // insert B here
  };

  class ElectricCar : public Car {
    public:
    bool accelerate(int change) const override {
      std::cout << "Shhhh...  " << change << std::endl;
      return true;
    }
  };

  int main () {
    vector<Car*> cars(3);
    cars[0] = new RaceCar();
    cars[1] = new ElectricCar();
    cars[2] = new Car();

    for (int x = 0; x < cars.size(); x++) {
      cars[x]->accelerate(x);
    }
    return 0;
  }
```

Examine each of the 4 pairs of code that follow and
describe what would happen when inserted at locations "A" and "B".
For **each pair**, answer **all** of the following:

- Which do not compile? 
- Which compile and produce the following output?

  ```
  Vroom! 0 
  Shhhh... 1 
  Change is: 2
  ```

- For those that compile,
  but do not produce the output above, explain why they do not.

### Pair #1:
**A:**  
```cpp
bool accelerate(int change) const {
  std::cout << "Change is: " << change << std::endl;
  return true;
}
```

**B:**  
```cpp
  bool accelerate(int change) const {
    std::cout << "Vroom!  " << change << std::endl;
    return false;
  }
```

Pair #1 does not compile.

problem:
- Car method is not marked virtual
- ElectricCar fails to compile

### Pair #2:
**A:**  
```cpp
virtual bool accelerate(int change) const {
  std::cout << "Change is: " << change << std::endl;
  return true;
}
```

**B:**  
```cpp
bool accelerate(int change) const {
  std::cout << "Vroom!  " << change << std::endl;
  return false;
}
```

Pair #2 compiles.

output is:  
```
Vroom!  0
Shhhh...  1
Change is: 2
```

### Pair #3:
**A:**  
```cpp
virtual bool accelerate(int change) const {
  std::cout << "Change is: " << change << std::endl;
  return true;
}
```

**B:**  
```cpp
bool accelerate(long change) const {
  std::cout << "Vroom!  " << change << std::endl;
  return false;
}
```

Pair #3 compiles.

output is:  
```
Change is:  0
Shhhh...  1
Change is: 2
```

The problem is that `RaceCar.accelerate` is not an override.

### Pair #4:
**A:**  
```cpp
virtual bool accelerate(int change) const {
  std::cout << "Change is: " << change << std::endl;
  return true;
}
```

**B:**  
```cpp
bool accelerate(long change) const override {
  std::cout << "Vroom!  " << change << std::endl;
  return false;
}
```

Pair #4 does not compile.

The override declaration on `RaceCar.accelerate`, 
which is not a valid override, generating a compile error.

## Turnitin
Check your progress by running `make test` or `ctest -V`.
This will attempt to run all tests.
Check partial progress by running the tests for a single step.
You can run tests for a single step with an IDE or ctest,
for example, `ctest -R step2`.

- Add your new and modified files: `git add . . . `
- Save your changes: `git commit . . . `
- Submit your work for grading: `git push`


