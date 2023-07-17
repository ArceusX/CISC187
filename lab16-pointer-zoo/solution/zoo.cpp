#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

#include "Animal.h"
#include "Cat.h"
#include "Dog.h"
#include "Fish.h"
#include "Owl.h"
#include "Wolf.h"
#include "Pet.h"
#include "RoboDog.h"

#include "zoo.h"

using std::vector;
using std::unique_ptr;

vector<Pet*> make_pets() 
{
  vector<Pet*> pets {
    new Cat, new Dog, new Fish, new RoboDog
  };
  return pets;
}

void play_with_pets(const vector<Pet*>& pets, int16_t n)
{
  auto tmp = n;
  while (tmp != 0) {
    for (const auto& p: pets) {
      p->play();
    }
    --tmp;
  }
}

vector<unique_ptr<Animal>> make_animals() 
{
  vector<unique_ptr<Animal>> zoo;
  zoo.push_back(unique_ptr<Animal>{new Cat});
  zoo.push_back(unique_ptr<Animal>{new Dog});
  zoo.push_back(unique_ptr<Animal>{new Owl});
  zoo.push_back(unique_ptr<Animal>{new Wolf});
  return zoo;
}

void treat_animals(const vector<unique_ptr<Animal>>& zoo) {
  for (const auto& a: zoo) {
    std::cout << a->make_sound() << '\n';
  }
}
