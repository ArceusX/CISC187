
//
// Unit tests for some functions found in the game.cpp, turn.cpp, and 
// utility.cpp files.
//
// NOTE: Not all functions in these files could be tested. This is because 
// they either
//    - only display standard output
//    - required input data from the user
//
// NOTE: Some functions tested display output to the screen.
// 
// NOTE: The number of assertions made will likely change each time the code is
// run. This is because some tests make assertions for each element in a vector,
// and the size of that vector may be random.
//

#include <doctest.h>

#include "game.h"
#include "turn.h"
#include "utility.h"

#include <iostream>
#include <string>
#include <vector>

// ----------------------------------------------------------------------
// --------------------- Unit tests for game.cpp ------------------------

SCENARIO("Testing the generateGameBoard() function") {
   GIVEN("the number of piles and stones") {
      
      WHEN( "the number of piles is 1 and the number of stones are 2") {
         THEN("the function should return {2}") {
            REQUIRE( (generateGameBoard(1,2)).size() == 
                    (std::vector<int>{2}).size() );
            REQUIRE((generateGameBoard(1,2)).at(0) == 
                    (std::vector<int>{2}).at(0) );
         }
      }

      WHEN( "the number of piles are 2 and the number of stones are 1") {
         THEN("the function should return {1 1}") {
            REQUIRE( (generateGameBoard(2,1)).size() == 
                    (std::vector<int>{1,1}).size() );
            REQUIRE( (generateGameBoard(2,1)).at(0) == 
                    (std::vector<int>{1,1}).at(0) );
            REQUIRE( (generateGameBoard(2,1)).at(1) == 
                    (std::vector<int>{1,1}).at(1) );
         }
      }
      WHEN( "the number of piles are 3 and the number of stones are 5") {
         THEN("the function should return {5, 5, 5}") {
            REQUIRE( (generateGameBoard(3,5)).size() == 
                    (std::vector<int>{5, 5, 5}).size() );
            REQUIRE( (generateGameBoard(3,5)).at(0) == 
                    (std::vector<int>{5, 5, 5}).at(0) );
            REQUIRE( (generateGameBoard(3,5)).at(1) == 
                    (std::vector<int>{5, 5, 5}).at(1) );
            REQUIRE( (generateGameBoard(3,5)).at(2) == 
                    (std::vector<int>{5, 5, 5}).at(2) );
         }
      }
   
      WHEN( "the number of piles are 3 and the number of stones are 0") {
         std::vector<int> board = generateGameBoard(3,0);
         THEN("the number of piles should be 3") {
            REQUIRE(board.size() == 3);
         }
         THEN("the number of stones in each pile should be a random number between 1 and MAX_STONES"){
            for (const auto& stones : board)
               REQUIRE((stones > 0 && stones <= MAX_STONES) == true);
         }
      }
      WHEN("the number of piles are 0 and the number of stones are 3") {
         std::vector<int> board = generateGameBoard(0,3);
         THEN("the number of piles should be a random number between 1 and MAX_PILES") {
            REQUIRE((board.size()>0 && board.size() <= MAX_PILES) == true);
         }
         THEN("the number of stones in each pile should be 3"){
            for (const auto& stones : board)
               REQUIRE(stones == 3);
         }
      }
      WHEN("the number of piles are 0 and the number of stones are 0") {
         std::vector<int> board = generateGameBoard(0,0);
         THEN("the number of piles should be a random number between 1 and MAX_PILES") {
            REQUIRE((board.size()>0 && board.size() <= MAX_PILES) == true);
         }
         THEN("the number of stones in each pile should be a random number between 1 and MAX_STONES"){
            for (const auto& stones : board)
               REQUIRE((stones > 0 && stones <= MAX_STONES) == true);
         }
      }
   }
}

// ----------------------------------------------------------------------
// --------------------- Unit tests for turn.cpp ------------------------

