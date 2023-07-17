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

Animal's roam, eat, sleep methods will be invoked because a is treated as 
an Animal reference. Wolf's make_noise will be invoked because make_noise
is virtual in the super-class and not defined until in the subclass Wolf.

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

- Draw a class diagram that makes sense. 
  Consider the use of inheritance, composition, and dependency relations.

  Don't over engineer this diagram.
  Simple ASCII art like:

  ```
   BassClass <|-- DerivedClass // inheritance
   Car  *-- Engine             // composition
   Car  --  Driver             // dependency
  ```

  is sufficient.
  
-  Explain why you chose the relationships you did.

// Inheritance because a RockStar is a specialization of a Musician  
//Musician <|-- RockStar  

//Dependency because a Musician requires a MusicFan  
//Musician --  MusicFan  

// Inheritance because a BassPlayer is a specialization of a Musician  
//Musician <|-- BassPlayer  

// Inheritance because a ConcertPianist is a specialization of a Musician  
//Musician <|-- BassPlayer  

### Part c.
Given the following classes:

```
  Bathtub     Bathroom     Bubbles     Sink
```

- Draw a class diagram that makes sense. 
  Consider the use of inheritance, composition, and dependency relations.
  
- Explain why you chose the relationships you did.

// Composition because Bathtub can only have relevance within a Bathroom  
//Bathroom *-- Bathtub  

// Aggregation (variant of Composition) because Bubbles has relevance within a Bathtub, but can also exist outside it  
//Bathroom ^-- Bathtub  

// Aggregation (variant of Composition) because Sink has relevance within a Bathroom, but can also exist outside it  
//Bathroom ^-- Bathtub  

## 2. Inheritance Declarations
Identify the relationships that make sense.

If a relationship doesn't make sense, explain why.
For example:
```cpp
struct base : derived       // no. Relationship is backwards.
```

Complete the following:

```cpp
struct oven : kitchen       //No. Oven shouldn't inherit from kitchen.  

struct guitar : instrument  //Yes. Guitar inherits from instrument.  

struct person : employee    //No. Rather, employee should inherit from person.  
  
struct ferrari : engine     //No. Engine shouldn't inherit from Ferrari.  

struct fried_egg : food     //Yes. FriedEgg inherits from Food.  

struct beagle : pet        //Yes. Beagles inherits from Pet.  

struct porch : house       //No. Porch shouldn't inherit from House.  

struct metal : titanium    //No. Rather Titanium should inherit from Metal.  

struct grateful_dead : band  //Yes. GratefulDead inherits from Band.  
```


## 3. Abstract classes: 30 minutes *maximum*
Given the following classes and a main method that uses them:

```cpp
  class car {
    public:
    // insert A here
  };

  class race_car : public car {
    public:
    // insert B here
  };

  class electric_car : public car {
    public:
    bool accelerate(int change) const override {
      std::cout << "Shhhh...  " << change << std::endl;
      return true;
    }
  };

  int main () {
    vector<car*> cars(3);
    cars[0] = new race_car();
    cars[1] = new electric_car();
    cars[2] = new car();

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
  but do not produce the output above, **explain** why they do not.

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
Does not compile. Subclass electric_car's accelerate overrides, so superclass  
car's accelerate should be virtual to accomodate.  

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

Compiles, matches intended. superclass car's accelerate is declared virtual.  

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

Compiles, doesn't match intended. Subclass race_car's accelerate's signature  
does not match the signature of the superclass method, so does not override  
and subclass function is unrelated.  

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

Doesn't compile. Signatures of accelerate of superclass and subclass don't match,  
so one isn't perceived to be intended to override the other. Gives "not overriding" error.  

## Turnitin
- Add your new and modified files: `git add . . . `
- Save your changes: `git commit . . . `
- Submit your work for grading: `git push`

## Reflection
When you are done, take a moment to 
[rate this lab](https://forms.gle/BWyXbCPt3dwwpVom6).
