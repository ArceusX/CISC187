// add includes required for std library facilities needed

#include "zoo.h"
#include "RoboDog.h"
#include <algorithm>

int main() {
	// declare a vector of raw pointers of Pet objectsf
	// using make_pets()

	auto pets = make_pets();

	// write a loop that plays with all the pets
	//
	// write a loop that plays with the RoboDog 5 more times
	// and then prints the charge remaining
	// - Do not make a new RoboDog.
	// - Use the RoboDog in pets

	play_with_pets(pets, 1);
	for (const auto& pet : pets) {
		if (dynamic_cast<const RoboDog*>(pet) != nullptr) {
			for (int i = 0; i < 5; i++) {
				pet->play();
			}
			RoboDog* r = dynamic_cast<RoboDog*>(pet);
			std::cout << *r;
			break;
		}
	}

  // cleanup pet vector memory
	for (const auto& pet : pets) {
		delete pet;
	}

  //
  // declare a vector of unique_ptr pointers of Animal objects
  // using make_animals()
  // give each animal a shot
	auto zoo = make_animals();
	treat_animals(zoo);
  return 0;
}



