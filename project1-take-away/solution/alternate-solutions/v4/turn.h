#pragma once

// 
// Functions that assist in completing a turn of a take-away game.
// 
// Note: Functions that expect addresses to be passed in as argument are        
// LIKELY TO MODIFY the values found at these addresses.

#include <string>
#include <vector>

using std::string;
using std::vector;

// ------------------------- Player Turn Moves -----------------------
// Play a turn for the given player. Return true if the player has won.
bool playerTurn(const string& playerName, vector<int>* ptr_board);

// Swap names of players.
void swapPlayers(string& playerA, string& playerB);

// Display the player names to the user.
void displayPlayers(const string& player1, const string& player2);

// ----------------------- Computer Turn Moves -----------------------
// Play a turn for the computer. Return true if computer has won.
bool computerTurn(vector<int>* ptr_board);

// Calculate and return the nim sum of the board.
int calculateNimSum(const vector<int>& board);

// Return which pile the computer will draw stones from. 
int whichPile(const vector<int>& board);

// Return how many stones the computer will draw from the given pile.
int howManyStones(const vector<int>& board, const int& pile);

// ------------------------- Moves done each turn --------------------
// Display the board game to the user.
void displayGameBoard(const vector<int>& board);

// Remove the given number of stones from the given pile on the game board. 
//
// If the game has ended, return true. Otherwise, return false.
bool adjustGameBoard(const int& pile, const int& stones,
                     vector<int>* ptr_board);



