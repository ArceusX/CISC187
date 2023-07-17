#include <algorithm>
#include <iostream>
#include <memory>
#include <random>
#include <vector>

#include "RoboDog.h"
#include "Robot.h"

#include "zoo.h"

using std::vector;
using std::unique_ptr;

int main () 
{
  std::cout << "declare a vector of raw pointers of Pet objects\n";
  auto pets = make_pets();
  for (auto* const p: pets) {
    std::cout << p->name() << ' ';
    p->play();
  }
  std::cout << std::endl;

  // write a loop that plays with a RoboDog 5 more times
  // and then prints the charge remaining
  std::cout << "play with RoboDog 5 more times\n";
  //
  // Do not make a new RoboDog.
  // Use the RoboDog in pets
  auto* robie = pets.back();
  for (int i = 0; i < 5; ++i) {
    robie->play();
  }
  
  std::cout << robie->name() << " charge remaining: "
            << dynamic_cast<Robot*>(robie)->charge_remaining() << '\n';

  // lots of people want to find robie, so here you go . . . 
  std::cout << "find robie in shuffled vector\n";
  std::random_device device;
  std::mt19937 gen(device());

  std::shuffle(pets.begin(), pets.end(), gen);
  for (auto* const p: pets) {
    std::cout << p->name() << ' ';
  }
  std::cout << '\n';
  auto it = std::find_if(pets.begin(), pets.end(), 
            [](const Pet* const p) 
              { 
                return p->name() == "RoboDog";
              });

  // since we took the time to find robie . . .
  if (it != pets.end()) {
    std::cout << "play more w/ robie\n";
    for (int i = 0; i < 5; ++i) {
      (*it)->play();
    }
    std::cout << dynamic_cast<RoboDog&>(*(*it)) << '\n';
  }

  // cleanup pets memory
  for (auto* const p: pets) {
    delete p;
  }

  std::cout << "declare a vector of unique_ptr pointers of Animal objects\n";
  auto zoo = make_animals();
  std::cout << "give each animal a shot\n";
  treat_animals(zoo);

  return 0;
}



