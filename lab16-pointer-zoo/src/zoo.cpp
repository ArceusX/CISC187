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

std::vector<Pet*> make_pets() {
	std::vector<Pet*> pets;
	Pet* cat = new Cat();
	pets.push_back(cat);

	Pet* dog = new Dog();
	pets.push_back(dog);

	Pet* fish = new Fish();
	pets.push_back(fish);

	Pet* roboDog = new RoboDog();
	pets.push_back(roboDog);

	return pets;
}

void play_with_pets(const std::vector<Pet*>& pets, const int16_t n) {
	for (int i = 0; i < n; i++) {
		for (const auto& pet : pets) {
			pet->play();
		}
	}
}

std::vector<std::unique_ptr<Animal>> make_animals() {
	std::vector<std::unique_ptr<Animal>> animals;

	std::unique_ptr<Animal> cat = std::make_unique<Cat>();
	animals.push_back(std::move(cat));

	std::unique_ptr<Animal> dog = std::make_unique<Dog>();
	animals.push_back(std::move(dog));

	std::unique_ptr<Animal> owl = std::make_unique<Owl>();
	animals.push_back(std::move(owl));

	std::unique_ptr<Animal> wolf = std::make_unique<Wolf>();
	animals.push_back(std::move(wolf));

	return animals;
}

void treat_animals(const std::vector<std::unique_ptr<Animal>>& animals) {
	for (const auto& animal : animals) {
		std::cout << animal->make_sound();
	}
}