SCENARIO( "Testing the swapPlayers() function") {
   GIVEN (" the names of two players as non-const string references") {
      WHEN( "they are 'name of playerA' and 'name of playerB'") {
         THEN ("the function should swap these names") {

            std::string playerA = "name of playerA";
            std::string playerB = "name of playerB";
            swapPlayers(playerA, playerB);

            REQUIRE(playerA == "name of playerB");
            REQUIRE(playerB == "name of playerA");
         }
      }
   }
}


SCENARIO( "Testing the calculateNimSum() function") {   
   GIVEN( "a vector of ints" ) {
      
      WHEN( "the vector is {2, 1, 12, 4}" ) {
         THEN(" the function should return 11 (the nim sum)") {
            REQUIRE(calculateNimSum({2, 1, 12, 4}) == 11);
         }
      }

      WHEN( "the vector is {1, 3, 3, 1}" ) {
         THEN(" the function should return 0 (the nim sum)") {
            REQUIRE(calculateNimSum({1, 3, 3, 1}) == 0);
         }
      }
   }
}


SCENARIO( "Testing the whichPile() function") {
   GIVEN( "a vector of ints" ) {
      
      WHEN( "the vector is {2, 1, 12, 4}" ) {
         THEN(" the function should return 3 (the only pile that can make the nim sum zero") {
            REQUIRE(whichPile({2, 1, 12, 4}) == 3);
         }
      }

      WHEN( "the vector is {1, 3, 3, 1}" ) {
         THEN("the function should return a random pile (the nim sum is zero") {
            int output = whichPile({1, 3, 3, 1});
            REQUIRE((output > 0 && output < 5) == true);
         }
      }

      WHEN( "the vector is {7, 6, 5, 4, 3}" ) {
         THEN(" the function should return 5 (removing from piles 1, 2, and 5 will make the nim sum zero, but my code is written to return the last one of these piles)") {
            REQUIRE(whichPile({7, 6, 5, 4, 3}) == 5);
         }
      }
   }
}


SCENARIO( "Testing the howManyStones() function") {  
   GIVEN( "a vector of ints)" ) {

      WHEN( "the vector is {2, 1, 12, 4}") {
         GIVEN("the pile to take from") {
            WHEN("the pile is 3") {
               THEN(" the function should return 5 (removing 5 stones from pile 3 will result in the num sum being zero)") {
                  REQUIRE(howManyStones({2, 1, 12, 4}, 3) == 5);
               }
            }
         }
      }      

      WHEN( "the vector is {1, 3, 3, 1}") {
         GIVEN("the pile to take from") {
            
            WHEN("the pile is 2") {
               THEN(" the function should return between 1 and 3 (because the nim sum is zero, the number returned should be a random number between 1 and the number of stones in pile 2)") {
                  int output = howManyStones({1, 3, 3, 1}, 2);  
                  REQUIRE((output > 0 && output < 4) == true);
               }
            }

            WHEN("the pile is 1") {
               THEN(" the function should return 1 (even though the nim sum is zero, there is one stone in pile 1)") {
                  REQUIRE(howManyStones({1, 3, 3, 1}, 1) == 1);
               }
            }
         }
      }

      WHEN( "the vector is {7, 6, 5, 4, 3}") {
         GIVEN("the pile to take from") {
            WHEN("the pile is 5") {
               THEN(" the function should return 3 (removing 3 stones from pile 5 will result in the num sum being zero)") {
                  REQUIRE(howManyStones({7, 6, 5, 4, 3}, 5) == 3);
               }
            }
         }
      }
   }
}



