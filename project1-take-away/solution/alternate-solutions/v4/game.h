#pragma once

//
// Functions that assist in starting and ending games.
//

#include <string>
#include <vector>

using std::string;
using std::vector;

// ------------------------- Constants --------------------------
const int MAX_PILES = 5; //MUST BE AT LEAST 1
const int MAX_STONES = 15; //MUST BE AT LEAST 1
const string COMPUTER_NAME = "HALL 2000";

// ------------------------ Functions  --------------------------

// Function that controls the entire execution of the program.
//
// It will create a game board and prompt the user for player name(s). 
//
// It then calls one of the overloaded functions to play a single game.
//
// It continues until the user opts out from playing again and the program
// ends.
void playTakeAway(bool defaultGame, int piles, int stones);

// Play a game against the computer.
//
// Return true if user wishes to play another game. Otherwise, return false.
bool playOneGame(const string& humanName, vector<int> gameBoard); 

// Play a multiplayer game.
//
// Return true if user wishes to play another game. Otherwise, return false.
bool playOneGame(const string& player1, const string& player2,
                       vector<int> gameBoard);

// Return a vector that represents the game board.
vector<int> generateGameBoard(int piles, int stones);

// Return true if the user wishes to play another game.
bool playAgain();