SCENARIO( "Testing the adjustGameBoard() function") {
   GIVEN( "a pointer to the game board (vector of ints)" ) {
      
      WHEN( "the vector it's pointing to is {1, 2, 3}" ) {
         std::vector<int> board = {1, 2, 3};
         GIVEN("the pile and number of stones to take from that pile") {     

            WHEN("the pile is 2 and the number of stones are 2") {
               THEN(" the function should return false because the game has not ended yet") {
                  REQUIRE(adjustGameBoard(2, 2, &board) == false);
               }
               THEN( "the vector should be {1, 3}" ) {
                  adjustGameBoard(2, 2, &board);
                  REQUIRE( board.size() == (std::vector<int>{1, 3}).size() );
                  REQUIRE( board.at(0) == (std::vector<int>{1, 3}).at(0) );
                  REQUIRE( board.at(1) == (std::vector<int>{1, 3}).at(1) );
               }
            }

            WHEN("the pile is 3 and the number of stones are 1") {
               THEN(" the function should return false because the game has not ended yet") {
                  REQUIRE(adjustGameBoard(3, 1, &board) == false);
               }
               THEN( "the vector should be {1, 2, 2}" ) {
                  adjustGameBoard(3, 1, &board);
                  REQUIRE( board.size() == (std::vector<int>{1, 2, 2}).size() );
                  REQUIRE( board.at(0) == (std::vector<int>{1, 2, 2}).at(0) );
                  REQUIRE( board.at(1) == (std::vector<int>{1, 2, 2}).at(1) );
                  REQUIRE( board.at(2) == (std::vector<int>{1, 2, 2}).at(2) );
               }
            }
         }
      }

      WHEN( "the vector it's pointing to is {4}") {
         std::vector<int> board = {4};
         GIVEN("the pile and number of stones to take from that pile") {
            WHEN("the pile is 1 and the number of stones are 4") {
               THEN(" the function should return true because the game has ended") {
                  REQUIRE(adjustGameBoard(1, 4, &board) == true);
               }
            }
         }   
      }
   }
}

// ----------------------------------------------------------------------
// --------------------- Unit tests for utility.cpp ---------------------

SCENARIO("Testing the stringToInt() function") {
   
   GIVEN( "the address to an integer") {
      int a;
      WHEN ("the address is '&a'") {
         GIVEN("a string") {
            
            WHEN ("the string is '23'") {
               THEN( "the function should return true") {
                  REQUIRE(stringToInt("23", &a, "") == true);
               }
               THEN(" the value at 'a' should be 23") {
                  REQUIRE(a == 23);
               }
            }
            WHEN ("the string is '23f'") {
               THEN ("the function should return false") {
                  REQUIRE(stringToInt("23f", &a, "") == false);
               }
            }
            WHEN ("the string is '2.4'") {
               THEN ("the function should return false") {
                  REQUIRE(stringToInt("2.4", &a, "") == false);
               }
            }
            WHEN ("the string is 'f23'") {
               THEN ("the function should return false") {
                  REQUIRE(stringToInt("f23", &a, "") == false);
               }
            }
         }
      }
   }
}  
               


SCENARIO("Testing the checkIntRange() function") {
   GIVEN("the maximum integer") {

      WHEN("the maximum integer is 12") {
         GIVEN("an integer") {
            WHEN("the integer is 0") {
               THEN ("the function should return false") {
                  REQUIRE(checkIntRange(0,12) == false);
               }
            }
            WHEN("the integer is 1") {
               THEN ("the function should return true") {
                  REQUIRE(checkIntRange(1,12) == true);
               }
             }
            WHEN("the integer is 12") {
               THEN ("the function should return true") {
                  REQUIRE(checkIntRange(12,12) == true);
               }
            }
            WHEN("the integer is 13") {
               THEN ("the function should return false") {
                  REQUIRE(checkIntRange(13,12) == false);
               }
            }
         }
      }

      WHEN("the maximum integer is 1") {
         GIVEN("an integer") {
            WHEN("the integer is 0") {
               THEN("the function should return false") {
                  REQUIRE(checkIntRange(0,1) == false);
                }
            }
            WHEN("the integer is 1") {
               THEN("the function should return true") {
                  REQUIRE(checkIntRange(1,1) == true);
                }
            }
            WHEN("the integer is 2") {
               THEN("the function should return false") {
                  REQUIRE(checkIntRange(2,1) == false);
               }
            }
         }
      }
   }
}

